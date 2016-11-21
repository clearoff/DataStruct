#pragma once 
#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;



void PrintArray(int *a, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void InsertSort(int *a, int size)
{
	int index = 1;
	while (index<size)
	{
		int pos = index - 1;
		int tmp = a[index];
		while (pos >= 0 && a[pos] > tmp)
		{
			a[pos + 1] = a[pos];
			pos--;
		}
		a[pos + 1] = tmp;
		index++;
	}
}
void ShellSort(int *a, int size)
{
	int gap=size;
	while (gap >1)
	{
		gap = gap / 3 + 1;
		int index = gap;
		for (index = gap; index <size; index++)
		{
			int tmp = a[index];
			int pos = index - gap;
			while (pos >= 0 && a[pos] > tmp)
			{
				a[pos + gap] = a[pos];
				pos -= gap;
			}
			a[pos + gap] = tmp;
		}
	}
}

void AdjustDown(int* a, int size, int parent);

void HeapSort(int*a, int size)
{
	for (int i = (size - 2) / 2; i > 0; i--)
	{
		AdjustDown(a, size, i);     //建大堆
	}

	int i = size - 1;
	while (i > 0)
	{
		swap(a[i], a[0]);
		AdjustDown(a, --i, 0);
	}
}

void AdjustDown(int* a, int size, int parent)
{

	int child = parent * 2 + 1;
	while (child < size)     //调整到最后一个非叶子节点
	{
		if ((child+ 1 < size) && a[child + 1] > a[child])
		{
			++child;
		}

		if (a[parent] < a[child])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

void BubbleSort(int* a, int size)
{
	assert(a);
	for (int i = 0 ; i < size; i++)
	{
		bool change = false;
		for (int j = 1; j < size-i; j++)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				change = true;
			}
		}
		if (change==false)
			break;
	}
}
size_t PortSort(int* a, int begin, int end);
void QuickSort(int *a, int begin,int end)
{
	assert(a);

	int div=PortSort(a, begin, end);
	if (div-1> begin)
	{
		QuickSort(a, begin, div-1);
	}
	if (div+1< end)
	{
		QuickSort(a, div + 1, end);
	}

}

size_t PortSort(int* a, int begin, int end)
{
	size_t left = begin;
	size_t right = end - 1;
	int key = a[end];
	while (left < right)
	{
		while ( left<right && a[left] <=key)
		{
			//left找比key大的
			left++;
		}
		while ( left < right && a[right] >= key)
		{
			//right为找a中小于key的下标
			right--;
		}

		if (left < right)             //left < right  交换
		{
			swap(a[left], a[right]);
		}
	}
	if (key <= a[left])
	{
		swap(a[end], a[left]);
		return left;
	}
	else
		return end;
}
//快速排序挖坑法
int PortPothSort(int* a, int begin, int end)
{
	int left = begin;
	int right = end - 1;
	int key = a[end];
	int index = end;             //初始的坑的位置
	
	while (left < right)
	{
		while (left < right&&a[left] <= key)          //left找大于key的元素
		{
			left++;
		}
		if (left < right)
		{
			a[index] = a[left];            //填坑
			index = left;                  //left所指向的位置现在变为坑
		}
		while (left < right&&a[right] >= key)
		{
			right--;
		}
		if (left < right)
		{
			a[index] = a[right];
			index = right;
		}	
	}
	a[index] = key;                      //一趟排序完成后把key填入坑中
	return index;                        //返回最后一个坑的位置
}
void QuickPothSort(int* a, int begin,int end)
{
	assert(a);
	int div = PortPothSort(a, begin, end);
	if (div - 1> begin)
	{
		QuickSort(a, begin, div - 1);
	}
	if (div + 1< end)
	{
		QuickSort(a, div + 1, end);
	}
}
//快速排序 优化
size_t PortSortOP(int* a, int begin, int end)
{
	int cur = begin;
	int prev = cur - 1;
	int key = a[end];

	while (cur <= end)
	{
		if (a[cur] < key && ++prev != cur)      //cur找比key小的数
			swap(a[cur], a[prev]);              //cur遇到比key大的数，prev不移动
		cur++;                                  //cur再次遇到比key小的数时如果prev不紧跟cur 则进行交换
	}
	swap(a[++prev], a[end]);
	return prev;
}

void QuickSortOP(int* a, int begin, int end)
{
	assert(a);
	int div = PortSortOP(a, begin, end);
	if (div - 1 > begin)
		QuickSortOP(a, begin, div - 1);
	
	if (div + 1 < end)
		QuickSortOP(a, div + 1, end);
}

void SelectSort(int* a, int size)
{
	assert(a);
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int max = right;
		int min = left;
		for (int i = left; i <= right; i++)
		{
			if (a[i] < a[min])
				min = i;
			if (a[i] > a[max])
				max = i;
		}
		swap(a[right], a[max]);  
		if (min == right)
		{
			min = max;
		}
		swap( a[min],a[left]);
		left++;
		right--;
	}
}
//归并排序
void _MergeSort(int* a, int* tmp, int left, int right)
{
	int mid = left + ((right - left) >> 1);          //找到数组的中间下标

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;

	if (begin1 < end1)
	{
		_MergeSort(a, tmp, begin1, end1);  //对子数组进行归并排序
	}
	if (begin2 < end2)
	{
		_MergeSort(a, tmp, begin2, end2);  //对子数组进行归并排序
	}

	int index = left;

	//while (begin1 <= end1 || begin2 <= end2)
	//{
	//	if (begin2>end2)
	//	{
	//		tmp[index++] = a[begin1++];
	//	}
	//	if (begin1 > end1)
	//	{
	//		tmp[index++] = a[begin2++];
	//	}
	//	if (begin1 <= end1 && begin2 <= end2)
	//	{
	//		if (a[begin1] < a[begin2])
	//			tmp[index++] = a[begin1++];
	//		else
	//			tmp[index++] = a[begin2++];   //向tmp数组中进行合并
	//	}
	//}

	while (begin1<=end1 && begin2<=end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];   //向tmp数组中进行合并
	}

	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}

	for (int i = left; i <= right; i++)
	{
		a[i] = tmp[i];
	}
}
void MergeSort(int* a, int size)
{
	assert(a);
	int* tmp = new int[size];
	_MergeSort(a, tmp, 0, size-1);
	delete[] tmp;
}

void TestMergeSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	MergeSort(a,sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestQuickSortOP()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	QuickSortOP(a,0, sizeof(a) / sizeof(a[0])-1);
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestSelectSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8,7, 1, 0 };
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestQuickPothSort()
{
	/*int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };*/
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	QuickPothSort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

void TestQuickSort()
{
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5};
	QuickSort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestBubble()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestInsert()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	InsertSort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a)/sizeof(a[0]));
}

void TestHeapSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	HeapSort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestShell()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}