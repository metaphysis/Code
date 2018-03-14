// GCD The Largest
// UVa ID: 12708
// Verdict: Accepted
// Submission Date: 2017-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    unsigned long long n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << (n / 2) << '\n';
    }
    
    return 0;
}
