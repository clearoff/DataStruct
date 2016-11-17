#pragma once 
#include <iostream>
using namespace std;


template<class K, int M>
struct BTreeNode
{
	K _keys[M];                       //关键字数组
	BTreeNode<K, M>* _subs[M + 1];    //子节点数组
	BTreeNode<K, M>* _parent;         //父节点
	size_t _size;

	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = K();
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}

};

template<class K, int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair<Node*, int> Find(const K& key)
	{
		
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			while (i < cur->_size)
			{
				if (cur->_keys[i] < key)               //如果cur->_keys[i] < key数组下标向后移动
				{
					++i;
				}
				else if (cur->_keys[i] > key)          //如果cur->_keys[i] > key
				{
					break;
				}
				else
					return pair<Node*, int>(cur, i);   //找到了返回cur和要查找的元素在cur->_keys中的下标
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return pair<Node*, int>(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (_root == NULL)                    //根节点为空
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}

		pair<Node*, int> FindNode = Find(key);
		if (FindNode.second != -1)            //节点已经存在不需要插入
		{
			return false;
		}

		//需要插入key
		Node* cur = FindNode.first;         //要插入节点
		Node* parent = cur->_parent;        //要插入节点的父节点
		Node* sub = NULL;
		K newKey = key;
		while (1)
		{
			InsertKey(cur, newKey, sub);       //插入关键字key
			//判断分裂
			if (cur->_size < M)
			{
				//不需要分裂
				return true;
			}

			//进行分裂
			size_t mid = cur->_size / 2;    //找到中间节点
			Node* tmp = new Node;
			size_t j = 0;
			newKey = cur->_keys[mid];
			size_t i = 0;
			for (i = mid + 1; i < cur->_size; i++)    //拷贝cur->_keys中间下标右边的关键字
			{
				//subs和keys的拷贝
				tmp->_keys[j] = cur->_keys[i];
				tmp->_subs[j] = cur->_subs[i];     //errot
				j++;

				if (cur->_subs[i])
					cur->_subs[i]->_parent = tmp;
				//恢复subs和keys的默认值
				cur->_subs[i] = NULL;
				cur->_keys[i] = K();

				//调整size
				cur->_size--;
				tmp->_size++;
			}
			tmp->_subs[j] = cur->_subs[i];
			if (cur->_subs[i])
				cur->_subs[i]->_parent = tmp;
			cur->_subs[i] = NULL;

			cur->_keys[mid] = K();
			cur->_size--;

			if (parent == NULL)   //cur是根节点
			{
				_root = new Node;
				_root->_keys[0] = newKey;
				_root->_size = 1;

				_root->_subs[0] = cur;
				_root->_subs[1] = tmp;

				if (cur)
					cur->_parent = _root;
				if (tmp)
					tmp->_parent = _root;
				return true;
			}

			//cur不是根节点，继续向上调整
			cur = parent;
			parent = cur->_parent;
			sub = tmp;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		Node* prev = NULL;
		for (size_t i = 0; (i < root->_size); i++)
		{
			if (root->_subs[i]!=prev)
				_InOrder(root->_subs[i]);
			cout << root->_keys[i] << " ";
			if (root->_subs[i + 1])
			{
				_InOrder(root->_subs[i + 1]);
				prev = root->_subs[i + 1];
			}
		}
	}

	void InsertKey(Node* node, const K& key, Node* sub)
	{
		int i = node->_size - 1;              //取得当前节点的keys的最后一个关键字的下标
		while (i >= 0)
		{
			if ((node->_keys[i] < key))
			{
				break;
			}
			else   //node->keys[i] > key    移动关键字和subs
			{
				node->_keys[i + 1] = node->_keys[i];
				node->_subs[i + 2] = node->_subs[i + 1];
			}
			i--;
		}
		node->_keys[i + 1] = key;          //插入关键字key
		node->_subs[i + 2] = sub;          //插入sub
		node->_size++;
		if (sub)
			sub->_parent = node;          //sub指向其父节点
	}

protected:
	Node* _root;
};



// _parent指针的问题