// t.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "uibase.h"
#include <vector>

class CBase
{
public:
	void display()
	{
		printf("in cbase\n");
	}
	void test()
	{
		display();
	}
};
class CDerived
	: public CBase
{
public:
	void display()
	{
		printf("in derived\n");
	}
	void t()
	{
		CBase::test();
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CDerived t;
	t.t();
	return 0;
}

