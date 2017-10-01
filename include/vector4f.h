#ifndef VECTOR4F_H
#define VECTOR4F_H

#include "mycppmath.h"
#include "matrix4f.h"

#define VECTORMASK ((uint32_t)1) << 32
#define INVERSEVECTORMASK ~(((uint32_t)1) << 32)

class Matrix4f;

/*
	basisklasse fuer einen 3-dimensionalen vektor (intern 4 dim. wegen der datenhaltung fuer intirinsics).
*/
class Vector4f 
{
	public:
		Vector4f(Vector4f &&v);
		Vector4f(const Vector4f &v);
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
		uint32_t isVertex() const;
		void setVertex();
		void setVector();
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
		Vector4f& 	operator+	(Vector4f &v)	const;
		/*
			analog operator+.
		*/
		void 		operator+=	(Vector4f &v);
		/*
			analog operator+.
		*/
		Vector4f& 	operator-	(Vector4f &v) 	const;
		/*
			analog operator+.
		*/
		void 		operator-=	(Vector4f &v);
		/*
			liefert das kreuzprodukt zurueck. (LIEFERT DAS KREUZPRODUKT FUER 3F!!!)
		*/
		Vector4f& 	operator*	(Vector4f &v) 	const;
		Vector4f& 	operator*	(Matrix4f &m) 	const;
		/*
			weisst den aufrufenden objekt das kreuzprodukt zu.
		*/
		void 		operator*=	(const Vector4f &v);
		void 		operator*=	(Matrix4f &m);
		/*
			zuweisungsoperator.
		*/
		Vector4f&	operator=	(Vector4f &v);
		//Vector4f&	operator=	(Vector4f &&v);
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
		std::string toString();
	private:
		/*
			4-elementiges array (dynamische zuweisung wegen adresse).
		*/
		float *m_content;
		uint32_t m_dimension;
		uint32_t m_readers,m_writer;
		std::mutex m_lock;
};

#endif