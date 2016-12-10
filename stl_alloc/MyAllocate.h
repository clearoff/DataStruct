#pragma once 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <cstdlib>
#include <cassert>
#include <stdarg.h>
#include <vector>

#define __DEBUG__
FILE* fo = fopen("Trace.log", "w");
static string  GetFileName(const string&  path)
{
	char ch ='/';
#ifdef _WIN32
	ch = '\\';
#endif
	size_t  pos = path.rfind(ch);
	if(pos == string::npos)
		return path;
	else
		return path.substr(pos + 1);
}
//���ڵ���׷�ݵ�trace  log
inline  static  void  __trace_debug(const  char*  function,const  char*  filename, int  line, char* format,...)
{
#ifdef __DEBUG__
	//������ú�������Ϣ
	fprintf(stdout,"��%s: %d��%s",GetFileName(filename).c_str(), line, function);
	fprintf(fo,"��%s: %d��%s",GetFileName(filename).c_str(), line, function);
	//����û����trace��Ϣ
	va_list args;
	va_start(args, format);
	vfprintf (stdout, format, args);
	vfprintf(fo, format, args);
	va_end(args);
#endif
}
#define __TRACE_DEBUG(...) __trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);

typedef void(*ALLOC_COM_FUN)();
template <int inst>
class _MallocAllocTemplate
{
	static ALLOC_COM_FUN  _MallocAllocOomHandler;    /*static void(*__MallocAllocOomHandler)();*/
private:
	static void* OomMalloc(size_t n)          //�����ڴ治��ĺ���
	{
		ALLOC_COM_FUN MyMallocHanlder = 0;   // _MallocAllocOomHandler;
		void* result;

		while (1)
		{
			MyMallocHanlder = _MallocAllocOomHandler;
			if (MyMallocHanlder == 0)
			{
				cout << "out of memory" << endl;
				exit(-1);
			}
			(*MyMallocHanlder)();
			
			result = malloc(n);
			if (result != 0)
				return result;
		}
	}
public:
	static void * allocate(size_t n)
	{
		__TRACE_DEBUG("ʹ��һ���ռ�����������%uBytes���ռ�\n", n);
		assert(n >= 0);
		void* result = malloc(n);
		if (result == 0)
		{
			OomMalloc(n);                  //����ڴ濪��ʧ�ܵ����ڴ治�㴦����
		}
		return result;
	}

	static void deallocate(void *p, size_t  n)
	{
		__TRACE_DEBUG("ʹ��һ���ռ��������ͷ�%uBytes���ռ�---0x%p \n", n,p);
		free(p);
		p = NULL;
	}

	static void(*set_malloc_handler(void(*f)()))()  //set_malloc_handler(void(*f)())
	{
		ALLOC_COM_FUN Old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;
		return old;
	}
};

template<int inst>
ALLOC_COM_FUN _MallocAllocTemplate<inst>::_MallocAllocOomHandler = 0;      //�Ծ�����г�ʼ��


template <bool threads, int inst>
class __DefaultAllocTemplate
{
	enum { _ALIGN = 8 };                        //FreeList[]���м��
	enum { _MAXBYTES = 128 };                   //FreeList bytes���ֵ
	enum { _NFREELISTS = _MAXBYTES / _ALIGN };  //FreeList ��С

	static size_t RoundUP(size_t bytes)          //������8�ı���
	{
		return (((bytes)+_ALIGN - 1) & ~(_ALIGN - 1));
	}

	static  size_t FreeListIndex(size_t bytes)    //���� bytes��Ӧ�����������index
	{
		return ((bytes+_ALIGN-1)/_ALIGN-1);
	}

	union Obj
	{
		union Obj* _FreeListLink;               //ָ����������ڵ��ָ��
		char client_data[1];                    /* The client sees this */
	};

protected:
	static Obj* volatile  _FreeList[_NFREELISTS];     //��������
	static char* _StartFree;                          //�ڴ����ָ���ڴ�ؿ��ÿռ��׵�ַ��ָ��
	static char* _EndFree;                            //�ڴ����ָ���ڴ��ĩβ��ָ��
	static size_t _HeapSize;                          //�ڴ���пռ�Ĵ�С
public:
	static void* allocate(size_t n)
	{
		__TRACE_DEBUG("ʹ�ö����ռ�����������%u Bytes���ռ�\n", n);
		if (n > 128)        //Ҫ���ٿռ���ֽ�������128����һ���ռ�������
		{
			void* result = _MallocAllocTemplate<0>::allocate(n);
			return result;
		}
		//���Ҫ���ٵ��ֽ��� <=128 bytes  ����õڶ����ռ�������
		size_t index = FreeListIndex(RoundUP(n));         //�ҵ������������ж�Ӧ���±�
		Obj* volatile* MyFreeList = _FreeList + index;
		Obj* head= *MyFreeList;
		if (head == 0)
		{
			void* ret = Refill(RoundUP(n));
			return ret;
		}
		*MyFreeList = head-> _FreeListLink;
		return head;
	}

	static void deallocate(void *p, size_t n)
	{
		__TRACE_DEBUG("ʹ��һ���ռ��������ͷ�%uBytes���ռ�---0x%p \n", n, p);
		Obj* q = (Obj*) p;

		if (n > _MAXBYTES)
		{
			//���õ�һ���ռ�������
			_MallocAllocTemplate<0>::deallocate(p,n);
			return;
		}

		size_t index = FreeListIndex(n);
		//��Ҫ�ͷŵĶ���Ŀռ�ֱ��ͷ������Ӧ������������
		q->_FreeListLink = _FreeList[index];
		_FreeList[index] = q;
	}

	static void* Refill(size_t n)
	{
		__TRACE_DEBUG("ʹ�ö����ռ����������ڴ������%uBytes���ռ�\n", n);
		Obj* volatile* MyFreeList = NULL;
		int nojbs = 20;                 //������ֱ�ӿ���20����������Ľڵ�
		Obj* result = NULL;
		char* chunck = ChuncAlloc(n,nojbs);

		if (nojbs == 1)
			return chunck;            //���ChuncAllocֻ������һ��nbytes����������ڵ㣬��ֱ�ӷ���������ʹ��

		size_t index = FreeListIndex(n);
		Obj* CurrentObj=NULL, *NextObj=NULL;

		result = (Obj*)chunck;        

		//�Ѵ�ChunckAlloc��õ��ڴ�����ڶ�Ӧ��freelist����
		_FreeList[index] = NextObj = (Obj*)(chunck + n);
		for (int i = 2; i < nojbs; i++)
		{
			CurrentObj = NextObj;
			NextObj= (Obj*)((char*)NextObj + n);
			CurrentObj-> _FreeListLink = NextObj;
		}
		NextObj->_FreeListLink = NULL;
		return result;
	}

	//���ڴ���п��ٴ���ڴ�
	static char* ChuncAlloc(size_t n, int& nojbs)
	{
		__TRACE_DEBUG("ʹ�ö����ռ����������ڴ������%uBytes���ռ�\n", n*nojbs);
		char* result=NULL;
		size_t totalBytes = n*nojbs;                     //Ҫ���ڴ��������ڴ�Ĵ�С
		size_t leftBytes = _EndFree - _StartFree;        //�ڴ����ʣ����ڴ�Ĵ�С

		if (leftBytes >= totalBytes)                       //ֱ�����ڴ������
		{
			__TRACE_DEBUG("�ڴ�ط���%d������\n",nojbs);
			result = _StartFree;
			_StartFree += totalBytes;                   //�ı��ڴ����ָ���λ��
			return result;
		}
		if (leftBytes >= n)                              //����ڴ��ʣ����ڴ�Ĵ�С����һ����������Ҫ���ڴ棬��ֱ�����ڴ������
		{
			__TRACE_DEBUG("�ڴ��ֻ�ܷ���%d������\n", nojbs);
			result = _StartFree;
			nojbs = leftBytes / n;
			_StartFree += nojbs*n;
			return result;
		}
		else                                         //�ڴ����ʣ����ڴ治��һ��������ʹ�õģ���Ҫ�����ϵͳ��������
		{
			size_t GetBytes = 2 * totalBytes + RoundUP(_HeapSize >> 4);      //�����ϵͳ��������ڴ�Ĵ�С

			if (leftBytes > 0)                       //���ڴ����ʣ����ڴ������Ӧ������������
			{
				//ͷ��
				size_t index = FreeListIndex(RoundUP(leftBytes));
				((Obj*)_StartFree)->_FreeListLink = _FreeList[index];  
				_FreeList[index]->_FreeListLink = (Obj*)_StartFree;
			}
			_StartFree = (char*)malloc(GetBytes);          //�ڴ����malloc�����ڴ�

			if (_StartFree == 0)
			{
				//��������ڴ�ʧ�ܣ�����������Ҫ�ڴ�
				for (int i = n; i < _MAXBYTES; i += _ALIGN)
				{
					if (_FreeList[i])
					{
						_StartFree = (char*)_FreeList[i];
						_EndFree = (char*)(_StartFree + i);
						_FreeList[i] = _FreeList[i]->_FreeListLink;
						return (ChuncAlloc(n, nojbs));
					}
				}
				_EndFree = 0;   //��ֹmalloc���ٿռ�ʧ�ܺ�ʹʵ��û���ڴ���ڴ�ر�á����ڴ��ˡ�
				//�������������Ҳû�п��õ��ڴ���,�����һ���ռ�������
				_StartFree = (char*)_MallocAllocTemplate<0>::allocate(GetBytes);
			}
			_HeapSize +=GetBytes;
			_EndFree = _StartFree + GetBytes;
			return(ChuncAlloc(n,nojbs));
		}
	}
};
//��̬�����ĳ�ʼ��
template <bool threads, int inst>
typename  char* __DefaultAllocTemplate<threads, inst>::_StartFree = 0;

template <bool threads, int inst>
typename  char* __DefaultAllocTemplate<threads, inst>::_EndFree = 0;

template <bool threads, int inst>
typename  size_t __DefaultAllocTemplate<threads, inst>::_HeapSize = 0;

template<bool threads,int inst>
typename  __DefaultAllocTemplate<threads,inst>::Obj* volatile  
__DefaultAllocTemplate<threads, inst>::_FreeList[__DefaultAllocTemplate<threads, inst>::_NFREELISTS] = { 0 };


void Test1()
{
	vector<pair<void*, size_t>> v;
	v.push_back(make_pair(__DefaultAllocTemplate<false, 0>::allocate(129), 129));

	for (size_t i = 0; i < 21; ++i)
	{
		v.push_back(make_pair(__DefaultAllocTemplate<false, 0>::allocate(12), 12));
	}

	while (!v.empty())
	{
		__DefaultAllocTemplate<false, 0>::deallocate(v.back().first, v.back().second);
		v.pop_back();
	}

	for (size_t i = 0; i < 21; ++i)
	{
		v.push_back(make_pair(__DefaultAllocTemplate<false, 0>::allocate(7), 7));
	}

	for (size_t i = 0; i < 10; ++i)
	{
		v.push_back(make_pair(__DefaultAllocTemplate<false, 0>::allocate(16), 16));
	}

	while (!v.empty())
	{
		__DefaultAllocTemplate<false, 0>::deallocate(v.back().first, v.back().second);
		v.pop_back();
	}
}
//
//void Test3()
//{
//	cout << "����ϵͳ���ڴ�ľ�" << endl;
//
//	/*SimpleAlloc<char, Alloc>::Allocate(1024 * 1024 * 1024);
//	SimpleAlloc<char, Alloc>::Allocate(1024 * 1024);*/
//
//	//���ò��ԣ�˵��ϵͳ����С���ڴ���������Ǻ�ǿ�ġ�
//	for (int i = 0; i< 100000; ++i)
//	{
//		char*p1 = SimpleAlloc<char, Alloc>::Allocate(128);
//	}
//
//	cout << "�������" << endl;
//}
