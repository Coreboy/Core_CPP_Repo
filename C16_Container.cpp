#ifdef C16
#include <iostream>
// 无序容器
#include <unordered_map>
#include <unordered_set>
// 有序容器
#include <map>
#include <set>
using namespace std;

/*
增：哈希表: O1 红黑树: Ologn 
删:	哈希表: O1 红黑树: Ologn 
	erase() 注意对应的迭代器变换 / 不让for循环控制自增

查: 哈希表: O1 红黑树: Ologn 
	自行iterator迭代器遍历 / foreach 遍历 / find()成员方法 / 中括号运算符重载函数 map operator[] (key) => value
	
	1. 注意 operator[] 如果key不存在 会插入一堆新数据
	2. find找不到返回end()
	3. map的迭代器返回的是 pair 通过it->key 访问键 it->value 访问值

如何区分 / 实现问题: 
	其实用这几个容器就处理好几个问题

	0. 按照自己的想法 和 对时空间效率的需求 来选用 哈希表/红黑树 + 容器类型
		比如想要去重 想到的是集合的互异性 / 统计或携带额外的属性 map / 预排序 [ordered]
	1. 连续erase insert 的迭代器问题 / 手动控制循环条件 
	2. 迭代器怎么用的问题 返回一个pair? 还是解引用

*/

int main() 
{
	//unordered_map<int, string> map1;
	//map1.insert(make_pair(1000, "小王"));
	//map1.insert(make_pair(1001, "小王"));
	//map1.insert({ 1002, "王五"});
	
	const int ARR_LENGTH = 200;
	int my_arr[ARR_LENGTH] = { 0 };
	for (int i = 0; i < ARR_LENGTH; ++i)
	{
		my_arr[i] = rand() % 100 + 1;
	}

	// 处理海量数据去重复 -- set
	unordered_set<int> my_set;
	unordered_map<int, int> my_map;
	for (int i = 0; i < ARR_LENGTH; ++i)
	{
		my_set.insert(my_arr[i]);
		if (my_map.find(my_arr[i]) == my_map.end())
		{
			my_map.insert({ my_arr[i], 1 });
			continue;
		}
		++my_map[my_arr[i]];
	}
	auto it = my_set.begin();
	for (; it != my_set.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "===============" << endl;

	// 处理海量数据统计次数 -- map
	auto it1 = my_map.begin();
	int sum = 0;
	for (; it1 != my_map.end(); ++it1)
	{
		cout << "{" << "it->first: " << it1->first << " it->second: " << it1->second << "}" <<  endl;
		sum += it1->second;
	}
	cout << "==============" << endl;
	cout << "sum: " << sum << endl;

	return 0;
}


#endif