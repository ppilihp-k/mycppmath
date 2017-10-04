#ifndef PLANE_H
#define PLANE_H

#include "include.h"
#include "triangle.h"

class Plane : public Triangle 
{
	public:
		Plane();
		~Plane();
		std::tuple<&Vector4f, &Vector4f> getDirectionalVectors();
};

#endif