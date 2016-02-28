/*
 * Transformation.h
 *
 *  Created on: 28-Feb-2016
 *      Author: enlighter
 */

#include <vector>

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

namespace enl {

class Transformation {
public:
	std::vector<std::vector<int>> translation;
	std::vector<std::vector<int>> scaling;
	std::vector<std::vector<int>> rotationx;
	std::vector<std::vector<int>> rotationy;
	std::vector<std::vector<int>> rotationz;

	Transformation();
	virtual ~Transformation();
	void set_translation(int, int, int);
	void set_scaling(int, int, int);
	void set_zoom(int);
	void set_x_rotation(int);
	void set_y_rotation(int);
	void set_z_rotation(int);
};

} /* namespace enl */

#endif /* TRANSFORMATION_H_ */
