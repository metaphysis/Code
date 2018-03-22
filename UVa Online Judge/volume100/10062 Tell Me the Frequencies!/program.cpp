// Tell Me the Frequencies!
// UVa ID: 10062
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<char, int> a, pair<char, int> b)
{
    if (a.second != b.second) return a.second < b.second;
    return a.first > b.first;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string line;
    while (getline(cin, line))
    {
        if (cases++ > 0) cout << '\n';
        map<char, int> cnt;
        for (auto c : line)
            cnt[c]++;
        vector<pair<char, int>> counter;
        for (auto p : cnt)
            counter.push_back(make_pair(p.first, p.second));
        sort(counter.begin(), counter.end(), cmp);
        for (auto p : counter)
            cout << (int)p.first << ' ' << p.second << '\n';
    }

    return 0;
}
