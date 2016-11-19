#include <iostream>
#include "BinaryTree.hpp"
#include <vector>
#include <cassert>
#include <cstdlib>
#include <queue>
using namespace std;


//size_t DistanceOfLeafNode(BinaryTreeNode<int>* node);
//
//
//
////// �����������Զ�������ڵ�ľ���
////����ⷨ��ȱ�����
//
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
//void _DistanceOfNode(BinaryTreeNode<int>* root,size_t& Left,size_t Right,size_t& Max)
//{
//	if (root == NULL)
//	{
//		//left = 0;
//		//right = 0;
//		return ;
//	}
//
//	if (root->_Left == NULL)
//		Left = 0;
//
//	if (root->_Right == NULL)
//		Right = 0;
//
//	if (root->_Left != NULL)
//	{
//		_DistanceOfNode(root->_Left, Left, Right, Max);
//	}
//	
//	if (root->_Right != NULL)
//	{
//		_DistanceOfNode(root->_Right, Left, Right, Max);
//	}
//
//	Left = DepthOfNode(root->_Left);   //�����������
//	Right = DepthOfNode(root->_Right); //�����������
//
//	//�����������ֵ
//	 if (Left + Right +1> Max)
//	 {
//		 Max = Left + Right+1;
//	 }
//}
//size_t DistanceOfNode(BinaryTree<int>& t)
//{
//	size_t Left = 0;     //�������߶�
//	size_t Right = 0;    //�������߶�
//	size_t Max = 0;
//
//     _DistanceOfNode(t.ReturnRoot(),Left,Right,Max);
//
//	 return Max;
//
//	//size_t MaxDepth = Left > Right ? Left+1: Right+1;          
//
//	//return MaxDepth > Left + Right ? MaxDepth : Left + Right;
//}

//void Test1()
//{
//	int b[] = { 1, 2, 3, 5, '#', '#', '#', 4, '#', 6, '#', '#', '#' };
//	int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	BinaryTree<int> t1(b, sizeof(b) / sizeof(b[0]), '#');
//	t1.InOrder();
//	t1.LevelOrder();
//	cout << "������Զ�������ڵ�֮��ľ����ǣ�" << DistanceOfNode(t1) << endl;
//}


//Test2
//��ǰ���������������ؽ���������ǰ�����У�1   2   3   4   5   6   -  ��������: 3   2   4   1   6   5 ��
//struct BinaryTreeNode
//{
//	int _value;
//	BinaryTreeNode* _Left;
//	BinaryTreeNode* _Right;
//
//	BinaryTreeNode(const int& x)
//		:_value(x)
//		, _Left(NULL)
//		, _Right(NULL)
//	{}
//};
//
//typedef BinaryTreeNode Node;
//
//Node* CreateBinaryTree(vector<int>& front, vector<int>& mid,int size)
//{
//	assert(front.size() == mid.size());
//	if (size <= 0||front.size()==0||mid.size()==0)
//		return NULL;
//
//	Node* root = new Node(front[0]);              //ǰ������ĵ�һ���ڵ�Ϊ���ڵ�
//
//	//������������ҵ����ڵ�
//	int index = 0;
//	for (index = 0; index < size; index++)
//	{
//		if (front[0] == mid[index])
//			break;
//	}
//	if (index == size)
//	{
//		cout << "Invaid Input!!!����ʧ��" << endl;
//		exit(0);
//	}
//	vector<int> b;   //����
//	vector<int> a;   //�������
//	for (int i = 0; i < index; i++)
//	{
//		b.push_back(mid[i]);
//		a.push_back(front[i+1]);
//	}
//	root->_Left = CreateBinaryTree(a, b, a.size());
//	a.clear();
//	b.clear();
//	for (int i =index+1; i < size; i++)
//	{
//		b.push_back(mid[i]);
//		a.push_back(front[i]);
//	}
//	root->_Right = CreateBinaryTree(a, b, a.size());
//
//	return root;
//}

//void PreOrder(Node* root)
//{
//	if (root == NULL)
//		return;
//	cout << root->_value << " ";
//	PreOrder(root->_Left);
//	PreOrder(root->_Right);
//}
//void InOrder(Node* root)
//{
//	if (root == NULL)
//		return;
//
//	InOrder(root->_Left);
//	cout << root->_value << " ";
//	InOrder(root->_Right);
//}

//void Test2()
//{
//	vector<int> front;
//	front.push_back(1);
//	front.push_back(2);
//	front.push_back(3);
//	front.push_back(4);
//	front.push_back(5);
//	front.push_back(6);
//	vector<int> mid;
//	mid.push_back(3);
//	mid.push_back(2);
//	mid.push_back(4);
//	mid.push_back(1);
//	mid.push_back(6);
//	mid.push_back(7);
//	Node* root=CreateBinaryTree(front,mid,mid.size());
//	cout << "�ؽ�����������:";
//	InOrder(root);
//	cout << endl;
//	cout << "�ؽ����ǰ�����:";
//	PreOrder(root);
//	cout << endl;
//}


//Test3 �ж�һ�ö������Ƿ�����ȫ������
//�������������
typedef BinaryTreeNode<int> Node;

bool _LevelOrder(BinaryTreeNode<int>* root)
{
	queue<Node*> q;

	q.push(root);

	while ((q.front())!=NULL)
	{
		q.push(q.front()->_Left);
		q.push(q.front()->_Right);

		q.pop();
	}

	while (q.size() != 0)
	{
		if (q.front() == NULL)
			q.pop();

		else
			return false;
	}
	return true;
}

bool Is_Compelete(const BinaryTree<int>& t)
{
	if (t.ReturnRoot() == NULL)
		return true;                    //���һ����Ϊ����������������Կ�����ȫ������

	return _LevelOrder(t.ReturnRoot());
}

void Test3()
{
	//int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int a[] = { 1, 2, 3, '#', '#', '#', '#', 5, '#', '#' };
	BinaryTree<int> t(a, sizeof(a) / sizeof(a[0]), '#');
	cout<<"�Ƿ�����ȫ������:"<<Is_Compelete(t)<<endl;
}

int main()
{
	/*Test2();*/
	//Test1();
	Test3();
	return 0;
}