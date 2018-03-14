// Hay Points
// UVa ID: 10295
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m;
    map<string, long long> dict;
    string keyword, line, word;
    long long money;

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> keyword >> money;
        dict[keyword] = money;
    }
    cin.ignore(1024, '\n');
    for (int i = 1; i <= m; i++)
    {
        long long salary = 0;
        while (getline(cin, line), line != ".")
        {
            istringstream iss(line);
            while (iss >> word)
            {
                if (dict.find(word) != dict.end()) salary += dict[word];
            }
        }
        cout << salary << '\n';
    }

    return 0;
}
