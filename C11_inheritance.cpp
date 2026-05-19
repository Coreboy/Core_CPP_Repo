#ifdef C11
#include <iostream>
#include <typeinfo>
using namespace std;

class Base 
{
public:
	Base(int data = 10) :ma(data) { cout << "Base" << endl; }
	// 虚函数
	virtual void show() { cout << "Base::show()" << endl; }
	// 虚函数
	virtual void show(int) { cout << "Base::show(int)" << endl; }
	
	~Base() { cout << "~Base()" << endl; }
protected:
	int ma;
};

class Derive : public Base 
{
public:
	Derive(int data = 10) :Base(data), mb(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; }
protected:
	int mb;
};

#if 0
int main() 
{
	Derive d(10);
	Base* pb = &d;
	pb->show();	// 静态(编译期)的绑定(函数的调用)
	pb->show(10); // 静态绑定
	
	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;

	cout << typeid(pb).name() << endl;
	cout << typeid(*pb).name() << endl; 
	
	return 0;
}
#endif

#if 1

int main() 
{
	Base b;
	Derive d;
	
	// 静态绑定 由对象直接调用
	b.show();
	d.show();	
	cout << "========" << endl;
	
	// 动态绑定 必须由指针调用虚函数
	Base *pb1 = &b;
	Base *pb2 = &d;
	pb1->show();
	pb2->show();
	cout << "========" << endl;
	
	// 动态绑定 必须由引用变量调用虚函数
	Base &rb1 = b;
	Base &rb2 = d;
	rb1.show();
	rb2.show();
	cout << "========" << endl;
	
	// 动态绑定 虚函数通过指针或者引用变量调用 发生动态绑定
	Derive *pd1 = &d;
	Derive &rd1 = d;
	pd1->show();
	rd1.show();
	cout << "========" << endl;

	// 难点	强制上转下
	// 猜猜看下面这个是动态绑定还是静态绑定
	Derive *pd3 = (Derive*)&b;
	pd3->show();
	
	cout << endl;
	return 0;
}

#endif

#endif