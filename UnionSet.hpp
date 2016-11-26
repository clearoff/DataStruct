#include <iostream>
using namespace std;
#include <cassert>
#include <vector>

template<class T>
class UnionSet
{
public:
	UnionSet(const size_t& size)
		:_size(size)
	{
		_a.resize(size);
		for (int i = 0; i < _size; i++)
		{
			_a[i] = -1;
		}
	}

	int FindParent(int x)
	{
		while (_a[x] >= 0)
		{
			x = _a[x];
		}
		return x;
	}

	int ReturnCount()
	{
		int count = 0;
		for (int i = 0; i < _size; i++)
		{
			if (_a[i] < 0)
			{
				count++;
			}
		}
		return count-1;
	}

	void Merge(size_t x1, size_t x2)
	{
		assert(x1 < _size&&x2 < _size);
		int parent1 = FindParent(x1);
		int parent2 = FindParent(x2);

		if (parent1 != parent2)
		{
			_a[parent1] += _a[parent2];
			_a[parent2] = parent1;
		}
	}
protected:
	vector<int> _a;
	size_t _size;
};

int Friends(int m, int n, int a[][2])
{
	UnionSet<int> s(n+1);
	for (int i = 0; i < m; i++)
	{
		s.Merge(a[i][0], a[i][1]);
	}
	return s.ReturnCount();
}
void TestFriends()
{
	const int n = 5;
	const int m = 3;
	int a[m][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
	cout<<"ÅóÓÑÈ¦µÄ¸öÊý£¿--¡·"<<Friends(m, n,a)<<endl;
}