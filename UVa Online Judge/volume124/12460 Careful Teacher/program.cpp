// Careful Teacher
// UVa ID: 12460
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.870s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int visited[20010];
list<int> edges[20010];
unordered_map<string, int> dicts;
vector<string> words;

bool likely(int i, int j)
{
    if (words[i].length() != words[j].length()) return false;
    int cnt = 0;
    for (int k = 0; k < words[i].length() && cnt < 2; k++)
        if (words[i][k] != words[j][k])
            cnt++;
    return cnt == 1;
}

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string word;
    int idx = 0;
    while (cin >> word)
    {
        if (word == "--") break;
        dicts[word] = idx++;
        words.push_back(word);
    }

    int n = words.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (likely(i, j))
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
    
    string start, end;
    while (cin >> start >> end)
    {
        if (dicts.find(start) == dicts.end() || dicts.find(end) == dicts.end()) cout << "No\n";
        memset(visited, 0, n * sizeof(int));
        int s = dicts[start], e = dicts[end];
        dfs(s);
        if (visited[e]) cout << "Yes\n";
        else cout << "No\n";
    }
    
    return 0;
}
