// Stupid Sequence
// UVa ID: 11319
// Verdict: Accepted
// Submission Date: 2017-08-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull gcd(ull a, ull b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

bool gaussianElimination(vector<vector<ull>> &A, vector<ull> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
            {
                ull t = A[j][i];
                for (int k = 0; k <= n; k++)
                    A[j][k] = A[j][k] * A[i][i] - A[i][k] * t;

                ull g = A[j][0];
                for (int k = 1; k <= n; k++)
                    g = gcd(g, A[j][k]);
                for (int k = 1; k <= n; k++)
                    A[j][k] /= g;
            }

    for (int i = 0; i < n; i++)
        if (A[i][i] != 1)
            return false;
    
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
        
        bool stupid = gaussianElimination(A, b);
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
