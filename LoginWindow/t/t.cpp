// t.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class TEST
{
public:
	~TEST()
	{
		printf("in ~Test\n");
	}
public:
	int m_nValue;
};
void display(const TEST& t)
{
	printf("in display, value: %d\n", t.m_nValue);
}
int _tmain(int argc, _TCHAR* argv[])
{
	TEST test;
	test.m_nValue = 100;
	display(test);



	return 0;
}

