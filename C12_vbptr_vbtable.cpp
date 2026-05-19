#ifdef C12
#include <iostream>
using namespace std;

class A 
{
public:
	virtual void func() { cout << "A::func()" << endl; }
	
	void operator delete(void* ptr) 
	{
		cout << "free: " << ptr << endl;
		free(ptr);
	}
private:
	int ma = 10;
};

class B : virtual public A
{
public:
	void* operator new(size_t size) 
	{
		void* p = malloc(size);
		cout << "new: " << p << endl;
		return p;
	}
	void func() { cout << "B::func()" << endl; }
private:
	int mb = 10;
};

int main()
{
	A* p = new B();
	p->func();

	return 0;
}


#endif