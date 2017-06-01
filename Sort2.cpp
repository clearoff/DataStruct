#include <iostream>
using namespace std;
#include <vector>
#include <cassert>

//size_t Port_Sort(int* a, int begin, int end)
//{
//	size_t left = begin;
//	size_t right = end - 1;
//	int key = a[end];
//	while (left < right)
//	{
//		while (left<right && a[left] <= key)
//		{
//			//left找比key大的
//			left++;
//		}
//		while (left < right && a[right] >= key)
//		{
//			//right为找a中小于key的下标
//			right--;
//		}
//
//		if (left < right)             //left < right  交换
//		{
//			swap(a[left], a[right]);
//		}
//	}
//	if (key <= a[left])
//	{
//		swap(a[end], a[left]);
//		return left;
//	}
//	else
//		return end;
//}


size_t Port_Sort(int* v1, int begin, int end){
	int left = begin;
	int right = end - 1;
	int key = v1[end];
	while (left < right){
		while (left < right && v1[left] <= key){
			left++;
		}
		while (left < right && v1[right] >= key){
			right--;
		}
		if (left < right){
			swap(v1[left], v1[right]);
		}
	}
	// left >= right 
	if (v1[left] >= key){
		swap(v1[left], v1[end]);
		return left;
	}
	return end;

}

//快速排序挖坑法
size_t Port_Sort_K(int* v1, int begin, int end)
{
	int left = begin;
	int right = end - 1;
	int key = v1[end];
	int index = end;
	while (left < right)
	{
		while (left < right && v1[left] <= key){
			left++;
		}
		//填坑
		if (left < right){
			v1[index] = v1[left];
			index = left;
		}
		while (left < right && v1[right] >= key){
			right--;
		}
		if (left < right){
			v1[index] = v1[right];
			index = right;
		}
	}
	v1[index] = key;
	return index;
}

void Quick_Sort(int* v1, int begin, int end)
{
	//assert(v1.size() >= 0);
	int div = Port_Sort_K(v1, begin, end);
	if (div - 1 > begin){
		Quick_Sort(v1, begin, div - 1);
	}
	if (div + 1 < end){
		Quick_Sort(v1, div + 1, end);
	}

}

void Adjust_Down(int* a,int size,int parent)
{
	assert(a);
	//拿到子节点
	int child = parent * 2 + 1;
	while (child < size){
		if ((child + 1) < size && a[child] < a[child + 1]){
			child = child + 1;
		}
		if (a[parent] < a[child]){
			swap(a[parent], a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

void Heap_Sort(int* a,int size)
{
	//建堆
	for (int i = (size - 1 - 1) / 2; i >= 0; i--){
		Adjust_Down(a, size, i);
	}

	for (int i = size - 1; i > 0;){
		swap(a[0], a[i]);
		Adjust_Down(a, --i, 0);
	}
}

//插入排序
void Insert_Sort(int* a,int size)
{
	assert(a);
	for (int index = 1; index < size; index++){
		int pos = index - 1;
		int tmp = a[index];
		while (pos >= 0 && a[pos] > tmp){
			swap(a[pos], a[pos + 1]);
			//a[pos + 1] = a[pos];
			pos--;
		}
		//a[pos+1] = tmp;
	}
}

//希尔排序
void Sheel_Sort(int* a,int size)
{
	int gap = size;
	while (gap > 1){
		gap = gap / 3 + 1;
		for (int index = gap; index < size; index += gap){
			int pos = index - gap;
			int tmp = a[index];
			while (pos >= 0 && a[pos] > tmp){
				swap(a[pos], a[pos + gap]);
				pos -= gap;
			}
		}
	}
}

void _MergeSort(int* a, int* tmp, int begin,int end){
	int mid = begin + (end - begin) / 2;
	int left1 = begin;
	int	right1 = mid ;
	int left2 = mid + 1;
	int right2 = end;
	if (left1 < right1){
		_MergeSort(a,tmp,left1,right1);
	}
	if (left2 < right2){
		_MergeSort(a, tmp, left2, right2);
	}
	int index = begin;
	while (left1<=right1 && left2<=right2){
		if (a[left1]>a[left2])
			tmp[index++] = a[left2++];
		else
			tmp[index++] = a[left1++];
	}
	while (left1 <= right1){
		tmp[index++] = a[left1++];
	}
	while (left2 <= right2){
		tmp[index++] = a[left2++];
	}

	for (int i = begin; i <= end; i++){
		a[i] = tmp[i];
	}
}

void Merge_Sort(int* a, int size){
	assert(a);
	int* tmp = new int[size];
	_MergeSort(a,tmp,0,size-1);
	delete[] tmp;
}

void PrintArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void TestQuickSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Quick_Sort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestInsertSort()
{
	//int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Insert_Sort(a,sizeof(a) / sizeof(a[0]) );
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestHeapSort()
{
	//int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Heap_Sort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestSheelSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Sheel_Sort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestMergeSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Merge_Sort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}
int main()
{
	TestQuickSort();
	TestHeapSort();
	TestInsertSort();
	TestSheelSort();
	TestMergeSort();
	return 0;
}