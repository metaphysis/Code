// Newspaper
// UVa ID: 11340
// Verdict: Accepted
// Submission Date: 2018-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, paid[256], k, p, value;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> k; in.ignore(1024, '\n');c
        memset(paid, 0, sizeof(paid));

        // Warning! The paid character may be space!
        for (int i = 0; i < k; i++)
        {
            getline(cin, line);
            paid[line[0] + 128] = stoi(line.substr(2));
        }

        cin >> p; cin.ignore(1024, '\n');

        long long money = 0;
        for (int i = 0; i < p; i++)
        {
            getline(cin, line);
            for (int j = 0; j < line.length(); j++)
                money += paid[line[j] + 128];
        }

        cout << (money / 100) << '.' << setw(2) << setfill('0') << (money % 100) << "$\n";
    }

    return 0;
}
