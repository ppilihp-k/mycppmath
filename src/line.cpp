#include "..\include\line.h"

Line::Line()
{
	
};

Line::Line(const Line &l)
{
	m_vertex = l.m_vertex;
	m_direction = l.m_direction;
};

Line::Line(Line &&l)
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

Line& Line::operator=(const Line &l)
{
	if(this == &l){
		return *this;
	}
	m_vertex = l.m_vertex;
	m_direction = l.m_direction;
	return *this;
};

Line& Line::operator=(Line &&l)
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

std::string Line::toString()
{
	return "Line{\n\tposition:"+m_vertex.toString()+",\n\tdirection:"+m_direction.toString()+"\n}";
};

Linesegment::Linesegment()
{
	
};

Linesegment::Linesegment(const Linesegment &l) : Line(l)
{
	m_vertex1 = l.m_vertex1;
};

Linesegment::Linesegment(Linesegment &&l) : Line(l)
{
	m_vertex1 = l.m_vertex1;
};

Linesegment::~Linesegment()
{
	
};

Linesegment& Linesegment::operator=(const Linesegment &l)
{
	if(this == &l)
	{
		return *this;
	}
	m_vertex = l.m_vertex;
	m_direction = l.m_direction;
	m_vertex1 = l.m_vertex1;
	return *this;
};

Linesegment& Linesegment::operator=(Linesegment &&l)
{
	if(this == &l)
	{
		return *this;
	}
	m_vertex = l.m_vertex;
	m_direction = l.m_direction;
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

std::string Linesegment::toString()
{
	return "Linesegment{\n\tvertex_0:"+getPosition().toString()+",\n\tvertex_1:"+m_vertex1.toString()+"direction:"+getDirection().toString()+"\n}";
};