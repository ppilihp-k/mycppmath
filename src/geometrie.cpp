#include "..\include\geometrie.h"

MathStatus testStatusTwoSpheres(
		const Vertex4f& m0, float r0, 
		const Vertex4f& m1, float r1
		)
{
	float distanceM[4];
	float result;
	subVectorf(m0.content(),m1.content(),distanceM,4);
	result = lengthVectorf(distanceM,3) - r0 - r1; 
	if(result < 0){
		return SCHNITT;
	} 
	else if(result == 0)
	{
		return IDENTITAET;
	} 
	else 
	{
		return KEINSCHNITT;
	}
};

MathStatus testStatusTwoPlanes(
		const Vector4f& n0,
		const Vector4f& n1
		)
{
	float result = abs(scalarproductVector4f(n0.content(), n1.content()));
	if(result == 1.0f)
	{
		return PARALLEL;
	}
	else 
	{
		return SCHNITT;
	}
};

Vertex4f& intersectLineWithPlane(
		Line &l, 
		Plane &p
		)
{
	float denominator,nominator,skalar;
	const Vertex4f positionP = p.getPosition();
	const Vector4f normalP = p.getPlaneNormal();
	const Vertex4f positionl = l.getPosition();
	const Vector4f directionalL = l.getDirection();
	
	nominator = (positionl[0] - positionP[0]) * normalP[0] + (positionl[1] - positionP[1]) * normalP[1] + (positionl[2] - positionP[2]) * normalP[2];
	denominator = directionalL[0] * normalP[0] + directionalL[1] * normalP[1] + directionalL[1] * normalP[2];
	skalar = nominator / denominator;
	
	Vector4f newDirectional;
	copyVector4f(directionalL.content(),newDirectional.content());
	newDirectional.scale(skalar);
	return positionl + newDirectional;
};

Vertex4f& intersectLineWithPlane(
		const Vertex4f& positionLine,
		const Vector4f& directionalLine,
		const Vertex4f& positionPlane,
		const Vector4f& normalPlane
		)
{
	/*
		das sollte noch parallelisiert werden!
	*/
	printf("intersectLineWithPlane parallelisieren!\n");
	float denominator,nominator,skalar;
	
	nominator = (positionLine[0] - positionPlane[0]) * normalPlane[0] + (positionLine[1] - positionPlane[1]) * normalPlane[1] + (positionLine[2] - positionPlane[2]) * normalPlane[2];
	denominator = directionalLine[0] * normalPlane[0] + directionalLine[1] * normalPlane[1] + directionalLine[1] * normalPlane[2];
	skalar = nominator / denominator;
	
	Vector4f newDirectional;
	copyVector4f(directionalLine.content(),newDirectional.content());
	newDirectional.scale(skalar);
	return positionLine + newDirectional;
};

Linesegment& intersect(Triangle &t0, Triangle &t1) throw (MathStatus)
{
	if(
		testStatusTwoSpheres(t0.getMidvertex(),t0.getRadius(),t1.getMidvertex(),t1.getRadius()) && 
		testStatusTwoPlanes(t0.getPlaneNormal(),t1.getPlaneNormal()))
	{
		/*
			wenn sich die dreiecke schneiden, so muss es obda zwei vertexe aus t0 geben, 
			die in der positiven halbebene von t1 liegen.
		*/
		uint32_t t0Top = 0x0;
		Vertex4f t00 = t0.getVertecies()[0];
		Vertex4f t01 = t0.getVertecies()[1];
		Vertex4f t02 = t0.getVertecies()[2];
		Vertex4f t10 = t1.getVertecies()[0];
		Vertex4f t11 = t1.getVertecies()[1];
		Vertex4f t12 = t1.getVertecies()[2];
		Vector4f n0 = t0.getPlaneNormal();
		Vector4f n1 = t1.getPlaneNormal();
		
		t0Top = (testPositiveHalfPlane(t00, t10, n1) >= 0.0f ? (1 << 2) : 0) |
				(testPositiveHalfPlane(t01, t10, n1) >= 0.0f ? (1 << 2) : 0) |
				(testPositiveHalfPlane(t02, t10, n1) >= 0.0f ? (1 << 2) : 0);
		if(t0Top)
		{
			Linesegment linesegment;
			if(t0Top == 3 || t0Top == 5 || t0Top == 6)
			{
				/*
					zwei punkte aus t0 liegen über t1.
					schneide die strecken s0 mit der ebene e1.
				*/
				
			}
			else if(t0Top != 1 || t0Top != 2 || t0Top != 4)
			{
				/*
					zwei punkte aus t1 liegen über t0.
					schneide die strecken s1 mit der ebene e0.
				*/
				
			}	
			return linesegment;
		}
	}
	throw KEINSCHNITT;
};

float testPositiveHalfPlane(
		Vertex4f& v, 
		Vertex4f& p, 
		Vector4f& n
		)
{
	Vector4f tmp = v - p;
	return  scalarproductVector4f(tmp.content(),n.content());
};