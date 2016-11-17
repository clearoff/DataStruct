#include "BTree.h"


int main()
{
	/*int a[] = { 53, 75, 139, 49, 145, 36, 101 };*/
	int a[] = { 1,2,3,4,5,6,7,8,9,10};
	BTree<int, 3> bt;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert(a[i]);
	}
	bt.InOrder();
	return 0;
}