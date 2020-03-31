// Blocks
// UVa ID: 10559
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int DUMM = 300;

map<string, int> dp;

string getHash(vector<int> blocks)
{
    string hash;
    for (int i = 0; i < blocks.size(); i++)
    {
        if (hash.size() > 0) hash += '.';
        hash += to_string(blocks[i]);
    }
    return hash;
}

int cnt = 0;

int dfs(vector<int> blocks)
{
    string hash = getHash(blocks);
    if (dp.find(hash) != dp.end()) return dp[hash];
    blocks.push_back(DUMM);
    int r = 0, last = 0, current = 0;
    while (current < blocks.size())
    {
        if (blocks[current] != blocks[last])
        {
            vector<int> next;
            next.assign(blocks.begin(), blocks.end());
            next.erase(next.begin() + last, next.begin() + current);
            int k = current - last;
            r = max(r, k * k + dfs(next));
            last = current;
        }
        current++;
    }
    return dp[hash] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n, color;
        cin >> n;
        vector<int> blocks;
        for (int i = 0; i < n; i++)
        {
            cin >> color;
            blocks.push_back(color);
        }
        dp.clear();
        dp[to_string(DUMM)] = 0;
        cnt = 0;
        cout << "Case " << cs << ": " << dfs(blocks) << '\n';
    }

    return 0;
}
