#include "stdafx.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void Test(int k, int N, char* str)
{
	int x;
	int y;
	k = k % N;
	for (int i = 0; i < k; i ++)
	{
		int t = (i+k)%N;
		x = str[(i + k)%N];
		y = str[N - (k - i)];
		
		str[(i + k)%N] = str[N - (k - i)];
		str[N- (k - i)] = str[i];
		str[i] = x;
	}
}

int main()
{
	char str1[100] = "abcdef";
	Test(8, 6, str1);
	printf("%s \n", str1);

	return 0;
}