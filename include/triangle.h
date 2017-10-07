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
		Vertex4f& getCentroidVertex();
		Vertex4f& getPlaneNormal();
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
		std::string toString();
	private:
		/*
			stuetzvektoren fuer das dreieck.
		*/
		Vertex4f m_vertecies[3];
		/*
			schwerpunkt des dreiecks.
		*/
		Vertex4f m_centroidVertex;
		float m_radius;	
		Vertex4f m_areaNormal;
};
#endif