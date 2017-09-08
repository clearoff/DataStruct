#include <iostream>
#include "BinaryTree.hpp"
#include "BinarySearchTree.hpp"
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
////˼��������ĺ������
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
//	if (root->_Left != NULL)                        //�����������ΪNULL  �����������������������
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
//
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
//
//	if (size <= 0||front.size()==0||mid.size()==0)       //�ݹ���ֹ����
//		return NULL;
//	
//	//�ȴ������ڵ�
//	Node* root = new Node(front[0]);                    //ǰ������ĵ�һ���ڵ�Ϊ���ڵ��Ԫ��
//
//	//������������ҵ����ڵ�Ԫ�ص�����λ��
//	int index = 0;
//	for (index = 0; index < size; index++)
//	{
//		if (front[0] == mid[index])
//			break;
//	}
//
//	if (index == size)
//	{
//		cout << "Invaid Input!!!����ʧ��" << endl;
//		exit(0);
//	}
//
//	//����������
//	vector<int> b;   //����
//	vector<int> a;   //�������
//	for (int i = 0; i < index; i++)
//	{
//		b.push_back(mid[i]);
//		a.push_back(front[i+1]);
//	}
//
//	//�ݹ鴴��������
//	root->_Left = CreateBinaryTree(a, b, a.size());
//	a.clear();
//	b.clear();
//	for (int i =index+1; i < size; i++)
//	{
//		b.push_back(mid[i]);
//		a.push_back(front[i]);
//	}
//
//	//�ݹ鴴��������
//	root->_Right = CreateBinaryTree(a, b, a.size());
//	a.clear();
//	b.clear();
//	return root;
//}
//
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
//
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
//	mid.push_back(5);
//	//mid.push_back(7);
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
//typedef BinaryTreeNode<int> Node;
//
//bool _LevelOrder(BinaryTreeNode<int>* root)
//{
//	queue<Node*> q;
//
//	q.push(root);
//
//	while ((q.front())!=NULL)
//	{
//		q.push(q.front()->_Left);
//		q.push(q.front()->_Right);
//
//		q.pop();
//	}
//
//	while (q.size() != 0)
//	{
//		if (q.front() == NULL)
//			q.pop();
//
//		else
//			return false;
//	}
//	return true;
//}
//
//bool Is_Compelete(const BinaryTree<int>& t)
//{
//	if (t.ReturnRoot() == NULL)
//		return true;                    //���һ����Ϊ����������������Կ�����ȫ������
//
//	return _LevelOrder(t.ReturnRoot());
//}
//
//void Test3()
//{
//	//int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	int a[] = { 1, 2, 3, '#', '#', '#', '#', 5, '#', '#' };
//	BinaryTree<int> t(a, sizeof(a) / sizeof(a[0]), '#');
//	cout<<"�Ƿ�����ȫ������:"<<Is_Compelete(t)<<endl;
//}



//������4Ѱ�Ҷ����������ڵ����͹�������
typedef BinaryTreeNode<int> Node;

//ͨ��ǰ������ķ�ʽ�������
bool FindPath(BinaryTreeNode<int>* root, vector<int>& path,const int& value)
{
	/*Ѱ�ҵ���ĳһ���ڵ��·���ҵ��˷���true������·��*/
	if (root == NULL)
	{
		return false;            //��ΪNULL��·��������
	}

	path.push_back(root->_Data); 
	if (root->_Data == value)
		return true;
	/*�����������в���*/
	bool IfFind = FindPath(root->_Left, path, value) || FindPath(root->_Right, path, value);
	if (IfFind)
		return true;
	
	path.pop_back();               //����ڸýڵ���û���ҵ���ɾ��·�����еĽڵ�
	return false;
}

//���Ҷ��������Ƿ����ֵΪn�Ľڵ�
bool HasNode(BinaryTreeNode<int>* root,const int& data)
{
	if (root == NULL)
		return false;
	if (root->_Data == data)
		return true;
	return HasNode(root->_Left, data) || HasNode(root->_Right, data);
}

//�ⷨһ:ʱ�临�Ӷ�ΪO(N^2)���㷨
Node* FindLCA1(BinaryTreeNode<int>* root,const int& n1,const int& n2)
{
	if (HasNode(root->_Left, n1) && HasNode(root->_Left, n2))
		return FindLCA1(root->_Left,n1,n2);
	if (HasNode(root->_Right, n1) && HasNode(root->_Right, n2))
		return FindLCA1(root->_Right, n1, n2);

	return root;
}

//�ⷨ��
Node* FindLCA2(BinaryTree<int>& tree, const int& n1, const int& n2)
{
	vector<int> Findn1Path;
	vector<int> Findn2Path;

	if (FindPath(tree.ReturnRoot(), Findn1Path, n1) && \
		FindPath(tree.ReturnRoot(), Findn2Path, n2))
	{
		int index = -1;
		int size = Findn1Path.size() > Findn2Path.size() ? Findn2Path.size() : Findn1Path.size();
		for (int i = 0; i < size; i++)
		{
			if (Findn1Path[i] != Findn2Path[i])
				break;
			index = i;
		}
		if (index == -1)
			return NULL;
		else
			return new Node(Findn2Path[index]);
	}

	return NULL;
}



//Node* FindLCA(BinaryTree<int>& t,const int& n1,const int& n2)
//{
//	vector<int> Findn1Path;
//	vector<int> Findn2Path;
//	
//	if (FindPath(t.ReturnRoot(), Findn1Path, n1) && FindPath(t.ReturnRoot(), Findn2Path, n2))
//	{
//		int index = -1;                      //��¼���һ����ȼ�ֵ��λ��
//		int size = Findn1Path.size() > Findn2Path.size() ? Findn2Path.size() : Findn1Path.size();
//		for (int i = 0; i < size; i++)
//		{
//			if (Findn1Path[i] != Findn2Path[i])
//				break;                   //�ҵ���һ������ȵļ�ֵ
//			index = i;
//		}
//		if (index == -1)
//			return NULL;               //index=0  ��ʾû����ȵļ�ֵ
//		else
//			return new Node(Findn1Path[index]);
//	}
//
//	cout << "������ֵ����һ����ֵ�ڶ�������û�нڵ�" << endl;
//	return NULL;
//}

//void Test4()
//{
//	int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	BinaryTree<int> t(a, sizeof(a) / sizeof(a[0]), '#');
//	cout<<FindLCA(t, 3, 5)->_Data<<endl;
//	cout << FindLCA(t, 7, 8)->_Data << endl;
//}


//Test5������������ת����һ�������˫������Ҫ���ܴ����κ��µĽ�㣬ֻ�ܵ������н��ָ���ָ��
//typedef BinarySearchTreeNode<int> Node;
//
//
//void ConvertNode(Node* root, Node*& PrevNode)
//{
//	if (root == NULL)
//		return;
//
//	if (root->_left != NULL)
//		ConvertNode(root->_left, PrevNode);
//	root->_left = PrevNode;                //��ǰ�ڵ�ָ��ǰһ���ڵ�
//	if (PrevNode)
//		PrevNode->_right = root;
//	PrevNode = root;
//	ConvertNode(root->_right, PrevNode);
//
//}
//
//Node* BinaryTreeTOList(Node* root)
//{
//	if (root == NULL)
//		return NULL;
//	Node* Head = root;
//	while (Head->_left != NULL)
//	{
//		Head = Head->_left;           //��������������ڵ�
//	}
//	Node* PrevNode = NULL;
//	Con                                                                                                                                                                                                                                                    ode);
//	return Head;
//}
//
//void PrintList(Node* Head)
//{
//	while (Head != NULL)
//	{
//		cout << Head->_key << " ";
//		Head = Head->_right;
//	}
//	cout << endl;
//}
//
//void Test5()
//{
//	BinarySearchTree<int> t1;
//	t1.Insert(5);
//	t1.Insert(4);
//	t1.Insert(6);
//	t1.Insert(7);
//	t1.Insert(1);
//	t1.Insert(3);
//	t1.Insert(2);
//	t1.Insert(9);
//	t1.Insert(8);
//	t1.InorderR();
//	Node* Head=BinaryTreeTOList(t1.ReturnRoot());
//	PrintList(Head);
//}

//int main()
//{
//	//*Test2();
//	//Test2();
//	//Test3();
//	//Test4();
//	/*Test5();*/
//	return 0;
//}

void TestLCA()
{
	int a[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int> t(a, sizeof(a) / sizeof(a[0]), '#');
	cout << "FindLCA(3,5):"<<FindLCA2(t ,3, 5)->_Data << endl;
	cout << "FindLCA(5,6):" << FindLCA2(t, 6, 5)->_Data << endl;
}

int main()
{
	TestLCA();
	return 0;
}