#include "..\include\triangle.h"

static void calculateAvgMidvertex(Triangle &t)
{
	Vector4f* vertecies = t.getVertecies();
	Vector4f  avgMidvertex = t.getCentroidVertex();
	addVectorf(
		vertecies[0].content(),
		vertecies[1].content(),
		avgMidvertex.content(),
		4);
	addVectorf(
		vertecies[2].content(),
		avgMidvertex.content(),
		avgMidvertex.content(),
		4);
	avgMidvertex.scale(INVERSETHREE);
};

static void calculateRadius(Triangle &t)
{
	Vertex4f* vertecies = t.getVertecies();
	Vertex4f avgMidvertex = t.getCentroidVertex();
	Vector4f dv_max, dv_tmp;
	subVectorf(vertecies[0].content(),avgMidvertex.content(),dv_max.content(),4);
	for(uint32_t i = 1;i < 3;i++)
	{
		subVectorf(vertecies[i].content(),avgMidvertex.content(),dv_tmp.content(),4);
		if(lengthVectorf(dv_tmp.content(),4) > lengthVectorf(dv_max.content(),4))
		{
			dv_max = dv_tmp;
		}
	}
	avgMidvertex = dv_max;
};

static void initTriangle(Triangle &t)
{
	t.write();
	calculateAvgMidvertex(t);
	calculateRadius(t);
	t.finishWrite();
};

Triangle::Triangle()
{
	
};

Triangle::Triangle(const Triangle &t)
{
	m_vertecies[0] = t.m_vertecies[0];
	m_vertecies[1] = t.m_vertecies[1];
	m_vertecies[2] = t.m_vertecies[2];
	m_centroidVertex = t.m_centroidVertex;
	m_radius = t.m_radius;
	m_areaNormal = t.m_areaNormal;
};

Triangle::~Triangle()
{
	
};

Triangle& Triangle::operator=(const Triangle& t)
{
	if(this == &t)
	{
		return *this;
	}
	m_vertecies[0] = t.m_vertecies[0];
	m_vertecies[1] = t.m_vertecies[1];
	m_vertecies[2] = t.m_vertecies[2];
	m_centroidVertex = t.m_centroidVertex;
	m_radius = t.m_radius;
	m_areaNormal = t.m_areaNormal;	
	return *this;
};

Triangle& Triangle::operator=(Triangle&& t)
{
	if(this == &t)
	{
		return *this;
	}
	m_vertecies[0] = t.m_vertecies[0];
	m_vertecies[1] = t.m_vertecies[1];
	m_vertecies[2] = t.m_vertecies[2];
	m_centroidVertex = t.m_centroidVertex;
	m_radius = t.m_radius;
	m_areaNormal = t.m_areaNormal;	
	return *this;	
};

Vector4f* Triangle::getVertecies()
{
	return m_vertecies;
};

Vertex4f& Triangle::getPlaneNormal()
{
	return m_areaNormal;
};

void Triangle::read()
{
	m_vertecies[0].read();
	m_vertecies[1].read();
	m_vertecies[2].read();
};

void Triangle::finishRead()
{
	m_vertecies[0].finishRead();
	m_vertecies[1].finishRead();
	m_vertecies[2].finishRead();	
};

void Triangle::write()
{
	m_vertecies[0].write();
	m_vertecies[1].write();
	m_vertecies[2].write();	
};

void Triangle::finishWrite()
{
	m_vertecies[0].finishWrite();
	m_vertecies[1].finishWrite();
	m_vertecies[2].finishWrite();	
};

float Triangle::getRadius()
{
	return m_radius;
};

Vertex4f& Triangle::getCentroidVertex()
{
	return m_centroidVertex;
};

std::string Triangle::toString()
{
	return "Triangle{\n\tcentroid:"+
			m_centroidVertex.toString()+",\n\t"+
			"radius:"+std::to_string(m_radius)+",\n\t"+
			"normal:"+m_areaNormal.toString()+",\n\t"+
			"vertex_0:"+m_vertecies[0].toString()+",\n\t"+
			"vertex_1:"+m_vertecies[1].toString()+",\n\t"+
			"vertex_2:"+m_vertecies[2].toString()+"}";
};