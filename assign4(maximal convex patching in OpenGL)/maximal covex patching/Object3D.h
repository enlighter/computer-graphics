/*
 * Object3D.h
 *
 *  Created on: 11-Mar-2016
 *      Author: enlighter
 */
#include <vector>

#ifndef MAXIMAL_COVEX_PATCHING_OBJECT3D_H_
#define MAXIMAL_COVEX_PATCHING_OBJECT3D_H_

#define DIMENSIONS 3

/* enl is my custom namespace */
namespace enl {

class Object3D {
public:
	class vertex
	{
	public:
		std::vector<float> coord; //coord system 3x1 matrix {x,y,z}
		vertex();
	};

	class face
	{
	public:
		std::vector<int> vertex_order;
		face();
	};

	Object3D();
	virtual ~Object3D();

	void print_vertices();
	void print_faces();
	//within each face sort the vertex no.s
	void sort_within_faces();
	//sort all faces for simplicity of generating connectivity tree
	void sort_all_faces();

	std::vector<vertex> vertices;
	std::vector<face> faces;
};

} /* namespace enl */

#endif /* MAXIMAL_COVEX_PATCHING_OBJECT3D_H_ */
