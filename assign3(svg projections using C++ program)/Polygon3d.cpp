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

} /* namespace enl */
