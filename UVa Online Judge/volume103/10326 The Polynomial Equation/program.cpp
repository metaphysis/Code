// The Polynomial Equation
// UVa ID: 10326
// Verdict: Accepted
// Submission Date: 2017-03-26
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

    int n, root;
    
    while (cin >> n)
    {
        vector<long long> coefficients{1};
        for (int i = 1; i <= n; i++)
        {
            cin >> root;
            vector<long long> next(coefficients.size() + 1, 0), multiple{1, -root};
            for (int i = 0; i < coefficients.size(); i++)
                for (int j = 0; j < multiple.size(); j++)
                    next[i + j] += coefficients[i] * multiple[j];
            coefficients.swap(next);
        }
        
        for (int i = 0, j = coefficients.size() - 1; i < coefficients.size() - 1; i++, j--)
        {
            if (abs(coefficients[i]) > 0)
            {
                if (i > 0)
                {
                    if (coefficients[i] > 0) cout << " + ";
                    else cout << " - ";
                }

                if (abs(coefficients[i]) != 1) cout << abs(coefficients[i]);
                cout << 'x';
                if (j > 1) cout << '^' << j;
            }
        }
        
        if (coefficients.back() >= 0) cout << " + " << coefficients.back();
        else cout << " - " << abs(coefficients.back());

        cout << " = 0\n";
    }
    
    return 0;
}
