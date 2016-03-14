// The Knights of the Round Table （圆桌骑士）
// PC/UVa IDs: 111303/10195, Popularity: A, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int ac, char *av[])
{
	double a, b, c, r;
	
	cout.precision(3);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> a >> b >> c)
	{
		if (a == 0.0 || b == 0.0 || c == 0.0)
			r = 0.0;
		else
		{
			double A, C;
			A = acos((b * b + c * c - a * a) / (2.0 * b * c));
			C = acos((a * a + b * b - c * c) / (2.0 * a * b)); 
			r = b * tan(A / 2) * tan(C / 2) / (tan(A / 2) + tan(C / 2));
		}

		cout << "The radius of the round table is: " << r << endl;	
	}

	return 0;
}
