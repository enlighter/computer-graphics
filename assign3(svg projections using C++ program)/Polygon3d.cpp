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

Polygon3d::Polygon3d(int no_of_edges) {

	if(no_of_edges < 3 || no_of_edges > 4)
	{
		std::cout<<"Polygon with "<<no_of_edges<<" not supported here.";
		exit(0);
	}

}

Polygon3d::~Polygon3d() {
	// TODO Auto-generated destructor stub
}



} /* namespace enl */
