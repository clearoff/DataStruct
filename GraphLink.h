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
	struct Node      //邻接表的顶点
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
		//	_Vertex[i] = Vertex[i];            //初始化顶点
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
		cout << "内存释放完毕" << endl;
	}

	size_t GetIndex(const V& value)          //返回值为value的元素在Vertex中的下标
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
			cout << "参数错误" << endl;
		}
	}

	bool Dijkstra(GraphLink<V,W>& tmp)         //图的迪杰斯特拉算法（针对无向图）
	{
		if (_Vertex.size() == 0)
			return false;

		Heap<Node*, Compare<Node*>> hp;

		for (size_t i = 0; i < _Vertex.size(); i++)          //将邻接表中所有的节点放在堆中（按照节点的边得最小堆）
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

			if (root1 != root2)     //没有构成回路 不能连通这条边
			{
				tmp.AddSide(cur->_src, cur->_dst,cur->_w);
				tmp.AddSide(cur->_dst, cur->_src, cur->_w);
				set.Merge(cur->_src, cur->_dst);
			}
		}
	}

	void DFS(const V& v) //深度优先遍历
	{
		vector<bool> Visited(_Vertex.size(), false);         //存储节点遍历标记的数组
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
				_DFS(cur->_dst, Visited);                   //如果下一个节点没有遍历过，继续深度遍历下一个节点
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
	//gm.DFS("北京");
	//gm.DFS("安康");
	//gm.DFS("克利夫兰");
	//gm.DFS("纽约");
	//gm.DFS("斯台普斯");
	//gm.BSF("北京");
}