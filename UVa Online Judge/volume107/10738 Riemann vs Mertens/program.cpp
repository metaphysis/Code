// Riemann vs Mertens
// UVa ID: 10738
// Verdict: Accepted
// Submission Date: 2018-03-11
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 20;

int mobius[MAXN] = {0}, M[MAXN] = {0};

void getMobius()
{
    for (int i = 1; i < MAXN; i++) {
        int sum = (i == 1 ? 1 : 0);
        int delta = sum - mobius[i];
        mobius[i] = delta;
        M[i] = M[i - 1] + mobius[i];
        for (int j = i + i; j < MAXN; j += i)
            mobius[j] += delta;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    getMobius();
    
    int n;
    while (cin >> n, n > 0)
    {
        cout << setw(8) << right << n;
        cout << setw(8) << right << mobius[n];
        cout << setw(8) << right << M[n];
        cout << '\n';
    }
    
    return 0;
}
