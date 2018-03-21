// Decoding
// UVa ID: 11541
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";

        string line;
        cin >> line;
        
        char last;
        int cnt = 0;
        for (auto c : line)
        {
            if (isalpha(c))
            {
                for (int i = 0; i < cnt; i++)
                    cout << last;
                last = c;
                cnt = 0;
            }
            else
            {
                cnt = cnt * 10 + c - '0';
            }
        }

        for (int i = 0; i < cnt; i++)
            cout << last;

        cout << '\n';
    }

    return 0;
}
