// GNU = GNU'sNotUnix
// UVa ID: 10625
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int R;
        cin >> R;
        string rule;
        vector<pair<char, string>> rules;
        for (int i = 1; i <= R; i++)
        {
            cin >> rule;
            rules.push_back(make_pair(rule.front(), rule.substr(rule.find('>') + 1)));
        }
        
        int Q;
        cin >> Q;
        for (int i = 1; i <= Q; i++)
        {
            string S;
            char x;
            int n;
            
            cin >> S >> x >> n;

            unsigned long long cnt[128] = {0}, changed[128], added[128];
            for (auto letter : S) cnt[letter]++;
            
            for (int j = 1; j <= n; j++)
            {
                memset(changed, 0, sizeof(changed));
                memset(added, 0, sizeof(added));
                for (auto r : rules)
                {
                    for (auto s : r.second)
                    {
                        if (s == r.first)
                            changed[s] += cnt[r.first];
                        else
                            added[s] += cnt[r.first];
                    }
                }
                for (auto r : rules)
                    cnt[r.first] = changed[r.first];
                for (int i = 33; i <= 126; i++)
                    cnt[i] += added[i];
            }
            
            cout << cnt[x] << '\n';
        }
    }

    return 0;
}
