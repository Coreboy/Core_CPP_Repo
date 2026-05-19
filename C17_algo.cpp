#ifdef C17
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // 包含了函数对象和绑定器
using namespace std;

// 泛型算法 = template + 迭代器 + 函数对象
// 特点一： 泛型算法接受的是迭代器
//		一个算法要做到泛用，必定要用一些不变的 / 风格统一的东西
// 特点二: 泛型算法的参数还可以接收函数对象 （C函数指针）
//		sort find find_if binary_seach for_each

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 213, 12, 19, 45, 17, 114, 514, 1919, 810 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0])); // 难怪迭代器 it->first it->second
	
	sort(vec.begin(), vec.end());

	for (auto v : vec) 
	{
		cout << v << endl;
	}

	int search = 191;
	if ( binary_search(vec.begin(), vec.end(), search) ){ cout << search << "存在！" << endl; }
	else{ cout << search << "不存在！" << endl; }

	// 绑定器 bind1st bind2nd
	// 绑定器 + 二元函数对象 = 一元函数对象
	// bind1st, 和二元函数对象的operator() (a, b) 的第一个形参绑定起来
	// bind2nd, 和二元函数对象的operator() (a, b) 的第二个形参绑定起来
	
	// 不过现在更多用lambda了， 其实就相当于自己临时写个函数对象

	auto it1 = find_if(vec.begin(), vec.end(),
		// bind2nd(greater<int>(), 45));
		// 这里引入lambda
		[](int val)->bool { return val > 45; });

	// 如果没找到返回end() 直接插入即可
	vec.insert(it1, 48);
	cout << "==================" << endl;
	
	for (auto v : vec)
	{
		cout << v << endl;
	}

	return 0;
}

#endif