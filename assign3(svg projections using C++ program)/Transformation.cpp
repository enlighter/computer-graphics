/*
 * Transformation.cpp
 *
 *  Created on: 28-Feb-2016
 *      Author: enlighter
 */

#include "Transformation.h"

#define DIMENSIONS 3

namespace enl {

Transformation::Transformation()
: translation( (DIMENSIONS+1,std::vector<int>(DIMENSIONS+1)) ) //initialize translation to a 4x4 homogenous coord system matrix
, scaling( (DIMENSIONS+1,std::vector<int>(DIMENSIONS+1)) )
, rotationx( (DIMENSIONS+1,std::vector<int>(DIMENSIONS+1)) )
, rotationy( (DIMENSIONS+1,std::vector<int>(DIMENSIONS+1)) )
, rotationz( (DIMENSIONS+1,std::vector<int>(DIMENSIONS+1)) )
{}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

void Transformation::set_translation(int tx, int ty, int tz)
{
	std::fill(this->translation.begin(), this->translation.end(), 0);
	for(auto i=0; i<DIMENSIONS+1; i++)
	{
		this->translation[i][i] = 1;
	}
	this->translation[0][3] = tx;
	this->translation[1][3] = ty;
	this->translation[2][3] = tz;
}

} /* namespace enl */
