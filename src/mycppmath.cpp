#include "..\include\mycppmath.h"
#include <chrono> 

/*
	+-------------------------------------------------------------------+
	|																	|
	|							C-Style 								|
	|																	|
	+-------------------------------------------------------------------+

	für effizientes rechnen sollten die folgenden funktionen genutzt werden!
	hier muss sich der nutzer selbst um die instantiierung der elementinstanzen kuemmern.
	So kann vermieden werden, dass unnoetige temporaere instanzen erzeugt werden.
	(das erzeugen einer objectinstanz von Vector4f oder Matrix4f dauert extrem lange...)
*/
void addVector4f(Vector4f *v0, Vector4f *v1, Vector4f *result)
{
	addVectorf(v0->content(),v1->content(),result->content(),4);
};

void subVector4f(Vector4f *v0, Vector4f *v1, Vector4f *result)
{
	subVectorf(v0->content(),v1->content(),result->content(),4);
};

void crossproductVector4f(Vector4f *v0, Vector4f *v1, Vector4f *result)
{
	crossproductVector4f(v0->content(),v1->content(),result->content());
};

void multiplyVector4fMatrix4f(Vector4f *v0, Matrix4f *m0, Vector4f* result)
{
	multiplyVector4fMatrix4f(v0->content(),m0->content(),result->content());
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

static float* alignAndCopy16Byte(const float *a, uint32_t n)
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
		const float *a,
		const float *b,
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
		const float *a, 
		const float *b, 
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
		const float *a, 
		const float *b, 
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
void subVectorf(
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
		result += pow(a[i],2);
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
	return result == 0.0f ? 0.0f : 1.0f / sqrt(result);
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
float scalarproductVector4f(
		const __m128 *a, 
		const __m128 *b
		)
{
	
	__m128 dst = _mm_mul_ps(*a,*b);
	__m128 res = _mm_add_ps(_mm_permute_ps(_mm_add_ps(_mm_permute_ps(dst, 0x1B), dst), 0xB1), dst);
	return _mm_cvtss_f32(res);
};

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
	const __m128 dst = _mm_mul_ps(*((__m128*)a),*((__m128*)b));
	const __m128 val = _mm_add_ps(dst, _mm_movehl_ps(dst, dst));
	float result = _mm_cvtss_f32(_mm_add_ss(val, _mm_shuffle_ps(val, val, 1)));
	return result;
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
		const float *a, 
		const float *b, 
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
		const float *a, 
		const float *b, 
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

/*
	+-------------------------------------------------------------------+
	|																	|
	|						MATRIXMULTIPLIKATION								|
	|																	|
	+-------------------------------------------------------------------+
*/

static void genericMultiplyMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		)
{
	float arr[11];
	arr[0] = 	m0[0] * m1[0] + m0[1] * m1[4] + m0[2] * m1[8];
	arr[1] = 	m0[0] * m1[1] + m0[1] * m1[5] + m0[2] * m1[9];
	arr[2] = 	m0[0] * m1[2] + m0[1] * m1[6] + m0[2] * m1[10];
	arr[4] = 	m0[4] * m1[0] + m0[5] * m1[4] + m0[6] * m1[8];
	arr[5] = 	m0[4] * m1[1] + m0[5] * m1[5] + m0[6] * m1[9];
	arr[6] = 	m0[4] * m1[2] + m0[5] * m1[6] + m0[6] * m1[10];
	arr[8] = 	m0[8] * m1[0] + m0[9] * m1[4] + m0[10] * m1[8];
	arr[9] = 	m0[8] * m1[1] + m0[9] * m1[5] + m0[10] * m1[9];
	arr[10] = 	m0[8] * m1[2] + m0[9] * m1[6] + m0[10] * m1[10];
	for(uint32_t i = 0;i < 11;i++)
	{
		m2[i] = arr[i];
	}
	m2[12] = 0.0f;
	m2[13] = 0.0f;
	m2[14] = 0.0f;
	m2[15] = 0.0f;
};

static void parallelMultiplyMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		)
{
	__m128 mulresult,valval,result;
	__m128 row01 = _mm_load_ps(m0);
    __m128 row02 = _mm_load_ps(m0 + 4);
    __m128 row03 = _mm_load_ps(m0 + 8);
    __m128 row04 = _mm_load_ps(m0 + 12);
	_MM_TRANSPOSE4_PS(row01, row02, row03, row04);
	
	__m128 row11 = _mm_load_ps(m1);
    __m128 row12 = _mm_load_ps(m1 + 4);
    __m128 row13 = _mm_load_ps(m1 + 8);
    __m128 row14 = _mm_load_ps(m1 + 12);
	
	m2[0] 	= scalarproductVector4f(&row01,&row11);
	m2[1] 	= scalarproductVector4f(&row01,&row12);
	m2[2] 	= scalarproductVector4f(&row01,&row13);
	m2[3] 	= scalarproductVector4f(&row01,&row14);
	m2[4] 	= scalarproductVector4f(&row02,&row11);
	m2[5] 	= scalarproductVector4f(&row02,&row12);
	m2[6] 	= scalarproductVector4f(&row02,&row13);
	m2[7] 	= scalarproductVector4f(&row02,&row14);
	m2[8] 	= scalarproductVector4f(&row03,&row11);
	m2[9] 	= scalarproductVector4f(&row03,&row12);
	m2[10] 	= scalarproductVector4f(&row03,&row13);
	m2[11] 	= scalarproductVector4f(&row03,&row14);
	m2[12] 	= scalarproductVector4f(&row04,&row11);
	m2[13] 	= scalarproductVector4f(&row04,&row12);
	m2[14] 	= scalarproductVector4f(&row04,&row13);
	m2[15] 	= scalarproductVector4f(&row04,&row14);	
};

void multiplyMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		)
{
	genericMultiplyMatrix4f(m0,m1,m2);
};

static void genericAddMatrix(
		const float *m0, 
		const float *m1, 
		float *m2, 
		uint32_t n)
{
	for(uint32_t i = 0;i < n;i++)
	{
		m2[i] = m0[i] + m1[i];
	}	
};

static void parallelAddMatrix4f(
		float *m0, 
		float *m1, 
		float *m2		
		)
{
	float *ptr0,*ptr1,*ptr2;
	ptr0 = m0;
	ptr1 = m1;
	ptr2 = m2;
	for(uint32_t i = 0;i < 4;i++, ptr0 += 4, ptr1 += 4, ptr2  += 4)
	{
		_mm_store_ps(ptr2,_mm_add_ps(*((__m128*)ptr0),*((__m128*)ptr1)));
	}
};

void addMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		)
{
	parallelAddMatrix4f(m0,m1,m2);
};	

static void parallelSubMatrix4f(
		float *m0, 
		float *m1, 
		float *m2		
		)
{
	float *ptr0,*ptr1,*ptr2;
	ptr0 = m0;
	ptr1 = m1;
	ptr2 = m2;
	for(uint32_t i = 0;i < 4;i++, ptr0 += 4, ptr1 += 4, ptr2 += 4)
	{
		_mm_store_ps(ptr0,_mm_sub_ps(*((__m128*)ptr1),*((__m128*)ptr2)));
	}
};

static void genericSubMatrix(
		float *m0, 
		float *m1, 
		float *m2, 
		uint32_t n)
{
	for(uint32_t i = 0;i < n;i++)
	{
		m2[i] = m0[i] - m1[i];
	}	
};

void subMatrix4f(
		float *m0, 
		float *m1, 
		float *m2
		)
{
	parallelSubMatrix4f(m0,m1,m2);
};	

static float genericDetMatrix4f(
		float *m
		)
{
		return 	m[0] * m[5] * m[10] + 
				m[1] * m[6] * m[8] + 
				m[2] * m[4] * m[9] 
				- m[2] * m[5] * m[8] 
				- m[1] * m[4] * m[10] 
				- m[0] * m[6] * m[9]; 
};

static float parallelDetMatrix4f(
		float *m
		)
{
	float result = 0.0f;
	__m128 row01 = _mm_load_ps(m);
    __m128 row02 = _mm_load_ps(m + 4);
    __m128 row03 = _mm_load_ps(m + 8);
	
	/*(+) multiplikation der 3 zeilen*/
	__m128 res0 = _mm_mul_ps(
							row01,
							_mm_shuffle_ps(row02, row02, _MM_SHUFFLE(3, 0, 2, 1)));
	res0 		= _mm_mul_ps(
							res0,
							_mm_shuffle_ps(row03, row03, _MM_SHUFFLE(3, 1, 0, 2)));
							
	__m128 val = _mm_add_ps(res0, _mm_movehl_ps(res0, res0));
	result = _mm_cvtss_f32(_mm_add_ss(val, _mm_shuffle_ps(val, val, 1)));	
	
	/*(-) multiplikation der 3 zeilen*/
	__m128 res1 = _mm_mul_ps(
							_mm_shuffle_ps(row01, row01, _MM_SHUFFLE(3, 0, 1, 2)),
							_mm_shuffle_ps(row02, row02, _MM_SHUFFLE(3, 2, 0, 1)));
	res1 		= _mm_mul_ps(
							res1,
							_mm_shuffle_ps(row03, row03, _MM_SHUFFLE(3, 1, 2, 0)));

	val = _mm_add_ps(res1, _mm_movehl_ps(res1, res1));
	result -= _mm_cvtss_f32(_mm_add_ss(val, _mm_shuffle_ps(val, val, 1)));
	
	return result;
};

float detMatrix4f(
		float *m	
		)
{
	return parallelDetMatrix4f(m);
};

static void genericMultiplyVector4fMatrix4f(
		float *m0, 
		float *v0, 
		float *v1
		)
{
	float tmp[3];
	for(uint32_t i = 0;i < 3;i++, m0 += 4)
	{
		tmp[i] = genericScalarproduct(m0,v0);
	}
	for(uint32_t i = 0;i < 3;i++)
	{
		v1[i] = tmp[i];
	}	
};

void multiplyVector4fMatrix4f(
		const float *m0, 
		const float *v0, 
		float *v1
		)
{
	float tmp[3];
	for(uint32_t i = 0;i < 3;i++, m0 += 4)
	{
		tmp[i] = scalarproductVector4f(m0,v0);
	}
	for(uint32_t i = 0;i < 3;i++)
	{
		v1[i] = tmp[i];
	}
	v1[3] = 0.0f;
	delete[] tmp;
};	

void copyVector4f(
		float* f0, 
		const float* f1
		)
{
	std::memcpy(f0, f1, 4 * sizeof(float));
};

int32_t sign(float f)
{
	if(f < 0)
	{
		return -1;
	} 
	else if(f == 0)
	{
		return 0;
	}
	return 1;
};