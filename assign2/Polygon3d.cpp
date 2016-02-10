/*
 * Polygon3d.cpp
 *
 *  Created on: 07-Feb-2016
 *      Author: enlighter
 */

#include <cmath> //std::abs

#include "Polygon3d.h"
#include "Polygon2d.h"

/* enl is my custom namespace */
namespace enl {

Polygon3d::Polygon3d() {
	// TODO Auto-generated constructor stub

}

Polygon3d::~Polygon3d() {
	// TODO Auto-generated destructor stub
}

void Polygon3d::make_triangle()
{
	vertex p1 = vertices[0], p2 = vertices[1], p3 = vertices[2];
	//p1 is first 3D coordinate and so on

	std::vector<efl::Polygon2d::vertex> projection; //the vector containing 2d triangle projection vertices
	vertex select;
	efl::Polygon2d::vertex intermediary;

	//DEBUG
	//cout<<p2.y;

	//A = (y2-y1)(z3-z1) - (y3-y1)(z2-z1)
	MainCoefficient[0] = ((p2.y - p1.y) * (p3.z - p1.z)) - ((p3.y - p1.y) * (p2.z - p1.z));

	//B = (z2-z1)(x3-x1) - (z3-z1)(x2-x1)
	MainCoefficient[1] = ((p2.z - p1.z) * (p3.x - p1.x)) - ((p3.z - p1.z) * (p2.x - p1.x));

	//C = (x2-x1)(y3-y1) - (x3-x1)(y2-y1)
	MainCoefficient[2] = ((p2.x - p1.x) * (p3.y - p1.y)) - ((p3.x - p1.x) * (p2.y - p1.y));

	//DEBUG
	std::cout<<MainCoefficient[0]<<" "<<MainCoefficient[1]<<" "<<MainCoefficient[2]<<std::endl;

	//which is max index in MainCoefficient?
	int maxindex = 0, max = std::abs(MainCoefficient[0]), temp=0;

	//find max
	for(int j=0; j<3;j++)
	{
		temp = abs(MainCoefficient[j]);
		if(max < temp)
		{
			max = temp;
			maxindex = j;
		}
	}

	//DEBUG
	std::cout<<"maxindex = "<<maxindex<<", max = "<<max<<std::endl;

	/* If A (MainCoefficient[0]) is max in magnitude, then the y-z projection
	 * 2D triangle will be the dominant one, and so on,
	 * if B (MainCoefficient[1]) = max, x-z projection
	 * if C (MainCoefficient[2]) = max, x-y projection
	 */
	for( temp=0; temp<3; temp++ )
	{
		//DEBUG
		std::cout<<temp<<" :\n";

		select = vertices[temp];

		if(maxindex == 0)
			//projection on y-z plane
		{
			intermediary.x = select.y;
			//DEBUG
			std::cout<<intermediary.x<<" ";
			intermediary.y = select.z;
			//DEBUG
			std::cout<<intermediary.y<<"\n";
		}
		else if(maxindex == 1)
			//projection on x-z plane
		{
			intermediary.x = select.x;
			//DEBUG
			std::cout<<intermediary.x<<" ";
			intermediary.y = select.z;
			//DEBUG
			std::cout<<intermediary.y<<"\n";
		}
		else if(maxindex == 2)
			//projection on x-y plane
		{
			intermediary.x = select.x;
			//DEBUG
			std::cout<<intermediary.x<<" ";
			intermediary.y = select.y;
			//DEBUG
			std::cout<<intermediary.y<<"\n";
		}

		projection.push_back(intermediary);
	}

	projection.shrink_to_fit();

	efl::Polygon2d projected_traingle{projection};
	projected_traingle.get_edge_table();
	projected_traingle.fill_triangle();
}

} /* namespace enl */
