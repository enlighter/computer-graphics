/*
 * get-triangle.cpp
 *
 *  Created on: 29-Jan-2016
 *      Author: enlighter
 */


#include <iostream>
#include <string>
#include <regex>

#include "Polygon2d.cpp"

#define COORDINATE_SYSTEM	3 //3d coordinate system used here
#define POLYGON_SIZE	3
#define FORMAT_ERROR "Please maintain proper format!"

using namespace std;

int process_coordinates(string input, int point[])
{
	std::string::iterator itf = input.begin();
	//int point[3];
	//int flag=2;

	/* check that the string is not empty
		and it starts with a '(' and ends with a ')'*/
	if (input.empty())
		throw "No value given";
	else if (*itf != '(')
		throw FORMAT_ERROR;

	itf = input.end();
	itf--;
	if (*itf != ')')
		throw FORMAT_ERROR;
	/*---------------------------------------*/

	input = input.substr(1, input.length()-2);
	//DEBUG
	//cout<<input<<endl;

	try
	{
		if (regex_match (input, regex("[[:digit:]]+\\,[[:digit:]]+\\,[[:digit:]]+") ))
			// regex comparison expression using ECMAScript syntax
		{
			cout<<"regex match!";//<<endl;

			//Split the regex complaint string along ',' character
			stringstream temp(input);
			string segment;
			vector<string> seglist;
			while(getline(temp, segment, ','))
			{
   				seglist.push_back(segment);
			}
			int j=0;
			for (vector<string>::const_iterator i = seglist.begin(); i != seglist.end(); ++i, j++)
			{
				//DEBUG
    			//cout << *i << ' ';
    			point[j] = std::stoi(*i, NULL, 10); //convert to integer value
			}
    		cout<<endl;

    		//DEBUG
    		/*for(j=0; j<COORDINATE_SYSTEM; j++)
    			cout<<point[j]<<" ";
			*/
			
    		return 1;
		}
		else
			throw FORMAT_ERROR;
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

	return 0;
}

int process_triangle_orientation( int **vertexTrio )
{
	int A=0, B=0, C=0; //for the plane of the triangle of the form Ax+By+Cz+D=0

	//A = (y2-y1)(z3-z1) - (y3-y1)(z2-z1)
	A = ((vertexTrio[1][1] - vertexTrio[0][1])*(vertexTrio[2][2] - vertexTrio[0][2])) - ((vertexTrio[3][1] - vertexTrio[0][1])*(vertexTrio[1][2] - vertexTrio[0][2]));

	//B = (z2-z1)(x3-x1) - (z3-z1)(x2-x1)

	//C = (x2-x1)(y3-y1) - (x3-x1)(y2-y1)
}

int main()
{
	string points[POLYGON_SIZE];
	int vertices[POLYGON_SIZE][COORDINATE_SYSTEM];
	int i=0, j=0;

	try
	{
		cout<<"Enter the coordinates for the 3 vertices of the 3D triangle:"<<endl;

		for(i=0; i<POLYGON_SIZE; i++)
		{
			cout<<"Enter vertex no. "<<i+1<<" coordinates in the format (x,y,z): ";
			getline(cin, points[i]);
		}
		
		for(i=0; i<POLYGON_SIZE; i++)
		{
			//cout<<points[i]<<endl;
			process_coordinates(points[i], vertices[i]);
			cout<<"Received point : ";
			for(j=0; j<COORDINATE_SYSTEM; j++)
			{
				cout<<vertices[i][j];
				if(j<COORDINATE_SYSTEM-1)
					cout<<",";
			}
			cout<<endl;
		}
		
		//process_triangle_orientation(vertices);
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}

	return 1;
}

