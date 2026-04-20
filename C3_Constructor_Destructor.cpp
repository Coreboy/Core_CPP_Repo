#ifdef C3
#include <iostream>
using namespace std;

// OOP实现一个顺序栈
// 顺序栈使用顺序存储结构实现的栈结构

class SeqStack {
public:
	SeqStack(int size = 10) 
	{	
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}

	~SeqStack()
	{
		delete[]_pstack;
		_pstack = nullptr;
	}
	void push(int val) 
	{
		if (full())
			resize();
		_pstack[++_top] = val;
	}

	void pop()
	{
		if (empty())
			return;
		--_top;
	}

	int top()
	{
			return _pstack[_top];
	}

	bool empty() { return _top == -1; }
	
	bool full() { return _top + 1 == _size; }
	

private:
	int* _pstack;
	int _top;
	int _size;
	
	void resize() 
	{
		int* ptmp = new int[_size * 2];
		for (int i = 0; i < _size; ++i) 
		{
			ptmp[i] = _pstack[i];
		}
		delete[] _pstack;
		_pstack = ptmp;
		_size *= 2;
	}

};

int main() {
	SeqStack my_stack(5);
	for (int i = 0; i < 15; ++i) 
	{
		my_stack.push(rand() % 100);
		cout << my_stack.top() << endl;
	}

	return 0;
}
#endif