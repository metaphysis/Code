// Dog and Gopher （狗拿地鼠）
// PC/UVa IDs: 111301/10310, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.044s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>

using namespace std;

int main(int ac, char *av[])
{
	int n;
	double gopherX, gopherY, dogX, dogY, holeX, holeY;
	double emptyX, emptyY;

	while (cin >> n >> gopherX >> gopherY >> dogX >> dogY)
	{
		bool successed = false;
		for (int i = 1; i <= n; i++)
		{
			cin >> holeX >> holeY;

			// 判断距离。
			if ((pow(dogX - holeX, 2) + pow(dogY - holeY, 2)) >=
				4.0 * (pow(gopherX - holeX, 2) +
						pow(gopherY - holeY, 2)))
			{
				successed = true;

				// 读取完剩余数据。
				for (int j = i + 1; j <= n; j++)
					cin >> emptyX >> emptyY;
				break;
			}
		}

		if (successed)
		{
			cout.precision(3);
			cout.setf(ios::fixed | ios::showpoint);
			cout << "The gopher can escape through the hole at (";
			cout << holeX << "," << holeY << ")." << endl;
		}
		else
			cout << "The gopher cannot escape." << endl;
	}

	return 0;
}
