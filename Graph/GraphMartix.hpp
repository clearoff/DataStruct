#include <iostream>
using namespace std;
#include <cassert>
#include<string>

template<class V, class W>
class GraphMartix
{
public:
	GraphMartix(const size_t& size, const V* Vertex, const bool& IsDirected = false)
		:_size(size)
		, _Vertex(new V[size])
		, _IsDirected(IsDirected)
	{
		for (int i = 0; i < size; i++)
		{
			_Vertex[i] = Vertex[i];
		}

		_Martix = new W*[size];
		for (int i = 0; i < size; i++)
		{
			_Martix[i] = new W[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				_Martix[i][j] = 0;
		}
	}

	size_t GetIndex(const V& value)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_Vertex[i] == value)
			{
				return i;
			}
		}

		throw invalid_argument("参数错误");  //没有查找到则抛出异常
	}

	void AddSide(const V& src, const V& dst, const W& w = W())
	{
		size_t SrcIndex = GetIndex(src);
		size_t DstIndex = GetIndex(dst);

		if (_IsDirected)
		{
			//如果是有向图
			_Martix[SrcIndex][DstIndex] = w;
			/*return true;*/
		}
		else
		{
			_Martix[SrcIndex][DstIndex] = w;
			_Martix[DstIndex][SrcIndex] = w;
			/*return true;*/
		}
	}

	void PrintMartix()
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
				cout << _Martix[i][j] << " ";
			cout << endl;
		}
	}
protected:
	V*   _Vertex;
	W**  _Martix;
	bool _IsDirected;
	size_t _size;
};


void TestGraphMartix()
{
	string City[5] = { "安康", "克利夫兰", "纽约", "斯台普斯", "北京" };
	GraphMartix<string, int> gm(5, City);
	gm.AddSide("安康", "北京", 450);
	gm.AddSide("克利夫兰", "北京", 1450);
	gm.AddSide("安康", "斯台普斯", 2450);
	gm.AddSide("安康", "纽约", 8450);
	gm.AddSide("纽约", "北京", 9450);
	gm.PrintMartix();

}