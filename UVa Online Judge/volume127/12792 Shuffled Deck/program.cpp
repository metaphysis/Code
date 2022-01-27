// Shuffled Deck
// UVa ID: 12792
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int P;
    while (cin >> P)
    {
        P++;
        int shuffle = 1, mod = 2;
        while (true)
        {
            if (mod == 1)
            {
                cout << shuffle << '\n';
                break;
            }
            mod *= 2;
            mod %= P;
            shuffle++;
        }
    }
    return 0;
}
