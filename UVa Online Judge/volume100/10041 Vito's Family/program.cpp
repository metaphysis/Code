// Vito’s Family （Vito 家族）
// PC/UVa IDs: 110401/10041, Popularity: A, Success rate: high Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-21
// UVa Run Time: 0.104s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <algorithm>
	
using namespace std;
	
#define MAXSIZE 500
	
int main(int ac, char *av[])
{
	int cases, total;
	int address[MAXSIZE];
	
	cin >> cases;
	while (cases--)
	{
		cin >> total;
		int counter = 0;
		while (counter < total)
			cin >> address[counter++];
	
		sort(address, address + total);
	
		// 找到中位数并求和，注意该题所求的中位数须为整数。
		int middle;
		if (total & 1)
			middle = address[total / 2];
		else
			middle = (int) (((float) (address[total / 2 - 1] +
					address[total / 2]) * 5.0 + 5.0) / 10.0);
	
		long shortest = 0;
	
		for (int i = 0; i < total; i++)
		{
			int distance = middle - address[i];
			shortest += (distance >= 0 ? distance : (-1) * distance);
		}
	
		cout << shortest << endl;
	}
	
	return 0;
}
