#include "..\include\geometrie.h"

MathStatus testStatusTwoSpheres(
		const Vertex4f& m0, float r0, 
		const Vertex4f& m1, float r1
		)
{
	float distanceM[4];
	float result;
	subVectorf(m0.content(),m1.content(),distanceM,4);
	result = lengthVectorf(distanceM,4) - r0 - r1; 
	if(result < 0){
		return SCHNITT;
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
	denominator = directionalLine[0] * normalPlane[0] + directionalLine[1] * normalPlane[1] + directionalLine[2] * normalPlane[2];
	skalar = nominator / denominator;
	printf("nom: %f, denom: %d\n",nominator,denominator);
	
	Vector4f newDirectional;
	copyVector4f(newDirectional.content(),directionalLine.content());
	newDirectional.scale(skalar);
	printf((positionLine + newDirectional).toString().c_str());
	return positionLine + newDirectional;
};

Linesegment& intersect(Triangle &t0, Triangle &t1) throw (MathStatus)
{
	printf("0");
	if(
		testStatusTwoSpheres(t0.getCentroidVertex(),t0.getRadius(),t1.getCentroidVertex(),t1.getRadius()))
	{
		if(testStatusTwoPlanes(t0.getPlaneNormal(),t1.getPlaneNormal()))
		{
			/*
				wenn sich die dreiecke schneiden, so muss es obda zwei vertexe aus t0 geben, 
				die in der positiven halbebene von t1 liegen.
			*/
			uint32_t t0Top = 0x0;
			Vertex4f t0Top0;
			Vertex4f t0Top1;
			Vertex4f t0Bot0;
			Vertex4f t10 = t1.getVertecies()[0];
			Vertex4f t11 = t1.getVertecies()[1];
			Vertex4f t12 = t1.getVertecies()[2];
			Vector4f n0 = t0.getPlaneNormal();
			Vector4f n1 = t1.getPlaneNormal();
			printf("1");
			/*
				vertexe sortieren
			*/
			t0Top = (testPositiveHalfPlane(t0.getVertecies()[0], t10, n1) >= 0.0f ? 1 		 : 0) |
					(testPositiveHalfPlane(t0.getVertecies()[1], t10, n1) >= 0.0f ? (1 << 1) : 0) |
					(testPositiveHalfPlane(t0.getVertecies()[2], t10, n1) >= 0.0f ? (1 << 2) : 0);	
			printf("top0Top: %ld\n",t0Top);
			switch(t0Top)
			{
				case 3:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[1];
					t0Bot0 = t0.getVertecies()[2];
					printf("t0Top = 3\n");
				break;
				case 5:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[2];
					t0Bot0 = t0.getVertecies()[1];	
printf("t0Top = 5\n");					
				break;
				case 6:
					t0Top0 = t0.getVertecies()[1];
					t0Top1 = t0.getVertecies()[2];
					t0Bot0 = t0.getVertecies()[0];		
printf("t0Top = 6\n");					
				break;
				default:
					throw KEINSCHNITT;
				break;
			}
			printf("2");
			/*
				schnittpunkte berechnen
			*/
			Vector4f r = t0Bot0 - t0Top0;
			printf("\n%f,%f,%f\n",r[0],r[1],r[2]);
			printf("\n%f,%f,%f\n",t0Bot0[0],t0Bot0[1],t0Bot0[2]);
			printf("\n%f,%f,%f\n",t0Top0[0],t0Top0[1],t0Top0[2]);
			printf("nach 2\n");
			Vertex4f s0;
			s0 = intersectLineWithPlane(t0Top0, r, t10, t1.getPlaneNormal());
			printf("nach 2\n");
			r = t0Bot0 - t0Top1;
			Vertex4f s1;
			s1 = intersectLineWithPlane(t0Top1, r, t10, t1.getPlaneNormal());
			
			printf("\n");
			printf(s0.toString().c_str());
			printf(s1.toString().c_str());
			/*
				testen, ob die schnittpunkte im dreieck t1 liegen
			*/
			Vector4f pNormal;
			Vector4f pDirectional;
			t0Top = 0x0;
			printf("3");
			/*
				test für s0
			*/
			pDirectional = s0 - t10;
			crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());
			if(	
				sign(testPositiveHalfPlane(t11,t10,pNormal)) != sign(testPositiveHalfPlane(t12,t10,pNormal))
				)
			{
				pDirectional = s0 - t11;
				crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());				
				if(
					sign(testPositiveHalfPlane(t10,t11,pNormal)) != sign(testPositiveHalfPlane(t12,t11,pNormal))
					)
				{
					/*
						s0 liegt im dreieck
					*/
					t0Top = 0x1;
				}
			}
			/*
				test für s1
			*/
			pDirectional = s1 - t10;
			crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());
			if(	
				sign(testPositiveHalfPlane(t11,t10,pNormal)) != sign(testPositiveHalfPlane(t12,t10,pNormal))
				)
			{
				pDirectional = s1 - t11;
				crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());				
				if(
					sign(testPositiveHalfPlane(t10,t11,pNormal)) != sign(testPositiveHalfPlane(t12,t11,pNormal))
					)
				{
					/*
						s0 liegt im dreieck
					*/
					t0Top |= 0x2;
				}
			}	

			/*
				wenn beide punkte im dreieck liegen, strecke zurueckgeben
			*/
			printf("4");
			if(t0Top == 0)
			{
				throw KEINSCHNITT;
			}
			
			Linesegment linesegment;
			if(t0Top == 3)
			{
				/*
					beide schnittpunkte liegen im dreieck
				*/
				copyVector4f(linesegment.getVertex0().content(), s0.content());
				copyVector4f(linesegment.getVertex1().content(), s1.content());
				copyVector4f(linesegment.getDirection().content(), (s1 - s0).content());
			}
			else 
			{
				/*
					neuen schnittpunkt bestimmen, nur ein schnittpunkt liegt im dreieck.
				*/
				float inverseDistance = 0.0f;
				if(t0Top == 1)
				{
					/*
						s0 liegt im dreieck.
					*/
					inverseDistance = inverseLengthVectorf(((s0 - t0Top0) * (t0Top0 - t0Bot0)).content(),3);
					copyVector4f(linesegment.getVertex0().content(),s0.content());
					copyVector4f(linesegment.getVertex1().content(),s0.content());
					linesegment.getVertex1().scale(inverseDistance);
				}
				else 
				{
					/*
						s1 liegt im dreieck.
					*/
					inverseDistance = inverseLengthVectorf(((s1 - t0Top0) * (t0Top0 - t0Bot0)).content(),3);
					copyVector4f(linesegment.getVertex0().content(),s1.content());
					copyVector4f(linesegment.getVertex1().content(),s1.content());
					linesegment.getVertex1().scale(inverseDistance);
				}
			}
			printf("5");
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
	Vector4f tmp;
	tmp	= v - p;
	return  scalarproductVector4f(tmp.content(),n.content());
};