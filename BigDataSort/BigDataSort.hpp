#pragma once 
#define  _CRT_SECURE_NO_WARNINGS
#include<vector>  
#include<cassert>  
#include<cstdio>  
#include<stdlib.h>  
#include<algorithm>  
using namespace std;

class BigDateMergeSort
{
public:
	BigDateMergeSort(const char* FileName, size_t FileSize, size_t FileNum)
		:_BigDateFIleName(FileName)
		, _FileSize(FileSize)
	{
		_SmallFileName.resize(FileNum);          //初始化小文件的数组
		for (int i = 0; i < FileNum; i++)
		{
			//创建小文件
			char name[128] = { 0 };
			_itoa(i, name, 10);
			_SmallFileName[i] = name;
		}
	}

	void Sort()
	{
		CutFile();
		SmallFileSort();
		FileMerge();
		/*separate();*/
	}

protected:
	void FileMerge()
	{
		/*while (_SmallFileName.size() > 1)
		{
			vector<string> NewFileName;*/
			while (_SmallFileName.size() > 1)
			{
				string name1 = _SmallFileName.back();
				_SmallFileName.pop_back();
				FILE* fRead1 = fopen(name1.c_str(), "rb");
				assert(fRead1);
				string name2 = _SmallFileName.back();
				_SmallFileName.pop_back();
				FILE* fRead2 = fopen(name2.c_str(), "rb");
				assert(fRead2);

				string NewName = name1 + name2;
				/*_SmallFileName.push_back(NewName);*/
				_SmallFileName.push_back(NewName);
				FILE* fWrite = fopen(NewName.c_str(), "wb");
				assert(fWrite);

				_Merge(fWrite, fRead1, fRead2);

				fclose(fRead1);
				fclose(fRead2);
				fclose(fWrite);

				remove(name1.c_str());
				remove(name2.c_str());       //删除已经合并的文件
			}
		//	for (size_t i = 0; i < NewFileName.size(); i++)
		//	{
		//		_SmallFileName.push_back(NewFileName[i]);
		//	}
		//}

			//将排好序的文件写入源文件中
			FILE* fRead = fopen(_SmallFileName[0].c_str(), "rb");
			FILE* fWrite = fopen(_BigDateFIleName.c_str(), "wb");
			assert(fRead);
			assert(fWrite);
			string line;
			fputs("排好序的文件如下\n", fWrite);
			while (_GetNum(fRead, line))
			{
				line += '\n';
				fputs(line.c_str(),fWrite);
				line.clear();
			}
			fclose(fWrite);
			fclose(fRead);

			remove(_SmallFileName[0].c_str());
			_SmallFileName.pop_back();
	}

	void SmallFileSort()            //对小文件的数据进行排序
	{
		for (size_t i = 0; i < _SmallFileName.size(); i++)
		{
			FILE* fR = fopen(_SmallFileName[i].c_str(), "rb");            
			assert(fR);
			vector<int> v;
			
			for (size_t count = 0; count < _FileSize; count++)
			{
				string line;
				if (_GetNum(fR, line))                  //从小文件中读一个字符串出来
				{
					int num = atoi(line.c_str());       //将字符串转化为数字
					v.push_back(num);
				}
			}
			fclose(fR);

			sort(v.begin(), v.end());                   //对内存中的数据进行排序

			//排序完毕后再写入到文件中
			FILE* fwrite = fopen(_SmallFileName[i].c_str(), "wb");
			assert(fwrite);

			for (size_t count = 0; count < v.size(); count++)
			{
				_InPutNumToFile(v[count], fwrite);
			}
			fclose(fwrite);
		}
	}

	void CutFile()
	{
		FILE* FR = fopen(_BigDateFIleName.c_str(), "rb");              //以读的方式打开大数据文件
		assert(FR);
		for (size_t i = 0; i < _SmallFileName.size(); i++)
		{
			FILE* FW = fopen(_SmallFileName[i].c_str(), "wb");
			assert(FW);
			for (size_t count = 0; count < _FileSize; count++)
			{
				string line;
				if (_GetNum(FR, line))
				{
					line += '\n';
					fputs(line.c_str(), FW);
					line.clear();
				}
				else
				{
					fclose(FR);      //大数据文件已经读取完毕 
					fclose(FW);
					return;
				}
			}
			fclose(FW);
		}
		fclose(FR);
	}
protected:
	void _Merge(FILE* fWrite, FILE* fRead1, FILE* fRead2)
	{
		int num1 = 0;
		bool file1 = _GetANum(fRead1, num1);
		int num2 = 0;
		bool file2 = _GetANum(fRead2, num2);

		while (file1 != false && file2 != false)
		{
			if (num1 > num2)
			{
				_InPutNumToFile(num2, fWrite);
				file2 = _GetANum(fRead2, num2);
			}
			else
			{
				_InPutNumToFile(num1,fWrite);
				file1 = _GetANum(fRead1, num1);
			}
		}
		while (file1 == true)
		{
			_InPutNumToFile(num1, fWrite);
			file1 = _GetANum(fRead1, num1);
		}

		while (file2 == true)
		{
			_InPutNumToFile(num2, fWrite);
			file2 = _GetANum(fRead2, num2);
		}
	}

	void _InPutNumToFile(int num,FILE* fWrite)
	{
		char data[128] = { 0 };
		string line;

		line = _itoa(num, data, 10);
		line += '\n';
		fputs(line.c_str(), fWrite);
	}

	bool _GetANum(FILE* fRead, int& num)
	{
		string line;
		if (_GetNum(fRead, line))
		{
			num = atoi(line.c_str());
			return true;
		}
		else
			return false;
	}

	bool _GetNum(FILE* fRead, string& line)               //读取一个整数
	{
		int ch = 0;
		while ((ch = getc(fRead)) != EOF&&ch != '\n')
		{
			line += ch;
		}
		if (ch == EOF)
			return false;
		else
			return true;
	}
protected:
	vector<string> _SmallFileName;   //切分的小文件的文件名
	size_t _FileSize;           //小文件中所装的数据的个数
	string _BigDateFIleName;    //要进行排序的大数据文件

};


//#include<vector>  
//#include<cassert>  
//#include<cstdio>  
//#include<stdlib.h>  
//#include<algorithm>  
//using namespace std;
//class BigDataSort
//{
//public:
//	BigDataSort(char * bigfile, int n, size_t limit)    //n表示要切分成多份少小文件  
//		:_bigfile(bigfile)                              //bigfile表示要排序的文件名  
//		, _limit(limit)                                 //_limit代表小文件中最多存放的数据个数  
//	{
//		_SmallFileName.resize(n);
//		for (int i = 0; i < n; ++i)                      //先创建n个文件名  
//		{
//			char name[128] = { 0 };
//			_itoa(i, name, 10);
//			_SmallFileName[i] = name;
//		}
//	}
//	void Sort()
//	{
//		separate();                 //切分文件  
//		SmallFileSort();            //小文件合并  
//		SmallFileMerge();           //小文件归并  
//	}
//protected:
//	void separate()         //将大文件数据分割到小文件中,_limit表示一个小文件中存放多少数据  
//	{
//		FILE *fRead = fopen(_bigfile, "rb");
//		assert(fRead);
//		for (size_t i = 0; i < _SmallFileName.size(); i++)
//		{
//			FILE *fWrite = fopen(_SmallFileName[i].c_str(), "wb");         //以写的方式打开小文件  
//			assert(fWrite);
//			for (size_t count = 0; count < _limit; count++)
//			{
//				string line;
//				if (_GetLine(fRead, line))  //如果读取成功，将这个数写到小文件中  
//				{
//					line += ' ';
//					fputs(line.c_str(), fWrite);
//					line.clear();
//				}
//				else
//				{
//					fclose(fWrite);
//					fclose(fRead);
//					return;
//				}
//			}
//			fclose(fWrite);        //关闭小文件  
//		}
//		fclose(fRead);
//	}
//	void SmallFileSort()           //对小文件进行排序  
//	{
//		for (size_t i = 0; i < _SmallFileName.size(); ++i)
//		{
//			FILE *fRead = fopen(_SmallFileName[i].c_str(), "rb");
//			assert(fRead);
//			vector<int> v;
//			for (size_t count = 0; count < _limit; ++count)    //将这些小文件中的数据加载到内存  
//			{
//				int num = 0;
//				if (_GetNum(fRead, num))               //如果读取成功，则将它放到vector中  
//					v.push_back(num);
//				else
//					break;
//			}
//			fclose(fRead);
//			对这些数据进行快速排序  
//			sort(v.begin(), v.end());
//
//			将这些数据再写到文件中  
//			FILE *fWrite = fopen(_SmallFileName[i].c_str(), "wb");
//			assert(fWrite);
//			for (size_t i = 0; i <v.size(); ++i)       //将这些小文件中的数据加载到内存  
//			{
//				_InputNum(fWrite, v[i]);         //向文件中写入一个数  
//			}
//			fclose(fWrite);
//		}
//	}
//	对这些文件进行归并排序  
//	void SmallFileMerge()
//	{
//		while (_SmallFileName.size()>1)       //将这些小文件最后合并的只剩一个文件  
//		{
//			vector<string> v;
//			while (_SmallFileName.size() > 1)
//			{
//				string filename1 = _SmallFileName.back();
//				_SmallFileName.pop_back();
//				string filename2 = _SmallFileName.back();
//				_SmallFileName.pop_back();
//				FILE *fRead1 = fopen(filename1.c_str(), "rb");
//				assert(fRead1);
//				FILE *fRead2 = fopen(filename2.c_str(), "rb");
//				assert(fRead2);
//				string newfile = filename1 + filename2;     //创建一个新的文件名，用来存放这两个文件合并后的结果  
//				v.push_back(newfile);                       //将新文件保存起来  
//				FILE* fWrite = fopen(newfile.c_str(), "wb");
//				assert(fWrite);
//				_Merge(fRead1, fRead2, fWrite);               //对这两个文件中的数据进行归并排序  
//				fclose(fRead1);
//				fclose(fRead2);
//				fclose(fWrite);
//				remove(filename1.c_str());                   //删除这些已经合并过的辅助文件  
//				remove(filename2.c_str());
//			}
//			for (size_t i = 0; i < v.size(); ++i)
//			{
//				_SmallFileName.push_back(v[i]);
//			}
//		}
//		将最后合并的文件再拷贝回原文件中  
//		FILE* fWrite = fopen(_bigfile, "wb");
//		assert(fWrite);
//		string filename = _SmallFileName[0];
//		FILE* fRead = fopen(filename.c_str(), "rb");
//		assert(fRead);
//		string line;
//		while (_GetLine(fRead, line))
//		{
//			line += ' ';
//			fputs(line.c_str(), fWrite);
//			line.clear();
//		}
//		fclose(fWrite);
//		fclose(fRead);
//		remove(filename.c_str());             //删除辅助文件  
//	}
//protected:
//	void _Merge(FILE* fRead1, FILE* fRead2, FILE* fWrite)        //将小文件进行合并  
//	{
//		int num1 = 0;
//		int num2 = 0;
//		bool file1 = _GetNum(fRead1, num1);
//		bool file2 = _GetNum(fRead2, num2);
//		while (file1 != false && file2 != false)          //归并排序  
//		{
//			if (num1<num2)
//			{
//				_InputNum(fWrite, num1);         //向文件中写入一个数  
//				file1 = _GetNum(fRead1, num1);
//			}
//			else
//			{
//				_InputNum(fWrite, num2);
//				file2 = _GetNum(fRead2, num2);
//			}
//		}
//		while (file1 == true)
//		{
//			_InputNum(fWrite, num1);         //向文件中写入一个数  
//			file1 = _GetNum(fRead1, num1);
//		}
//		while (file2 == true)
//		{
//			_InputNum(fWrite, num2);         //向文件中写入一个数  
//			file2 = _GetNum(fRead2, num2);
//		}
//	}
//protected:
//	bool _GetNum(FILE *fRead, int& num)  //读取一个整数,并将整数通过num返回  
//	{
//		int ch = 0;
//		string line;
//		while ((ch = getc(fRead)) != EOF&&ch != ' ')
//		{
//			line += ch;
//		}
//		if (ch == EOF)
//			return false;
//		else
//		{
//			num = atoi(line.c_str());
//			return true;
//		}
//	}
//	bool _GetLine(FILE* fRead, string& line)   //读取一个整数，将整数以转化成字符串用line返回  
//	{
//		int ch = 0;
//		while ((ch = getc(fRead)) != EOF&&ch != ' ')
//		{
//			line += ch;
//		}
//		if (ch == EOF)
//			return false;
//		else
//			return true;
//	}
//	void _InputNum(FILE *fWrite, int num)     //向文件中写一个整数，转化成字符串写入  
//	{
//		char buf[120] = { 0 };
//		string line;
//		line = _itoa(num, buf, 10);
//		line += ' ';
//		fputs(line.c_str(), fWrite);
//	}
//private:
//	vector<string> _SmallFileName;     //存放小文件名的数组  
//	char* _bigfile;               //记录要排序的文件名  
//	size_t _limit;                //记录小文件的最多存放数据个数  
//};