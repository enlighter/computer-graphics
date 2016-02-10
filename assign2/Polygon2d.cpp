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

//custom namespace efl
namespace efl{

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
		printf("x: %d, y: %d\n", it->x, it->y);

	}

	if(size == 3)
	{
		this->make_edge_table(vertices);
	}

}

void Polygon2d::make_edge_table(std::vector<vertex> vertices)
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

	edge_table.shrink_to_fit();

	//current_edge_table = edge_table; //initialize current table
}

void inline Polygon2d::process_unit(eth &header, etlm unit)
{
	if(!unit.delta_x) //delta x = 0
	{
		//if(!unit.delta_y)
	}
}

void Polygon2d::init_edge_table(std::vector<vertex> vertices)
{
	std::vector<vertex>::iterator it;
	vertex current, past;
	etlm unit;
	eth temp;
	temp.y = 0; temp.l = std::list<etlm>{}; //clean slate eth
	int vertices_processed = 0; //flag

	for(it = vertices.begin(); it != vertices.end(); ++it, vertices_processed++)
	{
		current = *it;
		temp.y = current.y;
		if(!vertices_processed) //this is the first vertex being processed
		{
			unit.x = current.x;

			unit.delta_x = it[1].x - current.x; //second_vertex.x - first_vertex.x;
			unit.delta_y = it[1].y - current.y; //second_vertex.y - first_vertex.y;
		}
	}
}

Polygon2d::~Polygon2d() {
	// TODO Auto-generated destructor stub
}

void Polygon2d::print_edge_table(std::vector<eth> et)
{
	for(std::vector<eth>::iterator it=et.begin(); it != et.end(); ++it)
	{
		std::cout<<it->y<<"--> \n";
		for(std::list<etlm>::iterator i = it->l.begin(); i != it->l.end(); ++i)
		{
			std::cout<<"\tx = "<<i->x<<", delta x = "<<i->delta_x<<", delta y = "<<i->delta_y<<"\n";
		}
	}
}

void inline Polygon2d::get_edge_table()
{
	this->print_edge_table(this->edge_table);
}

void Polygon2d::fill_triangle()
{
	this->current_edge_table.push_back( this->edge_table[0] ); //start sweeping from the lowest y
	//DEBUG
	print_edge_table(this->current_edge_table);
}

}//namespace efl
