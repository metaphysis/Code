// Joana and the Odd Numbers
// UVa ID: 913
// Verdict: Accepted
// Submission Date: 2017-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long int n;
    
    while (cin >> n)
    {
        long long int sum = (1 + n) * (n / 2 + 1) - 1;
        sum = sum + (sum - 2) + (sum - 4);
        cout << sum << '\n';
    }
    
    return 0;
}
