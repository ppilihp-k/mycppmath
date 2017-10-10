#include "..\include\matrix4f.h"
//#include "..\include\mycppmath.h"

/*
static void initXRotation(float *m, float angle)
{
	m[0] = 1.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	m[4] = 0.0f;
	m[5] = cos(angle) * TODEGREE;
	m[6] = -sin(angle) * TODEGREE;
	m[7] = 0.0f;
	m[8] = 0.0f;
	m[9] = sin(angle) * TODEGREE;
	m[10] = cos(angle) * TODEGREE;
	m[11] = 0.0f;	
	m[12] = 0.0f;	
	m[13] = 0.0f;	
	m[14] = 0.0f;	
	m[15] = 0.0f;	
};

static void initYRotation(float *m, float angle)
{
	m[0] = cos(angle) * TODEGREE;
	m[1] = 0.0f;
	m[2] = sin(angle) * TODEGREE;
	m[3] = 0.0f;
	m[4] = 0.0f;
	m[5] = 1.0f;
	m[6] = 0.0f;
	m[7] = 0.0f;
	m[8] = -sin(angle) * TODEGREE;
	m[9] = 0.0f;
	m[10] = cos(angle) * TODEGREE;
	m[11] = 0.0f;	
	m[12] = 0.0f;	
	m[13] = 0.0f;	
	m[14] = 0.0f;	
	m[15] = 0.0f;	
};

static void initZRotation(float *m, float angle)
{
	m[0] = cos(angle) * TODEGREE;
	m[1] = -sin(angle) * TODEGREE;
	m[2] = 0.0f;
	m[3] = 0.0f;
	m[4] = sin(angle) * TODEGREE;
	m[5] = cos(angle) * TODEGREE;
	m[6] = 0.0f;
	m[7] = 0.0f;
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = 1.0f;
	m[11] = 0.0f;
	m[12] = 0.0f;	
	m[13] = 0.0f;	
	m[14] = 0.0f;	
	m[15] = 0.0f;		
};

static void initializeRotationmatrix(float *m_content, Axis a, float angleX, float angleY, float angleZ)
{
	if(a == 0)
	{
		initXRotation(m_content,angleX);
	}
	else if(a == 1)
	{
		initYRotation(m_content,angleY);
	}
	else if(a == 2)
	{
		initZRotation(m_content,angleZ);
	} 
	else 
	{
		Matrix4f tmp;
		switch(a)
		{
			case 3:
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 4:
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 5:
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 6:
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 7:
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 8:
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 9:
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 10:
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 11:
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 12:
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 13:
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
			case 14:
				initYRotation(tmp.content(),angleY);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initZRotation(tmp.content(),angleZ);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
				initXRotation(tmp.content(),angleX);
				multiplyMatrix4f(m_content,tmp.content(),m_content);
			break;
		}
	}
};
*/

Matrix4f::Matrix4f()
{
	m_content = (float*) _aligned_malloc(16 * sizeof(float), 16);
	for(uint32_t i = 0;i < 16;i++)
	{
		m_content[i] = 0.0f;
	}
	//m_lock = std::mutex();
	m_readers = 0;
	m_writer = 0;
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
	m_content = (float*) _aligned_malloc(16 * sizeof(float), 16);
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
	m_content[12] = 0.0f;
	m_content[13] = 0.0f;
	m_content[14] = 0.0f;
	m_content[15] = 0.0f;
	//m_lock = std::mutex();
	m_readers = 0;
	m_writer = 0;
	
};

Matrix4f::Matrix4f(const Matrix4f &m)
{
	m_content = (float*) _aligned_malloc(16 * sizeof(float), 16);
	for(uint32_t i = 0;i < 16;i++)
	{
		m_content[i] = m.m_content[i];
	}
	m_readers = m.m_readers;
	m_writer = m.m_writer;
};

Matrix4f::Matrix4f(Matrix4f&& m)
{
	m_content = m.m_content;
	m_readers = m.m_readers;
	m_writer = m.m_writer;
	delete &m;
};

Matrix4f::~Matrix4f()
{
	_aligned_free(((void*)m_content));
	//m_lock->~mutex();
};
/*
void Matrix4f::initializeAsRotationmatrix(Axis a, float angleX, float angleY, float angleZ)
{
	initializeRotationmatrix(m_content,a,angleX,angleY,angleZ);
};
*/
float Matrix4f::get(uint32_t row, uint32_t col) const
{
	return m_content[row * 4 + col];
};

void Matrix4f::set(uint32_t row, uint32_t col, float f)
{
	m_content[row * 4 + col] = f;
};

Matrix4f& Matrix4f::operator*(const Matrix4f &m) const
{
	Matrix4f newMatrix;
	multiplyMatrix4f(m_content,m.m_content,newMatrix.m_content);
	return newMatrix;
};

Vector4f& Matrix4f::operator*(Vector4f &m) const
{
	Vector4f v;
	multiplyVector4fMatrix4f(m_content,m.content(),v.content());
	return v;	
};

void Matrix4f::operator*=(const Matrix4f &m)
{
	multiplyMatrix4f(m_content,m.m_content,m_content);
};

Matrix4f& Matrix4f::operator+(const Matrix4f &m) const
{
	//Matrix4f *newMatrix = new Matrix4f();
	Matrix4f newMatrix;
	addMatrix4f(m_content,m.m_content,newMatrix.m_content);
	return newMatrix;
};

void Matrix4f::operator+=(const Matrix4f &m)
{
	addMatrix4f(m_content,m.m_content,m_content);
};

Matrix4f& Matrix4f::operator-(const Matrix4f &m) const
{
	Matrix4f newMatrix;
	subMatrix4f(m_content,m.m_content,newMatrix.m_content);
	return newMatrix;
};

void Matrix4f::operator-=(const Matrix4f &m)
{
	subMatrix4f(m_content,m.m_content,m_content);
};

Matrix4f& Matrix4f::operator=(const Matrix4f &m)
{
	if(this == &m)
	{
		return *this;
	}
	float *ptra,*ptrb;
	ptra = m_content;
	ptrb = m.m_content;
	for(uint32_t i = 0;i < 3;i++, ptra += 4, ptrb += 4)
	{
		_mm_store_ps(ptra,*((__m128*)ptrb));
	}
	
	return *this;
};
/*
Matrix4f& Matrix4f::operator=(Matrix4f &&m)
{
	printf("operator=(Matrix4f &&m)\n");
	
	if(this == &m)
	{
		return *this;
	}
	
	_aligned_free(((void*)m_content));
	//delete &m.m_lock;
	
	m_content = m.m_content;
	m_readers = m.m_readers;
	m_writer = m.m_writer;
	
	return *this;
};
*/
uint32_t Matrix4f::operator==(const Matrix4f &m) const
{
	return this == &m ? 0xFFFFFFFF : 0x0;
};

uint32_t Matrix4f::equals(Matrix4f &m) const
{
	return 	equalVectorf(m_content		,m.m_content	,4) && 
			equalVectorf(m_content + 4	,m.m_content + 4,4) &&
			equalVectorf(m_content + 8	,m.m_content + 8,4) ? 0xFFFFFFFF : 0x0;
};

void Matrix4f::scale(float scalar)
{
	scaleVectorf(m_content,scalar,12);
};

float* Matrix4f::content() const
{
	return m_content;
};

float Matrix4f::det() const
{
	return detMatrix4f(m_content);
};

void Matrix4f::read()
{
	uint32_t in = 1;
	while(in)
	{
		m_lock.lock();
		if(m_writer == 0)
		{
			m_readers++;	
			in = 0;
		}
		m_lock.unlock();	
	}
};

void Matrix4f::finishRead()
{
	m_lock.lock();
	m_readers--;	
	m_lock.unlock();	
};

void Matrix4f::write()
{
	uint32_t in = 1;
	while(in)
	{
		m_lock.lock();
		if(m_readers == 0 && m_writer == 0)
		{
			in = 0;
			m_writer = 1;
		}
		m_lock.unlock();
	}
};

void Matrix4f::finishWrite()
{
	m_lock.lock();
	m_writer = 0;
	m_lock.unlock();
};

std::string Matrix4f::toString()
{
	return "Matrix4f<<"+std::to_string(m_content[0])+","+std::to_string(m_content[1])+","+std::to_string(m_content[2])+">,<"+std::to_string(m_content[4])+","+std::to_string(m_content[5])+","+std::to_string(m_content[6])+">,<"+std::to_string(m_content[8])+","+std::to_string(m_content[9])+","+std::to_string(m_content[10])+">>";
};