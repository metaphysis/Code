// Prince and Princess
// UVa ID: 10635
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct jump
{
    int idx, number;
    jump (int idx = 0, int number = 0): idx(idx), number(number) {}
    bool operator<(const jump &m) const
    {
        return number < m.number;
    }
    bool operator==(const jump &m) const
    {
        return number == m.number;
    }
};

vector<int> s1, s2;

int lis()
{
    vector<jump> indexer(s1.size());
    for (int i = 0; i < s1.size(); i++)
        indexer[i].idx = i, indexer[i].number = s1[i];
    sort(indexer.begin(), indexer.end());

    vector<int> M;
    for (auto number : s2)
    {
        int k = lower_bound(indexer.begin(), indexer.end(), jump(0, number)) - indexer.begin();
        if (k < indexer.size())
        {
            if (indexer[k].number == number)
            {
                if (!M.size() || indexer[k].idx > M.back()) M.push_back(indexer[k].idx);
                else
                {
                    auto location = upper_bound(M.begin(), M.end(), indexer[k].idx);
                    *location = indexer[k].idx;
                }
            }
        }
    }
    return M.size();
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, p, q;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> p >> q;
        s1.clear();
        for (int i = 0; i <= p; i++)
        {
            cin >> n;
            s1.push_back(n);
        }
        s2.clear();
        for (int i = 0; i <= q; i++)
        {
            cin >> n;
            s2.push_back(n);
        }
        cout << "Case " << c << ": " << lis() << '\n';
    }

    return 0;
}
