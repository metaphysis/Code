// The Trip （旅行）
// PC/UVa IDs: 110103/10137, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-04-09
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

#define SIZE 1000

double findChange(double *money, int total)
{
	double average = 0.0, changeDown = 0.0, changeUp = 0.0, change = 0.0;

	for (int i = 0; i < total; i++)
		average += money[i];

	average /= total;
	average = (long) (average * 100 + 0.5) / 100.00;

	for (int i = 0; i < total; i++)
	{
		if (money[i] > average)
			changeUp += (money[i] - average);
		else
			changeDown += (average - money[i]);
	}

	if (changeDown > 0 && changeUp > 0)
	{
		if (changeDown > changeUp)
			change = changeUp;
		else
			change = changeDown;
	}
	else
	{
		if (changeUp == 0 && changeDown == 0)
			change = 0.0;
		else
		{
			if (changeDown == 0)
			{
				for (int i = 0; i < total; i++)
					if (money[i] > average)
						change +=
							(money[i] - average -
							0.01);
			}
			else
			{
				for (int i = 0; i < total; i++)
					if (money[i] < average)
						change +=
							(average - money[i] -
							0.01);
			}
		}
	}

	return change;
}

int main(int ac, char *av[])
{
	double money[SIZE], result = 0.0;
	int total;

	while (cin >> total, total)
	{
		for (int i = 0; i < total; i++)
			cin >> money[i];

		result = findChange(money, total);

		cout.precision(2);
		cout.setf(ios::fixed | ios::showpoint);
		cout << "$" << result << endl;
	}

	return 0;
}
