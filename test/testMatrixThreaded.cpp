#include "..\include\mycppmath.h"
#include <chrono> 
#include <thread>

void write_strange0(Matrix4f *m0)
{
	m0->write();
	for(uint32_t i = 0;i < 3;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			printf("%f  ",m0->get(i,j));
			m0->set(i,j,0.0f);
		}
		printf("\n");
	}
	m0->set(0,0,1.5f);
	m0->set(1,1,1.5f);
	m0->set(2,2,1.5f);
	m0->finishWrite();
};

void write_strange1(Matrix4f *m0)
{
	m0->write();
	for(uint32_t i = 0;i < 3;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			printf("%f  ",m0->get(i,j));
			m0->set(i,j,0.0f);
		}
		printf("\n");
	}
	m0->set(2,0,1.5f);
	m0->set(1,1,1.5f);
	m0->set(0,2,1.5f);
	m0->finishWrite();
};

void write(Matrix4f *m0)
{
	m0->write();
	printf("writing!\n");
	for(uint32_t i = 0;i < 3;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			printf("%f  ",m0->get(i,j));
			m0->set(i,j,m0->get(i,j) + 3.0f);
		}
		printf("\n");
	}
	std::this_thread::sleep_for(std::chrono::seconds(5));
	printf("writing end!\n");
	m0->finishWrite();
};

void read(Matrix4f *m0,std::string *s)
{
	m0->read();
	printf("reading!\n");
	for(uint32_t i = 0;i < 3;i++)
	{
		for(uint32_t j = 0;j < 3;j++)
		{
			*s += std::to_string(m0->get(i,j)) + "  ";
		}
		*s += "\n";
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	printf("reading end!\n");
	m0->finishRead();
};

uint32_t testSyncrhonizedMaltrixsRead()
{
	Matrix4f *m0 = new Matrix4f();
	Matrix4f *m1 = new Matrix4f();
	std::string s2,s3,s5;
	std::thread t1(write,m0);
	std::this_thread::sleep_for(std::chrono::nanoseconds(50));
	std::thread t2(read,m0,&s2);
	std::this_thread::sleep_for(std::chrono::nanoseconds(100));	
	std::thread t3(read,m0,&s3);
	std::thread t4(write,m0);
	std::this_thread::sleep_for(std::chrono::seconds(5));	
	std::thread t6(write_strange0,m0);
	std::thread t7(write_strange1,m0);
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::thread t5(read,m0,&s5);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	
	printf("\ns2:\n");
	for(uint32_t i = 0;i < s2.length();i++)
	{
		printf("%c",s2[i]);
	}
	printf("\ns3:\n");
	for(uint32_t i = 0;i < s3.length();i++)
	{
		printf("%c",s3[i]);
	}
	printf("\ns5:\n");
	for(uint32_t i = 0;i < s5.length();i++)
	{
		printf("%c",s5[i]);
	}
	return 1;
};

int main(int argc,char** argv)
{
	testSyncrhonizedMaltrixsRead();
	return 0;
};