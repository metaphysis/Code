// Optical Reader
// UVa ID: 11839
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

    int n, gray;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            int answer = 0, cnt = 0;
            for (int j = 0; j < 5; j++)
            {
                cin >> gray;
                if (gray <= 127) answer = j, cnt++;
            }
            if (cnt != 1) cout << '*' << '\n';
            else cout << (char)('A' + answer) << '\n';
        }
    }

    return 0;
}
