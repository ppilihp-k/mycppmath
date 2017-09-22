#include "..\include\mycppmath.h"
#include <chrono> 

/*
	+-------------------------------------------------------------------+
	|																	|
	|								WRAPPER 							|
	|																	|
	+-------------------------------------------------------------------+
	
*/

/*
	+-------------------------------------------------------------------+
	|																	|
	|								MATRIX	 							|
	|																	|
	+-------------------------------------------------------------------+
	
*/

Matrix4f::Matrix4f()
{
	m_content = (float*) _aligned_malloc(16 * sizeof(float), 16);
	for(uint32_t i = 0;i < 16;i++)
	{
		m_content[i] = 0.0f;
	}
};

Matrix4f::Matrix4f(
		float a0,
		float a1,
		float a2,
		float a3,
		float a4,
		float a5,
		float a6,
		float a7,
		float a8
		)
{
	m_content = (float*) _aligned_malloc(12 * sizeof(float), 16);	
	m_content[0] = a0;
	m_content[1] = a1;
	m_content[2] = a2;
	m_content[3] = 0.0f;
	m_content[4] = a3;
	m_content[5] = a4;
	m_content[6] = a5;
	m_content[7] = 0.0f;
	m_content[8] = a6;
	m_content[9] = a7;
	m_content[10] = a8;
	m_content[11] = 0.0f;
};

Matrix4f::~Matrix4f()
{
	delete[] m_content;
};

float Matrix4f::get(uint32_t row, uint32_t col) const
{
	return m_content[row * 4 + col];
};

void Matrix4f::set(uint32_t row, uint32_t col, float f)
{
	m_content[row * 4 + col] = f;
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|								VECTOR	 							|
	|																	|
	+-------------------------------------------------------------------+
	
*/
Vector4f::Vector4f()
{
	m_dimension = 4;
	/*
		m_content muss eine 16-byte ausgerichtete adresse haben, damit es von sse und avx profitieren kann!
	*/
	m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
};

Vector4f::Vector4f(
		float f0,
		float f1,
		float f2,
		float f3
		)
{
	m_dimension = 4;
	m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
	m_content[0] = f0;
	m_content[1] = f1;
	m_content[2] = f2;
	m_content[3] = f3;
};

Vector4f::~Vector4f()
{
	delete[] m_content;
};

uint32_t Vector4f::dimension() const
{
	return m_dimension;
};

const float Vector4f::operator[](uint32_t i) const
{
	return m_content[i];
};

void Vector4f::set(uint32_t i, float t)
{
	m_content[i] = t;
};

Vector4f* Vector4f::operator+(Vector4f &v)	const
{
	Vector4f *result = new Vector4f();
	addVectorf(m_content,v.m_content,(*result).m_content,((uint32_t)4));
	return result;
};

void Vector4f::operator+=(Vector4f &v)
{
	addVectorf(m_content,v.m_content,m_content,((uint32_t)4));
};

Vector4f* Vector4f::operator-(Vector4f &v) 	const
{
	Vector4f *result = new Vector4f();
	subVectorf(m_content,v.m_content,(*result).m_content,((uint32_t)4));
	return result;
};

void Vector4f::operator-=(Vector4f &v)
{
	subVectorf(m_content,v.m_content,m_content,((uint32_t)4));
};

Vector4f* Vector4f::operator*(Vector4f &v) 	const
{
	Vector4f* result = new Vector4f();
	crossproductVector4f(m_content,v.m_content,(*result).m_content);
	return result;
};

void Vector4f::operator*=(Vector4f &v)
{
	crossproductVector4f(m_content,v.m_content,m_content);
};

void Vector4f::scale(float scalar)
{
	scaleVectorf(m_content,scalar,4);
};

void Vector4f::printVector4f()
{
	printf("Vector4f<%f,%f,%f,%f>",m_content[0],m_content[1],m_content[2],m_content[3]);
};

void Vector4f::printlnVector4f()
{
	printf("Vector4f<%f,%f,%f,%f>\n",m_content[0],m_content[1],m_content[2],m_content[3]);
};

void Vector4f::operator=(Vector4f &v)
{
	m_content[0] = v.m_content[0];
	m_content[1] = v.m_content[1];
	m_content[2] = v.m_content[2];
	m_content[3] = v.m_content[3];
};

uint32_t Vector4f::operator==(Vector4f &v)
{
	return this == &v ? 0xFFFFFFFF : 0x0;
};

uint32_t Vector4f::equals(Vector4f &v)
{
	return equalVectorf(m_content,v.m_content,4);
};

float Vector4f::angle(Vector4f &v)
{
	return angleVector4f(m_content,v.m_content);
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|							ALLGEMEIN								|
	|																	|
	+-------------------------------------------------------------------+

	alle funktionen muessen mit arrays einer groesse eines vielfachen von 4 aufgerufen werden!	
	ausserdem muessen alle floatarrays 16-byte ausgerichtete adressen aufweisen!
	
*/

static float* alignAndCopy(const float *a, uint32_t n)
{
	float *b = (float*) _aligned_malloc(n * sizeof(float), 16);
	//float b[] __attribute__ ((aligned (16))) = new float[n];
	for(uint32_t i = 0;i < n;i++)
	{
		b[i] = a[i];
	}
	return b;
};

uint32_t equalVectorf(
		float *a,
		float *b,
		uint32_t n
		)
{
	__m128 dst;
	uint32_t iterations = n * INVFOUR;
	for(uint32_t i = 0;i < iterations;i++, a += 4, b += 4)
	{
		__m128 dst = _mm_cmpneq_ps(*((__m128*)a),*((__m128*)b));
		if(dst[0] || dst[1] || dst[2] || dst[3]){
			return 0;
		}
	}
	return 0xFFFFFFFF;
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|							ADDITION								|
	|																	|
	+-------------------------------------------------------------------+
*/

/*
	serielle hilfsfunktion für die addition
*/
static void genericAddVectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n
		)
{
	for(uint32_t i = 0;i < n;i++)
	{
		c[i] = a[i] + b[i];
	}
};

/*
	parallele hilfsfunktion für die addition mit 16 parallelen elementen.
*/
static void parallelAdd512Vectorf(
		float **a, 
		float **b, 
		float **c,
		uint32_t n0,
		uint32_t n1
		)
{	
/*
	__m512 *ptra = (__m512*)a;
	__m512 *ptrb = (__m512*)b;
	float *aa = (float*) _aligned_malloc(16 * sizeof(float), 16);
	float *bb = (float*) _aligned_malloc(16 * sizeof(float), 16);
	float *cc = (float*) _aligned_malloc(16 * sizeof(float), 16);
	uint32_t iterations = (uint32_t)(n * INVSIXTEEN);	
	
	for(uint32_t i = 0;i < iterations;i++)
	{
		for(uint32_t j = 0;j < 16;j++)
		{
			aa[j] = a[i * 16 + j][j];
			bb[j] = b[i * 16 + j];
		}
		*ptra = _mm512_load_ps(aa);
		*ptrb = _mm512_load_ps(bb);
		_mm512_store_ps(cc, _mm512_add_ps(*ptra,*ptrb));
		for(uint32_t j = 0;j < 16;j++)
		{
			c[i * 16 + j] = cc[j];
		}
	}
*/
};

/*
	parallele hilfsfunktion für die addition.
*/
static void parallelAdd128Vectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n
		)
{	
	__m128 *ptra = (__m128*)a;
	__m128 *ptrb = (__m128*)b;
	uint32_t iterations = (uint32_t)(n * INVFOUR);	
	for(uint32_t i = 0;i < iterations;i++)
	{
		_mm_store_ps(c, _mm_add_ps(*ptra,*ptrb));
		ptra++;
		ptrb++;
		c += 4;
	}
};
/*
	vektor a und vektor b addieren und das ergebnis in vektor c speichern
	a + b = c
	die werte in a und b werden von dieser funktion nich geaendert
*/
void addVectorf(
		float **a, 
		float **b, 
		float **c,
		uint32_t n0,
		uint32_t n1
		)
{	
	for(uint32_t i = 0;i < n0;i++)
	{	
		parallelAdd128Vectorf(a[i], b[i], c[i], n1);
	}
};

void addVectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n1
		)
{
	parallelAdd128Vectorf(a, b, c, n1);
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|							SUBTRAKTION								|
	|																	|
	+-------------------------------------------------------------------+
*/

/*
	serielle hilfsfunktion für die subtraktion
*/
static void genericSubVectorf(
		float *a, 
		float *b, 
		float *c, 
		uint32_t n
		)
{
	for(uint32_t i = 0;i < n;i++){
		c[i] = a[i] - b[i];
	}
};

/*
	generische subtraktion eines einzelnen vektors.
*/
void subVectorf(
		float *a, 
		float *b, 
		float *c,
		uint32_t n1
		)
{
	genericSubVectorf(a,b,c,n1);
};

/*
	parallele hilfsfunktion für die subtraktion
*/
static void parallelSub128Vector4f(
		float *a, 
		float *b, 
		float *c, 
		uint32_t n
		)
{
	__m128 *ptra = (__m128*)a;
	__m128 *ptrb = (__m128*)b;
	uint32_t iterations = n * INVFOUR;
	for(uint32_t i = 0;i < iterations;i++,++ptra,++ptrb,a +=4,b+=4,c+=4)
	{
		_mm_store_ps(c, _mm_sub_ps(*ptra,*ptrb));
	}	
};

/*
	a[i] - b[i] = c[i], für i < n0 und n1 ist die laenge eines einzelnen vektors.
*/
void subVector4f(
		float **a, 
		float **b, 
		float **c, 
		uint32_t n0, 
		uint32_t n1
		)
{	
	for(uint32_t i = 0;i < n0;i++)
	{
		parallelSub128Vector4f(a[i], b[i], c[i], n1);
	}
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|							SKALIEREN								|
	|																	|
	+-------------------------------------------------------------------+
*/

/*
	skaliert den vektor a.
	nach dem funktionsaufruf ist der vektor a und das skalar s angepasst
*/
void scaleVectorf(float *a,float s, uint32_t n)
{
	uint32_t iterations = n * INVFOUR;
	__m128* ptra = (__m128*)a;
	__m128 scalar;
	for(uint32_t i = 0;i < iterations;i++, ++ptra, a += 4)
	{
		scalar = _mm_set_ps(s,s,s,s);
		_mm_store_ps(a,_mm_mul_ps(*ptra,scalar));
	}
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|								LAENGE								|
	|																	|
	+-------------------------------------------------------------------+
*/

float genericLengthVectorf(const float *a, uint32_t n)
{
	float result = 0.0f;
	for(uint32_t i = 0;i < n;i++){
		result += a[i];
	}
	return sqrt(result);
};

static void parallelLength(const float *a,float *b, uint32_t n)
{
	/*
	__m128* ptra = (__m128*)a;
	uint32_t iterations = (uint32_t)floor(n * INVFOUR);
	for(uint32_t i = 0;i < iterations;i++,++ptra,a += 4,b++)
	{
		__m128 dst0 = _mm_add_ps();
	} 
	*/
};

/*
	berechnet die laenge der vektoren aus a und speichert das ergebnis in b.
	b muss mindestens 4 mal so klein sein wie a.
*/
float lengthVectorf(const float *a, uint32_t n)
{
	return genericLengthVectorf(a,n);
};

static float serialInverseLength(const float *a, uint32_t n)
{
	float result = 0.0f;
	for(uint32_t i = 0;i < n;i++){
		result += a[i];
	}
	return 1.0f / sqrt(result);
};

float inverseLengthVectorf(const float *a, uint32_t n)
{
	return serialInverseLength(a,n);
};


/*
	macht aus a einen einheitsvektor
*/
void toUnitlengthVectorf(float *a, uint32_t n)
{
	scaleVectorf(a,inverseLengthVectorf(a,n),n);
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|						SKALARPROPDUKT								|
	|																	|
	+-------------------------------------------------------------------+
*/

/*
	berechnet das skalarprodukt.
	a und b muessen eine laenge eines vielfacvhen von 4 haben, c muss mindestens so lang sein,
	wie ein viertel der laenge von a oder b
*/

static float genericScalarproduct(		
		const float *a, 
		const float *b
		)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
};

float scalarproductVector4f(
		const float *a, 
		const float *b
		)
{
	__m128 dst = _mm_mul_ps(*((__m128*)a),*((__m128*)b));
	return dst[0] + dst[1] + dst[2] + dst[3];
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|							KREUZPRODUKT							|
	|																	|
	+-------------------------------------------------------------------+
*/

/*
	
*/
void genericCrossproductVector4f(
		const float *a, 
		const float *b, 
		float *c
)
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	c[3] = 0.0f;
};

static void parallelCrossproductVector4f(
		float *a, 
		float *b, 
		float *c
		)
{
	_mm_store_ps(
			c,
			_mm_sub_ps(
					_mm_mul_ps(
							_mm_shuffle_ps(*((__m128*)a), *((__m128*)a), _MM_SHUFFLE(3, 1, 2, 0)), 
							_mm_shuffle_ps(*((__m128*)b), *((__m128*)b), _MM_SHUFFLE(3, 2, 0, 1))
							),
					_mm_mul_ps(
							_mm_shuffle_ps(*((__m128*)a), *((__m128*)a), _MM_SHUFFLE(3, 2, 0, 1)), 
							_mm_shuffle_ps(*((__m128*)b), *((__m128*)b), _MM_SHUFFLE(3, 1, 2, 0))
							)
					)
				);
	
};

/*
	einfaches kreuzprodukt der ersten ->drei<- elemente!.
	berechnet einen zu beiden vektoren senkrecht stehenden vektor.
	noch keine implementierung fuer eine parallele abarbeitung!
*/
void crossproductVector4f(
		float *a, 
		float *b, 
		float *c
		)
{
	parallelCrossproductVector4f(a,b,c);
};

/*
	+-------------------------------------------------------------------+
	|																	|
	|								WINKEL								|
	|																	|
	+-------------------------------------------------------------------+
*/

static float genericAngleVector4f(
		const float *a,
		const float *b
		)
{
	return acos((genericScalarproduct(a,b) / (genericLengthVectorf(a,4) * genericLengthVectorf(b,4))) * INVERSE360) * TODEGREE;
};

static float parallelAngleVector4f(
		const float *a,
		const float *b
		)
{
	return acos(scalarproductVector4f(a,b) * inverseLengthVectorf(a,4) * inverseLengthVectorf(b,4) * INVERSE360) * TODEGREE;
};

/*
	berechnet den durch die vektoren a und b eingeschlossenen winkel.
	der winkel muss zwischen 0 und 360 grad liegen, ansonsten wir eine exception geworfen!
*/
float angleVector4f(
		const float *a,
		const float *b
		)
{	
	return parallelAngleVector4f(a,b);
};