#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "include.h"
#include <atomic>

class MyAllocator
{
	public:
		MyAllocator();
		~MyAllocator();
	
		uint32_t addPointer(float* ptr);
		float* getPointer();
		void terminate();
		uint32_t isTerminated();
		uint32_t stateOf();
		void start();
		void terminate();
	private:
		void startThread();
		void cleanUp();
		
		std::atomic_uint m_terminate;
		
		std::list<float*> m_L0, m_R0;
		std::atomic_uint m_state;
		std::thread* m_allocator;
};

#endif