// Close Relatives
// UVa ID: 11131
// Verdict: Accepted
// Submission Date: 2018-02-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<string, vector<string>> tree;

void dfs(string u, bool leftToRight)
{
    if (leftToRight)
        for (auto v : tree[u])
            dfs(v, leftToRight);
    else
        for (int v = tree[u].size() - 1; v >= 0; v--)
            dfs(tree[u][v], leftToRight);
    cout << u << '\n';
    
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, block, root;
    int lineNumber = 0;

    while (getline(cin, line))
    {
        istringstream iss(line);
        vector<string> quesnots;
        while (getline(iss, block, ','))
            quesnots.push_back(block);
        for (int i = 1; i < quesnots.size(); i++)
            tree[quesnots.front()].push_back(quesnots[i]);
        lineNumber++;
        if (lineNumber == 1) root = quesnots.front();
    }

    cout << 2 << '\n';
    cout << '\n';
    dfs(root, true);
    cout << '\n';
    dfs(root, false);

    return 0;
}
