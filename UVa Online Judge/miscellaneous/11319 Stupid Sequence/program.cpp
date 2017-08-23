// Stupid Sequence
// UVa ID: 11319
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

typedef unsigned long long ull;

void print(vector<vector<ull>> A)
{
    for (auto u : A)
    {
        for (auto v : u)
            cout << v << ' ';
        cout << '\n';
    }
}

bool gaussianElimination(vector<vector<ull>> &A, vector<ull> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
            for (int k = 0; k < n; k++)
                A[j][k] -= A[i][k] * A[i][i];

        print(A);
        cout << '\n';
    }

    for (int i = 0; i < n; i++) b[i] = A[i][n];

    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        ull x, term;
        
        vector<vector<ull>> A(7, vector<ull>());
        for (ull i = 1; i <= 7; i++)
        {
            x = 1;
            for (ull j = 1; j <= 7; j++)
            {
                A[i - 1].push_back(x);
                x *= i;
            }
        }
        
        vector<ull> b;
        for (int i = 1; i <= 7; i++)
        {
            cin >> term;
            b.push_back(term);
        }
        
        bool smart = gaussianElimination(A, b);
        if (smart)
        {
            for (ull i = 7; i <= 1500; i++)
            {
                term = 0, x = 1;
                for (int j = 0; j <= 6; j++)
                {
                    term += b[j] * x;
                    x *= i;
                }
                if (term != b[i])
                {
                    smart = false;
                    break;
                }
            }
        }
        
        if (smart)
        {
            for (int i = 0; i <= 6; i++)
            {
                if (i) cout << ' ';
                cout << b[i];
            }
            cout << '\n';
        }
        else cout << "This is a smart sequence!\n";
    }

    return 0;
}
