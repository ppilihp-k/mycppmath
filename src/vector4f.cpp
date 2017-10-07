#include "..\include\vector4f.h"
//#include "..\include\mycppmath.h"
#include <chrono> 

typedef std::chrono::duration<float, std::milli> duration;


static uint32_t MAXALLOCATIONS = 50000;
static uint32_t s_deltaAllocated = 0;
static uint32_t s_deltaRetourned = 0;
static uint32_t s_terminateAllocator = 0xFFFFFFFF;
static std::mutex s_allocatedadrLock, s_retournedadrLock;
static std::list<float*> s_allocatedadr;
static std::list<float*> s_retournedadr;

static double start,end;

static void init(uint32_t size)
{
	s_allocatedadrLock.lock(); 
	for(uint32_t i = 0;i < size;i++)
	{
		s_allocatedadr.push_back((float*) _aligned_malloc(4 * sizeof(float), 16));
	}
	s_allocatedadrLock.unlock(); 	
};

static void allocateSomeMem(float** ptr, uint32_t amount)
{
	for(uint32_t i = 0;i < amount;i++)
	{
		ptr[i] = (float*) _aligned_malloc(4 * sizeof(float), 16);
	}
};

static void allocator()
{
	init(20000);
	uint32_t size,difference;
	float *ptr[500];
	while(~s_terminateAllocator)
	{
		s_allocatedadrLock.lock(); 
		size = s_allocatedadr.size();
		s_allocatedadrLock.unlock(); 
		if(size < MAXALLOCATIONS)
		{
			allocateSomeMem(ptr,500);
			s_allocatedadrLock.lock();
			for(uint32_t i = 0;i < 500;i++)
			{
				s_allocatedadr.push_back(ptr[i]);
				s_deltaAllocated++;	
			}
			s_allocatedadrLock.unlock();
		} 	
		
		if(size > 1000000)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));	
		}
	}
};

static std::thread *s_allocator;

static void swap()
{
	float *ptr;
	uint32_t allocSize,retSize;
	while(~s_terminateAllocator)
	{
		s_allocatedadrLock.lock(); 
		allocSize = s_allocatedadr.size();
		s_allocatedadrLock.unlock();
		
		s_retournedadrLock.lock();
		retSize = s_retournedadr.size();
		s_retournedadrLock.unlock();
		
		if(retSize > 0)
		{
			s_retournedadrLock.lock();
			ptr = s_retournedadr.front();
			s_retournedadr.pop_front();
			s_retournedadrLock.unlock();
			
			if(retSize > allocSize || allocSize >= MAXALLOCATIONS)
			{
				_aligned_free((void*)ptr);
			}
			else 
			{
				s_allocatedadrLock.lock(); 
				s_allocatedadr.push_back(ptr);
				s_allocatedadrLock.unlock();
			}	
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
};

static std::thread *s_swapper;

static float* allocateMem()
{
	if(~s_terminateAllocator)
	{
		float *ptr;
		if(s_allocatedadrLock.try_lock())
		{
			if(s_allocatedadr.size() > 0)
			{
				ptr = s_allocatedadr.front();
				s_allocatedadr.pop_front();
			}
			else 
			{
				ptr = (float*) _aligned_malloc(4 * sizeof(float), 16);
			}
			s_allocatedadrLock.unlock(); 
			return ptr;				
		} 
		else if(s_retournedadrLock.try_lock())
		{
			float *ptr;
			if(s_retournedadr.size() > 0)
			{
				ptr = s_retournedadr.front();
				s_retournedadr.pop_front();
			}
			else
			{
				ptr = (float*) _aligned_malloc(4 * sizeof(float), 16);
			}
			s_retournedadrLock.unlock();
			return ptr;
		}
	} 
	return (float*) _aligned_malloc(4 * sizeof(float), 16);
};

static void deallocateMem(float* ptr)
{
	if(~s_terminateAllocator)
	{
		if(s_retournedadrLock.try_lock())
		{
			s_retournedadr.push_back(ptr);
			s_retournedadrLock.unlock();
		}
		else 
		{
			_aligned_free((void*)ptr);
		}	
	}
	else 
	{
		_aligned_free((void*)ptr);
	}
};

void Vector4f::startSmartAllocator()
{
	s_terminateAllocator = 0x0;
	s_allocator = new std::thread(allocator);
	s_swapper = new std::thread(swap);
};

void Vector4f::terminateSmartAllocator()
{
	s_terminateAllocator = 0xFFFFFFFF;
	s_allocator->join();
	s_swapper->join();
	delete s_allocator;
	delete s_swapper;
	
};

Vector4f::Vector4f(Vector4f &&v)
{
	m_content = v.m_content;
	m_readers = v.m_readers;
	m_writer = v.m_writer;
	m_dimension = 3;
};

Vector4f::Vector4f(const Vector4f &v)
{
	m_dimension = 3;
	//m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
	m_content = allocateMem();
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
	//m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
	m_content = allocateMem();
	m_content[0] = 0.0f;
	m_content[1] = 0.0f;
	m_content[2] = 0.0f;
	m_content[3] = 0.0f;
};

Vector4f::Vector4f(
		float f0,
		float f1,
		float f2
		)
{
	m_dimension = 3;
	//m_content = (float*) _aligned_malloc(4 * sizeof(float), 16);
	m_content = allocateMem();
	m_content[0] = f0;
	m_content[1] = f1;
	m_content[2] = f2;
	m_content[3] = 0.0f;
};

Vector4f& Vector4f::operator=(const Vector4f &v)
{
	if(this == &v){
		return *this;
	}
	m_content[0] = v.m_content[0];
	m_content[1] = v.m_content[1];
	m_content[2] = v.m_content[2];
	m_content[3] = v.m_content[3];
	m_dimension = v.m_dimension;
	m_readers = v.m_readers;
	m_writer = v.m_writer;
	return *this;
};

Vector4f& Vector4f::operator=(Vector4f &&v)
{
	if(this == &v){
		return *this;
	}
	//_aligned_free((void*)m_content);
	deallocateMem(m_content);
	m_content = v.m_content;
	m_dimension = v.m_dimension;
	m_readers = v.m_readers;
	m_writer = v.m_writer;
	return *this;
};

Vector4f::~Vector4f()
{
	//_aligned_free((void*)m_content);
	deallocateMem(m_content);
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

float* Vector4f::content() const
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