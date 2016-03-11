// Pairsumonious Numbers （两两之和）
// PC/UVa IDs: 110508/10202, Popularity: B, Success rate: high Level: 4
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.024s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
	
using namespace std;
	
bool cmp(int a, int b)
{
	return a < b;
}
	
// smallest 为假定的 A[0]，尝试从此找到所有 A 的元素而不发生冲突。
vector < int > complete_all(int smallest, vector < int > sum)
{
	vector < int > parameters;
	parameters.push_back(smallest);
	
	while (sum.size())
	{
		int next = sum[0] - parameters[0];
		for (int i = 0; i < parameters.size(); i++)
		{
			vector < int >::iterator it = 
			find(sum.begin(), sum.end(), next + parameters[i]);
			if (it != sum.end())
				sum.erase(it);
			else
			{
				parameters.clear();
				return parameters;
			}
		}
		
		parameters.push_back(next);
	}
	
	return parameters;
}
	
// 用第一种方法，枚举 0 <= A[0] <= (P[0] / 2)。
void find_pairsumonious_numbers_by_first_method(vector < int > sum)
{
	// 将和按照从小到大排列。
	sort(sum.begin(), sum.end(), cmp);
	
	// 将和调整到自然数范围。
	int adjust = 0;
	if (sum[0] < 0)
		adjust = sum[0] * (-2);
	else
		adjust = 0;
	
	for (int i = 0; i < sum.size(); i++)
		sum[i] += adjust;
	
	bool found = false;
	for (int i = 0; i <= (sum[0] / 2); i++)
	{
		vector < int > answer;
		answer = complete_all(i, sum);
	
		if (answer.size())
		{
			for (int i = 0; i < answer.size(); i++)
			{
				cout << (answer[i] - adjust / 2);
				if (i < (answer.size() - 1))
					cout << " ";
			}
			cout << endl;
			found = true;
			break;
		}
	}
	
	if (!found)
		cout << "Impossible" << endl;
}
	
// 用第二种方法，枚举数组 P[2] 至 P[N + 1] 为 A[1] + A[2]。
void find_pairsumonious_numbers_by_second_method(vector < int > sum, int n)
{
	// 将和按照从小到大排列。
	sort(sum.begin(), sum.end(), cmp);
	
	bool found = false;
	for (int i = 2; i <= (n + 1); i++)
	{
		vector < int > answer;
		
		// 只有当 tmp 为偶数才有可能。
		int tmp = sum[0] + sum[1] - sum[i];
		if (tmp % 2 == 1)
			continue;
		
		answer = complete_all(tmp / 2, sum);
	
		if (answer.size())
		{
			for (int i = 0; i < answer.size(); i++)
			{
				cout << answer[i];
				if (i < (answer.size() - 1))
					cout << " ";
			}
			cout << endl;
			found = true;
			break;
		}
	}
	
	if (!found)
		cout << "Impossible" << endl;
}
	
int main(int ac, char *av[])
{
	int n, tmp;
	vector < int > sum;
	
	while (cin >> n)
	{
		int capacity = (n * (n - 1) / 2);	// 和数组元素个数。
		int counter = 0;	// 计数器。
		
		sum.clear();	// 清空和数组。
		
		// 读入和。
		while (counter++ < capacity)
		{
			cin >> tmp;
			sum.push_back(tmp);
		}
		
		// find_pairsumonious_numbers_by_first_method(sum);
		find_pairsumonious_numbers_by_second_method(sum, n);
	}
	
	return 0;
}
