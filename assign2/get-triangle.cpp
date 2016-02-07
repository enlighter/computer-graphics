/*
 * get-triangle.cpp
 *
 *  Created on: 29-Jan-2016
 *      Author: enlighter
 */


#include <iostream>
#include <string>
#include <regex>
#include <cmath> //std::abs

#include "Polygon2d.cpp"
#include "Polygon3d.cpp"

#define COORDINATE_SYSTEM	3 //3d coordinate system used here
#define POLYGON_SIZE	3
#define FORMAT_ERROR "Please maintain proper format!"
#define X 0
#define Y 1
#define Z 2

using namespace std;

enl::Polygon3d::vertex process_coordinates(string input)
{
	enl::Polygon3d::vertex point;
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
			/*int j=0;
			for ( i != seglist.end(); ++i, j++)
			{

    			point[j] = std::stoi(*i, NULL, 10); //convert to integer value
			}*/

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

	//return 0;
}

int process_triangle_orientation( vector<enl::Polygon3d::vertex> vertexTrio )
{
	int S[3];//A=0, B=0, C=0; //for the plane of the triangle of the form Ax+By+Cz+D=0
	// where S[0] = A, S[1]= B, S[2] = C

	enl::Polygon3d::vertex p1 = vertexTrio[0], p2 = vertexTrio[1], p3 = vertexTrio[2];
	//p1 is first 3D coordinate and so on

	vector<Polygon2d::vertex> projection; //the vector containing 2d triangle projection vertices
	enl::Polygon3d::vertex select;
	Polygon2d::vertex intermediary;

	//DEBUG
	//cout<<p2.y;

	//A = (y2-y1)(z3-z1) - (y3-y1)(z2-z1)
	S[0] = ((p2.y - p1.y) * (p3.z - p1.z)) - ((p3.y - p1.y) * (p2.z - p1.z));

	//B = (z2-z1)(x3-x1) - (z3-z1)(x2-x1)
	S[1] = ((p2.z - p1.z) * (p3.x - p1.x)) - ((p3.z - p1.z) * (p2.x - p1.x));

	//C = (x2-x1)(y3-y1) - (x3-x1)(y2-y1)
	S[2] = ((p2.x - p1.x) * (p3.y - p1.y)) - ((p3.x - p1.x) * (p2.y - p1.y));

	//DEBUG
	cout<<S[0]<<" "<<S[1]<<" "<<S[2]<<endl;

	//which is max index in S?
	int maxindex = 0, max = abs(S[0]), temp=0;

	//find max
	for(int j=0; j<3;j++)
	{
		temp = abs(S[j]);
		if(max < temp)
		{
			max = temp;
			maxindex = j;
		}
	}

	//DEBUG
	cout<<"maxindex = "<<maxindex<<", max = "<<max<<endl;
	//maxindex ++;

	/* If A (S[0]) is max in magnitude, then the y-z projection
	 * 2D triangle will be the dominant one, and so on,
	 * if B (S[1]) = max, x-z projection
	 * if C (S[2]) = max, x-y projection
	 */
	for( temp=0; temp<3; temp++ )
	{
		//DEBUG
		cout<<temp<<" :\n";

		select = vertexTrio[temp];

		if(maxindex == 0)
			//projection on y-z plane
		{
			intermediary.x = select.y;
			//DEBUG
			cout<<intermediary.x<<" ";
			intermediary.y = select.z;
			//DEBUG
			cout<<intermediary.y<<"\n";
		}
		else if(maxindex == 1)
			//projection on x-z plane
		{
			intermediary.x = select.x;
			//DEBUG
			cout<<intermediary.x<<" ";
			intermediary.y = select.z;
			//DEBUG
			cout<<intermediary.y<<"\n";
		}
		else if(maxindex == 2)
			//projection on x-y plane
		{
			intermediary.x = select.x;
			//DEBUG
			cout<<intermediary.x<<" ";
			intermediary.y = select.y;
			//DEBUG
			cout<<intermediary.y<<"\n";
		}

		projection.push_back(intermediary);
	}

	projection.shrink_to_fit();

	return 0;
}

int main()
{
	string points[POLYGON_SIZE];
	//int vertices[POLYGON_SIZE][COORDINATE_SYSTEM];
	vector<enl::Polygon3d::vertex> vertices;
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
			vertices.push_back(temp);
		}
		
		vertices.shrink_to_fit();
		//DEBUG
		/*for(vector<enl::Polygon3d::vertex>::iterator it=vertices.begin(); it != vertices.end(); ++it)
		{
			printf("x: %d, y: %d, z: %d\n", it->x, it->y, it->z);
		}*/

		process_triangle_orientation( vertices );
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}

	return 1;
}

