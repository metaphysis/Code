// Automatic Editing
// UVa ID: 10115
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string fs, rs, text;

    while (cin >> n, n > 0)
    {
        vector<pair<string, string>> rules;
        cin.ignore(1024, '\n');
        for (int i = 0; i < n; i++)
        {
            getline(cin, fs);
            getline(cin, rs);
            rules.push_back(make_pair(fs, rs));
        }

        getline(cin, text);
        for (int i = 0; i < rules.size(); i++)
        {
            fs = rules[i].first, rs = rules[i].second;
            size_t pos;
            while ((pos = text.find(fs)) != text.npos)
                text.replace(pos, fs.length(), rs);
        }
        cout << text << '\n';
    }

    return 0;
}
