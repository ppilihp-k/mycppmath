#ifndef MATRIX4F_H
#define MATRIX4F_H

#include "mycppmath.h"
#include "vector4f.h"

class Vector4f;

/*
	basisklasse fuer eine 3x3 matrix (intern eine 3x4 matrix wegen den intrinsics). 
*/
class Matrix4f 
{
	public:
		/*
			move konstruktor. verschiebt die daten aus m in die aufgerufene objektinstanz
			und löscht m dann!
		*/
		Matrix4f(Matrix4f &&m);
		/*
			kopierkonstruktor. kopiert die daten aus m in die aufgerufene objektinstanz.
			wichtig: in diesem konstruktor wird eine 16-byte ausgerichtete malloc funktion
			aufgerufen -> sehr zeitintensiv!
		*/
		Matrix4f(const Matrix4f &m);
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
		/*
			getter / setter.
		*/
		float 			get(uint32_t row, uint32_t col) const;
		void 			set(uint32_t row, uint32_t col, float f);
		/*
			matrixmultiplikation.
		*/
		Matrix4f& 		operator*	(const Matrix4f &m) const;
		Vector4f& 		operator*	(Vector4f &m) const;
		/*
			matrixmultiplikation mit zuweisung in die aufgerufene instanz.
		*/
		void 			operator*=	(const Matrix4f &m);
		/*
			addition und subtraktion.
		*/
		Matrix4f& 		operator+ 	(const Matrix4f &m) const;
		void	 		operator+= 	(const Matrix4f &m);
		Matrix4f& 		operator- 	(const Matrix4f &m) const;
		void	 		operator-= 	(const Matrix4f &m);
		/*
			zuweisungsoperator (kopiert die daten aus m in die aufgerufene objektinstanz).
		*/
		Matrix4f&  		operator= 	(const Matrix4f &m);
		//Matrix4f& 		operator= 	(Matrix4f &&m) = default;
		/*
			vergleichsoperator. testet, of die referenzen gleich sind.
		*/
		uint32_t 		operator== 	(const Matrix4f &m) const;
		/*
			vergleichsfunktion fuer den inhalt der objekte.
		*/
		uint32_t 		equals		(Matrix4f &m) const;
		/*
			elementweise skalierung der objektdaten.
		*/
		void 			scale		(float scalar);
		/*
			das array, welches diese matrix repraesentiert.
		*/
		float* 			content		() const;
		/*
			berechnet die determinante dieser matrix.
		*/
		float 			det			() const;
		/*
		void initializeAsRotationmatrix(
				Axis a, 
				float angleX, 
				float angleY, 
				float angleZ
				);
		*/
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
		float *m_content;
		std::mutex m_lock;
		uint32_t m_readers,m_writer;
};

#endif