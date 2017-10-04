#include "../include/polygon.h"

Polygon::Polygon(float *array, uint32_t numElements) throw (uint32_t)
{
	if(numElements % 3 != 0)
	{
		throw 400;
	}
	
};