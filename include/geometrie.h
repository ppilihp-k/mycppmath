#ifndef GEOMETRI_H
#define GEOMETRI_H

#include "include.h"
#include "mycppmath.h"
#include "vector4f.h"
#include "polygon.h"
#include "triangle.h"
#include "plane.h"
#include "line.h"
#include <math.h>

enum MathStatus {PARALLEL = 0, SCHNITT = 1, IDENTITAET = 2, KEINSCHNITT = 3};
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
void deallocateVector4f(Vector4f &v);
/*
	beschreibung: 	erstllt einen neuen vertex mit dem "new"-operator und gibt ihr zurueck.
	bedingungen: 	-
	parameter:		-
	rueckgabewert:	ein neuer vertex, der von dieser bibliothek verwaltet wird.					
*/
Vertex4f& allocateVertex4f();
/*
	beschreibung: 	loescht den gegebenen vertex oder nutzt ihn weiter, je nachdem wie er benoetigt wird.
	bedingungen: 	-
	parameter:		ein vertex, der nicht mehr gebraucht wird.
	rueckgabewert:	-				
*/
void deallocateVertex4f(Vertex4f &v);
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
void  deallocateMatrix4f(Matrix4f &m);
/*
	beschreibung: 	testet die lagebeziehung von einem punkt zu einer ebene.
	bedingungen: 	-
	parameter:		m0 und m1 sind die mittelpunkte der jeweiligen kugeln und r0 bzw. r1 die zugehoeruigen radien.
	rueckgabewert:	SCHNITT, wenn sie die spheren schneiden, IDENTITAET, wenn m0 = m1 und r0 = r1, KEINSCHNITT sonst.		
*/
float testPositiveHalfPlane(
		Vertex4f& v, 
		Vertex4f& p, 
		Vector4f& n
		);
/*
	beschreibung: 	testet die lagebeziehung von zwei kugeln im 3-dimensionalen raum.
	bedingungen: 	-
	parameter:		m0 und m1 sind die mittelpunkte der jeweiligen kugeln und r0 bzw. r1 die zugehoeruigen radien.
	rueckgabewert:	SCHNITT, wenn sie die spheren schneiden, IDENTITAET, wenn m0 = m1 und r0 = r1, KEINSCHNITT sonst.		
*/
MathStatus testStatusTwoSpheres(
		const Vertex4f& m0, float r0, 
		const Vertex4f& m1, float r1
		);
/*
	beschreibung: 	testet die lagebeziehung von zwei ebenen im 3-dimensionalen raum.
	bedingungen: 	-
	parameter:		die normalenvektoren n0 der ebene e0 und n1 der ebene e1.
	rueckgabewert:	PARALLEL, wenn n0 o n1 = 1.0f, SCHNITT sonst				
*/
MathStatus testStatusTwoPlanes(
		const Vector4f& n0,
		const Vector4f& n1
		);
/*
	beschreibung: 	berechnet den schnittpunkt einer geraden mit einer ebene.
	bedingungen: 	die gerade muss die ebene schneiden, sonst ist das ergebnis undefiniert.
	parameter:		eine gerade l und einen ebene p.
	rueckgabewert:	den schnittpunkt v der gerade l mit der ebene p.
*/
Vertex4f& intersectLineWithPlane(
		const Line &l, 
		const Plane &p
		);

Vertex4f& intersectLineWithPlane(
		const Vertex4f& positionLine,
		const Vector4f& directionalLine,
		const Vertex4f& positionPlane,
		const Vector4f& normalPlane
		);
		
std::list<Linesegment> intersect(Polygon &p0, Polygon &p1);

Linesegment& intersect(Triangle &t0, Triangle &t1) throw (MathStatus);

Linesegment& intersect(Plane &p0, Plane &p1);

void triangulate(Polygon &p);

#endif