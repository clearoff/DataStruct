#pragma once 
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <queue>
#include "Heap.hpp"
#include "UnionSet.hpp"

template<class T>
struct Compare
{
	bool operator()(const T& n1, const T& n2)
	{
		return n1->_w  <  n2->_w;
	}
};

template<class V,class W>
class GraphLink
{
	struct Node      //�ڽӱ�Ķ���
	{
		W _w;
		size_t _dst;
		size_t _src;
		Node* _next;

		Node(size_t src, size_t dst, const W& w)  
			:_src(src)
			, _dst(dst)
			, _w(w)
			, _next(NULL)
		{}


	};
public:
	GraphLink( const size_t& size,const V* Vertex, const bool& IsDirected = false)
		: _Vertex(Vertex,Vertex+size)
		, _IsDirected(IsDirected)
		, _tables(size,NULL)
	{
		//for (int i = 0; i < Vertex.size(); i++)
		//{
		//	_Vertex[i] = Vertex[i];            //��ʼ������
		//}

	/*	_tables.resize(Vertex.size());    */
	}

	GraphLink()
	{}

	~GraphLink()
	{
		//for (int i = 0; i < _Vertex.size(); i++)
		//{
		//	Node* cur = _tables[i];
		//	while (cur != NULL)
		//	{
		//		Node* tmp = cur;
		//		cur = cur->_next;
		//		delete tmp;
		//	}
		//}
		//delete[] _tables;
		cout << "�ڴ��ͷ����" << endl;
	}

	size_t GetIndex(const V& value)          //����ֵΪvalue��Ԫ����Vertex�е��±�
	{
		for (int i = 0; i < _Vertex.size(); i++)
		{
			if (_Vertex[i] == value)
				return i;
		}

		throw GraphLink();
	}

	void AddSide(const size_t& src, const size_t& dst, const W& w)
	{
		Node* tmp = new Node(src, dst, w);

		tmp->_next = _tables[src];
		_tables[src] = tmp;
	}

	void AddNode(const V& src, const V& dst, const W& w = W())
	{
		size_t SrcIndex, DstIndex;
		try{
			SrcIndex = GetIndex(src);
			DstIndex = GetIndex(dst);
			AddSide(SrcIndex, DstIndex, w);
			AddSide(DstIndex, SrcIndex, w);
		}
		catch (...)
		{
			cout << "��������" << endl;
		}
	}

	bool Dijkstra(GraphLink<V,W>& tmp)         //ͼ�ĵϽ�˹�����㷨���������ͼ��
	{
		if (_Vertex.size() == 0)
			return false;

		Heap<Node*, Compare<Node*>> hp;

		for (size_t i = 0; i < _Vertex.size(); i++)          //���ڽӱ������еĽڵ���ڶ��У����սڵ�ıߵ���С�ѣ�
		{
			Node* cur = _tables[i];
			while (cur)
			{
				hp.Push(cur);
				cur = cur->_next;
			}
		}

		UnionSet<W> set(_Vertex.size());
		while (hp.size() > 0)
		{
			Node* cur = hp.Top();
			hp.Pop();

			/*set.Merge(cur->_src, cur->_dst);*/
			int root1 = set.ReturnRoot(cur->_src);
			int root2 = set.ReturnRoot(cur->_dst);

			if (root1 != root2)     //û�й��ɻ�· ������ͨ������
			{
				tmp.AddSide(cur->_src, cur->_dst,cur->_w);
				tmp.AddSide(cur->_dst, cur->_src, cur->_w);
				set.Merge(cur->_src, cur->_dst);
			}
		}
	}

	void DFS(const V& v) //������ȱ���
	{
		vector<bool> Visited(_Vertex.size(), false);         //�洢�ڵ������ǵ�����
		_DFS(GetIndex(v), Visited);
		cout << endl;
	}

	void BSF(const V& v)
	{
		int Index = GetIndex(v);
		vector<bool> Visited(_Vertex.size(), false);
		_BSF(v, Visited);
		for (int i = 0; i < _Vertex.size(); i++)
		{
			_BSF(_Vertex[i],Visited);
		}
		cout << endl;
	}

	void _BSF(const V& v,vector<bool>& Visited)
	{
		/*vector<bool> Visited(_Vertex.size(), false);*/
		queue<size_t> q;
		q.push(GetIndex(v));
		while (!q.empty())
		{
			int index=q.front();
			cout << _Vertex[index] << ":" << index << "->";
			Visited[index] = true;
			q.pop();
			Node* cur = _tables[index];
			while (cur&&Visited[cur->_dst] == false)
			{
				q.push(cur->_dst);
				cur = cur->_next;
			}
		}
		cout << endl;
	}

	void PrintLink()
	{
		for (int i = 0; i < _Vertex.size(); i++)
		{
			Node* cur = _tables[i];
			cout << _Vertex[i]<<":"<<GetIndex(_Vertex[i])<<"->";
			while (cur)
			{
				cout << _Vertex[cur->_dst] << ":" << cur->_dst << "->";
				cur = cur->_next;
			}
			cout << endl;
		}
	}
protected:
	void _DFS(const size_t& index,vector<bool>& Visited)
	{
		cout << _Vertex[index] << ":"<<index << "->";
		Visited[index] = true;
		Node* cur = _tables[index];
		while (cur)
		{
			if (Visited[cur->_dst] == false)
			{
				_DFS(cur->_dst, Visited);                   //�����һ���ڵ�û�б�������������ȱ�����һ���ڵ�
			}
			cur = cur->_next;
		}
	}
protected:
	vector<V> _Vertex;
	vector<Node*> _tables;
	bool _IsDirected;
};


void TestGraphLink()
{
	string City[5] = { "A","B","C","D","E"};
	GraphLink<string, int> gm(5, City);
	gm.AddNode("A", "B", 10);
	gm.AddNode("A", "E", 30);
	gm.AddNode("A", "D", 20);
	gm.AddNode("B", "C", 15);
	gm.AddNode("D", "C", 20);
	//gm.AddNode("A", "B", 10);
	gm.PrintLink();
	cout << endl;
	GraphLink<string, int> gm1(5, City);
	gm.Dijkstra(gm1);
	gm1.PrintLink();
	//cout << endl;
	//gm.DFS("����");
	//gm.DFS("����");
	//gm.DFS("��������");
	//gm.DFS("ŦԼ");
	//gm.DFS("˹̨��˹");
	//gm.BSF("����");
}