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
	MyGoods(char* p1, int num2) : _ID(p1), _price(num2) {}
	~MyGoods() {}
	void setName(MyGoods* pointer, char* temp_string) { strncpy(pointer->_ID, temp_string, ID_LENGTH); }
	void setPrice(MyGoods* pointer, int temp_num) { pointer->_price = temp_num; }
	static void setCount(); // static member func
	void show();
};

int MyGoods::_count = 0;

void MyGoods::setCount() {
	MyGoods::_count += 1;
}

void MyGoods::show() {
	cout << this->_ID << endl;
	cout << this->_count << endl;
	cout << this->_price << endl;
}

int main() {
	MyGoods g1();
	MyGoods* g2 = new MyGoods();

	// 指向成员方法的指针
	// 这里的作用域是必要的 告诉编译器不是普通的函数指针
	void (MyGoods::*show_pointer)() = &MyGoods::show;  
	// 依赖对象
	g1.*show_pointer();
	g2->*show_pointer();

	// 训练: 指向类的static成员方法
	void (MyGoods::sCount_pointer)() = &MyGoods::setCount;
	*sCount_pointer();
	
	return 0;
}
