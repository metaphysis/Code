// Stacks of Flapjacks
// UVa IDs: 120
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <sstream>
#include <algorithm>
	
using namespace std;
	
#define MAXSIZE 30
	
struct pancake
{
	int diameter;
	int index;
};
	
pancake pancakes[MAXSIZE];
pancake original[MAXSIZE];
	
bool cmp(pancake x, pancake y)
{
	return x.diameter < y.diameter;
}
	
void flip(int pos, int size)
{
	pancake tmp;
	int i = 0, j = size - pos;
	for (; i < j; i++, j--)
		if (original[i].diameter != original[j].diameter)
		{
			tmp = original[i];
			original[i] = original[j];
			original[j] = tmp;
		}
}
	
int main(int ac, char *av[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
	string line;
	while (getline(cin, line))
	{
		// 回显。
		cout << line << endl;
	
		// 读入数据。
		int capacity = 0;
		istringstream iss(line);
		while (iss >> pancakes[capacity].diameter)
		{
			pancakes[capacity].index = capacity;
			original[capacity] = pancakes[capacity];
			capacity++;
		}
	
		// 排序。
		sort(pancakes, pancakes + capacity, cmp);
	
		// 执行翻转操作，若第 i 大元素未在第i位上，则先找到其序号，然后
		// 先将其翻转到顶端，然后再翻转到位置i。
		for (int i = capacity - 1; i >= 0; i--)
		{
			// 在当前序列中找到该元素。
			// 假如数原来的序号与当前的序号不等，需要翻转操作。
			int marker;
			for (int j = 0; j < capacity; j++)
				if (original[j].index == pancakes[i].index)
				{
					marker = j;
					break;
				}
	
			if (marker != i)
			{
				if (marker != 0)
				{
					cout << (capacity - marker) << " ";
					flip(capacity - marker, capacity);
				}

				cout << (capacity - i) << " ";
				flip(capacity - i, capacity);
			}
		}
	
		cout << "0" << endl;
	}
	
	return 0;
}
