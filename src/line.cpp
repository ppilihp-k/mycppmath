#include "..\include\line.h"

Line::Line()
{
	
};

Line::Line(const Line &l)
{
	m_vertex = l.m_vertex;
	m_direction = l.m_direction;
};
/*
Line::Line(Line &&l)
{
	
};
*/
Line::~Line()
{
	
};

Line& Line::operator=(Line &l)
{
	if(this == &l){
		return *this;
	}
	m_vertex = l.m_vertex;
	m_direction = l.m_direction;
	return *this;
};
/*
Line* Line::operator=(Line &&l)
{
	
};
*/
Vertex4f& Line::getPosition()
{
	return m_vertex;
};

Vector4f& Line::getDirection()
{
	return m_direction;
};

Linesegment::Linesegment()
{
	
};

Linesegment::Linesegment(const Linesegment &l) : Line(l)
{
	m_vertex1 = l.m_vertex1;
};

Linesegment::~Linesegment()
{
	
};

Linesegment& Linesegment::operator=(Linesegment &l)
{
	if(this == &l)
	{
		return *this;
	}
	Line::operator=(l);
	m_vertex1 = l.m_vertex1;
	return *this;
};

Vertex4f& Linesegment::getVertex0()
{
	return Line::getPosition();
};

Vertex4f& Linesegment::getVertex1()
{
	return m_vertex1;
};