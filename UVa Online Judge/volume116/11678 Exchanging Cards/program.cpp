// Exchanging Cards
// UVa ID: 11678
// Verdict: Accepted
// Submission Date: 2017-12-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int A, B, card1[10001], card2[10001];
    
    while (cin >> A >> B, A > 0)
    {
        for (int i = 0; i < A; i++)
            cin >> card1[i];
        for (int i = 0; i < B; i++)
            cin >> card2[i];
            
        int trade1 = 0, trade2 = 0;
        for (int i = 0; i < A; i++)
        {
            if (i && card1[i] == card1[i - 1]) continue;
            if (!binary_search(card2, card2 + B, card1[i]))
                trade1++;
        }
        for (int i = 0; i < B; i++)
        {
            if (i && card2[i] == card2[i - 1]) continue;
            if (!binary_search(card1, card1 + A, card2[i]))
                trade2++;
        }
        cout << min(trade1, trade2) << '\n';
    }

    return 0;
}
