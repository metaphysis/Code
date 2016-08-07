// Binomial Showdown
// UVa ID: 530
// Verdict: Accepted
// Submission Date: 2016-08-07
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

int gcd(int a, int b)
{
    int t;
    while (a % b) t = a, a = b, b = t % b;
    return b;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, k;
    while (cin >> n >> k, n || k)
    {
        if (k > n / 2)
            k = n - k;

        vector<int> up, down;
        for (int i = 1; i <= k; i++)
        {
            up.push_back(n - i + 1);
            down.push_back(i);
        }
        
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
            {
                if (up[i] > 1 && down[j] > 1)
                {
                    int divider = gcd(up[i], down[j]);
                    if (divider > 1)
                        up[i] /= divider, down[j] /= divider;
                }
            }
            
        long long int number = 1;
        for (int i = 0; i < k; i++)
            if (up[i] > 1)
                number *= up[i];
                
        cout << number << '\n';
    }
    
	return 0;
}
