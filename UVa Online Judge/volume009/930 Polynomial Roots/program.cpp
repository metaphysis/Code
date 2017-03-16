// Polynomial Roots
// UVa ID: 930
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        int degree, n, used[100];
        double coefficients[100], temp[100], roots[100];
        
        cin >> n;
        for (int i = 0; i <= n; i++)
            cin >> coefficients[i];
            
        n -= 2;
        for (int i = 0; i < n; i++)
            cin >> roots[i];
        
        memset(used, 0, sizeof(used));
        degree = n + 2;
        
        while (degree >= 0)
        {
            bool updated = false;
            for (int i = 0; i < n; i++)
            {
                if (!used[i])
                {
                    copy(coefficients, coefficients + 100, temp);
                    for (int j = 1; j < degree; j++)
                        temp[j] += temp[j - 1] * roots[i];
                    if (fabs(temp[degree]) < 1e-7)
                    { 
                        used[i] = 1;
                        updated = true;
                        copy(temp, temp + 100, coefficients);
                        break;
                    }
                }
            }
            
            if (!updated)
            {
                double root = -
                for (int j = 1; j < degree; j++)
                    temp[j] += temp[j - 1] * roots[i];
            }
            
            degree--;
        }
    }
    
    return 0;
}
