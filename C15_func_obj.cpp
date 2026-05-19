#ifdef C15
#include <iostream>
#include <queue>
#include <set>
using namespace std;

// 体会一下函数指针&开闭原则

// 函数对象实例，如何把priority_quque 由大根堆转换为小根堆

int main() 
{
	priority_queue<int> que1;
	// 对象定义
	//_EXPORT_STD template <class _Ty, class _Container = vector<_Ty>, class _Pr = less<typename _Container::value_type>>
	//	class priority_queue {
	
	// 即更改 _Pr为greater 即可
	using MinHeap = priority_queue<int, vector<int>, greater<int>>;
	MinHeap que2;

	return 0;
}

#endif