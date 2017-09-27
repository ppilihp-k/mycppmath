#include "..\include\mycppmath.h"
#include <chrono> 

uint32_t testConstructorDestructor()
{
	try{
		Matrix4f *m = new Matrix4f();
		m->~Matrix4f();		
	} 
	catch (int x)
	{
		return 0;
	}
	return 1;
};

uint32_t testSetGet()
{
	try{
		Matrix4f *m = new Matrix4f();
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				m->set(i,j,4.0f);
			}
		}
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				if(m->get(i,j) != 4.0f){
					return 0;
				}
			}
		}		
		m->~Matrix4f();		
	} 
	catch (int x)
	{
		return 0;
	}
	return 1;
};

uint32_t testOperatorPlusAndPlusEquals()
{
	try{
		uint32_t broke = 0;
		Matrix4f *m0 = new Matrix4f();
		Matrix4f *m1 = new Matrix4f();
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				m0->set(i,j,2.0f);
				m1->set(i,j,2.0f);
			}
		}
		Matrix4f *m2 = *m0 + *m1;
		*m0 += *m1;
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				if(m2->get(i,j) != 4.0f || m0->get(i,j) != 4.0f || m1->get(i,j) != 2.0f)
				{
					printf("i: %d, j: %d\n",i,j);
					printf("testOperatorPlusAndPlusEquals -- m2->get(%d,%d) = %f, soll 4.0f\n",i,j,m2->get(i,j));
					printf("testOperatorPlusAndPlusEquals -- m1->get(%d,%d) = %f, soll 4.0f\n",i,j,m1->get(i,j));
					printf("testOperatorPlusAndPlusEquals -- m0->get(%d,%d) = %f, soll 4.0f\n",i,j,m0->get(i,j));
					broke = 1;
					break;
				}
			}
			if(broke == 1)
			{
				break;
			}
		}		
		if(broke){
			printf("Fehler in Plus und Plus/Gleich\n");
			printf("m0: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m0->get(i,j));
				}
				printf("\n");
			}
			printf("m1: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m1->get(i,j));
				}
				printf("\n");
			}	
			printf("m2: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m2->get(i,j));
				}
				printf("\n");
			}		
			return 0;
		}
		m2->~Matrix4f();
		m0->~Matrix4f();	
		m1->~Matrix4f();			
	} 
	catch (int x)
	{
		printf("Plus und Plus/Gleich, Fehlercode: %d\n",x);
		return 0;
	}
	return 1;	
};

uint32_t testOperatorMinusAndMinusEquals()
{
	try{
		uint32_t broke = 0;
		Matrix4f *m0 = new Matrix4f();
		Matrix4f *m1 = new Matrix4f();
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				m0->set(i,j,2.0f);
				m1->set(i,j,2.0f);
			}
		}
		Matrix4f *m2 = *m0 - *m1;
		*m0 -= *m1;
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				if(m2->get(i,j) != 0.0f || m0->get(i,j) != 0.0f || m1->get(i,j) != 2.0f)
				{
					printf("i: %d, j: %d\n",i,j);
					printf("testOperatorMinusAndMinusEquals -- m2->get(%d,%d) = %f, soll 0.0f\n",i,j,m2->get(i,j));
					printf("testOperatorMinusAndMinusEquals -- m1->get(%d,%d) = %f, soll 2.0f\n",i,j,m1->get(i,j));
					printf("testOperatorMinusAndMinusEquals -- m0->get(%d,%d) = %f, soll 0.0f\n",i,j,m0->get(i,j));
					broke = 1;
					break;
				}
			}
			if(broke)
			{					
				break;
			}
		}		
		if(broke){
			printf("Fehler in Minus und Minus/Gleich\n");
			printf("m0: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m0->get(i,j));
				}
				printf("\n");
			}
			printf("m1: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m1->get(i,j));
				}
				printf("\n");
			}	
			printf("m2: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m2->get(i,j));
				}
				printf("\n");
			}	
			return 0;
		}
		m2->~Matrix4f();
		m0->~Matrix4f();	
		m1->~Matrix4f();			
	} 
	catch (int x)
	{
		printf("Minus und Minus/Gleich, Fehlercode: %d\n",x);
		return 0;
	}
	return 1;	
};

uint32_t testOperatorMultAndMultEquals()
{
	try{
		uint32_t broke = 0;
		Matrix4f *m0 = new Matrix4f();
		/*
		m0->set(0,0,2.0f);
		m0->set(1,1,2.0f);
		m0->set(2,2,2.0f);
		*/
		Matrix4f *m1 = new Matrix4f();
		/*
		m1->set(0,0,2.0f);
		m1->set(1,1,2.0f);
		m1->set(2,2,2.0f);	
		*/
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				m0->set(i,j,2.0f);
				m1->set(i,j,2.0f);
			}
		}
		Matrix4f *m2 = *m0 * *m1;
		*m0 *= *m1;
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				if(m2->get(i,j) != 12.0f || m0->get(i,j) != 12.0f || m1->get(i,j) != 2.0f)
				{
					printf("i: %d, j: %d\n",i,j);
					printf("testOperatorMultAndMultEquals -- m2->get(%d,%d) = %f, soll 12.0f\n",i,j,m2->get(i,j));
					printf("testOperatorMultAndMultEquals -- m1->get(%d,%d) = %f, soll 2.0f\n",i,j,m1->get(i,j));
					printf("testOperatorMultAndMultEquals -- m0->get(%d,%d) = %f, soll 12.0f\n",i,j,m0->get(i,j));
					broke = 1;
					break;
				}
			}
			if(broke)
			{
				break;
			}
		}
		if(broke){
			printf("Fehler in Mult und Mult/Gleich\n");
			printf("m0: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m0->get(i,j));
				}
				printf("\n");
			}
			printf("m1: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m1->get(i,j));
				}
				printf("\n");
			}
			printf("m2: \n");
			for(uint32_t i = 0;i < 3;i++)
			{
				for(uint32_t j = 0;j < 3;j++)
				{
						printf("%f\t",m2->get(i,j));
				}
				printf("\n");
			}	
			return 0;			
		}
		m2->~Matrix4f();
		m0->~Matrix4f();	
		m1->~Matrix4f();			
	} 
	catch (int x)
	{
		printf("Mult und Mult/Gleich, Fehlercode: %d\n",x);
		return 0;
	}
	return 1;	
};

uint32_t testOperatorEquals()
{
	Matrix4f *m0 = new Matrix4f();
	Matrix4f *m1 = new Matrix4f();
	for(uint32_t i = 0;i < 3;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			m1->set(i,j,2.0f);
		}
	}
	*m0 = *m1;
	for(uint32_t i = 0;i < 3;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			if(m0->get(i,j) != 2.0f)
			{
				printf("Zuweisung: m0->get(%d,%d) = %f, soll %f \n",i,j,m0->get(i,j),2.0f);
				return 0;	
			}
		}
	}
	m0->~Matrix4f();	
	m1->~Matrix4f();	
	return 1;
};

uint32_t testOperatorEqualsEquals()
{
	Matrix4f *m0 = new Matrix4f();
	Matrix4f *m1 = new Matrix4f();
	if(*m0 == *m1){
		m0->~Matrix4f();	
		m1->~Matrix4f();
		return 0;
	} 
	else if(*m0 == *m0)
	{
		m0->~Matrix4f();	
		m1->~Matrix4f();
		return 1;
	} else {
		m0->~Matrix4f();	
		m1->~Matrix4f();
		return 0;
	}
};

uint32_t testEquals()
{
	try
	{
		Matrix4f *m0 = new Matrix4f();
		Matrix4f *m1 = new Matrix4f();
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				m0->set(i,j,2.0f);
				m1->set(i,j,2.0f);
			}
		}
		m1->set(0,0,1.0f);
		if(m0->equals(*m1))
		{
			m0->~Matrix4f();
			m1->~Matrix4f();
			return 0;
		} 
		m1->set(0,0,2.0f);
		if(m0->equals(*m1) != 0)
		{
			m0->~Matrix4f();
			m1->~Matrix4f();
			return 1;
		} 
		else if(m0->equals(*m1) == 0)
		{
			m0->~Matrix4f();
			m1->~Matrix4f();
			return 0;			
		}
	} 
	catch(int x)
	{
		return 0;
	}
};

uint32_t testScale()
{
	try
	{
		Matrix4f *m0 = new Matrix4f();
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				m0->set(i,j,2.0f);
			}
		}
		m0->scale(0.5f);
		for(uint32_t i = 0;i < 3;i++)
		{
			for(uint32_t j = 0;j < 3;j++)
			{
				if(m0->get(i,j) != 1.0f)
				{
					return 0;
				}
			}
		}		
		m0->~Matrix4f();
		return 1;
	} 
	catch(int x)
	{
		return 0;
	}
};

uint32_t testMatrixDet()
{
	uint32_t i = 0;
	Matrix4f *m0 = new Matrix4f(9.0f,7.0f,7.0f,7.0f,9.0f,4.0f,1.0f,2.0f,3.0f);
	float det = m0->det();
	if(det == 87.0f)
	{
		i = 1;
	} 
	else 
	{
		printf("Det ist %f, soll %f\n",det,87.0f);
	}
	m0->set(2,2,4.0f);
	m0->set(1,2,10.0f);
	det = m0->det();
	if(det == 53.0f)
	{
		i = 1;
	} 
	else 
	{
		printf("Det ist %f, soll %f\n",det,53.0f);
	}	
	m0->~Matrix4f();
	return i;
};

uint32_t testMatrixMultiplyVector()
{
	Matrix4f *m = new Matrix4f(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f);
	Vector4f *v = new Vector4f(1.0f,2.0f,3.0f);
	Vector4f *r = new Vector4f();
	multiplyVector4fMatrix4f(m->content(),v->content(),r->content());
	if(r->get(0) != 14.0f || r->get(1) != 32.0f || r->get(2) != 50.0f)
	{
		return 0;
	}
	return 1;
};

int main(int argc,char** argv)
{
	uint32_t test = 0;
	test = testConstructorDestructor();
	printf("Konstruktor und Destruktor: %d\n",test);
	test = testSetGet();
	printf("Set und Get: %d\n",test);
	test = testOperatorPlusAndPlusEquals();
	printf("Plus und Plus/Gleich: %d\n",test);
	test = testOperatorMinusAndMinusEquals();
	printf("Minus und Minus/Gleich: %d\n",test);
	test = testOperatorMultAndMultEquals();
	printf("Mal und Mal/Gleich: %d\n",test);
	test = testOperatorEquals();
	printf("Zuweisungsoperator: %d\n",test);
	test = testOperatorEqualsEquals();
	printf("Operator==: %d\n",test);
	test = testEquals();
	printf("Equals: %d\n",test);
	test = testScale();
	printf("Scale: %d\n",test);
	test = testMatrixDet();
	printf("Det: %d\n",test);
	test = testMatrixMultiplyVector();
	printf("Matrix * Vektor: %d\n",test);
	return 0;
};