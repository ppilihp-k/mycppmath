#ifndef GEOMETRI_H
#define GEOMETRI_H

#include "include.h"
#include "vector4f.h"
#include "polygon.h"
#include "triangle.h"

/*
	beschreibung: 	erstllt einen neuen vektor mit dem "new"-operator und gibt ihr zurueck.
	bedingungen: 	-
	parameter:		-
	rueckgabewert:	ein neuer vektor, der von dieser bibliothek verwaltet wird.					
*/
Vector4f& allocateVector4f();
/*
	beschreibung: 	loescht den gegebenen vektor oder nutzt ihn weiter, je nachdem wie er benoetigt wird.
	bedingungen: 	-
	parameter:		ein vector4f, der nicht mehr gebraucht wird.
	rueckgabewert:	-				
*/
deallocateVector4f(Vector4f &v);
/*
	beschreibung: 	erstllt einen neuen vertex mit dem "new"-operator und gibt ihr zurueck.
	bedingungen: 	-
	parameter:		-
	rueckgabewert:	ein neuer vertex, der von dieser bibliothek verwaltet wird.					
*/
Vertex& allocateVertex4f();
/*
	beschreibung: 	loescht den gegebenen vertex oder nutzt ihn weiter, je nachdem wie er benoetigt wird.
	bedingungen: 	-
	parameter:		ein vertex, der nicht mehr gebraucht wird.
	rueckgabewert:	-				
*/
deallocateVertex4f(Vertex4f &v);
/*
	beschreibung: 	erstllt eine neue matrix4f mit dem "new"-operator und gibt ihr zurueck.
	bedingungen: 	-
	parameter:		-
	rueckgabewert:	eine neue matrix4f, der von dieser bibliothek verwaltet wird.					
*/
Matrix4f allocateMatrix4f();
/*
	beschreibung: 	loescht die gegebene matrix4f oder nutzt ihn weiter, je nachdem wie er benoetigt wird.
	bedingungen: 	-
	parameter:		eine matrix4f, die nicht mehr gebraucht wird.
	rueckgabewert:	-				
*/
Matrix4f deallocateMatrix4f(Matrix4f &m);

std::list<Vertex4f> intersect(Polygon &p0, Polygon &p1);

std::list<Vertex4f> intersect(Triangle &t0, Triangle &t1);

std::list<Vertex4f> intersect(Plane &p0, Plane &p1);

void triangulate(Polygon &p);

uint32_t isLocatedOnPositiveHalfplane(Vector4f& planeNormal, Vertex& v);

#endif