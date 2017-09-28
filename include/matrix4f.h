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
		Vector4f* 		operator*	(Vector4f &m) const;
		void 			operator*=	(const Matrix4f &m);
		Matrix4f* 		operator+ 	(const Matrix4f &m) const;
		void	 		operator+= 	(const Matrix4f &m);
		Matrix4f* 		operator- 	(const Matrix4f &m) const;
		void	 		operator-= 	(const Matrix4f &m);
		void	 		operator= 	(const Matrix4f &m) const;
		uint32_t 		operator== 	(const Matrix4f &m) const;
		uint32_t 		equals		(Matrix4f &m) const;
		void 			scale		(float scalar);
		float* 			content		();
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
	private:
		float *m_content;
		std::mutex *m_lock;
		uint32_t m_readers,m_writer;
};

#endif