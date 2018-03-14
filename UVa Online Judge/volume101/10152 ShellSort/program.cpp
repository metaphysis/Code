// ShellSort （龟壳排序）
// PC/UVa IDs: 110407/10152, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-05-27
// UVa Run Time: 0.656s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
#define MAXSIZE 200
	
#ifndef DEBUG_MODE
//#define DEBUG_MODE
#endif
	
struct turtle
{
	string name;
	int index;
};
	
void shell_sort(turtle start[], turtle last[], int capacity)
{
	// 为初始状态的乌龟赋予序号。
	for (int i = 0; i < capacity; i++)
		for (int j = 0; j < capacity; j++)
			if (start[j].name == last[i].name)
			{
				start[j].index = last[i].index;
				break;
			}
	
	// 对初始乌龟状态排序。
	for (int i = capacity; i > 1; i--)
	{
		// 找到序号为i和（i - 1）的两只乌龟在数组的位置。
		int current, previous;
		for (int j = 0; j < capacity; j++)
		{
			if (start[j].index == i)
				current = j;
			if (start[j].index == (i - 1))
				previous = j;
		}
		
		// 如果序号为（i - 1）的乌龟在序号为i的乌龟的下方，则将其放到顶端。
		if (previous > current)
		{
			cout << start[previous].name << endl;
			turtle tmp = start[previous];
			for (int j = previous; j > 0; j--)
			{
				start[j].name = start[j - 1].name;
				start[j].index = start[j - 1].index;
			}
			start[0].name = tmp.name;
			start[0].index = tmp.index;
		}
		
	#ifdef DEBUG_MODE
		cout << "<Debug Begin>" << endl;
		for (int j = 0; j < capacity; j++)
			cout << start[j].index << " " << start[j].name << endl;
		cout << "<Debug End>" << endl;
	#endif
	}
}
	
int main(int ac, char *av[])
{
	int cases, capacity;
	turtle start[MAXSIZE];
	turtle last[MAXSIZE];
	
	cin >> cases;
	while(cases--)
	{
		cin >> capacity;
		cin.ignore();
		
		// 读入初始状态。
		for (int i = 0; i < capacity; i++)
			getline(cin, start[i].name);
		
		// 读入最终状态，并赋予每只乌龟序号。
		for (int i = 0; i < capacity; i++)
		{
			getline(cin, last[i].name);
			last[i].index = (i + 1);
		}
		
		// 开始龟壳排序！
		shell_sort(start, last, capacity);
		
		cout << endl;
	}
	
	return 0;
}
