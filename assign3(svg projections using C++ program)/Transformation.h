/*
 * Transformation.h
 *
 *  Created on: 28-Feb-2016
 *      Author: enlighter
 */

#include <vector>

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

/*
#define TRANSLATION 1
#define SCALING 1
#define X 1
#define TRANSLATION 1
#define TRANSLATION 1
*/

namespace enl {

class Transformation {
private:
	std::vector<std::vector<int>> translation;
	std::vector<std::vector<int>> scaling;
	std::vector<std::vector<double>> rotation;
	//std::vector<std::vector<double>> rotationy;
	//std::vector<std::vector<double>> rotationz;

	void apply_rotation(enl::Polygon3d *);

public:
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
