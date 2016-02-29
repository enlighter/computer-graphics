/*
 * Polygon3d.cpp
 *
 *  Created on: 07-Feb-2016
 *      Author: enlighter
 */

#include <iostream>

#include "Polygon3d.h"

#define DIMENSIONS 3

/* enl is my custom namespace */
namespace enl {

Polygon3d::Polygon3d() {
	// TODO Auto-generated constructor stub

}

Polygon3d::~Polygon3d() {
	// TODO Auto-generated destructor stub
}

Polygon3d::vertex::vertex()
{
	this->h_coord = std::vector<int> (DIMENSIONS+1);
	std::fill(this->h_coord.begin(), this->h_coord.end(), 0);
	this->h_coord[DIMENSIONS] = 1;
}

void Polygon3d::print_vertices()
{
	for(auto it = this->vertices.begin(); it != this->vertices.end(); ++it)
	{
		std::cout<<"x="<<it->h_coord[0]<<",y="<<it->h_coord[1]<<",z="<<it->h_coord[2]<<std::endl;
	}
}

void Polygon3d::print_faces()
{
	for(auto it = this->faces.begin(); it != this->faces.end(); ++it)
	{
		for(auto i = it->vertex_order.begin(); i != it->vertex_order.end(); ++i)
		{
			std::cout<<*i<<"->";
		}
		std::cout<<std::endl;
	}
}

} /* namespace enl */
