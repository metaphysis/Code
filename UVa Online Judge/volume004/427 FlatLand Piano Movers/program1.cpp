// FlatLand Piano Movers
// UVa ID: 427
// Verdict: Accepted
// Submission Date: 2016-08-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-6;

double L, W, w1, w2;
char comma;

double f(double x)
{
    return sqrt(L * L - x * x) * (w1 - x) + w2 * x - L * W;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);

        iss >> L >> comma >> W;

        if (L < W)
            swap(L, W);

        while (iss >> w1 >> comma >> w2)
        {
            double left = 0, right = L;
            do {
                double leftThird = left + (right - left) / 3;
                double rightThird = right - (right - left) / 3;

                if (f(leftThird) > f(rightThird))
                    left = leftThird;
                else
                    right = rightThird;
            } while (fabs(left - right) > EPSILON);

            cout << (f(left) >= 0 ? 'Y' : 'N');
        }
        cout << '\n';
    }

	return 0;
}
