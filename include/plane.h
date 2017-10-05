#ifndef PLANE_H
#define PLANE_H

#include "include.h"
#include "vector4f.h"

class Plane
{
	public:
		Plane();
		Plane(const Plane &p);
		Plane(Plane &&p);
		Plane& operator=(const Plane &p);
		Plane& operator=(Plane &&p);
		~Plane();
		Vector4f& getDirectional0();
		Vector4f& getDirectional1();
		Vector4f& getPlaneNormal();
		Vector4f& getPosition();
	private:
		Vertex4f m_position;	
		Vector4f m_directional0, m_directional1;
		Vector4f m_normal;
};

#endif