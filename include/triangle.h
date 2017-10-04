#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector4f.h"
#define INVERSETHREE 1.0f / 3.0f

class Triangle 
{
	public: 
		Triangle();
		Triangle(const Triangle &t);
		~Triangle();
		Triangle& operator=(const Triangle& t);
		Triangle& operator=(Triangle&& t);
		Vertex4f* getVertecies();
		Vertex4f& getMidvertex();
		Vertex4f& getAreaNormal();
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
		/*
			stuetzvektoren fuer das dreieck.
		*/
		Vertex4f m_vertecies[3];
		Vertex4f m_avgmidvertex;
		Vector4f m_radius;	
		Vertex4f m_areaNormal;
};
#endif