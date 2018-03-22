// Election
// UVa ID: 10374
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b)
{
    return a.second > b.second;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n;
        cin >> n; cin.ignore(1024, '\n');
        
        string name, party;
        map<string, string> candidate;
        map<string, int> cnt;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, name);
            getline(cin, party);
            candidate[name] = party;
        }
        
        cin >> n; cin.ignore(1024, '\n');
        string ballot;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, ballot);
            if (candidate.find(ballot) != candidate.end())
            {
                cnt[ballot]++;
            }
        }
        
        vector<pair<string, int>> all;
        for (auto p : cnt)
            all.push_back(make_pair(p.first, p.second));
        sort(all.begin(), all.end(), cmp);
        
        if (c > 1) cout << '\n';
        if (all.size() == 1 || (all.size() > 1 && all[0].second > all[1].second))
        {
            cout << candidate[all.front().first] << '\n';
        }
        else
        {
            cout << "tie\n";
        }
    }

    return 0;
}
