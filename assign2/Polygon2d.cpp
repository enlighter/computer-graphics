/*
 * Polygon2d.cpp
 *
 *  Created on: 02-Feb-2016
 *      Author: enlighter
 */

#include <stdexcept>
#include <algorithm> //std::sort
#include <stdio.h> //printf

#include "Polygon2d.h"

using namespace std;

Polygon2d::Polygon2d(std::vector<vertex> vertices,int size)
//takes the polygon vertices and size as parameter input
{
	// check that sufficient no. of vertices has been provided
	if(vertices.size() != size)
	{
		throw std::invalid_argument( "proper no. of vertices not provided" );
	}

	//sort the vertices, default is sorting by 'y' asc
	std::sort(vertices.begin(), vertices.end());

	for(std::vector<vertex>::iterator it=vertices.begin(); it != vertices.end(); ++it)
	{
		printf("x: %d, y: %d\n", *it->x, *it->y);

		eth temp;
		temp.y = *it->y;
		temp.l = NULL;

		edge_table.push_back(temp);
	}
}

Polygon2d::~Polygon2d() {
	// TODO Auto-generated destructor stub
}

