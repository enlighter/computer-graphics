/*
 * Polygon2d.cpp
 *
 *  Created on: 02-Feb-2016
 *      Author: enlighter
 */

#include <stdexcept>
#include <algorithm> //std::sort
#include <limits> //for setting standard numeric types to max value
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

	for(auto it=vertices.begin(); it != vertices.end(); ++it)
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
	//TODO
	//handle the case where delta x = 0

	std::vector<etlm> elist;
	etlm unit;
	eth temp;
	temp.y = 0; temp.l = {}; //clean slate eth
	int vertices_processed = 0; //flag

	for(auto it = vertices.begin(); it != vertices.end(); ++it, vertices_processed++)
	{
		//at this point temp still retains the value from previous iteration

		if(!vertices_processed) //this is the first vertex being processed
		{
			unit.x = it->x;

			for(int i=1; i<=2; i++)
			{
				unit.delta_x = it[i].x - it->x; //second_vertex.x or third_vertex.x - first_vertex.x;
				unit.delta_y = it[i].y - it->y; //second_vertex.y or third_vertex.x - first_vertex.y;

				//assume for now delta x is never 0
				elist.push_back(unit);
			}

			//temp.y = *it->y;
			//temp.l = elist;
			//this->edge_table.push_back(temp);
			//elist.clear();
		}
		else if(vertices_processed == 1) //this is the 2nd lowest y coordinate vertex being processed
		{
			unit.x = it->x;
			//it is now already at vertices.begin()[1]
			unit.delta_x = it[1].x - it->x; //third_vertex.x - second_vertex.x;
			unit.delta_y = it[1].y - it->y; //third_vertex.x - second_vertex.y;

			//at this point temp still retains the value from previous iteration
			//check if this y is same as that of the lowest y coordinate vertex, which is the vertex in last iteration
			if(it->y == temp.y)
			{
				this->edge_table[0].l.push_back(unit);
				continue;
			}
			else
			{
				elist.push_back(unit);

				//temp.y = *it->y;
				//temp.l = elist;
				//this->edge_table.push_back(temp);
			}
			//elist.clear();
		}

		temp.y = it->y;
		if(!elist.empty())
			temp.l = elist;
		else
			temp.l = {};
		this->edge_table.push_back(temp);
		elist.clear();
	}

	//sort all edge_table etlm lists by 'x' asc
	for(auto it=this->edge_table.begin(); it != this->edge_table.end(); ++it)
	{
		if(!it->l.empty())
		{
			std::sort(it->l.begin(), it->l.end());
		}
	}
}

Polygon2d::~Polygon2d() {
	// TODO Auto-generated destructor stub
}

void Polygon2d::print_edge_table(std::vector<eth> et)
{
	for(auto it=et.begin(); it != et.end(); ++it)
	{
		std::cout<<it->y<<"--> \n";
		for(auto i = it->l.begin(); i != it->l.end(); ++i)
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
	int next_checkpoint = std::numeric_limits<int>::max();
	int max_y = this->edge_table.back().y;
	bool insert_mode = false;
	//int xcompare = std::numeric_limits<int>::max(); //
	this->current_edge_table = this->edge_table[0] ; //start sweeping from the lowest y

	if( !this->edge_table[1].l.empty() )
	{
		next_checkpoint = this->edge_table[1].y;
		//xcompare = this->edge_table[1].l[1].x;

	}
	//DEBUG
	print_edge_table(std::vector<eth> {this->current_edge_table} );
	std::cout<<"next checkpoint = "<<next_checkpoint<<std::endl;


	while( this->current_edge_table.y <= max_y  )
	{
		if( this->current_edge_table.y == next_checkpoint)
		{
			//insert_mode = true;
			this->current_edge_table.l.push_back( this->edge_table[1].l[1] );
			std::sort(this->current_edge_table.l.begin(), this->current_edge_table.l.end());
		}

		//DEBUG
		std::cout<<"y="<<this->current_edge_table.y<<":";

		//traverse the whole current_table.l list
		for(auto it = this->current_edge_table.l.begin(); it != this->current_edge_table.l.end(); ++it)
		{
			//if delta_y is 0 then
			//dynamically popping off elements from the vector l is complicated
			//so just logically ignore all elements of l with non-positive delta_y value
			if(it->delta_y < 1)
				continue;

			//DEBUG
			std::cout<<" "<<it->delta_y<<",";


			//decrease delta_y for all in l list for each while loop iteration
			(it->delta_y)--;
		}

		//iteration end conditions
		this->current_edge_table.y += 1;
		std::cout<<"\n";
	}

}

}//namespace efl
