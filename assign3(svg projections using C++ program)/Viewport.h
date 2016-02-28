/*
 * Viewport.h
 *
 *  Created on: 28-Feb-2016
 *      Author: enlighter
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

namespace enl {

class Viewport {
private:
	int height, width;
	int start_x, start_y; //lies on X-Y plane
public:
	Viewport();
	virtual ~Viewport();
};

} /* namespace enl */

#endif /* VIEWPORT_H_ */
