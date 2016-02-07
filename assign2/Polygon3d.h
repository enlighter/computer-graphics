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
	};
	Polygon3d();
	virtual ~Polygon3d();
	void make_triangle();

	std::vector<vertex> vertices;
};

} /* namespace enl */

#endif /* POLYGON3D_H_ */
