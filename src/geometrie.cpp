#include "..\include\geometrie.h"

static const uint32_t MAXNUMVECTORS = 30000;
static std::mutex s_lock_inUse;
static std::mutex s_lock_notInUse;
static Vector4f* vectors[MAXNUMVECTORS];

static void initStacks()
{
	s_lock_notInUse.lock();
	for(uint32_t i = 0;i < MAXNUMVECTORS;i++)
	{
		Vector4f* v = new Vector4f();
		s_notInUseVector4f.push(v);
	}
	s_lock_notInUse.unlock();
};

Vector4f& allocateVector4f()
{
	s_lock_inUse.lock();
	if(s_inUseVector4f.size() < MAXNUMVECTORS){
		s_lock_notInUse.lock();
		s_inUseVector4f.push(s_notInUseVector4f.pop());
		s_lock_notInUse.unlock();
	}
	s_lock_inUse.unlock();
};

deallocateVector4f(Vector4f &v)
{
	s_lock_notInUse.lock();
	if(s_inUseVector4f.size() < MAXNUMVECTORS)
	{
		s_notInUseVector4f.push(s_inUseVector4f.pop());
	}
	s_lock_notInUse.unlock();
};

Vertex& allocateVertex4f();

deallocateVertex4f(Vertex4f &v);

Matrix4f allocateMatrix4f();

Matrix4f deallocateMatrix4f(Matrix4f &m);

uint32_t isLocatedOnPositiveHalfplane(Vector4f& planeNormal, Vertex& v)
{
	float result[4];
	float f = crossproductVector4f(planeNormal.content(),v.content(),result);
	if(f >= 0){
		return true;
	} else {
		return false;
	}
};

std::list<Vertex4f> intersect(Triangle &t0, Triangle &t1,std::list<Vertex4f> list)
{
	if(t0 == t1)
	{
		
	}
	uint32_t flags = 	isLocatedOnPositiveHalfplane() ? 1 << 2 : 0 | 
						isLocatedOnPositiveHalfplane() ? 1 << 1 : 0 | 
						isLocatedOnPositiveHalfplane() ? 1 : 0;
	if(~flags)
	{
		return std::list<Vertex4f>;
	}
	else 
	{
		
	}
};