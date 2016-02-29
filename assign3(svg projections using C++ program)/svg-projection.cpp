/*
 * svg-projection.cpp
 *
 *  Created on: 27-Feb-2016
 *      Author: enlighter
 */

#include <iostream>
#include <string>
#include <regex>
#include <fstream> //file handling
#include <sstream> //for reading things word by word
#include <vector>

#include "Polygon3d.cpp"
#include "Viewport.cpp"
#include "Transformation.cpp"

#define DIMENSIONS 3

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
	enl::Polygon3d object;
	enl::Polygon3d::vertex v;
	enl::Polygon3d::face f;
	int viewport_width=0, viewport_length=0;
	enl::Viewport vwp;
	int rotation=0;
	short rotation_choice=0, rotation_count=0;
	char proceed;
	enl::Transformation transform;
	//char c;

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
						//cout<<"vertex\n";

						for(auto i=1; i<=DIMENSIONS; i++)
						{
							v.h_coord[i-1] = stoi(line_stubs[i]);
						}

						//DEBUG
						cout<<v.h_coord[0]<<","<<v.h_coord[1]<<","<<v.h_coord[2]<<","<<v.h_coord[3]<<endl;

						object.vertices.push_back(v);
					}
					else if(line_stubs[0].compare("f") == 0)
					//this line in obj file corresponds to a vertex
					{
						//DEBUG
						cout<<"face\n";

						for(auto it = line_stubs.begin()+1; it != line_stubs.end(); ++it)
						//line_stubs.begin() here points to 'f', so we start reading from the next ones
						{
							f.vertex_order.push_back( stoi(*it) );
						}

						object.faces.push_back(f);
					}

					f.vertex_order.clear();
					line_stubs.clear(); //empty the line_stubs for next iteration
				}

				//DEBUG
				object.print_vertices();
				object.print_faces();
			}
			else
			{
				cout<<"Couldn't open the file.\n";
				return 0;
			}

			while( viewport_length<300 || viewport_length>1000 || viewport_width<300 || viewport_width>1000)
			{
				cout<<"Enter the width of the viewport (range 300 to 1000) :";
				cin >> viewport_width;
				cout<<"Enter the length of the viewport (range 300 to 1000) :";
				cin >> viewport_length;
				cout<<"So you want a viewport of "<<viewport_width<<"X"<<viewport_length<<endl;
			}

			vwp.set_viewport(viewport_width, viewport_length);

			//ask for rotations
			while(true)
			{
				cout<<"Current rotation count : "<<rotation_count<<". Do you want to set another rotation (y/n) : ";
				cin >> proceed;

				if(proceed == 'y')
				{
					cout<<"Along which axis do you want to rotate the object?\n";
					cout<<"Press '1' for X-axis\nPress '2' for X-axis\nPress '3' for X-axis\n:";
					cin >> rotation_choice;
					cout<<"Enter how much do you want to rotate the object? :";
					cin >> rotation;

					//DEBUG
					cout<<"rotation of "<<rotation<<" degrees about "<<rotation_choice<<" axis.\n";

					switch(rotation_choice)
					{
					case 1:
					{
						transform.set_x_rotation(rotation);
						rotation_count++;
						break;
					}
					case 2:
					{
						transform.set_y_rotation(rotation);
						rotation_count++;
						break;
					}
					case 3:
					{
						transform.set_z_rotation(rotation);
						rotation_count++;
						break;
					}
					default:
						cout<<"That's not a valid choice.\n";
					}
				}
				else
				{
					break;
				}
			}

			cout<<"end.\n";

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
