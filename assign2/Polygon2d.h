/*
 * Polygon2d.h
 *
 *  Created on: 02-Feb-2016
 *      Author: enlighter
 */
#include <iostream>
#include <list>
#include <vector>

#ifndef POLYGON2D_H_
#define POLYGON2D_H_

//#define COORDINATE_SYSTEM	2

using namespace std;

class Polygon2d {
private:
	class vertex
	{
	public:
		int x,y;
		//overload '<' operator for sorting using std::sort
		bool operator<(const vertex &rhs) const { return y < rhs.y; }
	};

	typedef struct edge_table_list_member
	{
		int x; //x coordinate
		int delta_x, delta_y;
	} etlm;

	typedef struct edge_table_header
	{
		int y;
		std::list<etlm> *l;
	} eth;

	//define the global edge table
	std::vector<eth> edge_table;

public:
	Polygon2d(std::vector<vertex>, int);
	virtual ~Polygon2d();
};

#endif /* POLYGON2D_H_ */