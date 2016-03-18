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
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Object3D.cpp"

using namespace std;

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
					if(line_stubs.size() != 4)
					{
						//this vertex is not 3 Dimensional
						throw "Vertex encountered that is not 3 Dimensional.\nThis program only works on 3 Dimensional Objects!";
					}

					//vertex is 3 Dimensional
					for(auto i=0; i<=2; i++)
					{
						vertex.coord[i] = stof( line_stubs[i+1] );
					}

					//DEBUG
					cout<<"Inserted vertex : ";
					for(auto i=0; i<=2; i++)
					{
						cout<<vertex.coord[i]<<" ,";
					}
					cout<<endl;
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
					if(line_stubs.size() != 4)
					{
						//this face is not triangular
						throw "Non triangular face encountered.\nThis program only works on triangulated objects!";
					}
				}

				line_stubs.clear(); //empty the line_stubs for next iteration
			}
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
