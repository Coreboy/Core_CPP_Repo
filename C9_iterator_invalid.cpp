#ifdef C9
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> m_vec;
	for (int i = 0; i < 100; ++i)
	{
		m_vec.push_back(rand() % 100 + 1);
	}

	auto it = m_vec.begin();
	for (; it != m_vec.end(); ++it)
	{
		if (*it % 2 == 0) 
		{ 
			m_vec.erase(it); 
			break; 
		}
	}

	return 0;
}


#endif