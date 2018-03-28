// Calculating Yuan Fen
// UVa ID: 12414
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.160s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int digit[128];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        bool flag = false;
        for (int n = 1; n <= 10000; n++)
        {
            string number;
            for (auto c : line) number += to_string(n + c - 'A');
            int cnt = number.length();
            for (int i = 0; i < cnt; i++) digit[i] = number[i] - '0';
            if (cnt >= 3)
            {
                cnt -= 3;
                for (int i = 1; i <= cnt; i++)
                {
                    int up = number.length() - i;
                    for (int j = 0; j < up; j++)
                        digit[j] = (digit[j] + digit[j + 1]) % 10;
                }
                if (digit[0] == 1 && digit[1] == 0 && digit[2] == 0)
                {
                    cout << n << '\n';;
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) cout << ":(\n";
    }

    return 0;
}
