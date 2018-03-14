// The Eurocup is Here!
// UVa ID: 10666
// Verdict: Accepted
// Submission Date: 2018-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, x;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> x;
        bitset<32> bits(x);
        cout << (bits.count() + 1) << ' ';
        int worser = 0;
        while (worser < n)
        {
            if (bits.test(worser)) break;
            worser++;
        }
        cout << (int)pow(2, n) - ((int)pow(2, worser) - 1) << '\n';
    }
    
    return 0;
}
