#ifdef C10
#include <iostream>
using namespace std;

#if 0
void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "malloc pointer:" << p << endl;
	return p;
}

void operator delete(void* ptr)
{
	cout << "free pointer:" << ptr << endl;
	free(ptr);
}

int main() 
{
	try 
	{
		int* p = new int();
		delete p;
	}
	catch (const bad_alloc &err)
	{
		cerr << err.what() << endl;
	}

	return 0;
}
#endif

void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "malloc pointer:" << p << endl;
	return p;
}

void operator delete(void* ptr)
{
	cout << "free pointer:" << ptr << endl;
	free(ptr);
}

// 实现对象池
template<typename T>
class Queue 
{
public:
	Queue() 
	{
		cout << "Queue()" << endl;
		_front = _rear = new QueueItem();
	}
	~Queue() 
	{
		QueueItem* cur = _front;
		while (cur != nullptr) 
		{
			_front = _front->_next;
			delete cur;
			cur = _front;
		}
		cout << "~Queue()" << endl;
	}
	
	bool empty() 
	{
		return _front == _rear;
	}

	void push(const T& val) // 入队操作
	{
		QueueItem* item = new QueueItem(val);
		_rear->_next = item;
		_rear = item;
	}

	void pop() // 出队操作
	{
		if (empty()) return;
		// 头节点不存放数据 _front->_next 即为首元素
		QueueItem* first = _front->_next;
		_front->_next = first->_next;
		if (_front->_next == nullptr)
		{
			_rear = _front;
		}
		delete first;
	}

	T front()const
	{
		return _front->_next->_data;
	}

private:
	struct QueueItem 
	{
		QueueItem(T data = T()) :_data(data), _next(nullptr) {}
		
		// QueueItem 自定义内存管理
		// 属于静态方法，调用的时候不依赖对象
		static void* operator new(size_t size)
		{
			cout << "member new" << endl;
			// 对象池为空 或者 已到末尾
			if (_itemPool == nullptr) 
			{
				_itemPool = (QueueItem*) new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
				QueueItem *p = _itemPool;
				for (; p < _itemPool + POOL_ITEM_SIZE - 1; ++p)
				{
					p->_next = p + 1;
				}
				
				// 末尾next为nullptr 作为扩充判据
				p->_next = nullptr;
			}
			QueueItem *p = _itemPool;
			_itemPool = _itemPool->_next;
			return p;
		}
		static void operator delete(void* ptr)
		{
			// delete 不需要考虑为空的问题
			// 外层宏观上的对象创建 已经有empty()
			
			cout << "member delete" << endl;
			QueueItem *p = (QueueItem*)ptr;
			p->_next = _itemPool;
			_itemPool = p;
		}
		
		T _data;
		QueueItem* _next;
		static QueueItem* _itemPool;
		static const int POOL_ITEM_SIZE = 100000; // 静态常量得看能否在类体里面初始化
	};

	QueueItem* _front;
	QueueItem* _rear;
};

template<typename T>
// QueueItem *_itemPool = nullptr;
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;

int main() 
{
	Queue<int> que;
	for (int i = 0; i < 2; ++i) 
	{
		que.push(i);
		cout << que.front() << endl;
		que.pop();
	}
	cout << "isEmpty?: " << que.empty() << endl;

	return 0;
}

#endif