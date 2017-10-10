#include "..\include\myallocator.h"

#define MAXALLOCS 1000
typedef std::chrono::duration<float, std::milli> duration;

static void loopWrapper(MyAllocator* ma)
{
	printf("loop start\n");
	float* ptr;
	while(ma->isTerminated() == 0)
	{
		ptr = (float*) _aligned_malloc(4 * sizeof(float), 16);
		ma->addPointer(ptr);
		
		std::this_thread::sleep_for(((duration)10));
	}
	printf("loop ende\n");
};

MyAllocator::MyAllocator()
{
	printf("konstruktor begin\n");
	for(uint32_t i = 0;i < MAXALLOCS;i++)
	{
		m_L0.push_back((float*) _aligned_malloc(4 * sizeof(float), 16));
	}
	m_terminate = 0x1;
	printf("konstruktor end\n");
};

MyAllocator::~MyAllocator()
{
	printf("destruktor begin \n");
	terminate();
	printf("destruktor ende \n");
};

void MyAllocator::addPointer(float* ptr)
{
	if(m_state == 1)
	{
		m_R0.push_back(ptr);
		return 1;
	} 
	else if(m_state == 2)
	{
		m_L0.push_back(ptr);
		return 1;
	}
	return 0;
};

float* MyAllocator::getPointer()
{
	float* ptr;
	if(m_state == 1)
	{
		ptr = m_R0.front();
		m_R0.pop_front();
	} 
	else if(m_state == 2)
	{
		ptr = m_L0.front();
		m_L0.pop_front();		
	}
	else 
	{
		ptr = (float*) _aligned_malloc(4 * sizeof(float), 16)
	}	
	return ptr;
};

void MyAllocator::terminate()
{
	printf("terminate\n");
	if(m_terminate == 0)
	{
		printf("terminate 1\n");
		m_terminate = 1;
		
		m_allocator->join();
		
		printf("terminate 2\n");
	}
};

uint32_t MyAllocator::isTerminated()
{
	printf("terminate zustand: %d\n", m_terminate.load());
	return m_terminate.load();
};

uint32_t MyAllocator::stateOf()
{
	printf("state zustand: %d\n", m_state.load());
	return m_state.load();	
};

void MyAllocator::startThread()
{
	if(m_terminate.load() == 1)
	{
		m_allocator = new std::thread(loopWrapper,this);
		m_terminate = 0;
	}
};

void MyAllocator::cleanUp()
{
	float* ptr;
	for(uint32_t i = 0;i < m_R0.size();i++)
	{
		ptr = m_R0.front();
		m_R0.pop_front();
		_aligned_free((void*)ptr);
	}
	for(uint32_t i = 0;i < m_L0.size();i++)
	{
		ptr = m_L0.front();
		m_L0.pop_front();
		_aligned_free((void*)ptr);
	}	
	delete m_allocator;	
};

void MyAllocator::start()
{
	MyAllocator::startThread();
};

void terminate()
{
	m_terminate = 0x1;
};