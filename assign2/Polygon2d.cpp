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

Polygon2d::Polygon2d(std::vector<vertex> vertices,int size = 3)
//takes the polygon vertices and size as parameter input
//size=3 i.e. triangle is taken as the default
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

	}

	if(size == 3)
	{
		this->make_triangle(vertices);
	}

}

void Polygon2d::make_triangle(std::vector<vertex> vertices)
{
	vertex first_vertex=vertices.begin()[0], second_vertex=vertices.begin()[1], third_vertex=vertices.begin()[2];
	std::list<etlm> elist;

	eth temp;
	temp.y = first_vertex.y;

	etlm unit;
	//insert first edge
	unit.x = first_vertex.x;
	unit.delta_x = second_vertex.x - first_vertex.x;
	unit.delta_y = second_vertex.y - first_vertex.y;
	elist.push_back(unit);

	//insert second edge
	unit.x = first_vertex.x;
	unit.delta_x = third_vertex.x - first_vertex.x;
	unit.delta_y = third_vertex.y - first_vertex.y;
	elist.push_back(unit);

	//copy this elist to first entry in edge table
	temp.l = elist;
	edge_table.push_back(temp);
	elist.clear();

	//increment y for edge_table
	temp.y = second_vertex.y;
	unit.x = second_vertex.x;
	unit.delta_x = third_vertex.x - second_vertex.x;
	unit.delta_y = third_vertex.y - second_vertex.y;
	elist.push_back(unit);
	temp.l = elist;
	edge_table.push_back(temp);
	elist.clear();

	//increment y again
	temp.y = third_vertex.y;
	temp.l=  std::list<etlm> {}; //empty list
	edge_table.push_back(temp);
}

Polygon2d::~Polygon2d() {
	// TODO Auto-generated destructor stub
}

