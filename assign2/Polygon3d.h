/*
 * Polygon3d.h
 *
 *  Created on: 07-Feb-2016
 *      Author: enlighter
 */

#ifndef POLYGON3D_H_
#define POLYGON3D_H_

/* enl is my custom namespace */
namespace enl {

class Polygon3d {
public:
	class vertex
	{
	public:
		int x,y,z;
	};
	Polygon3d();
	virtual ~Polygon3d();
};

} /* namespace std */

#endif /* POLYGON3D_H_ */
