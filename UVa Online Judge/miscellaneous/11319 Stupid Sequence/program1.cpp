// Stupid Sequence
// UVa ID: 11319
// Verdict: Accepted
// Submission Date: 2017-08-24
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

typedef unsigned long long ull;

ull gcd(ull a, ull b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

bool gaussianElimination1(vector<vector<ull>> &A, vector<ull> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++)
                    A[j][k] -= A[j][i] * A[i][k];
                    
        ull g = gcd(A[j][i + 1], A[j][i + 1]);
            for (int k = i + 2; k < n + 1; k++)
                g = gcd(g, A[j][k]);
            for (int k = 0; k < n + 1; k++)
                A[j][k] /= g;
    }

    for (int i = 0; i < n; i++) b[i] = A[i][n];
    
    return true;
}

bool gaussianElimination(vector<vector<ull>> &A, vector<ull> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = i + 1; k < n + 1; k++)
                A[j][k] = A[j][k] * A[i][i] - A[i][k] * A[j][i];
            A[j][i] = 0;
            
            ull g = gcd(A[j][i + 1], A[j][i + 1]);
            for (int k = i + 2; k < n + 1; k++)
                g = gcd(g, A[j][k]);
            for (int k = 0; k < n + 1; k++)
                A[j][k] /= g;
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (A[i][i] == 0 || (A[i][n] % A[i][i]) != 0) return false;
        A[i][n] /= A[i][i];
        
        for (int j = 0; j < i; j++)
        {
            A[j][n] -= A[i][n] * A[j][i];
            A[j][i] = 0;
        }
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
        for (int i = 1; i <= 1500; i++)
        {
            cin >> term;
            b.push_back(term);
        }
        
        bool stupid = gaussianElimination1(A, b);
        if (stupid)
        {
            for (ull i = 8; i <= 1500; i++)
            {
                term = 0, x = 1;
                for (int j = 0; j <= 6; j++)
                {
                    term += b[j] * x;
                    x *= i;
                }
                if (term != b[i - 1])
                {
                    stupid = false;
                    break;
                }
            }
        }
        
        if (stupid)
        {
            for (int i = 0; i <= 6; i++)
                if (b[i] > 1000)
                {
                    stupid = false;
                    break;
                }
        }
        
        if (stupid)
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
