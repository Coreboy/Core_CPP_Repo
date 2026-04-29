#ifdef C4
#include <iostream>
using namespace std;

#if 0
class String
{
public:
	String(const char* str = nullptr) // 普通构造函数
	{
		if (str != nullptr) // 不为空字符串
		{
			cout << "Default Construcor From" << this << endl;
			m_data = new char[strlen(str) + 1];
			strcpy(m_data, str);
		}
		else
		{
			cout << "Default Empty Construcor From" << this << endl;
			m_data = new char[1]; // Q1. 为什么这里使用char[1] 而不是直接char? 涉及运算符重载问题
			*m_data = '\0';
		}
	}

	String(const String& str) // 拷贝构造函数
	{
		cout << "Copy Construcor From" << this << endl;
		m_data = new char[strlen(str.m_data) + 1];
		strcpy(m_data, str.m_data);
	}

	~String(void) // 析构函数
	{
		cout << "Deonstrucor From" << this << endl;
		delete[] m_data;
		m_data = nullptr;
	}

	String& operator=(const String& str) 
		// 赋值重载函数
		// 返回值是当前类型的引用
		// 是为了支持连续赋值	
	{
		cout << "Assignment Override From" << this << endl;
		// 赋值重载主要防止自赋值
		if (this == &str) 
		{
			return *this;
		}
			
		delete[] m_data;
		strcpy(m_data, str.m_data);
		return *this;
	}
private:
	char* m_data; // 用于保存字符串
};

int main() {
	
	String str1;
	String str2("hello");
	String str3 = "world!";

	String str4 = str3;
	String str5(str3);

	str1 = str2 = str3;

	return 0;
}
#endif

#if 1
// 循环队列
class Queue 
{
public:
	Queue(int size = 20)
	{
		_pQue = new int[size];
		_front = _rear = 0;
		_size = size;
	}

	~Queue() 
	{
		delete[] _pQue;
		_pQue = nullptr;
	}
	void push(int val) 
	{
		if (full()) return;
		_pQue[_rear] = val;
		_rear = (_rear + 1) % _size;
	}
	void pop() 
	{
		if (empty()) return;
		_front = (_front + 1) % _size;
	}
	int top() 
	{
		return _pQue[_front];
	}
	bool full() 
	{
		return (_rear + 1) % _size == _front;
	}
	bool empty() 
	{
		return _rear == _front;
	}
private:
	int* _pQue; // 申请队列的数组空间
	int _front; // 指示队头的位置
	int _rear; // 指示队尾的位置
	int _size; // 队列扩容的总大小

	void resize() // 扩容
	{
		int* ptmp = new int[2 * _size];
		int index = 0;
		for (int i = _front; i != _rear; i = (i + 1) % _size)
		{
			ptmp[index++] = _pQue[i];
		}
		delete[] _pQue;
		_pQue = ptmp;
		_front = 0;
		_rear = index;
		_size *= 2;
	}
};

int main() 
{
	Queue queue;
	for (int i = 0; i < 100; ++i) 
	{
		queue.push(rand() % 100);
	}

	Queue queue1 = queue;
	
	return 0;
}

#endif

#endif