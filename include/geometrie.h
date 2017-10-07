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
	beschreibung: 	testet die lagebeziehung von einem punkt zu einer ebene.
	bedingungen: 	-
	parameter:		v, der punkt, welcher getestet werden soll, p der stuetzvektor der ebene und n dessen normalenvektor.
	rueckgabewert:	einen wert x >= 0, wenn v in (v - p) o n = 0, x < 0 sonst.	
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