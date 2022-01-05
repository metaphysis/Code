// Rockabye Tobby
// UVa ID: 13190
// Verdict: Accepted
// Submission Date: 2022-01-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct drug
{
    int idx, time, frequency;
    bool operator<(const drug& d) const
    {
        if (time != d.time) return time > d.time;
        return idx > d.idx;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n, k, f;
    string names[3010];

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n >> k;
        priority_queue<drug> q;
        for (int i = 0; i < n; i++)
        {
            cin >> names[i] >> f;
            q.push(drug{i, f, f});
        }
        for (int i = 1; i <= k; i++)
        {
            drug d = q.top();
            q.pop();
            cout << d.time << ' ' << names[d.idx] << '\n';
            d.time += d.frequency;
            q.push(d);
        }
    }
    return 0;
}
