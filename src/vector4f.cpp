#include "..\include\vector4f.h"
//#include "..\include\mycppmath.h"

Vector4f::Vector4f(Vector4f &&v)
{
	m_content = v.m_content;
	m_readers = v.m_readers;
	m_writer = v.m_writer;
	m_dimension = 3;
	delete &v;
};

Vector4f::Vector4f(const Vector4f &v)
{
	m_dimension = 3;
	m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
	m_content[0] = v.m_content[0];
	m_content[1] = v.m_content[1];
	m_content[2] = v.m_content[2];
	m_content[3] = v.m_content[3];	
};

Vector4f::Vector4f()
{
	m_dimension = 3;
	/*
		m_content muss eine 16-byte ausgerichtete adresse haben, damit es von sse und avx profitieren kann!
	*/
	m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
};

Vector4f::Vector4f(
		float f0,
		float f1,
		float f2
		)
{
	m_dimension = 3;
	m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
	m_content[0] = f0;
	m_content[1] = f1;
	m_content[2] = f2;
	m_content[3] = 0.0f;
};

Vector4f::~Vector4f()
{
	_aligned_free((void*)m_content);
	//m_lock->~mutex();
};

uint32_t Vector4f::isVertex() const
{
	return m_dimension & VECTORMASK ? 0xFFFFFFFF : 0x0;
};

void Vector4f::setVertex()
{
	m_dimension |= VECTORMASK;
};

void Vector4f::setVector()
{
	m_dimension &= INVERSEVECTORMASK;
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

Vector4f& Vector4f::operator+(Vector4f &v)	const
{
	Vector4f result;
	addVectorf(m_content,v.m_content,result.m_content,((uint32_t)4));
	return result;
};

void Vector4f::operator+=(Vector4f &v)
{
	addVectorf(m_content,v.m_content,m_content,((uint32_t)4));
};

Vector4f& Vector4f::operator-(Vector4f &v) 	const
{
	Vector4f result;
	subVectorf(m_content,v.m_content,result.m_content,((uint32_t)4));
	return result;
};

void Vector4f::operator-=(Vector4f &v)
{
	subVectorf(m_content,v.m_content,m_content,((uint32_t)4));
};

Vector4f& Vector4f::operator*(Vector4f &v) 	const
{
	Vector4f result;
	crossproductVector4f(m_content,v.m_content,result.m_content);
	return result;
};

void Vector4f::operator*=(const Vector4f &v)
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

Vector4f& Vector4f::operator=(Vector4f &v)
{
	if(this == &v){
		return *this;
	}
	m_content[0] = v.m_content[0];
	m_content[1] = v.m_content[1];
	m_content[2] = v.m_content[2];
	m_content[3] = v.m_content[3];
	return *this;
};
/*
Vector4f& Vector4f::operator=(Vector4f &&v)
{
	if(this == &v){
		return *this;
	}
	m_content[0] = v.m_content[0];
	m_content[1] = v.m_content[1];
	m_content[2] = v.m_content[2];
	m_content[3] = v.m_content[3];
	delete &v;
	return *this;
};
*/
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

float* Vector4f::content()
{
	return m_content;
};

Vector4f& Vector4f::operator*(Matrix4f &m) const
{
	Vector4f v;
	multiplyVector4fMatrix4f(m.content(),m_content,v.m_content);
	return v;
};

void Vector4f::operator*=(Matrix4f &m)
{
	multiplyVector4fMatrix4f(m.content(),m_content,m_content);
};

float Vector4f::get(uint32_t i)
{
	return m_content[i];
};

void Vector4f::read()
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

void Vector4f::finishRead()
{
	m_lock.lock();
	m_readers--;	
	m_lock.unlock();	
};

void Vector4f::write()
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

void Vector4f::finishWrite()
{
	m_lock.lock();
	m_writer = 0;
	m_lock.unlock();
};

std::string Vector4f::toString()
{
	return "Vector4f<"+std::to_string(m_content[0])+","+std::to_string(m_content[1])+","+std::to_string(m_content[2])+">";
};