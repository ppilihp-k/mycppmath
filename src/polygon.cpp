#include "../include/polygon.h"

void Polygon::copy(const Polygon& p1)
{
	m_numElements = p1.m_numElements;
	m_triangles = new Triangle[m_numElements];
	for(uint32_t i = 0;i < m_numElements;i++)
	{
		m_triangles[i] = p1.m_triangles[i];
	}
};

void Polygon::move(Polygon& p)
{
	m_numElements = p.m_numElements;
	if(m_numElements > 0)
	{
		delete[] m_triangles;
	}
	m_triangles = p.m_triangles;	
}

Polygon::Polygon()
{
	m_numElements = 0;
};

Polygon::Polygon(const Polygon &p)
{
	copy(p);
};

Polygon::Polygon(Polygon &&p)
{
	move(p);
};

Polygon::~Polygon()
{
	if(m_numElements > 0)
	{
		delete[] m_triangles;
	}	
};

Polygon& Polygon::operator=(const Polygon &p)
{
	if(*this == p)
	{
		return *this;
	}
	copy(p);
	return *this;
};

Polygon& Polygon::operator=(Polygon &&p)
{
	if(*this == p)
	{
		return *this;
	}
	move(p);
	return *this;
};

uint32_t Polygon::operator==(const Polygon& p)
{
	if(this == &p)
	{
		return 0xFFFFFFFF;
	}
	return 0x0;
};

void Polygon::operator*=(const Matrix4f &m)
{
	for(uint32_t i = 0;i < m_numElements;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			m_triangles[i].getVertecies()[j] *= m;
		}
	}
};

void Polygon::operator*=(float f)
{
	for(uint32_t i = 0;i < m_numElements;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			m_triangles[i].getVertecies()[j].scale(f);
		}
	}	
};

/*
void Polygon::operator*=(const Vector4f &v)
{
	for(uint32_t i = 0;i < m_numElements;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			for(uint32_t k = 0;k < 3;j++)
			{
				m_triangles[i].getVertecies()[j].get() *= m;
			}
		}
	}
};
*/

Triangle* Polygon::getTriangles() const
{
	return m_triangles;
};

uint32_t Polygon::size() const
{
	return m_numElements;
};

Vertex4f& Polygon::getCentroidVertex()
{
	return m_centroidVertex;
};

float Polygon::getRadius()
{
	return m_radius;
};