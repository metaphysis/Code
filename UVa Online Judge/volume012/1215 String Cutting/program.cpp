// String Cutting
// UVa ID: 1215
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    int cases, k;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> k;
        vector<int> cuts(k), sorted;
        for (int i = 0; i < k; i++) cin >> cuts[i];

        cin >> line;
        vector<vector<int>> idx(26);
        for (int i = 0; i < line.length(); i++)
            idx[line[i] - 'a'].push_back(i);

        int cost = 0;
        sorted.push_back(0); sorted.push_back(line.length());
        for (auto m : cuts)
        {
            int l = -1, r = -1;
            for (int i = sorted.size() - 1; i >= 0; i--)
                if (m > sorted[i])
                {
                    l = sorted[i], r = sorted[i + 1];
                    for (auto x : idx)
                    {
                        bool inLeft = 0, inRight = 0;
                        for (auto y : x)
                        {
                            if (y >= l && y < m) inLeft = 1;
                            if (y >= m && y < r) inRight = 1;
                        }
                        if (inLeft + inRight == 1) cost++;
                    }   
                    sorted.insert(sorted.begin() + i + 1, m);
                    break;
                }
        }
        cout << cost << '\n';
    }

    return 0;
}
