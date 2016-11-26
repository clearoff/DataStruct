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

		throw invalid_argument("��������");  //û�в��ҵ����׳��쳣
	}

	void AddSide(const V& src, const V& dst, const W& w = W())
	{
		size_t SrcIndex = GetIndex(src);
		size_t DstIndex = GetIndex(dst);

		if (_IsDirected)
		{
			//���������ͼ
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
	string City[5] = { "����", "��������", "ŦԼ", "˹̨��˹", "����" };
	GraphMartix<string, int> gm(5, City);
	gm.AddSide("����", "����", 450);
	gm.AddSide("��������", "����", 1450);
	gm.AddSide("����", "˹̨��˹", 2450);
	gm.AddSide("����", "ŦԼ", 8450);
	gm.AddSide("ŦԼ", "����", 9450);
	gm.PrintMartix();

}