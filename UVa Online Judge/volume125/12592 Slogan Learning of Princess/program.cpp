// Slogan Learning of Princess
// UVa ID: 12592
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m;
    while (cin >> n)
    {
        map<string, string> slogan;
        string line1, line2;
        cin.ignore(1024, '\n');

        for (int i = 1; i <= n; i++)
        {
            getline(cin, line1); getline(cin, line2);
            slogan[line1] = line2;
        }

        cin >> m;
        cin.ignore(1024, '\n');

        for (int i = 1; i <= m; i++)
        {
            getline(cin, line1);
            cout << slogan[line1] << '\n';
        }
    }

    return 0;
}
