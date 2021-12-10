// King's Poker
// UVa ID: 12366
// Verdict: Accepted
// Submission Date: 2021-12-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int A, B, C;
    while (cin >> A >> B >> C)
    {
        if (A == 0) break;
        if (A > B) swap(A, B);
        if (B > C) swap(B, C);
        if (A > B) swap(A, B);
        if (A == B && B == C)
        {
            if (A == 13) cout << "*\n";
            else cout << A + 1 << ' ' << B + 1 << ' ' << C + 1 << '\n';
        }
        else if (A == B)
        {
            if (C == 13)
                cout << 1 << ' ' << A + 1 << ' ' << B + 1 << '\n';
            else
                cout << A << ' ' << B << ' ' << C + 1 << '\n';
        }
        else if (B == C)
        {
            if (A == 12 && B == 13) cout << "1 1 1\n";
            else
            {
                A++;
                if (A == B) A++;
                if (A < B) cout << A << ' ' << B << ' ' << C << '\n';
                else cout << B << ' ' << C << ' ' << A << '\n';
            }
        }
        else cout << "1 1 2\n";
    }

    return 0;
}
