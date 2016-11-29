#include "BinaryTree.hpp"
#include "BinarySearchTree.hpp"
#include <cassert>

//Test1:��һ�Ŷ���������Զ�������ڵ�֮��ľ���
//typedef BinaryTreeNode<int> Node;
//size_t DepthOfNode(BinaryTreeNode<int>* node)
//{
//	if (node == NULL)
//	{
//		return 0;
//	}
//
//	//�ֱ�����������
//	size_t Left = DepthOfNode(node->_Left) + 1;
//	size_t Right = DepthOfNode(node->_Right) + 1;
//
//	/*cout << "Left:"<<Left << endl;
//	cout << "Right:" << Right << endl;*/
//	return Left > Right ? Left : Right;
//}
//
//void _DisTanceOfNode(Node* root, size_t& LeftHigh, size_t RightHigh, size_t& Max);
//size_t DisTanceOfNode(BinaryTree<int>& tree)
//{
//	size_t LeftHight = 0;
//	size_t RightHight = 0;
//	size_t Max = 0;
//
//	 _DisTanceOfNode(tree.ReturnRoot(), LeftHight, RightHight,Max);
//
//	 return Max;
//}

//ʱ�临�Ӷ�ΪO(N*N)���㷨
//void _DisTanceOfNode(Node* root, size_t& LeftHigh, size_t RightHigh,size_t& Max)
//{
//	if (root == NULL)
//		return;
//
//	if (root->_Left == NULL)
//		LeftHigh = 0;
//
//	if (root->_Right == NULL)
//		RightHigh = 0;
//
//	if (root->_Left != NULL)
//		_DisTanceOfNode(root->_Left, LeftHigh, RightHigh, Max);
//
//	if (root->_Right != NULL)
//		_DisTanceOfNode(root->_Right, LeftHigh, RightHigh, Max);
//
//	LeftHigh = DepthOfNode(root->_Left);
//	RightHigh = DepthOfNode(root->_Right);
//
//	//���µ�ǰ���ڵ����Զ�����ڵ�֮��ľ���
//	if (LeftHigh + RightHigh + 1 > Max)
//		Max = LeftHigh + RightHigh + 1;
//
//}

//
//void _DisTanceOfNode(Node* root, size_t& LeftHigh, size_t RightHigh, size_t& Max)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	_DisTanceOfNode(root->_Left, LeftHigh, RightHigh, Max);            //�ݹ�����������Զ�����ڵ�֮��ľ���
//
//	_DisTanceOfNode(root->_Right, LeftHigh,RightHigh, Max);                     //��������
//
//	LeftHigh = DepthOfNode(root->_Left);
//	RightHigh = DepthOfNode(root->_Right);
//
//	if (LeftHigh + RightHigh + 1 > Max)
//		Max = LeftHigh + RightHigh + 1;
//}
//void Test1()
//{
//	int b[] = { 1, 2, 3, 5, '#', '#', '#', 4, '#', 6, '#', '#', '#' };
//	int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	BinaryTree<int> t1(b, sizeof(b) / sizeof(b[0]), '#');
//	t1.InOrder();
//	t1.LevelOrder();
//	cout << "������Զ�������ڵ�֮��ľ����ǣ�" << DisTanceOfNode(t1) << endl;
//}


////Test2   �������ڵ�������������
//typedef BinaryTreeNode<int> Node;
//Node* _GetAncestor(Node* root, Node* node1, Node* node2)
//{
//	if (root == NULL)
//		return NULL;
//
//	Node* Left = _GetAncestor(root->_Left, node1, node2);
//	Node* Right = _GetAncestor(root->_Right, node1, node2);
//
//	if (Left&&Right)    //���Left��Right����ΪNULL   ��root�ڵ�Ϊ���ǵ��������
//		return root;
//
//	if (root == node2)
//		return node2;
//	if (root == node1)
//		return node1;
//
//	if ((Right == NULL) && Left)
//		return Left;
//	if ((Left == NULL) && Right)
//		return Right;
//
//    return NULL;
//}

//Node* GetAncestor(BinaryTree<int>& tree, Node* node1, Node* node2)
//{
//	//assert(node1);
//	//assert(node2);
//	Node* ancestor = _GetAncestor(tree.ReturnRoot(), node1, node2);
//	return ancestor;
//}



//void Test2()
//{
//	    int b[] = { 1, 2, 3, 5, '#', '#', '#', 4, '#', 6, '#', '#', '#' };
//		int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//		BinaryTree<int> t1(b, sizeof(b) / sizeof(b[0]), '#');
//		t1.InOrder();
//		t1.LevelOrder();
//		cout << "����������ǣ�" << GetAncestor(t1,t1.Find(5),t1.Find(7))->_Data<< endl;
//}

//��һ�Ŷ���������ת��Ϊ������
//typedef BinarySearchTreeNode<int> Node;
//
//void _TreeToList(Node* cur, Node*& prev)
//{
//	if (cur == NULL)
//		return;
//
//	_TreeToList(cur->_left, prev);
//	
//	cur->_left = prev;
//	if (prev != NULL)
//		prev->_right = cur;
//	
//	prev = cur;
//	_TreeToList(cur->_right, prev);
//}
//
//Node* TreeToList(BinarySearchTree<int>& tree)
//{
//	Node* Head = tree.ReturnRoot();
//	while (Head->_left)
//	{
//		Head = Head->_left;         //����������������ڵ���ǵ�����ĵ�һ���ڵ�
//	}          
//	Node* Prev = NULL;
//	Node* cur = tree.ReturnRoot();
//	_TreeToList(cur, Prev);
//	return Head;
//}
//
//void OrDerList(Node* root)
//{
//	assert(root);
//	while (root)
//	{
//		cout << root->_key << " ";
//		root = root->_right;
//	}
//	cout << endl;
//}
//
//void Test5()
//{
//	BinarySearchTree<int> t;
//	t.Insert(5);
//	t.Insert(4);
//	t.Insert(7);
//	t.Insert(3);
//	t.Insert(6);
//	t.Insert(9);
//	t.Insert(2);
//	t.Insert(0);
//	t.Insert(1);
//	t.Insert(8);
//	t.InorderR();
//	Node* head=TreeToList(t);
//	OrDerList(head);
//}

enum A
{
	a1,
	a2,
	a3 = 10,
	a4,
}a;

void Test()
{
	cout << a << endl;
}

int main()
{
	Test();
	return 0;
}