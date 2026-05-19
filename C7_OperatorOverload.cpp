#ifdef C7
#include <iostream>
using namespace std;

#if 1
class CComplex 
{
public:
	CComplex(int r = 0, int i = 0)
		:mreal(r), mimage(i) {}

	CComplex& operator+(const CComplex & src) 
	{
		return CComplex(this->mreal + src.mreal
			,this->mimage + src.mimage);
	}

	void show() { cout << "real:" << mreal << " imgae:" << mimage << endl; }

	friend CComplex& operator+(const CComplex& lhs, const CComplex& rhs);
	friend CComplex& operator++(CComplex& lhs);
	friend CComplex& operator++(CComplex& lhs, int);
	friend istream& operator>>(istream& in, CComplex& rhs);
	friend ostream& operator<<(ostream& out, const CComplex& rhs);

private:
	int mreal;
	int mimage;
};

CComplex& operator+(const CComplex& lhs, const CComplex& rhs) 
{
	// 访问类内私有成员
	// 引入友元
	return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mreal);
}

// 后缀++
CComplex& operator++(CComplex& lhs)
{
	return CComplex(lhs.mreal++, lhs.mimage++);
}

// 前缀++
CComplex& operator++(CComplex& lhs, int)
{
	return CComplex(++lhs.mreal, ++lhs.mimage);
}

// 输入流
istream& operator>>(istream& cin, CComplex& rhs) 
{
	cin >> rhs.mreal >> rhs.mimage;
	return cin;
}

// 输出流
ostream& operator<<(ostream& cout, const CComplex& rhs)
{
	cout << "mreal: " << rhs.mreal << " " << "mimage: " << rhs.mimage;
	return cout;
}

int main() 
{   
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);
	CComplex comp3 = comp1 + comp2;

	comp3.show();

	CComplex comp4 = comp3 + 10;
	comp4.show();
	
	// 没有任何由头告诉编译器 调用运算符重载函数 
	// 如果没有成员方法 就在全局作用域找合适的运算符重载
	
	CComplex comp5 = 10 + comp4;
	comp5.show(); 

	cout << comp1 << endl;
	cin >> comp1 >> comp2;
	cout << comp1 << comp2 << endl;


	return 0;
}

#endif
#endif