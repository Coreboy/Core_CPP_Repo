#ifdef C8
#include <iostream>
using namespace std;


class String 
{
public:
	String(const char* p = nullptr) 
	{
		if (p != nullptr) 
		{
			_pstr = new char[strlen(p) + 1];
			for (int i = 0; i < strlen(p) + 1; ++i) 
			{
				_pstr[i] = p[i];
			}
			//strcpy(_pstr, p);
		}
		else 
		{
			_pstr = new char[1];
			*_pstr = '\0';
		}
	}

	~String() 
	{
		delete[] _pstr;
		_pstr = nullptr;
	}

	String(const String& str) 
	{
		_pstr = new char[strlen(str._pstr)];
		strcpy(_pstr, str._pstr);
	}



	String& operator=(const String& rhs) 
	{
		if (rhs._pstr == _pstr) return *this;
		delete[] _pstr;
		_pstr = new char(strlen(rhs._pstr) + 1);
		strcpy(_pstr, rhs._pstr);
		return *this;
	}

	bool operator>(const String& str) const
	{
		return strcmp(_pstr, str._pstr) > 0;
	}

	bool operator<(const String &str) const 
	{
		return strcmp(_pstr, str._pstr) < 0;
	}

	bool operator==(const String& str) const
	{
		return strcmp(_pstr, str._pstr) == 0;
	}

	int length() const { return strlen(_pstr); }
	char& operator[](int i) { return _pstr[i]; }
	const char* c_str() { return _pstr; }
	
	class iterator 
	{
	public:
		iterator(char* p = nullptr) :_p(p) {}
		
		bool operator!=(const iterator& it) 
		{
			return _p != it._p;
		}

		void operator++()
		{
			++_p;
		}

		char& operator*() 
		{
			return *_p;
		}

	private:
		char *_p;
	};

	iterator begin() { return iterator(_pstr); }
	iterator end() { return iterator(_pstr + length()); }

private:
	char* _pstr;
	
	// 为什么要提供全局的加法运算符重载?
	// 因为有些对象看不出成员方法 需要找全局的重载运算符
	friend String operator+(const String& lhs, const String& rhs);
	friend ostream& operator<<(ostream& out, const String& str);
	friend istream& operator>>(istream& in, const String& str);

};

// 关于全局重载问题 
// 可以思考一下复数类中 当 10 + com1 的时候 10进行构造 是加到实部 还是虚部？

String operator+(const String& lhs, const String& rhs)
{
	char* _tmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(_tmp, lhs._pstr);
	strcat(_tmp, rhs._pstr);
	String tmp(_tmp);
	delete[] _tmp;
	return tmp;
}

ostream& operator<<(ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}

istream& operator>>(istream& in, const String& str)
{
	in >> str._pstr;
	return in;
}


int main() 
{
	String str1 = "hello world!";
	cout << str1 << endl;
	// 实现了迭代器以后
	// 可以使 foreach 写法

	for (char ch : str1) 
	{
		cout << ch << " ";
	}
	cout << endl;

	return 0;
}

#endif