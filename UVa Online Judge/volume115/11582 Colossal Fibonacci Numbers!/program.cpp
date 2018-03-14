// Colossal Fibonacci Numbers!
// UVa ID: 11582
// Verdict: Accepted
// Submission Date: 2017-06-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> f[1001];

int pow_mod(int a, unsigned long long b, int n)
{
    if (b == 0) return 1;
    int r = pow_mod(a, b >> 1, n);
    r = (r * r) % n;
    if (b & 1) r = (r * a) % n;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    unsigned long long a, b, n;
    
    for (int i = 2; i <= 1000; i++)
    {
        f[i].push_back(0); f[i].push_back(1);

        int j = 1; 
        do
        {
            j += 1;
            f[i].push_back((f[i][j - 1] + f[i][j - 2]) % i);
        }
        while (f[i][j - 1] != f[i][0] || f[i][j] != f[i][1]);

        f[i].pop_back(); f[i].pop_back();
    }

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> a >> b >> n;

        if (a == 0 || n == 1) { cout << "0\n"; continue; }
        if (a == 1) { cout << "1\n"; continue; }
        
        int mod = f[n].size();
        int r = pow_mod(a % mod, b, mod);
        cout << f[n][r] << '\n';
    }

    return 0;
}
