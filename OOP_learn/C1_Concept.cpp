#include <iostream>
#include <cstring>
using namespace std;

#define ID_LENGTH 10

class MyGoods{
private:
	char _ID[ID_LENGTH];
	static int _count;	// static member variable
	int _price;

public:
	MyGoods(){}
	~MyGoods(){}
	void setName(MyGoods* pointer, char * temp_string){ strncpy(pointer->_ID, temp_string, ID_LENGTH);}
	void setPrice(MyGoods* pointer, int temp_num) { pointer->_price = temp_num; }
	void setCount(); // static member func
	void show();
};

int MyGoods::_count = 0;

void MyGoods::setCount() {
	MyGoods::_count += 1;
}

int main(){
	
	return 0;
}
