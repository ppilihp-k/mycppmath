#include "..\include\plane.h"

Plane::Plane()
{
	
};

Plane::Plane(const Plane &p)
{

};

Plane::Plane(Plane &&p)
{
	
};

Plane& Plane::operator=(const Plane &p)
{
	if(this == &p)
	{
		return *this;
	}
	m_position = p.m_position;
	m_normal = p.m_normal;
	return *this;
};

Plane& Plane::operator=(Plane &&p)
{
	if(this == &p)
	{
		return *this;
	}
	m_position = p.m_position;
	m_normal = p.m_normal;	
	return *this;	
};

Plane::~Plane()
{
	
};

Vector4f& Plane::getDirectional0()  
{
	return m_directional0;
};

Vector4f& Plane::getDirectional1()  
{
	return m_directional1;
};

Vector4f& Plane::getPlaneNormal()  
{
	return m_normal;
};

Vector4f& Plane::getPosition()  
{
	return m_position;
};