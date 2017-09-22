#ifndef MYCPPMATH_H
#define MYCPPMATH_H

#include "include.h"
#include "immintrin.h"

#define PI 			3.14159265f
#define TODEGREE 	180.0f / PI
#define TORADIANS	PI / 180.0f
#define INVERSE360  1.0f / 360.0f
#define INVFOUR		1.0f / 4.0f
#define INVEIGHT	1.0f / 8.0f
#define INVSIXTEEN  1.0f / 16.0f

/*
	+-------------------------------------------------------------------+
	|																	|
	|								WRAPPER 							|
	|																	|
	+-------------------------------------------------------------------+
	
*/
/*
	basisklasse fuer eine 3x3 matrix (intern eine 3x4 matrix wegen den intrinsics). 
*/
class Matrix4f 
{
	public:
		Matrix4f();
		Matrix4f(
				float a0,
				float a1,
				float a2,
				float a3,
				float a4,
				float a5,
				float a6,
				float a7,
				float a8
				);
		~Matrix4f();
		float 	get(uint32_t row, uint32_t col) const;
		void 	set(uint32_t row, uint32_t col, float f);
		Matrix4f* 	operator*	(const Matrix4f &m) const;
		void 		operator*=	(const Matrix4f &m);
		Matrix4f* 	operator+ 	(const Matrix4f &m) const;
		void	 	operator+= 	(const Matrix4f &m);
		Matrix4f* 	operator- 	(const Matrix4f &m) const;
		void	 	operator-= 	(const Matrix4f &m);
		void	 	operator= 	(const Matrix4f &m) const;
		uint32_t 	operator== 	(const Matrix4f &m) const;
		uint32_t 	equals		(Matrix4f &m) const;
		void 		scale(float scalar);
	private:
		float *m_content;
};

/*
	basisklasse fuer einen 3-dimensionalen vektor (intern 4 dim. wegen der datenhaltung fuer intirinsics).
*/
class Vector4f 
{
	public:
		/*
			erzeugt einen Vector4f mit 4 float elementen, die in einem
			16-byte adress ausgerichteten array abgelegt werden.
		*/
		Vector4f();
		Vector4f(
				float f0,
				float f1,
				float f2,
				float f3
				);
		/*
			destructor.
		*/
		~Vector4f();
		/*
			gibt die anzahl an elementen zurueck (offensichlich immer 4).
		*/
		uint32_t dimension() const;
		/*
			liefert zugriff auf die einzelnen elemente, ohne die instanz 
			zu aendern.
		*/
		const float	operator[]	(uint32_t i) 	const;	
		/*
			addiert die gegebenen vektoren. liefert einen neuen vektor mit dem ergebnis, 
			der mit dem "new"-operator erzeugt wird!
			die methode wird mit der parallelen variante der vektoraddition
			ausgefuehrt.
		*/
		Vector4f* 	operator+	(Vector4f &v)	const;
		/*
			analog operator+.
		*/
		void 		operator+=	(Vector4f &v);
		/*
			analog operator+.
		*/
		Vector4f* 	operator-	(Vector4f &v) 	const;
		/*
			analog operator+.
		*/
		void 		operator-=	(Vector4f &v);
		/*
			liefert das kreuzprodukt zurueck. (LIEFERT DAS KREUZPRODUKT FUER 3F!!!)
		*/
		Vector4f* 	operator*	(Vector4f &v) 	const;
		/*
			weisst du aufrufenden objekt das kreuzprodukt zu.
		*/
		void 		operator*=	(Vector4f &v);
		/*
			zuweisungsoperator.
		*/
		void 		operator=	(Vector4f &v);
		/*
			vergleichsoperator. vergleicht die uebergebene referenz mit der eigenen.
		*/
		uint32_t	operator==	(Vector4f &v);
		/*
			vergleicht den inhalt: wenn gleich -> 0xFFFF sonst 0x0.
		*/
		uint32_t 	equals(Vector4f &v);
		/*
			skaliert den vektor
		*/
		void 		scale		(float scalar);
		/*
			weisst der position i den float t zu.
		*/
		void set(uint32_t i, float t);
		float angle(Vector4f &v);
		/*
			vektor in der konsole ausgeben.
		*/
		void printVector4f();
		void printlnVector4f();
	private:
		/*
			4-elementiges array (dynamische zuweisung wegen adresse).
		*/
		float *m_content;
		uint32_t m_dimension;
};

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

void addVectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n1
		);
		
void subVector4f(
		const float **a,
		const float **b, 
		float **c,
		uint32_t n0,
		uint32_t n1
		);

void subVectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n1
		);
				
void scaleVectorf(
		float *a,
		float s, 
		uint32_t n
		);

float lengthVectorf(
		const float *a,
		uint32_t n
		);

float inverseLengthVectorf(
		const float *a,
		uint32_t n
		);

void toUnitlengthVectorf(
		float *a, 
		uint32_t n
		);

float scalarproductVector4f(
		const float *a, 
		const float *b, 
		float *c, 
		uint32_t n
		);
				
void crossproductVector4f(
		float *a, 
		float *b, 
		float *c
		);

float angleVector4f(
		const float *a,
		const float *b
		);

uint32_t equalVectorf(
		float *a,
		float *b,
		uint32_t n
		);
		
#endif