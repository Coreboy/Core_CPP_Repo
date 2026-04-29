#ifdef C5
#include <iostream>
using namespace std;

#if 1
template<typename T>
int sum(T a, T b) 
{
	cout << "Template sum" << endl;
	// cout 这个流里面的是 临时参数存放吗， 如果是的话 临时参数会推导类型？
	cout << "a+b=" << a + b << endl;
	return a + b;
}

int main() 
{
	// 在函数调用点 编译器用用户指定的类型 从原模板实例化一份函数代码出来
	// 这样是不是就不用内联了?	
	int r1 = sum<int>(10, 20);
	cout << "return " << r1 << endl;
	int r2 = sum<double>(10.5, 21.4);
	cout << "return " << r2 << endl;
	
	// 函数模板实参的推演
	sum("aaa", "bbb");
	
	// 有时候需要避免推演
	// 因为大多数推演的结果不对
	// 引入函数模板特例化
	// 特例化是会走编译的 链接的时候符号表能找到定义的地方

	// 总结 模板代码不能在不同的文件定义
	// 一定要能够看到模板定义的地方，模板才能正常的实例化
	
	// 模板代码所以一般放在头文件里面 通过#include 引入
  
	return 0;
}

#endif
#endif