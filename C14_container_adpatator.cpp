#ifdef C14
#include <iostream>
#include <list>
#include <stack>
using namespace std;


// 容器适配器 =》 设计模式：适配器模式
template<typename T, typename Container=deque<T>>
class Stack 
{
public:
	void push(const T& val) { con.push_back(val); }
	void pop() { con.pop_back(); }
	T top()const { return con.back(); }
private:
	Container con;
};

int main() 
{
	
	return 0;
}

#endif