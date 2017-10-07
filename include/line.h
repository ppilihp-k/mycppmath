#ifndef LINE_H
#define LINE_H

#include "vector4f.h"
#include "include.h"

class Line 
{
	public:
		Line();
		Line(const Line &l);
		//Line(Line &&l);
		~Line();
		Vertex4f& getPosition();
		Vector4f& getDirection();
		Line& operator=(Line &l);
		//Line* operator=(Line &&l);
		std::string toString();
	private:
		Vertex4f m_vertex;
		Vector4f m_direction;
};

class Linesegment : public Line
{
	public:
		Linesegment();
		Linesegment(const Linesegment &l);
		~Linesegment();
		Linesegment& operator=(Linesegment &l);
		Vertex4f& getVertex0();
		Vertex4f& getVertex1();
		std::string toString();
	private:
		Vertex4f m_vertex1;
};

#endif