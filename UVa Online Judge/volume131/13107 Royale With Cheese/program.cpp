// Royale With Cheese
// UVa ID: 13107
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int number[26];
    int code[27] = {0, 1, 5, 3, 4, 2, 9, 7, 8, 6, 10, 11, 15, 13, 14, 12, 19, 17, 18, 16, 50, 51, 55, 53, 54, 52, 59};
    string line;
    while (cin >> line)
    {
        memset(number, 0, sizeof number);
        int idx = 1;
        for (int i = 0; i < line.length(); i++)
        {
            int d = line[i] - 'a';
            if (!number[d]) number[d] = idx++;
            cout << code[number[d]];
        }
        cout << '\n';
    }
    return 0;
}
