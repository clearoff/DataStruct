#include "BinaryTree.hpp"


int main()
{
	int array[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 ,'#','#',7};
	BinaryTree<int> t1(array,sizeof(array)/sizeof(array[0]),'#');
	t1.PrevOrder();
	t1.InOrder();
	t1.InOrdefNR();
	t1.PostOrder();
	t1.LevelOrder();
	cout << (t1.Depth())<<endl;
	cout << t1.Size() << endl;
	cout << t1.LeafSize() << endl;
	BinaryTree<int> t2(t1);
	cout << "t2:" << endl;
	t2.PrevOrder();
	t2.PrevOrdefNR();
	t2.PostOrder();
	t2.PostOrderNR();
	cout << t2.Find(6)->_Data<<endl;
	cout << t2.FindKLevel(3) << endl;
	return 0;
}