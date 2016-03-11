/*
 * Object3D.h
 *
 *  Created on: 11-Mar-2016
 *      Author: enlighter
 */

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
		std::vector<float> h_coord; //homogenous coord system 4x1 matrix {x,y,z,1}
		vertex();
	};

	class face
	{
	public:
		std::vector<int> vertex_order;
	};

	Object3D();
	virtual ~Object3D();

	void print_vertices();
	void print_faces();

	std::vector<vertex> vertices;
	std::vector<face> faces;
};

} /* namespace enl */

#endif /* MAXIMAL_COVEX_PATCHING_OBJECT3D_H_ */
