#ifndef MYCPPMATH_H
#define MYCPPMATH_H

#include "include.h"
#include "immintrin.h"
#include "matrix4f.h"
#include "vector4f.h"

#define PI			3.14159265f
#define TODEGREE	180.0f / PI
#define TORADIANS	PI / 180.0f
#define INVERSE360  1.0f / 360.0f
#define INVFOUR		1.0f / 4.0f
#define INVEIGHT	1.0f / 8.0f
#define INVSIXTEEN  1.0f / 16.0f

class Matrix4f;
class Vector4f;

/*
	+-------------------------------------------------------------------+
	|																	|
	|								WRAPPER 							|
	|																	|
	+-------------------------------------------------------------------+
	
	die klassen sind extrem zeitintensiv zu erzeugen! 
	es sollte zur laufzeit unbedingt darauf geachtet werden, keine zu 
	erstellen, um eine gute leistung zu erzielen!
	
*/

enum Axis{X=0,Y=1,Z=2,XY=3,YX=4,XZ=5,ZX=6,YZ=7,ZY=8,XYZ=9,XZY=10,ZXY=11,ZYX=12,YXZ=13,YZX=14};


/*
	multipliziert die gegebene matrix mit dem gegebenen vektor und speichert das 
	ergebnis im resultvektor.
*/
//void multiplyVector4fMatrix4f(Vector4f *v0, Matrix4f *m0, Vector4f* result);

/*
	+-------------------------------------------------------------------+
	|																	|
	|						ALLGEMEIN HINWEISE							|
	|																	|
	+-------------------------------------------------------------------+
	
	die folgenden funktionen muessen mit 16-byte ausgerichteten adressen 
	aufgerufen werden -> ansonsten fuehrt ein aufruf zu einem fehler (programmstop)!
	FUER EINE ZUVERLAESSIGE FUNKTIONSWEISE SOLLTEN DIE WRAPPERMETHODEN GENUTZT WERDEN!
*/
void addVectorf(
		float **a, 
		float **b, 
		float **c,
		uint32_t n0,
		uint32_t n1
		);
/*
	beschreibung: 	addiert den vektor b zum vektor a -> c = a + b
	bedingungen: 	length(a) = length(b) = length(c) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/
void addVectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n1
		);
		
void subVectorf(
		const float **a,
		const float **b, 
		float **c,
		uint32_t n0,
		uint32_t n1
		);
/*
	beschreibung: 	subtrahiert den vektor b vom vektor a -> c = a - b
	bedingungen: 	length(a) = length(b) = length(c) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/	
void subVectorf(
		const float *a, 
		const float *b, 
		float *c,
		uint32_t n1
		);
/*
	beschreibung: 	skaliert den vektor.
	bedingungen: 	length(a) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/			
void scaleVectorf(
		float *a,
		float s, 
		uint32_t n
		);
/*
	beschreibung: 	berechnet die laenge des vektors a -> |a|.
	bedingungen: 	length(a) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/	
float lengthVectorf(
		const float *a,
		uint32_t n
		);
/*
	beschreibung: 	berechnet die inverse laenge des vektors a -> 1 / |a|.
	bedingungen: 	length(a) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/	
float inverseLengthVectorf(
		const float *a,
		uint32_t n
		);
/*
	beschreibung: 	transformiert einen vektor a zu einem vektor mit der laenge 1, 
					der in die selbe richtung zeigt.
	bedingungen: 	length(a) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/	
void toUnitlengthVectorf(
		float *a, 
		uint32_t n
		);
/*
	beschreibung: 	kreuzprodukt fuer zwei vektoren a und b.
	bedingungen: 	length(a) = length(b) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	einen float, dessen wert dem skalarprodukt von a und b entspricht.					
*/	
float scalarproductVector4f(
		const float *a, 
		const float *b
		);
/*
	beschreibung: 	kreuzprodukt fuer zwei vektoren a und b.
	bedingungen: 	-
	rueckgabewert:	einen float, dessen wert dem skalarprodukt von a und b entspricht.					
*/	
float scalarproductVector4f(
		const __m128 *a, 
		const __m128 *b
		);
/*
	beschreibung: 	kreuzprodukt fuer zwei vektoren a und b -> c = a o b
	bedingungen: 	length(a) = length(b) = length(c) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-					
*/		
void crossproductVector4f(
		const float *a, 
		const float *b, 
		float *c
		);
/*
	beschreibung: 	berechnet den winkel, den a und b einschliessen.
	bedingungen: 	length(a) = length(b) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	ein float, dessen wert dem von a und b eingeschlossen winkel entspricht
*/
float angleVector4f(
		const float *a,
		const float *b
		);
/*
	beschreibung: 	gleichheitstest fuer zwei vektoren -> a = b gdw. a(i) = b(i) i€{0,1,2,3}.
	bedingungen: 	length(a) = length(a) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	0xFFFFFFFF, wenn gleich, sonst 0x0					
*/
uint32_t equalVectorf(
		const float *a,
		const float *b,
		uint32_t n
		);
/*
	beschreibung: 	multipliziert m1 von rechts an m0 -> m2 = m0 * m1.
	bedingungen: 	length(m0) = length(m1) = length(m2) = 16, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-
*/		
void multiplyMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		);
/*
	beschreibung: 	elementweise addition.
	bedingungen: 	length(m0) = length(m1) = length(m2) = 16, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-
*/
void addMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		);
/*
	beschreibung: 	elementweise subtraktion.
	bedingungen: 	length(m0) = length(m1) = length(m2) = 16, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-
*/
void subMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		);		
/*
	beschreibung: 	berechnet die determinante der matrix.
	bedingungen: 	length(m) = 16, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	einen float, dessen wert der determinaten von m entspricht.
*/
float detMatrix4f(
		float *m	
		);
/*
	beschreibung: 	multipliziert den vektor v0 von rechts an die matrix m0 -> v1 = m0 * v1.
	bedingungen: 	length(m0) = 16, 
					length(v0) = length(v1) = 4, 
					nur fuer 16-byte ausgerichtete adressen.
	rueckgabewert:	-
*/		
void multiplyVector4fMatrix4f(
		float *m0, 
		float *v0, 
		float *v1
		);

		
void copyVector4f(
		float* f0, 
		const float* f1
		);
		
uint32_t sign(float f);
#endif