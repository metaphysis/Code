// Error Curves
// UVa ID: 1476
// Verdict: Accepted
// Submission Date: 2016-08-02
// UVa Run Time: 0.150s
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

const double epsilon = 1e-10;

struct quadric
{
    double a, b, c;
};

vector<quadric> coefficients;

double f(double x)
{
    double max_value = coefficients.front().a * x * x + coefficients.front().b * x + coefficients.front().c;
    for (int i = 1, size = coefficients.size(); i < size; i++)
        max_value = max(max_value, coefficients[i].a * x * x + coefficients[i].b * x + coefficients[i].c);
    return max_value;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        int n;
        cin >> n;
        
        double a, b, c;
        coefficients.clear();
        
        for (int j = 1; j <= n; j++)
        {
            cin >> a >> b >> c;
            coefficients.push_back((quadric){a, b, c});
        }
        
        double left = 0, right = 1000;
        while (fabs(right - left) > epsilon)
        {
            double leftThird = left + (right - left) / 3;
            double rightThird = right - (right - left) / 3;

            if (f(leftThird) > f(rightThird))
                left = leftThird;
            else
                right = rightThird;
        }
            
        cout << fixed << setprecision(4) << f(left) << '\n';
    }
    
	return 0;
}
