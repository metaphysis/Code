// Bridge （过桥）
// PC/UVa IDs: 110403/10037, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <algorithm>
	
using namespace std;
	
#define MAXSIZE (1000 + 1)
	
int shortest_time(int time[], int capacity)
{
	if (capacity == 1)
		return time[0];
	
	if (capacity == 2)
		return time[1];
	
	if (capacity == 3)
		return time[0] + time[1] + time[2];
	
	if (2 * time[1] < (time[0] + time[capacity - 2]))
		return time[0] + 2 * time[1] + time[capacity - 1] + 
			shortest_time(time, capacity - 2);
	else
		return 2 * time[0] + time[capacity - 2] + time[capacity - 1] + 
			shortest_time(time, capacity - 2);
}
	
void bridge(int time[], int capacity)
{
	if (capacity == 1)
	{
		cout << time[0] << "\n";
		return;
	}
	
	if (capacity == 2)
	{
		cout << time[0] << " " << time[1] << "\n";
		return;
	}
	
	if (capacity == 3)
	{
		cout << time[0] << " " << time[2] << "\n";
		cout << time[0] << "\n";
		cout << time[0] << " " << time[1] << "\n";
		return;
	}
	
	if (2 * time[1] < (time[0] + time[capacity - 2]))
	{
		cout << time[0] << " " << time[1] << "\n";
		cout << time[0] << "\n";
		cout << time[capacity - 2] << " " << time[capacity - 1] << "\n";
		cout << time[1] << "\n";
	}
	else
	{
		cout << time[0] << " " << time[capacity - 1] << "\n";
		cout << time[0] << "\n";
		cout << time[0] << " " << time[capacity - 2] << "\n";
		cout << time[0] << "\n";
	}
	
	bridge(time, capacity - 2);
}
	
int main(int ac, char *av[])
{
	int cases;
	int time[MAXSIZE];
	int capacity, index;
	
	cin >> cases;
	while (cases--)
	{
		// 总人数。
		cin >> capacity;

		// 读取每个人的过桥时间。
		index = 0;
		while (index < capacity)
			cin >> time[index++];
	
		// 将用时数组予以排序。
		sort(time, time + capacity);

		// 计算最短过桥时间，输出过桥顺序。
		cout << shortest_time(time, capacity) << endl;
		bridge(time, capacity);

		if (cases)
			cout << endl;
	}
	
	return 0;
}
