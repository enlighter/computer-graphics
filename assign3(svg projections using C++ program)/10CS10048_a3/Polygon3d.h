/*
 * Polygon3d.h
 *
 *  Created on: 07-Feb-2016
 *      Author: enlighter
 */

#include <vector>

#ifndef POLYGON3D_H_
#define POLYGON3D_H_

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
		int x,y,z;
		//overload < operator for it to be sorted along x ascending using std::sort
		bool operator<(const vertex &rhs) const { return x < rhs.x; }
	};
	class face
	{
	public:
		std::vector<int> vertex_order;
	};
	Polygon3d();
	//no of edges here can be 3 or 4
	virtual ~Polygon3d();
	void make_triangle();
	void print_vertices();
	void print_faces();

	std::vector<vertex> vertices;
	std::vector<face> faces;
};

} /* namespace enl */

#endif /* POLYGON3D_H_ */