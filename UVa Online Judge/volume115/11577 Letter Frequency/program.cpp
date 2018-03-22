// Letter Frequency
// UVa ID: 11577
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<char, int> a, pair<char, int> b)
{
    if (a.second != b.second)
        return a.second > b.second;
    return a.first < b.first;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cnt[26] = {0};
    cin >> n; cin.ignore(1024, '\n');
    for (int c = 1; c <= n; c++)
    {
        string line;
        getline(cin, line);
        memset(cnt, 0, sizeof(cnt));
        for (auto letter : line)
            if (isalpha(letter))
                cnt[tolower(letter) - 'a']++;
        vector<pair<char, int>> counter;
        for (int i = 0; i < 26; i++)
            if (cnt[i])
                counter.push_back(make_pair((char)('a' + i), cnt[i]));
        sort(counter.begin(), counter.end(), cmp);
        cout << counter[0].first;
        for (int i = 1; i < counter.size(); i++)
            if (counter[i].second == counter[0].second)
                cout << counter[i].first;
        cout << '\n';
    }

    return 0;
}
