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

using namespace std;

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
			cout<<"Enter vertex no. "<<i<<" coordinates in the format (x,y,z): ";
			getline(cin, points[i]);
		}
		
		for(i=0; i<POLYGON_SIZE; i++)
		{
			cout<<points[i]<<endl;
		}
		//process_coordinates(start, start_point);
		//process_coordinates(end, end_point);

		//draw3Dline(start_point, end_point);
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}

	return 1;
}

