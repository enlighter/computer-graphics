/*
 * run.cpp
 *
 *  Created on: 11-Mar-2016
 *      Author: enlighter
 */

#include <iostream>
#include <string>
#include <regex>
#include <fstream> //file handling
#include <sstream> //for reading things word by word
#include <vector>
/* inlude the headers for OpenGL development */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Object3D.cpp"
#include "utils.c"

using namespace std;

/* OPenGl based func defs
 *
 */

static struct {
    /* ... fields for buffer and texture objects */
    GLuint vertex_shader, program, fragment_shader;

    GLuint vertex_buffer, element_buffer;
    GLuint textures[2];

    /* fields for shader objects ... */
    struct {
        GLint fade_factor;
        GLint textures[2];
    } uniforms;

    struct {
        GLint position;
    } attributes;

    GLfloat fade_factor;
} g_resources;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
};
static const GLushort g_element_buffer_data[] = { 0, 1, 2, 3 };

static GLuint make_buffer(
    GLenum target,
    const void *buffer_data,
    GLsizei buffer_size
) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    return buffer;
}

static GLuint make_texture(const char *filename)
{
    GLuint texture;
    int width, height;
    void *pixels = NULL; //read_tga(filename, &width, &height);

    if (!pixels)
        return 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0,           /* target, level of detail */
        GL_RGB8,                    /* internal format */
        width, height, 0,           /* width, height, border */
        GL_BGR, GL_UNSIGNED_BYTE,   /* external format, type */
        pixels                      /* pixels */
    );
    free(pixels);
    return texture;
}

static void show_info_log(
    GLuint object,
    PFNGLGETSHADERIVPROC glGet__iv,
    PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
)
{
    GLint log_length;
    char *log;

    glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
    log = (char *)malloc(log_length);
    glGet__InfoLog(object, log_length, NULL, log);
    cerr<<log;
    free(log);
}

static GLuint make_shader(GLenum type, const char *filename)
{
    GLint length;
    GLchar *source = (GLchar *)file_contents(filename, &length);
    GLuint shader;
    GLint shader_ok;

    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    free(source);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        cerr<<"Failed to compile "<<filename<<":";
        show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
{

    GLint program_ok;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        cerr<<"Failed to link shader program:";
        show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

static int make_resources()
{
	/* make buffers */
    g_resources.vertex_buffer = make_buffer(
        GL_ARRAY_BUFFER,
        g_vertex_buffer_data,
        sizeof(g_vertex_buffer_data)
    );
    g_resources.element_buffer = make_buffer(
        GL_ELEMENT_ARRAY_BUFFER,
        g_element_buffer_data,
        sizeof(g_element_buffer_data)
    );
    /* don't make textures */
    /* make shaders ... */

    g_resources.vertex_shader = make_shader(
        GL_VERTEX_SHADER,
        "vertex-shader.glsl"
    );
    if (g_resources.vertex_shader == 0)
        return 0;

    g_resources.fragment_shader = make_shader(
        GL_FRAGMENT_SHADER,
        "fragment-shader.glsl"
    );
    if (g_resources.fragment_shader == 0)
        return 0;

    g_resources.program = make_program(
        g_resources.vertex_shader,
        g_resources.fragment_shader
    );
    if (g_resources.program == 0)
        return 0;

    g_resources.uniforms.fade_factor
        = glGetUniformLocation(g_resources.program, "fade_factor");
    g_resources.uniforms.textures[0]
        = glGetUniformLocation(g_resources.program, "textures[0]");
    g_resources.uniforms.textures[1]
        = glGetUniformLocation(g_resources.program, "textures[1]");

    g_resources.attributes.position
        = glGetAttribLocation(g_resources.program, "position");

    return 1;
}

static void render(void)
{
    glUseProgram(g_resources.program);
    glUniform1f(g_resources.uniforms.fade_factor, g_resources.fade_factor);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_resources.textures[0]);
    glUniform1i(g_resources.uniforms.textures[0], 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, g_resources.textures[1]);
    glUniform1i(g_resources.uniforms.textures[1], 1);

    glBindBuffer(GL_ARRAY_BUFFER, g_resources.vertex_buffer);
    glVertexAttribPointer(
        g_resources.attributes.position,  /* attribute */
        2,                                /* size */
        GL_FLOAT,                         /* type */
        GL_FALSE,                         /* normalized? */
        sizeof(GLfloat)*2,                /* stride */
        (void*)0                          /* array buffer offset */
    );
    glEnableVertexAttribArray(g_resources.attributes.position);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_resources.element_buffer);
    glDrawElements(
        GL_TRIANGLE_STRIP,  /* mode */
        4,                  /* count */
        GL_UNSIGNED_SHORT,  /* type */
        (void*)0            /* element array buffer offset */
    );

    glDisableVertexAttribArray(g_resources.attributes.position);

    glutSwapBuffers();
}

static void update_fade_factor(void)
{
    int milliseconds = glutGet(GLUT_ELAPSED_TIME);
    g_resources.fade_factor = sinf((float)milliseconds * 0.001f) * 0.5f + 0.5f;
    glutPostRedisplay();
}

/*--------------------------OPENGL--------------------------*/

void process_filename(string name, ifstream *data)
{
	try
	{
		if(regex_match (name, regex("(\\w+\\.*)*\\w+") ))
		{
			//data->exceptions(ifstream::failbit | ifstream::badbit | ifstream::eofbit);
			data->open(name);
		}
		else
		{
			throw "Invalid pattern encountered for filename.";
		}
	}
	catch(regex_error& e)
	{
		//extensive regex_error handling
		if (e.code() == regex_constants::error_collate)
			throw "The expression contained an invalid collating element name.";
		//else if (e.code() == regex_constants::codeerror_ctype)
		//throw "The expression contained an invalid character class name.";
		else if (e.code() == regex_constants::error_escape)
			throw "The expression contained an invalid escaped character, or a trailing escape.";
		else if (e.code() == regex_constants::error_backref)
			throw "The expression contained an invalid back reference.";
		else if (e.code() == regex_constants::error_brack)
			throw "The expression contained mismatched brackets ([ and ]).";
		else if (e.code() == regex_constants::error_paren)
			throw "The expression contained mismatched parentheses (( and )).";
		else if (e.code() == regex_constants::error_brace)
			throw "The expression contained mismatched braces ({ and }).";
		else if (e.code() == regex_constants::error_badbrace)
			throw "The expression contained an invalid range between braces ({ and }).";
		else if (e.code() == regex_constants::error_range)
			throw "The expression contained an invalid character range.";
		else if (e.code() == regex_constants::error_space)
			throw "There was insufficient memory to convert the expression into a finite state machine.";
		else if (e.code() == regex_constants::error_badrepeat)
			throw "The expression contained a repeat specifier (one of *?+{) that was not preceded by a valid regular expression.";
		else if (e.code() == regex_constants::error_complexity)
			throw "The complexity of an attempted match against a regular expression exceeded a pre-set level.";
		else if (e.code() == regex_constants::error_stack)
			throw "There was insufficient memory to determine whether the regular expression could match the specified character sequence.";
		}
		/*catch(ifstream::failure &e)
		{
			throw ("Error encountered opening/reading file" + string(e.what())).c_str();
		}*/
		catch (const char* msg)
		{
			throw msg;
		}
		catch(exception &e)
		{
			throw e.what();
		}
}

int main()
{
	string filename, line, word;
	vector<string> line_stubs;
	ifstream obj_file;
	enl::Object3D object;
	enl::Object3D::vertex vertex;
	enl::Object3D::face face;
	int argc = 1;
	char *argv[1] = {(char*)"Something"};

	try
	{
		cout<<"Enter the filename {<name>.obj} for input obj file: ";
		getline(cin, filename);

		process_filename(filename, &obj_file);

		if(obj_file.is_open())
		{
			while( getline(obj_file,line) )//!obj_file.eof())
			{
				//DEBUG
				cout<<line<<endl;

				//process the line
				istringstream iss(line);
				while( iss >> word)
				{
					//DEBUG
					//cout<<word;

					line_stubs.push_back(word);
				}

				if(line_stubs[0].compare("v") == 0)
				//this line in obj file corresponds to a vertex
				{
					//DEBUG
					cout<<"vertex\n";

					//check that the vertex is 3 Dimensional
					if(line_stubs.size() != DIMENSIONS + 1)
					{
						//this vertex is not 3 Dimensional
						throw "Vertex encountered that is not 3 Dimensional.\nThis program only works on 3 Dimensional Objects!";
					}

					//vertex is 3 Dimensional
					for(auto i=0; i<DIMENSIONS; i++)
					{
						vertex.coord[i] = stof( line_stubs[i+1] );
					}

					//DEBUG
					/*cout<<"Inserted vertex : ";
					for(auto i=0; i<=2; i++)
					{
						cout<<vertex.coord[i]<<" ,";
					}
					cout<<endl;
					*/

					object.vertices.push_back(vertex);
				}
				else if(line_stubs[0].compare("f") == 0)
				//this line in obj file corresponds to a vertex
				{
					//DEBUG
					cout<<"face\n";

					/*  check that the face is a triangular object
						as this code assumes that 3D objects to
						process are triangulated
					*/
					if(line_stubs.size() != DIMENSIONS + 1)
					{
						//this face is not triangular
						throw "Non triangular face encountered.\nThis program only works on triangulated objects!";
					}

					//face is a triangular object
					for(auto i=0; i<DIMENSIONS; i++)
					{
						face.vertex_order[i] = stoi( line_stubs[i+1] );
					}

					//DEBUG
					/*cout<<"Inserted vertex : ";
					for(auto i=0; i<=2; i++)
					{
						cout<<vertex.coord[i]<<" ,";
					}
					cout<<endl;
					*/

					object.faces.push_back(face);
				}

				line_stubs.clear(); //empty the line_stubs for next iteration
			}

			object.sort_within_faces();

			//DEBUG
			cout<<"Stored vertices : \n";
			object.print_vertices();
			cout<<"Stored faces : \n";
			object.print_faces();

			/* opengl render
			 *
			 */
			glutInit(&argc, argv);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutInitWindowSize(400, 300);
			glutCreateWindow("Hello World");
			glutDisplayFunc(&render);
			glutIdleFunc(&update_fade_factor);
		    glewInit();
		    if (!GLEW_VERSION_2_0) {
		        cerr<<"OpenGL 2.0 not available\n";
		        return 1;
		    }
		    if (!make_resources()) {
		        cerr<<"Failed to load resources\n";
		        return 1;
		    }

		    glutMainLoop();

		    /*-----------------OpenGl------------------*/
		}
		else
		{
			cout<<"Couldn't open the file.\n";
			return 0;
		}
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}
	catch(exception &e)
	{
		cerr<<e.what()<<endl;
	}

	return 1;
}
