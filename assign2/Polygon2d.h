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

//custom namespace efl
namespace efl{

using namespace std;

class Polygon2d {
public:
	class vertex
	{
		public:
			int x,y;
			//overload '<' operator for sorting using std::sort
			bool operator<(const vertex &rhs) const { return y < rhs.y; }
	};
private:

	typedef struct edge_table_list_member
	{
		int x; //x coordinate
		int delta_x, delta_y;
	} etlm;

	typedef struct edge_table_header
	{
		int y;
		std::list<etlm> l;
	} eth;

	//define the global edge table
	std::vector<eth> edge_table;
	//define the edge table at any instant after processing
	std::vector<eth> current_edge_table;

	//define set of points in the triangle filled till now
	std::vector<vertex> filled;

	void make_edge_table(std::vector<vertex>);
	void init_edge_table(std::vector<vertex>);
	void print_edge_table(std::vector<eth>);
	void inline process_unit(eth &, etlm);

public:
	Polygon2d(std::vector<vertex>, int);
	virtual ~Polygon2d();
	void inline get_edge_table();
	void fill_triangle();
};

}//namespace efl
#endif /* POLYGON2D_H_ */
