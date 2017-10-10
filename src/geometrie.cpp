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

static float genericIntersectLineWithPlane(
		const Vertex4f& positionLine,
		const Vector4f& directionalLine,
		const Vertex4f& positionPlane,
		const Vector4f& normalPlane
		)
{
	float nominator, denominator, scalar;
	
	nominator = 		positionPlane[0] * normalPlane[0] + positionPlane[1] * normalPlane[1] + positionPlane[2] * normalPlane[2]
					-	positionLine[0] * normalPlane[0] - positionLine[1] * normalPlane[1] - positionLine[2] * normalPlane[2];
	
	denominator = 		directionalLine[0] * normalPlane[0] + directionalLine[1] * normalPlane[1] + directionalLine[2] * normalPlane[2];
	
	return denominator == 0.0f ? 0.0f : nominator / denominator;
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
	float scalar = genericIntersectLineWithPlane(positionLine, directionalLine, positionPlane, normalPlane);
	Vector4f newDirectional;
	copyVector4f(newDirectional.content(),directionalLine.content());
	newDirectional.scale(scalar);
	newDirectional += positionLine;
	return newDirectional;
};

Linesegment& intersect(Triangle &t0, Triangle &t1) throw (MathStatus)
{
	/*
		optimierungsbedarf! diese funktion kann noch parallelisiert werden!
	*/
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
			printf("1\n");
			/*
				vertexe sortieren
			*/
			t0Top = (testPositiveHalfPlane(t0.getVertecies()[0], t10, n1) >= 0.0f ? 1 		 : 0) |
					(testPositiveHalfPlane(t0.getVertecies()[1], t10, n1) >= 0.0f ? (1 << 1) : 0) |
					(testPositiveHalfPlane(t0.getVertecies()[2], t10, n1) >= 0.0f ? (1 << 2) : 0);	
			switch(t0Top)
			{
				case 1:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[1];
					t0Bot0 = t0.getVertecies()[2];				
				break;
				case 2:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[2];
					t0Bot0 = t0.getVertecies()[1];				
				break;
				case 3:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[1];
					t0Bot0 = t0.getVertecies()[2];
				break;
				case 4:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[1];
					t0Bot0 = t0.getVertecies()[2];			
				break;
				case 5:
					t0Top0 = t0.getVertecies()[0];
					t0Top1 = t0.getVertecies()[2];
					t0Bot0 = t0.getVertecies()[1];				
				break;
				case 6:
					t0Top0 = t0.getVertecies()[1];
					t0Top1 = t0.getVertecies()[2];
					t0Bot0 = t0.getVertecies()[0];					
				break;
				default:
					throw KEINSCHNITT;
				break;
			}
			/*
				schnittpunkte berechnen
			*/
			Vector4f r = t0Bot0 - t0Top0;
			Vertex4f s0;
			s0 = intersectLineWithPlane(t0Top0, r, t10, t1.getPlaneNormal());
			r = t0Bot0 - t0Top1;
			Vertex4f s1;
			s1 = intersectLineWithPlane(t0Top1, r, t10, t1.getPlaneNormal());
			
			/*
				testen, ob die schnittpunkte im dreieck t1 liegen
			*/
			Vector4f pNormal;
			Vector4f pDirectional;
			t0Top = 0x0;
			/*
				diese tests sind nicht funktionsfaehig!
			*/
			/*
				test für s0
			*/
			pDirectional = s0 - t10;
			crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());
			if(	
				sign(testPositiveHalfPlane(t11,t10,pNormal)) + sign(testPositiveHalfPlane(t12,t10,pNormal) == 0)
				)
			{
				pDirectional = s0 - t11;
				crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());		
				if(
					sign(testPositiveHalfPlane(t10,t11,pNormal)) + sign(testPositiveHalfPlane(t12,t11,pNormal) == 0)
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
				sign(testPositiveHalfPlane(t11,t10,pNormal)) + sign(testPositiveHalfPlane(t12,t10,pNormal) == 0)
				)
			{
				pDirectional = s1 - t11;
				crossproductVector4f(pDirectional.content(),n1.content(),pNormal.content());				
				if(
					sign(testPositiveHalfPlane(t10,t11,pNormal)) + sign(testPositiveHalfPlane(t12,t11,pNormal) == 0)
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
					copyVector4f(linesegment.getVertex0().content(),s0.content());
					inverseDistance = inverseLengthVectorf(s0.content(),3);
					//(s0 - t0Top0) * (t0Top0 - t0Bot0);
					s0 -= t0Top0;
					r = t0Top0 - t0Bot0;
					s0 *= r;
					s0.scale(inverseDistance);
					copyVector4f(linesegment.getVertex1().content(),s0.content());
				}
				else 
				{
					/*
						s1 liegt im dreieck.
					*/
					copyVector4f(linesegment.getVertex0().content(),s1.content());
					s1 -= t0Top0;
					r = t0Top0 - t0Bot0;
					s1 *= r;
					inverseDistance = inverseLengthVectorf(s1.content(),3);
					s1.scale(inverseDistance);
					copyVector4f(linesegment.getVertex1().content(),s1.content());
					
				}
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
	Vector4f tmp;
	tmp	= v - p;
	return  scalarproductVector4f(tmp.content(),n.content());
};