#include <windows.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace std;

void new_func1(void);
int resultOfSum(int, int);

int func1(int a, int b)
{
	int res = 0;
		for (int i = 0; i < 10; i++)
		{
			Sleep(1);
			if (i > 8)
				res = resultOfSum(a, b);
			if (res > 0)
				return res;
		}
	return res;
}
int func2(int a, int b)
{
	int res = 0;
	for (int i = 0; i < 10; i++)
	{
		int res = func1(a, b);
		if (res > 0)
			return res;
	}

	return 0;
}


int resultOfSum(int a, int b)
{
	return a + b;
}

int main(void)
{
	srand(time(0));
	func2(51, 110);
	cout << "runtime = " << clock() / 1000.0 << endl;
	return 0;
}