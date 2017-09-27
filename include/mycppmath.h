#ifndef MYCPPMATH_H
#define MYCPPMATH_H

#include "include.h"
#include "immintrin.h"

#define PI 					3.14159265f
#define TODEGREE 			180.0f / PI
#define TORADIANS			PI / 180.0f
#define INVERSE360  		1.0f / 360.0f
#define INVFOUR				1.0f / 4.0f
#define INVEIGHT			1.0f / 8.0f
#define INVSIXTEEN  		1.0f / 16.0f

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
		float 			get(uint32_t row, uint32_t col) const;
		void 			set(uint32_t row, uint32_t col, float f);
		Matrix4f* 		operator*	(const Matrix4f &m) const;
		void 			operator*=	(const Matrix4f &m);
		Matrix4f* 		operator+ 	(const Matrix4f &m) const;
		void	 		operator+= 	(const Matrix4f &m);
		Matrix4f* 		operator- 	(const Matrix4f &m) const;
		void	 		operator-= 	(const Matrix4f &m);
		void	 		operator= 	(const Matrix4f &m) const;
		uint32_t 		operator== 	(const Matrix4f &m) const;
		uint32_t 		equals		(Matrix4f &m) const;
		void 			scale		(float scalar);
		float* 			content		() const;
		float 			det			() const;
		void initializeAsRotationmatrix(
				Axis a, 
				float angleX, 
				float angleY, 
				float angleZ
				);
		/*
			methoden zur synchronisation.
			ein vektor kann immer von meheren lesern
			gelesen werden, aber nur von einem schreiber
			bearbeitet werden.
			die aufrufe sind BLOCKIEREND.
		*/
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
		float *m_content;
		std::mutex *m_lock;
		uint32_t m_readers,m_writer;
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
				float f2
				);
		/*
			destructor.
		*/
		~Vector4f();
		/*
			gibt die anzahl an elementen zurueck (immer 3).
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
		Vector4f* 	operator*	(Matrix4f &m) 	const;
		/*
			weisst den aufrufenden objekt das kreuzprodukt zu.
		*/
		void 		operator*=	(const Vector4f &v);
		void 		operator*=	(const Matrix4f &m);
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
		float get(uint32_t i);
		/*
			berechnet den winkel zwischen dem aufrufenden und dem uebergebenen
			vektor.
		*/
		float angle(Vector4f &v);
		
		float* content();
		/*
			vektor in der konsole ausgeben.
		*/
		void printVector4f();
		void printlnVector4f();
		/*
			methoden zur synchronisation.
			ein vektor kann immer von meheren lesern
			gelesen werden, aber nur von einem schreiber
			bearbeitet werden.
			die aufrufe sind BLOCKIEREND.
		*/
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
			4-elementiges array (dynamische zuweisung wegen adresse).
		*/
		float *m_content;
		uint32_t m_dimension;
		uint32_t m_readers,m_writer;
		std::mutex *m_lock;
};

/*
	diese funktionen sollten fuer berechnungen genutzt werden.
	sie erzeugen keinen neuen instanzen und vermeiden somit eine teuere 
	speicher allokation!
*/
/*
	addition.
*/
void addVector4f(const Vector4f* v0, const Vector4f* v1, Vector4f* result);
/*
	subtraktion
*/
void subVector4f(Vector4f* v0, Vector4f* v1, Vector4f* result);
/*
	kreuzprodukt.
*/
void crossproductVector4f(Vector4f* v0, Vector4f* v1, Vector4f* result);
/*
	multipliziert die gegebene matrix mit dem gegebenen vektor und speichert das 
	ergebnis im resultvektor.
*/
void multiplyVector4fMatrix4f(Vector4f *v0, Matrix4f *m0, Vector4f* result);

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
		float *a, 
		float *b, 
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
#endif