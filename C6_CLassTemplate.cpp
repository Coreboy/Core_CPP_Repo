#ifdef C6
#include <iostream>
using namespace std;
#if 1
template<typename T>
class Allocator 
{
public:
	T* allocate(size_t size) // 负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}
	
	void deallocate(T* ptr) // 负责内存释放
	{
		free(ptr);
	}
	
	void construct(T *p, const T &val) // 负责对象构造
	{	
		new (p) T(val);
	}
	
	void destory(T *p) // 负责对象析构
	{
		p->~T(); 
	}

};

template<typename T, typename Alloc = Allocator<T>>
class vector 
{
public:
	// Construtor
	vector(int size = 10) 
	{
		_first = _allocator.allocate(size);
		_last = _first;
		_end = _first + size;
	}

	// Deconstructor
	~vector() 
	{
		// _allocator.deallocate(_first); 
		// 乱写， 怎么你知道delete[] 的[] 表示连带着一起删
		// 这里就忘记了批量删除了？

		// 逐个析构对象
		for (T* p = _first; p != _last; ++p) 
		{
			_allocator.destroy(p);
		}
		// 释放malloc 申请的空间
		_allocator.deallocate(_first);

		// 置空 防止野指针
		_first = _last = _end = nullptr;
		~_allocator(); // Q: 这里是否需要释放内存
	}
	
	// Copy Construtor
	vector(const vector<T> &rhs);

	// Assignment Operator
	// 人类的本质就是爱重复
	vector<T, Alloc>& operator=(const vector<T>& rhs);

	void push_back(const T& val);

	void pop_back();

	bool isEmpty() 
	{
		return _first == _last;
	}


	bool isFull()
	{
		return _last == _end;
	}



private:
	T* _first;			// 指向数组的起始位置
	T* _last;			// 指向数组中有效元素的后继位置
	T* _end;			// 指向数组空间的后继位置
	Alloc _allocator;	// 定义容器的空间配置器对象

	void expand() 
	{
		// 计算原尺寸
		int size = _last - _first;
		
		// 申请新的空间
		T* tmp_p = _allocator.allocate(size << 1);
		
		// 把元素搬运到新空间
		for (T* p = _first; p != _last; ++p) 
		{
			_allocator.construct(tmp_p + (p - _first), *p);
			_allocator.destroy(p)
		}

		// 删除旧空间
		_allocator.deallocate(_first);

		// 指向新区域
		_first = tmp_p;
		_last = tmp_p + size;
		_end = tmp_p + 2 * size - 1;

	}
};

template<typename T, typename Alloc>
inline vector<T, Alloc>::vector(const vector<T>& rhs)
// Copy Construtor
// 这里的rhs 指的是Right Hand Side 为右值

{
	int size = rhs._end - rhs._first;
	_first = _allocator.allocate(size);
	_last = _first + rhs._last - rhs._first;
	_end = _first + size;
	for (T* p = rhs._first; p != rhs._last; ++p)
	{
		_allocator.construct(_last, *p);
		++_last;
	}
}

template<typename T, typename Alloc>
inline vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T>& rhs)
{
	// step 1 防止自赋值
	if (this == &rhs) return;

	// step 2 释放旧空间
	for (T* p = _first; p != _last; ++p) 
	{
		// 析构对象
		_allocator.destory(p); 
	}

		// 释放内存
	_allocator.deallocate(_first);
	_first = _allocator.allocate(rhs._end - rhs._first);
	_last = _first;
	_end = _first + rhs._end - rhs._first;

	// step 3 分配新元素
	for (T* p = rhs._first; p != rhs._last; ++p) 
	{
		_allocator.construct(_last, *p);
		++_last;
	}

	return *this;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::push_back(const T& val) 
{
	if (this->isFull()) this->expand();

	// 构造对象
	this->_allocator.construct(_last, val);
	++_last;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::pop_back()
{
	if (this->isEmpty) return;

	// 析构对象
	this->_allocator.destory(--_last);
}

int main() 
{
	 
	return 0;
}

#endif
#endif

