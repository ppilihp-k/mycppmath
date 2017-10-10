#include "..\include\geometrie.h"
#include "..\include\mycppmath.h"
#include <cmath>

uint32_t testPositiveHalfPlane()
{
	Vertex4f v0,v1;
	v0.set(1,1.0f);
	v1.set(1,-1);
	Vertex4f p1;
	Vector4f d1;
	d1.set(1,1.0f);
	float result;
	result = testPositiveHalfPlane(v0,p1,d1);
	if(result < 0.0f)
	{
		printf("result = %f, soll -> result >= 0\n",result);
		return 0;
	}
	result = testPositiveHalfPlane(v1,p1,d1);
	if(result >= 0.0f)
	{
		printf("result = %f, soll -> result < 0\n",result);
		return 0;
	}
	return 1;
}

uint32_t testStatusTwoSpheres()
{
	Vertex4f v0, v1;
	float r0, r1;
	r0 = 4.9f;
	r1 = 5.0f;
	MathStatus status;
	v1.set(0,10);
	r0 = 4.9f;
	status = testStatusTwoSpheres(v0,r0,v1,r1);
	if(status != KEINSCHNITT)
	{
		printf("status ist: %d, soll 3\n",status);
		return 0;
	}	
	
	r0 = 5.1f;
	status = testStatusTwoSpheres(v0,r0,v1,r1);
	if(status != SCHNITT)
	{
		printf("status ist: %d, soll 1\n",status);
		return 0;
	}		
	return 1;
} 

uint32_t testStatusTwoPlanes()
{
	Vector4f v0, v1;
	v0.set(1,1.0f);
	v1.set(1,1.0f);
	MathStatus status;
	status = testStatusTwoPlanes(v0,v1);
	if(status != PARALLEL)
	{
		printf("status ist %d, soll 0\n",status);
		return 0;
	}
	v1.set(0,1.0f);
	v1.set(1,0.0f);
	status = testStatusTwoPlanes(v0,v1);
	if(status != SCHNITT)
	{
		printf("status ist %d, soll 1\n",status);
		return 0;
	}	
	return 1;
}

uint32_t intersectLineWithPlane()
{
	Vertex4f positionLine;
	positionLine.set(0,0.0f);
	positionLine.set(1,1.0f);
	positionLine.set(2,3.0f);
	Vector4f directionalLine;
	directionalLine.set(0,3.0f);
	directionalLine.set(1,1.0f);
	directionalLine.set(2,7.0f);
	Vertex4f positionPlane;
	positionPlane.set(0,2.0f);
	positionPlane.set(1,9.0f);
	positionPlane.set(2,6.0f);
	Vector4f normalPlane;
	normalPlane.set(0,1.0f);
	normalPlane.set(1,10.0f);
	normalPlane.set(2,4.0f);
	Vertex4f v;
	v = intersectLineWithPlane(positionLine,directionalLine,positionPlane,normalPlane);
	if( std::round(v[0]) !=  std::round(6.878048780487804f) ||  std::round(v[1]) !=  std::round(6.878048780487804f) ||  std::round(v[2]) !=  std::round(19.048780487804876f))
	{
		printf(v.toString().c_str());
		return false;
	}
	printf("\n");
	return 1;
};

static uint32_t testIntersectTwoTriangles()
{
	try
	{
		Triangle t0,t1;
		
		t0.getPlaneNormal().set(0,0.0f);
		t0.getPlaneNormal().set(1,0.0f);
		t0.getPlaneNormal().set(2,1.0f);
		
		t0.getVertecies()[0].set(0,0.0f);
		t0.getVertecies()[0].set(1,0.0f);
		t0.getVertecies()[0].set(2,0.0f);
		
		t0.getVertecies()[1].set(0,1000.0f);
		t0.getVertecies()[1].set(1,0.0f);
		t0.getVertecies()[1].set(2,0.0f);
		
		t0.getVertecies()[2].set(0,0.0f);
		t0.getVertecies()[2].set(1,1000.0f);
		t0.getVertecies()[2].set(2,0.0f);
		
		
		t1.getPlaneNormal().set(0,0.0f);
		t1.getPlaneNormal().set(1,1.0f);
		t1.getPlaneNormal().set(2,0.0f);
		
		t1.getVertecies()[0].set(0,0.0f);
		t1.getVertecies()[0].set(1,0.0f);
		t1.getVertecies()[0].set(2,1.0f);
		
		t1.getVertecies()[1].set(0,1.0f);
		t1.getVertecies()[1].set(1,0.0f);
		t1.getVertecies()[1].set(2,1.0f);
		
		t1.getVertecies()[2].set(0,1.0f);
		t1.getVertecies()[2].set(1,1.0f);
		t1.getVertecies()[2].set(2,-1.0f);
		
		try
		{
			Linesegment ls = intersect(t0,t1);
		}
		catch(MathStatus s)
		{
			if(s != KEINSCHNITT)
			{
				printf("dreiecke schneiden sich, sind aber parallel!\n");
				return 0;
			}
		}
		printf("\n");
		try
		{
			
			t1.getVertecies()[0].set(0,50.0f);
			t1.getVertecies()[0].set(1,50.0f);
			t1.getVertecies()[0].set(2,1.0f);
			
			t1.getVertecies()[1].set(0,25.0f);
			t1.getVertecies()[1].set(1,25.0f);
			t1.getVertecies()[1].set(2,1.0f);
			
			t1.getVertecies()[2].set(0,50.0f);
			t1.getVertecies()[2].set(1,25.0f);
			t1.getVertecies()[2].set(2,-10.0f);
			
			Linesegment ls;
			ls = intersect(t0,t1);
			printf(ls.toString().c_str());
			printf("6");
		}
		catch(...)
		{
			printf("dreiecke muessten sich schneiden!\n");
			return 0;
		}
	}
	catch(...)
	{
		printf("sonstiger fehler!\n");
		return 0;
	}
	return 1;
};

int main(int argc,char** argv)
{
	uint32_t test;
	test = testPositiveHalfPlane();
	printf("testPositiveHalfPlane: %ld\n",test);
	test = testStatusTwoSpheres();
	printf("testStatusTwoSpheres: %ld\n",test);
	test = testStatusTwoPlanes();
	printf("testStatusTwoPlanes: %ld\n",test);
	test = intersectLineWithPlane();
	printf("intersectLineWithPlane: %ld\n",test);
	test = testIntersectTwoTriangles();
	printf("testIntersectTwoTriangles: %ld\n",test);
	return 0;
};