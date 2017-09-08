#pragma once

#include <iostream>
using namespace std;
#include <cassert>

template<class T>
struct BinarySearchTreeNode
{
	T _key;
	BinarySearchTreeNode<T>* _left;
	BinarySearchTreeNode<T>* _right;
	/*BinarySearchTreeNode<T>* _parent;*/

	BinarySearchTreeNode(const T& x)
		:_key(x)
		, _left(NULL)
		, _right(NULL)
		//, _parent(NULL)
	{}

	BinarySearchTreeNode()
		:_left(NULL)
		, _right(NULL)
		//, _parent(NULL)
	{}
};



template <class T>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<T> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	Node* ReturnRoot()
	{
		return _root;
	}

	bool Insert(const T& x)
	{
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}

		Node* cur = _root;
		Node* prev = NULL;
		while (cur)
		{
			prev = cur;
			if (cur->_key < x)
				cur = cur->_right;
			else if (cur->_key > x)
				cur = cur->_left;
			else
				return false;
		}
		if (x > prev->_key)
		{
			prev->_right = new Node(x);
			/*if (prev->_right)
			{
				prev->_right->_parent = prev;
			}*/
		}
		else
		{
			prev->_left = new Node(x);
			/*if (prev->_left)
			    prev->_left->_parent = prev;*/
		}
		return true;
	}

	void InorderR()
	{
		_InorderR(_root);
		cout << endl;
	}

	bool Remove(const T& x)
	{
		if (_root == NULL)
			return false;
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < x)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > x)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				Node* del = cur;
				if (cur->_left == NULL)
				{
					if (cur==_root)
					{
						//
						_root = _root->_right;
					}
					else
					{
						if (parent->_left == cur)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;
					}
				}
				else if (cur->_right == NULL)
				{
					if (cur==_root)
					{
						//
						_root = _root->_left;
					}
					else
					{
						if (parent->_left == cur)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;
					}
				}
				else
				{
					Node* MinRight = cur->_right;
					parent = cur;
					while (MinRight->_left)
					{
						parent = MinRight;
						MinRight = MinRight->_left;
					}
					del = MinRight;
					cur->_key = MinRight->_key;
					if (parent->_left == MinRight)
					{
						parent->_left = MinRight->_right;
					}
					else
						parent->_right = MinRight->_right;
				}
				delete del;
				return true;
			}
		}
		return false;
	}

	bool InsertR(const T& x)
	{
		return _InsertR(_root, x);
	}
protected:
	bool _InsertR(Node*& root,const T& x)
	{
		if (root == NULL)
		{
			root = new Node(x);
			return true;
		}
		
		
		if (root->_key > x)
			return _InsertR(root->_left, x);

		if (root->_key < x)
			return _InsertR(root->_right, x);

		else
			return false;
	}

	void _InorderR(Node* root)
	{
		if (root == NULL)
			return;

		_InorderR(root->_left);
		cout << root->_key << " ";
		_InorderR(root->_right);
	}
protected:
	Node* _root;
};