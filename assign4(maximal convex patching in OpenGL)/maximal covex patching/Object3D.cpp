/*
 * Object3D.cpp
 *
 *  Created on: 11-Mar-2016
 *      Author: enlighter
 */
#include <iostream>

#include "Object3D.h"

/* enl is my custom namespace */
namespace enl {

Object3D::Object3D() {
	// TODO Auto-generated constructor stub

}

Object3D::~Object3D() {
	// TODO Auto-generated destructor stub
}

Object3D::vertex::vertex()
{
	this->coord = std::vector<float> (DIMENSIONS);
	std::fill(this->coord.begin(), this->coord.end(), 0);
}

Object3D::face::face()
{
	this->vertex_order = std::vector<int> (DIMENSIONS);
	std::fill(this->vertex_order.begin(), this->vertex_order.end(), 0);
}

void Object3D::print_vertices()
{
	for(auto it = this->vertices.begin(); it != this->vertices.end(); ++it)
	{
		std::cout<<"x="<<it->coord[0]<<",y="<<it->coord[1]<<",z="<<it->coord[2]<<std::endl;
	}
}

void Object3D::print_faces()
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

//within each face sort the vertex no.s
void Object3D::sort_within_faces()
{
	for(auto it = this->faces.begin(); it != this->faces.end(); ++it)
	{
		//we need to sort it in asc order
		std::sort( it->vertex_order.begin(), it->vertex_order.end() );
	}
}

//sort all faces for simplicity of generating connectivity tree
void Object3D::sort_all_faces()
{

}

} /* namespace enl */
