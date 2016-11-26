#pragma once 
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <queue>

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

	size_t GetIndex(const V& value)          //返回值为value的元素在Vertex中的下标
	{
		for (int i = 0; i < _Vertex.size(); i++)
		{
			if (_Vertex[i] == value)
				return i;
		}

		throw invalid_argument("参数错误");
	}

	void AddSide(const size_t& src, const size_t& dst, const W& w)
	{
		Node* tmp = new Node(src, dst, w);

		tmp->_next = _tables[src];
		_tables[src] = tmp;
	}

	void AddNode(const V& src, const V& dst, const W& w = W())
	{
		size_t SrcIndex = GetIndex(src);
		size_t DstIndex = GetIndex(dst);

		AddSide(SrcIndex, DstIndex, w);
		AddSide(DstIndex, SrcIndex, w);
	}

	void DFS(const V& v) //深度优先遍历
	{
		vector<bool> Visited(_Vertex.size(), false);         //存储节点遍历标记的数组
		_DFS(GetIndex(v), Visited);
		cout << endl;
	}

	void BSF(const V& v)
	{
		vector<bool> Visited(_Vertex.size(), false);
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
	string City[5] = { "安康", "克利夫兰", "纽约", "斯台普斯", "北京" };
	GraphLink<string, int> gm(5, City);
	gm.AddNode("安康", "北京", 200);
	gm.AddNode("安康", "纽约", 200);
	gm.AddNode("安康", "克利夫兰", 200);
	gm.AddNode("斯台普斯", "北京", 200);
	gm.AddNode("克利夫兰", "北京", 200);
	gm.AddNode("纽约", "北京", 200);
	gm.AddNode("纽约", "克利夫兰", 200);
	//gm.PrintLink();
	/*gm.DFS("北京");
	gm.DFS("安康");
	gm.DFS("克利夫兰");
	gm.DFS("纽约");
	gm.DFS("斯台普斯");*/
	gm.BSF("北京");
}