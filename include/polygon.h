#ifndef POLYGON_H
#define POLYGON_H

#include "include.h"
#include "vector4f.h"
#include "triangle.h"

class Polygon 
{
	public:
		Polygon(float *array, uint32_t numElements) throw (uint32_t);
		~Polygon();
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
		Triangle *m_triangles;
};

#endif