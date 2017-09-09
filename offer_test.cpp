#include <iostream>
using namespace std;
#include <unordered_map>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

//解法1：开辟空间---时间复杂度为O(N)的解法
void twoSum1(vector<int>& data, int target)
{
	unordered_map<int, int> hashMap;
	for (size_t i = 0; i < data.size(); i++){
		if (hashMap.find(data[i])!=hashMap.end()){
			int index = hashMap[data[i]];
			cout << hashMap[i] << "-" << data[i] << endl;
		}
		else{
			hashMap[target-data[i]] = i;
		}
	}
}

void twoSum2(const vector<int>& data,int target)
{
	int j = data.size() - 1;
	sort(data.begin(), data.end());
	for (int i = 0; i < j;)
	{
		if (data[i] + data[j] == target)
			cout << data[i] << "---" << data[j];
		else if (data[i] + data[j] < target)
			i++;
		else
			j--;
	}
}

int main()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<int> data(a, a + sizeof(a) / sizeof(a[0]));
	twoSum1(data,10);
	return 0;
}

//struct ListNode{
//public:
//	int _data;
//	ListNode* pNext;
//public:
//	ListNode(int data = 0)
//		:_data(data)
//		,pNext(NULL)
//	{}
//};
//
//typedef ListNode Node;
//
////非递归版本的逆序链表
//Node* ReverseList(Node* head)
//{
//	if (head == NULL || head->pNext == NULL)
//		return head;
//
//	Node* next = head;
//	Node* pre = NULL;
//	
//	while (head){
//		next = head->pNext;
//		head->pNext = pre;
//		pre = head;
//		head = next;
//	}
//
//	return pre;
//}
//
////递归版本
//Node* ReverseR(Node* head)
//{
//	if (head == NULL || head->pNext ==NULL)
//		return head;
//
//	Node* newHead = ReverseList(head->pNext);
//
//	head->pNext->pNext = head;
//	head->pNext = NULL;
//
//	return newHead;
//}
//
//void PrintList(Node* head)
//{
//	while (head){
//		cout << head->_data << " ";
//		head = head->pNext;
//	}
//	cout << endl;
//}
//
//int main()
//{
//	Node* head;
//	Node n1(1);
//	Node n2(2);
//	Node n3(3);
//	Node n4(4);
//	Node n5(5);
//	head = &n1;
//	n1.pNext = &n2;
//	n2.pNext = &n3;
//	n3.pNext = &n4;
//	n4.pNext = &n5;
//	PrintList(&n1);
//	head = ReverseR(&n1);
//	PrintList(head);
//	return 0;
//}