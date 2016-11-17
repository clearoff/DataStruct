#pragma once

#include <iostream>
using namespace std;
#include <cassert>
#include <string>


template <class K,class V>
struct AVLTreeNode
{
	K _key;
	AVLTreeNode<K, V>* _Left;
	AVLTreeNode<K, V>* _Right;
	AVLTreeNode<K, V>* _parent;
	V _value;
	int _bf;             //平衡因子（右子树高度-左子树高度）

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		, _Left(NULL)
		, _Right(NULL)
		, _parent(NULL)
		, _value(value)
		, _bf(0)
	{}
};


template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V>  Node;

public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		//找到所要插入的位置
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_Left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_Right;
			}
			else
				return false;
		}

		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_Right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_Left = cur;
			cur->_parent = parent;

		}

		while (parent)
		{
			//
			if (parent->_Left ==cur)
				parent->_bf--;
			else
				parent->_bf++;


			if (parent->_bf == 0)
				break;
			else if (abs(parent->_bf) == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else
			{
				/*_UpdataBalanceFactor(parent);*/
				if ((parent->_bf == -2) && (parent->_Left->_bf == -1))
				{
					//进行右单旋
					_RotateR(parent);
				}

				else if ((parent->_bf == 2) && (parent->_Right->_bf) == 1)
				{
					//进行左单旋
					_RotateL(parent);
				}

				else if ((parent->_bf == 2) && (parent->_Right->_bf == -1))
				{
					//进行右左双旋
					_RotateRL(parent);
				}

				else
				{
					//进行左右双旋
					_RotateLR(parent);
				}
				break;
			}
		}
			return true;
	}

		void Inorder()
		{
			_Inorder(_root);
			cout << endl;
		}

		//判断是否平衡
		bool IsBalance()
		{
			return _IsBalance(_root);
		}

		size_t GetHeight()
		{
			return _Height(_root);
		}

		bool IsBalanceOp()
		{
			int Height = 0;
			bool ret= _IsBalanceOp(_root,Height);
			cout << "Tree's height is:" << Height << endl;
			return ret;
		}
protected:
	bool _IsBalanceOp(Node* root,int& Height)
	{  
		if (root == NULL)
		{
			Height = 0;
			return true;
		}

		int RHeight = 0;
		int LHeight = 0;

		if (_IsBalanceOp(root->_Left, LHeight) == false)
		{
			Height = _Height(root);
			return false;
		}
		else if (_IsBalanceOp(root->_Right, RHeight) == false)
		{
			Height = _Height(root);
			return false;
		}

		Height = LHeight > RHeight ? LHeight + 1 : RHeight + 1;
		return abs(RHeight-LHeight) <= 1;
	}

		bool _IsBalance(Node* root)
		{
			if (root == NULL)
			{
				return true;
			}

			int LHeight = _Height(root->_Left);
			int RHeight = _Height(root->_Right);
			int bf = RHeight - LHeight;
			if (bf != root->_bf)
			{
				cout << "平衡因子异常：" << root->_key << endl;
				return false;
			}
			return (abs(RHeight-LHeight)<2)&&(_IsBalance(root->_Left))&&(_IsBalance(root->_Right));
		}


		size_t _Height(Node* root)
		{
			if (root == NULL)
				return 0;

			if (root->_Right==NULL&&root->_Left==NULL)
				return 1;

			return _Height(root->_Left) > _Height(root->_Right) ?
				_Height(root->_Left) + 1 : _Height(root->_Right) + 1;
		}
		//中序遍历
		void _Inorder(Node* root)
		{
			if (root == NULL)
				return;

			_Inorder(root->_Left);
			cout << "Key:"<<root->_key << " Balance Factor:"<<root->_bf<<endl;
			_Inorder(root->_Right);
		}
		//使树平衡
		void _UpdataBalanceFactor(Node*& root)
		{
			if ((root->_bf == -2) && (root->_Left->_bf == -1))
			{
				//进行右单旋
				_RotateR(root);
			}

			else if ((root->_bf == 2) && (root->_Right->_bf) == 1)
			{
				//进行左单旋
				_RotateL(root);
			}

			else if ((root->_bf == 2) && (root->_Right->_bf == -1))
			{
				//进行右左双旋
				_RotateRL(root);
			}

			else
			{
				//进行左右双旋
				_RotateLR(root);
			}
		}
		//右单旋
		void _RotateR(Node* root)
		{
			Node* SubL = root->_Left;
			Node* SubLR = root->_Left->_Right;
			Node* ppNode = root->_parent;
			root->_Left = SubLR;
			if (SubLR)
				SubLR->_parent = root;
			SubL->_Right = root;
			if (root->_parent == NULL)
			{
				SubL->_parent = NULL;
				_root = SubL;
			}
			else
			{
				SubL->_parent = ppNode;
				if (ppNode->_Left == root)
					ppNode->_Left = SubL;
				else
					ppNode->_Right = SubL;
			}
			root->_parent = SubL;
			root->_bf = SubL->_bf = 0;
		}

		void _RotateL(Node* root)
		{
			Node* SubR = root->_Right;
			Node* SubRL = root->_Right->_Left;
			Node* ppNode = root->_parent;

			root->_Right = SubRL;
			if (SubRL)
				SubRL->_parent = root;
			SubR->_Left = root;
			if (root->_parent == NULL)
			{
				_root = SubR;
				SubR->_parent = NULL;
			}
			else
			{
				SubR->_parent = ppNode;
				if (ppNode->_Left == root)
					ppNode->_Left = SubR;
				else
					ppNode->_Right = SubR;
			}
			root->_parent = SubR;
			root->_bf = SubR->_bf = 0;
		}
	
		void _RotateRL(Node* root)
		{
			Node* parent = root;
			Node* SubR = parent->_Right;
			Node* SubRL = SubR->_Left;
			int bf = SubRL->_bf;
			_RotateR(root->_Right);
			_RotateL(root);

			//双旋后更新平衡因子
			if (bf == 0)
			{
				parent->_bf = SubR->_bf = SubRL->_bf = 0;
			}
			else if (bf == -1)
			{
				SubRL->_bf = parent->_bf = 0;
				SubR->_bf = 1;
			}
			else
			{
				SubRL->_bf = SubR->_bf = 0;
				parent->_bf = -1;
			}
		}

		void  _RotateLR(Node* root)
		{
			Node* parent = root;
			Node* SubL = root->_Left;
			Node* SubLR = SubL->_Right;
			int bf = SubLR->_bf;
			_RotateL(root->_Left);
			_RotateR(root);

			//双旋后更新平衡因子

			if (bf == 0)
			{
				parent->_bf = SubL->_bf = SubLR->_bf = 0;
			}
			else if (bf == 1)
			{
				parent->_bf = SubLR->_bf = 0;
				SubL->_bf = -1;
			}
			else
			{
				SubL->_bf = 0;
				parent->_bf = 1;
				SubLR->_bf = 0;
			}
		}
	protected:
		Node* _root;

};
