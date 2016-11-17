#include "AVLTree.h"


int main()
{
	AVLTree<int, int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		t1.Insert(a[i], i);
	}
	t1.Inorder();

	cout << t1.GetHeight() << endl;
	cout << "IsBalance?" << t1.IsBalance() << endl;
	cout << "IsBalanceOp?" << t1.IsBalanceOp() << endl;

	int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t2;
	for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
	{
		t2.Insert(a1[i], i);
	}
	t2.Inorder();

	cout << t2.GetHeight() << endl;
	cout << "IsBalance?" << t2.IsBalance() << endl;
	cout << "IsBalanceOp?" << t2.IsBalanceOp() << endl;
	return 0;
}