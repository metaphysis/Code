// I Love String!
// UVa ID: 10679
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, q;
    string S, T;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> S >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> T;
            if (S.length() < T.length()) cout << 'n';
            else
            {
                if (S.length() <= 128)
                {
                    if (S.find(T) != S.npos)
                        cout << 'y';
                    else
                        cout << 'n';
                }
                else
                {
                    bool same = true;
                    for (int j = 0; j < T.length(); j++)
                        if (S[j] != T[j])
                        {
                            same = false;
                            break;
                        }
                    cout << (same ? 'y' : 'n');
                }
            }
            cout << '\n';
        }
    }

    return 0;
}
