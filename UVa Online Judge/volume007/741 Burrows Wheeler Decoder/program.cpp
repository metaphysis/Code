// Burrows Wheeler Decoder
// UVa ID: 741
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, row;
    string message;
    while (cin >> message)
    {
        cin >> row;
        if (message == "END" && row == 0) break;
        int n = message.length();
        string rotate[n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                rotate[j].insert(rotate[j].begin(), message[j]);
            sort(rotate, rotate + n);
        }
        if (cases++ > 0) cout << '\n';
        cout << rotate[row - 1] << '\n';
    }

    return 0;
}
