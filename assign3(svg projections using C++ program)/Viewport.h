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
	const int padding;
	int width, length;
	int start_x, start_y; //lies on X-Y plane
	class imageplane : public Viewport
	{

	} imp;
public:
	Viewport();
	virtual ~Viewport();
	void set_viewport(int, int);
};

} /* namespace enl */

#endif /* VIEWPORT_H_ */
