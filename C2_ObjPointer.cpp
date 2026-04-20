#ifdef C2
#include <iostream>
#include <cstring>
using namespace std;

#define ID_LENGTH 10

class MyGoods {
private:
	char _ID[ID_LENGTH];
	static int _count;	// static member variable
	int _price;

public:
	MyGoods() {}
	~MyGoods() {}
	void setName(MyGoods* pointer, char* temp_string) { strncpy(pointer->_ID, temp_string, ID_LENGTH); }
	void setPrice(MyGoods* pointer, int temp_num) { pointer->_price = temp_num; }
	static void setCount(); // static member func
	void show();
};

int MyGoods::_count = 0;

void MyGoods::setCount() {
	cout << "Static Func Test !" << endl;
	MyGoods::_count += 1;
}

int main() {
	MyGoods g1;
	MyGoods* g2 = new MyGoods();
	
	// 指向成员方法的指针
	void (MyGoods::*sNamePointer)(MyGoods *, char*) = &MyGoods::setName;
	
	// 指向static成员方法的指针
	// 调用已经不依赖成员了，不用加对象作用域
	void (*sCountPointer)() = &MyGoods::setCount;
	(*sCountPointer)();

	return 0;
}
#endif