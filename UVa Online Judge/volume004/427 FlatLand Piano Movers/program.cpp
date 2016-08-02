// FlatLand Piano Movers
// UVa ID: 427
// Verdict: Accepted
// Submission Date: 2016-08-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const double epsilon = 1e-6;

double l, w, a, b;
char comma;

double f(double x)
{
    return sqrt(l * l - x * x) * (a - x) + b * x - l * w;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);

        iss >> l >> comma >> w;

        if (l < w)
            swap(l, w);

        while (iss >> a >> comma >> b)
        {
            double left = 0, right = l;
            do
            {
                double mid = (left + right) / 2, midmid = (right + mid) / 2;
                if (f(mid) > f(midmid))
                    left = mid;
                else
                    right = mid;
                
            } while (fabs(left - right) > epsilon);
            
            cout << (f(left) >= 0 ? 'Y' : 'N');
        }
        cout << '\n';
    }
    
	return 0;
}
