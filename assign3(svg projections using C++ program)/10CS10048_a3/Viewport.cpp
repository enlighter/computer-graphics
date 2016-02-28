/*
 * Viewport.cpp
 *
 *  Created on: 28-Feb-2016
 *      Author: enlighter
 */

#include "Viewport.h"

namespace enl {

Viewport::Viewport() : padding(10)
{

	this->width = 0;
	this->length = 0;
	this->start_x = 0;
	this->start_y = 0;

	this->imp.length = 0;
	this->imp.width = 0;
	this->imp.start_x = 0;
	this->imp.start_y = 0;

}

Viewport::~Viewport() {
	// TODO Auto-generated destructor stub
}

void Viewport::set_viewport(int width, int length)
{
	this->width = width;
	this->length = length;

	//image plane + 10 pixels padding = viewport
	this->imp.start_x = this->start_x+this->padding;
	this->imp.start_y = this->start_y+this->padding;
	this->imp.width = this->width-2*this->padding;
	this->imp.width = this->length-2*this->padding;
}

} /* namespace enl */
