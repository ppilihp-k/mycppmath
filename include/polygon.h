#ifndef POLYGON_H
#define POLYGON_H

#include "include.h"
#include "vector4f.h"
#include "triangle.h"

class Polygon 
{
	public:
		Polygon();
		Polygon(const Polygon &p);
		Polygon(Polygon &&p);
		~Polygon();
		Polygon& operator=(const Polygon &p);
		Polygon& operator=(Polygon &&p);
		void operator*=(const Matrix4f &m);
		//void operator*=(const Vector4f &v);
		void operator*=(float f);
		uint32_t operator==(const Polygon& p);
		Triangle* getTriangles() const;
		uint32_t size() const;
		Vertex4f& getCentroidVertex();
		float getRadius();
		/*
			fuer synchronisiertes lesen sollte der kritische
			bereich in die read methoden eingeschlossen werden.
		*/
		void read();
		void finishRead();
		/*
			fuer synchronisiertes schreiben sollte der kritische
			bereich in die write methoden eingeschlossen werden.
		*/
		void write();
		void finishWrite();
	private:
		void copy(const Polygon& p1);
		void move(Polygon& p1);
		Triangle *m_triangles;
		uint32_t m_numElements;
		Vertex4f m_centroidVertex;
		float m_radius;
};

#endif