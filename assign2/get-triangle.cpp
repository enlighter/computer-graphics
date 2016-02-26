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
#include "Polygon3d.cpp"

#define COORDINATE_SYSTEM	3 //3d coordinate system used here
#define POLYGON_SIZE	3
#define FORMAT_ERROR "Please maintain proper format!"
//#define X 0
//#define Y 1
//#define Z 2

using namespace std;

enl::Polygon3d::vertex process_coordinates(string input)
{
	enl::Polygon3d::vertex point;
	std::string::iterator itf = input.begin();

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

			vector<string>::const_iterator i = seglist.begin();
			//DEBUG
			//cout << *i << ' ';
			point.x = stoi(*i, NULL, 10);
			++i;
			//DEBUG
			//cout << *i << ' ';
			point.y = stoi(*i, NULL, 10);
			++i;
			//DEBUG
			//cout << *i << ' ';
			point.z = stoi(*i, NULL, 10);

    		cout<<endl;

    		//DEBUG
    		/*for(j=0; j<COORDINATE_SYSTEM; j++)
    			cout<<point[j]<<" ";
			*/
			
    		return point;
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

	return enl::Polygon3d::vertex{};
}

int main()
{
	string points[POLYGON_SIZE];
	enl::Polygon3d polfig;
	enl::Polygon3d::vertex temp;
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
			temp = process_coordinates(points[i]);
			cout<<"Received point : "<<temp.x<<", "<<temp.y<<", "<<temp.z;
			cout<<endl;
			polfig.vertices.push_back(temp);
		}
		
		polfig.vertices.shrink_to_fit();
		sort(polfig.vertices.begin(), polfig.vertices.end());
		//DEBUG
		for(auto it=polfig.vertices.begin(); it != polfig.vertices.end(); ++it)
		{
			printf("x: %d, y: %d, z: %d\n", it->x, it->y, it->z);
		}

		polfig.make_triangle();
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}

	return 1;
}

