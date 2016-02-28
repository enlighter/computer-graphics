/*
 * Polygon3d.cpp
 *
 *  Created on: 07-Feb-2016
 *      Author: enlighter
 */

#include <iostream>

#include "Polygon3d.h"

/* enl is my custom namespace */
namespace enl {

Polygon3d::Polygon3d() {
	// TODO Auto-generated constructor stub

}

Polygon3d::~Polygon3d() {
	// TODO Auto-generated destructor stub
}

void Polygon3d::print_vertices()
{
	for(auto it = this->vertices.begin(); it != this->vertices.end(); ++it)
	{
		std::cout<<"x="<<it->x<<",y="<<it->y<<",z="<<it->z<<std::endl;
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
