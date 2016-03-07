// The Trip （旅行）
// PC/UVa IDs: 110103/10137, Popularity: B, Success rate: average Level: 1
// Verdict: Wrong Answer
// Submission Date: 2014-02-16
// UVa Run Time: N/A
//
// 版权所有（C）2014，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

#define SIZE 1000

long findChange(long *money, int total)
{
	long long sum = 0, average = 0, remain = 0, change = 0;

	for (int i = 0; i < total; i++)
		sum += money[i];

	average = sum / total;
    remain = sum % total;
    
	for (int i = 0; i < total; i++)
	{
	    if (money[i] > average)
	    {
	        change += (money[i] - average);
	        if (remain > 0)
	        {
	            remain -= 1;
	            change -= 1;
	        }
	    }
	}

	return change;
}

long convertLng(string money)
{
    long result = 0;
    for (int i = 0; i < money.length(); i++)
    {
        if (money[i] >= '0' && money[i] <= '9')
            result = result * 10 + (money[i] - '0');
    }
    
    return result;
}

int main(int ac, char *av[])
{
	long money[SIZE], result = 0.0;
	string temp;
	int total;

	while (cin >> total, total)
	{
		for (int i = 0; i < total; i++)
		{
		    cin >> temp;
			money[i] = convertLng(temp);
		}

		result = findChange(money, total);
        cout << "$" << (result / 100) << "." << ((result % 100) / 10) << (result % 10) << endl;
		
	}

	return 0;
}
