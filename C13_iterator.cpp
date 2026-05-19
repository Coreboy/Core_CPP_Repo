#ifdef C13
#include <iostream>
#include <vector>
using namespace std;

// begin() end()
// iterator 普通的正向迭代器
// const_iterator 常迭代器 只能读不能写

// rbegin() rend()
// reverse_iterator 普通的反向迭代器
// const_reverse_iterator 常反向迭代器 只能读不能写

int main() 
{
	vector<int> myarr;
	
	for (int i = 0; i < 40; ++i)
	{
		myarr.push_back(rand() % 100);
	}

	vector<int>::const_iterator it1 = myarr.begin();
	for (; it1 != myarr.end(); ++it1) 
	{
		cout << *it1 << " ";
	}
	cout << endl;
	cout << "===============" << endl;

	vector<int>::reverse_iterator rit = myarr.rbegin();
	for (; rit != myarr.rend(); ++rit) 
	{
		cout << *rit << " ";
	}
	cout << endl;
	cout << "===============" << endl;

	return 0;
}

#endif