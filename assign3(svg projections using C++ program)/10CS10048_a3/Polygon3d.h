/*
 * Polygon3d.h
 *
 *  Created on: 07-Feb-2016
 *      Author: enlighter
 */

#include <vector>

#ifndef POLYGON3D_H_
#define POLYGON3D_H_

#define DIMENSIONS 3

/* enl is my custom namespace */
namespace enl {

class Polygon3d {
private:
	int MainCoefficient[3];//A=0, B=0, C=0; //for the plane of the triangle of the form Ax+By+Cz+D=0
		// where S[0] = A, S[1]= B, S[2] = C
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
	Polygon3d();
	//no of edges here can be 3 or 4
	virtual ~Polygon3d();
	//void make_triangle();
	void print_vertices();
	void print_faces();
	/* check if any vertex in this object is in +ve Z, and if it does,
	 * then make it so that all vertices of this object are in -ve Z
	 */
	void normalize();

	std::vector<vertex> vertices;
	std::vector<face> faces;
};

} /* namespace enl */

#endif /* POLYGON3D_H_ */
