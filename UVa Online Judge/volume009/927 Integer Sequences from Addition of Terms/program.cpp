// Integer Sequences from Addition of Terms
// UVa ID: 927
// Verdict: Accepted
// Submission Date: 2017-03-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<int> total;
    
    for (int i = 0; i <= 2000; i++)
        total.push_back(i * (i + 1) / 2);

    int cases = 0;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int coefficients[30], degree;

        cin >> degree;
        for (int i = 0; i <= degree; i++)
            cin >> coefficients[i];
        
        int d, k;

        cin >> d >> k;
        for (int i = 1; i <= 2000; i++)
        {
            if (total[i] * d >= k)
            {
                unsigned long long int n = coefficients[0], power = 1;

                for (int k = 1; k <= degree; k++)
                {
                    power *= i;
                    n += coefficients[k] * power;
                }
                
                cout << n << '\n';
                break;
            }
        }
    }
    
    return 0;
}
