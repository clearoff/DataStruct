#pragma once 
#include <iostream>
using namespace std;
#include <assert.h>
#include <queue>
#include <stack>
#include <vector>

template<class T>
struct BinaryTreeNode
{
	T _Data;
	BinaryTreeNode<T>* _Left;
	BinaryTreeNode<T>* _Right;
	BinaryTreeNode()
		:_Left(NULL)
		, _Right(NULL)
		, _Data(T())
	{}
	BinaryTreeNode(const T&  x)
		:_Data(x)
		, _Left(NULL)
		, _Right(NULL)
	{}
};


template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T>* pNode;
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
		//, _index(0)
	{}

	BinaryTree(const T* str,size_t size,const T& invaild)
		//:_index(0)
	{
		cout << "创建二叉树" << endl;
		size_t index = 0;
		_root=_CreateBinaryTree(str,size,invaild,index);          //前序创建二叉树
	}

	~BinaryTree()
	{
		_Destroy(_root);
	}

	BinaryTree(const BinaryTree<T>& BT)
	{
		_root=_Copy(BT._root);
	}

	size_t FindKLevel(size_t k)                              //找到第K层的节点数
	{
		assert(k > 0);
		assert(k <= Depth());
		size_t count = k - 1;
		return _FindKLevel(_root, count);
	}

	void PrevOrder()                                        //前序遍历二叉树
	{ 
		assert(_root);
		_PreOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		assert(_root);
		_InOrder(_root);
		cout << endl;
	}

	void PrevOrderNR()
	{
		Node* cur = _root;
		stack<Node*>   s;
		if (cur != NULL)
		{
			s.push(cur);
			while (!s.empty())
			{
				Node* top = s.top();  
				cout << top->_Data << " ";             //访问当前节点
				s.pop();
				if (top->_Right)
					s.push(top->_Right);
				if (top->_Left)
					s.push(top->_Left);
			}
		}
	}

	/*void PrevOrderfNR()
	{
		stack<Node*> s;
		Node* cur = _root;

		while (cur||!s.empty())
		{
			while (cur)
			{
				cout << cur->_Data << " ";
				s.push(cur);
				cur = cur->_Left;
			}

			Node* top = s.top();
			s.pop();

			cur = top->_Right;
		}
		cout << endl;
	}
*/
	//void InOrderNR()
	//{
	//	stack<Node*> s;
	//	Node* cur = _root;

	//	while (cur || !s.empty())
	//	{
	//		while (cur)
	//		{
	//			s.push(cur);
	//			cur = cur->_Left;
	//		}

	//		Node* top = s.top();
	//		s.pop();
	//		cout << top->_Data << " ";

	//		cur = top->_Right;
	//	}
	//	cout << endl;
	//}

	///*void PostOrderNR()
	//{
	//	Node* cur = _root;
	//	stack<Node*> s;
	//	Node* Prev = NULL;
	//	while (cur)
	//	{
	//		while (cur->_Left)
	//		{
	//			s.push(cur);
	//			cur = cur->_Left;
	//		}
	//		while (cur->_Right==NULL || cur->_Right == Prev)
	//		{
	//			cout << cur->_Data << " ";
	//			Prev = cur;

	//			if (s.empty())
	//				return;

	//			cur = s.top();
	//			s.pop();
	//		}
	//		s.push(cur);
	//		cur = cur->_Right;
	//	}
	//	cout << endl;*/
	//}

	void PostOrderNR()
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* Prev=NULL;           //右子树访问标志位
		while (cur || !s.empty())
		{
			while (cur)              //左子树入栈，直到左子树遇到空节点
			{
				s.push(cur);
				cur = cur->_Left;
			}

			cur = s.top();      //遇到左子树为空，退回到上一节点
			if (cur->_Right == NULL || cur->_Right == Prev)
			{
				cout << cur->_Data << " ";
				Prev = cur;
				s.pop();
				cur = NULL;
			}
			else
			{
				cur = cur->_Right;
			}
		}
		cout << endl;
	}

	void PostOrder()
	{
		assert(_root);
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()   //层序遍历
	{
		queue<Node*> q1;
		q1.push(_root);
		while (!q1.empty())
		{
			cout << q1.front()->_Data << " ";
			if (q1.front()->_Left != NULL)
			{
				q1.push((q1.front()->_Left));
			}
			if (q1.front()->_Right != NULL)
			{
				q1.push((q1.front()->_Right));
			}
			q1.pop();
		}
		cout << endl;
	}

	void MorrisInorder()
	{
		Node* cur = _root;
		Node* tmp = NULL;
		while (cur)
		{
			if (!cur->_Left)
			{
				cout << cur->_Data << " ";
				cur = cur->_Right;
			}
			else
			{
				tmp = cur->_Left;
				while (tmp->_Right&&tmp->_Right != cur)
				{
					tmp = tmp->_Right;                //找到左子树中最右边的节点
				}

				if (tmp->_Right == NULL)
				{
					tmp->_Right = cur;
					cur = cur->_Left;
				}
				else
				{
					cout << cur->_Data << " ";
					tmp->_Right = NULL;
					cur = cur->_Right;
				}
			}
		}
	}

	size_t Depth()        //二叉树的深度
	{
			return _Depth(_root);
	}

	size_t Size()         //二叉树结点个数
	{
		return _Size(_root);
	}

	size_t LeafSize()     //叶子节点个数
	{
		return _LeafSize(_root);
	}

	virtual Node* Find(const T& x)
	{
		Node* ret=_Find(_root, x);
		return ret;
	}

	void InsertNode(const T& Ins)
	{
		Node* cur = _root;
		Node* Prev = NULL;

		while (cur)
		{
			Prev = cur;
			if (cur->_Data > Ins)
				cur = cur->_Left;
			else
				cur = cur->_Right;
		}

		if (_root == NULL)
		{
			_root = new Node(Ins);
		}
		else if (Ins < Prev->_Data)
			Prev->_Left = new Node(Ins);
		else
			Prev->_Right = new Node(Ins);
	}

	void CopyDelete(pNode& node)
	{
		Node* DelNode = node;
		Node* Prev = NULL;
		if (node->_Right == NULL)              //右子树为空,
			node = node->_Left;
		else if (node->_Left == NULL)          //左子树为空
			node = node->_Right;
		else                                   //左右子树都不为空，找左子树中的最右边的节点
		{
			DelNode = node->_Left;
			Prev = node;;
			while (DelNode->_Right)
			{
				Prev = DelNode;
				DelNode = DelNode->_Right;
			}
			node->_Data = DelNode->_Data;
			if (Prev == node)
			{
				Prev->_Left = DelNode->_Left;
			}
			else
			{
				Prev->_Right = DelNode->_Left;
			}
		}
		delete DelNode;
	}

	Node* ReturnRoot() const
	{
		return _root;
	}
protected:

	size_t _FindKLevel(Node* root,size_t count)
	{
		if (count == 0 && root != NULL)
		{
			return 1;
		}
		if (count != 0 && root != NULL)
		{
			return  _FindKLevel(root->_Left,count-1) +
				_FindKLevel(root->_Right, count-1) ;
		}
		return 0;
	}

	Node* _Find(Node* root, const T& x)
	{
		if (root == NULL)
			return root;
		else if (root->_Data != x)
		{
			Node* tmp = tmp = _Find(root->_Left, x);
			if (tmp == NULL)    //如果左子树没有找到则访问右子树
			{
				tmp = _Find(root->_Right, x);
			}
			return tmp;
		}
		else
		{
			return root;
		}
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		else if (root->_Left=NULL&&root->_Right==NULL)
		{
			delete root;
		}
		else
		{
			_Destory(root->_Left);
			_Destory(root->_Right);
		}
	}
	Node* _Copy(Node* root)
	{
		Node* NewNode = new Node;
		if (root == NULL)
		{ 
			return NULL;
		}
		else
		{
			NewNode->_Data = root->_Data;
			NewNode->_Left = _Copy(root->_Left);
			NewNode->_Right = _Copy(root->_Right);
		}
		return NewNode;
	}

	size_t _LeafSize(Node* root)
	{
		size_t count = 0;
		if (root == NULL)
			return 0;
		else if ((root->_Left) == NULL && (root->_Right == NULL))
		{
			return 1;
		}
		else
		{
			return count+=(_LeafSize(root->_Left) + _LeafSize(root->_Right));
		}
	}

	size_t _Size(Node* root)
	{
		size_t count = 0;
		if (root != NULL)
		{
			count++;
			count += _Size(root->_Left)+_Size(root->_Right);
		}
		else
		{
			return count;
		}
		return count;
	}

	size_t _Depth(Node* root)
	{
		size_t Left_Depth = 1;
		size_t Right_Depth = 1;
		if (root != NULL)
		{
			Left_Depth += _Depth(root->_Left);
			Right_Depth += _Depth(root->_Right);
			return (Left_Depth > Right_Depth) ? Left_Depth : Right_Depth;
		}
		else
		{
			return 0;
		}
	}

	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_Left);
			_PostOrder(root->_Right);
			cout << root->_Data << " ";
		}
		else
		{
			return;
		}
	}

	void _InOrder(Node* root)
	{
		if (root != NULL)
		{
			_InOrder(root->_Left);
			cout << root->_Data<<" ";
			_InOrder(root->_Right);
		}
		else
		{
			return;
		}
	}

	void _PreOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_Data << " ";
			_PreOrder(root->_Left);
			_PreOrder(root->_Right);
		}
		else
		{
			return;
		}
	}

	Node* _CreateBinaryTree(const T*& a, size_t size, const T& invaild,size_t& index)
	{
		Node* root = NULL;
		if ((index < size) && (a[index] != invaild))
		{
			root = new Node(a[index]);
			root->_Left = _CreateBinaryTree(a, size, invaild, ++index);
			root->_Right = _CreateBinaryTree(a, size, invaild, ++index);
		}
		return root;
	}

protected:
	Node* _root;
};




template<class T>
class BinaryBalanceTree :public BinaryTree<T>
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryBalanceTree(BinaryTree<T>& bt)
	{
         _GenerateArry(bt.ReturnRoot());
		 _GenerateBalanceTree(0,v1.size()-1);
	}

	void Print_Array()
	{
		for (int i = 0; i < v1.size(); i++)
		{
			cout << v1[i] << " ";
		}
		cout << endl;
	}

	virtual Node* Find(const T& x)
	{
		return _Find(_root, x);
	}
private:
	Node* _Find(Node* root, const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_Data == x)
		{
			return root;
		}

		if (root->_Data > x)            //如果要查找的节点的值小于根节点的值  再左子树中查找
		{
			return _Find(root->_Left, x);
		}
		else
		{
			return _Find(root->_Right, x);
		}
	}

	void Sort_Array()
	{
		int j;
		int i;
		for (i = 1; i < v1.size(); i++)
		{
			T TmpData = v1[i];
			for (j = i - 1; (j >= 0) && (TmpData < v1[j]); j--)
			{
				v1[j+1] = v1[j];
			}
			v1[j + 1] = TmpData;
		}
	}

	void _GenerateBalanceTree(int first,int last)
	{
		Sort_Array();
		if (first <= last)
		{
			int mid = first + (last - first) / 2;
			this->InsertNode(v1[mid]);
			_GenerateBalanceTree(first, mid - 1);
			_GenerateBalanceTree(mid+1,last);
		}
	}

	void _GenerateArry(Node* root)
	{
		Node* cur = root;
		stack<Node*> s;
		if (cur)
		{
			s.push(cur);
			while (!s.empty())
			{
				Node* top = s.top();
				v1.push_back(top->_Data);
				s.pop();
				if (top->_Right)
					s.push(top->_Right);
				if (top->_Left)
					s.push(top->_Left);
			}
		}
	}
protected:
	vector<T> v1;
};