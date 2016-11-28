#define  _CRT_SECURE_NO_WARNINGS
#include "BigDataSort.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int N = 100000;




void TestBigDataSort()
{
	BigDateMergeSort bs("BigDataFile.txt", 10000, 10);
	bs.Sort();
}

void GenerateBigDataFile()
{
	FILE* fo = fopen("BigDataFile.txt", "wb");

	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		int num = rand() % 30000;
		char buf[128] = { 0 };
		string line = _itoa(num, buf, 10);
		line += '\n';
		fputs(line.c_str(), fo);
	}
	fclose(fo);
}

int main()
{
	GenerateBigDataFile();
	TestBigDataSort();
	return 0;
}


