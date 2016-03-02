/*
 * Transformation.cpp
 *
 *  Created on: 28-Feb-2016
 *      Author: enlighter
 */
#include <cmath>

#include "Transformation.h"

#define PI 3.14159265

namespace enl {

Transformation::Transformation()
{
	translation = std::vector<std::vector<int> > (DIMENSIONS+1); //initialize translation to a 4x4 homogenous coord system matrix
	for ( auto i = 0 ; i < DIMENSIONS+1 ; i++ )
		translation[i].resize(DIMENSIONS+1);

	scaling = std::vector<std::vector<int> > (DIMENSIONS+1);
	for ( auto i = 0 ; i < DIMENSIONS+1 ; i++ )
		scaling[i].resize(DIMENSIONS+1);

	rotation = std::vector<std::vector<double> > (DIMENSIONS+1);
	for ( auto i = 0 ; i < DIMENSIONS+1 ; i++ )
		rotation[i].resize(DIMENSIONS+1);

	/*
	rotationy = std::vector<std::vector<double> > (DIMENSIONS+1);
	for ( auto i = 0 ; i < DIMENSIONS+1 ; i++ )
		rotationy[i].resize(DIMENSIONS+1);

	rotationz = std::vector<std::vector<double> > (DIMENSIONS+1);
	for ( auto i = 0 ; i < DIMENSIONS+1 ; i++ )
		rotationz[i].resize(DIMENSIONS+1);
	*/
}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

void Transformation::set_translation(int tx, int ty, int tz)
{
	for(auto it = this->translation.begin(); it != this->translation.end(); ++it)
		std::fill(it->begin(), it->end(), 0);
	for(auto i=0; i<DIMENSIONS+1; i++)
	{
		this->translation[i][i] = 1;
	}
	this->translation[0][3] = tx;
	this->translation[1][3] = ty;
	this->translation[2][3] = tz;
}

void Transformation::set_scaling(int sx, int sy, int sz)
{
	for(auto it = this->scaling.begin(); it != this->scaling.end(); ++it)
		std::fill(it->begin(), it->end(), 0);
	this->scaling[0][0] = sx;
	this->scaling[1][1] = sy;
	this->scaling[2][2] = sz;
	this->scaling[3][3] = 1;
}

void Transformation::set_zoom(int zoom)
{
	this->set_scaling(zoom, zoom, zoom);
}

void Transformation::set_z_rotation(int thetaz)
{
	double pi_angle = 0.0;

	std::cout<<"Applying theta = "<<thetaz<<std::endl;

	pi_angle = ((double)thetaz / 180.0) * PI;

	std::cout<<"Converted to PI form : "<<thetaz<<std::endl;

	this->rotation = { {cos(thetaz), -sin(thetaz), 0.0, 0.0},
						{sin(thetaz), cos(thetaz), 0.0, 0.0},
						{0.0, 0.0, 1.0, 0.0},
						{0.0, 0.0, 0.0, 1.0}
	};
}

void Transformation::set_y_rotation(int thetay)
{
	double pi_angle = 0.0;

	std::cout<<"Applying theta = "<<thetay<<std::endl;

	pi_angle = ((double)thetay / 180.0) * PI;

	std::cout<<"Converted to PI form : "<<pi_angle<<std::endl;

	this->rotation = { {cos(pi_angle), 0.0, sin(pi_angle), 0.0},
						{0.0, 1, 0.0, 0.0},
						{-sin(pi_angle), 0.0, cos(pi_angle), 0.0},
						{0.0, 0.0, 0.0, 1.0}
	};
}

void Transformation::set_x_rotation(int thetax)
{
	double pi_angle = 0.0;

	std::cout<<"Applying theta = "<<thetax<<std::endl;

	pi_angle = ((double)thetax / 180.0) * PI;

	std::cout<<"Converted to PI form : "<<pi_angle<<std::endl;

	this->rotation = { {1.0, 0.0, 0.0, 0.0},
						{0.0, cos(pi_angle), -sin(pi_angle), 0.0},
						{0.0, sin(pi_angle), cos(pi_angle), 0.0},
						{0.0, 0.0, 0.0, 1.0}
	};
}

void Transformation::apply_rotation(enl::Polygon3d *object)
{
	for(auto it = object->vertices.begin(); it != object->vertices.end(); ++it)
	{
		*it = this->multiply_matrix( this->rotation, *it);
	}
}

enl::Polygon3d::vertex Transformation::multiply_matrix(std::vector<std::vector<double>> transform, enl::Polygon3d::vertex to_transform)
//This method multiplies a 4x4 matrix with a 4x1 matrix returning a 4x1 matrix as a result
{
	//DEBUG
	for(auto i = 0; i<(DIMENSIONS+1); i++)
	{
		for(auto j=0; j<(DIMENSIONS+1); j++)
		{
			std::cout<<transform[i][j]<<" ";
		}
		std::cout<<" | "<<to_transform.h_coord[i]<<std::endl;
	}

	enl::Polygon3d::vertex transformed;

	for(auto i = 0; i<(DIMENSIONS+1); i++)
	{
		for(auto j=0; j<(DIMENSIONS+1); j++)
		{
			transformed.h_coord[i] += transform[i][j] * to_transform.h_coord[j];
		}
	}

	//DEBUG
	std::cout<<"After Transformation:\n";
	for(auto i = 0; i<(DIMENSIONS+1); i++)
	{
		std::cout<<transformed.h_coord[i]<<" ";
	}
	std::cout<<std::endl;

	return transformed;
}

} /* namespace enl */
