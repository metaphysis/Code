// Hats
// UVa ID: 12024
// Verdict: Accepted
// Submission Date: 2017-07-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    int F[13] = {0, 1}, D[13] = {0};

    for (int i = 2; i <= 12; i++)
    {
        F[i] = F[i - 1] * i;
        D[i] = i * D[i - 1] + (i % 2 == 0 ? 1 : -1);
    }
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << D[n] << '/' << F[n] << '\n';
    }
    
    return 0;
}
