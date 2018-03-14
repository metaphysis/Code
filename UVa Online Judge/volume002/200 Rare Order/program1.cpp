// Rare Order
// UVa ID: 200
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 26;
vector<int> edges[MAXV];
int degreeOfIn[MAXV], visited[MAXV];

int main(int argc, char *argv[])
{
    string word;
    vector<string> words;

    while (getline(cin, word)) {
        if (word != "#") {
            words.push_back(word);
            continue;
        }

        for (int u = 0; u < MAXV; u++) edges[u].clear();
        memset(degreeOfIn, 0, sizeof(degreeOfIn));
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < words.size() - 1; i++)
            for (int j = 0; j < min(words[i].length(), words[i + 1].length()); j++)
            {
                int u = words[i][j] - 'A', v = words[i + 1][j] - 'A';
                visited[u] = visited[v] = 1;
                if (u != v)
                {
                    edges[u].push_back(v);
                    degreeOfIn[v]++;
                    break;
                }
            }

        queue<int> q;
        for (int u = 0; u < MAXV; u++)
            if (visited[u] && degreeOfIn[u] == 0)
                q.push(u);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (auto v : edges[u])
                if (--degreeOfIn[v] == 0)
                    q.push(v);
            cout << (char)('A' + u);
        }
        cout << '\n';

        words.clear();
    }

    return 0;
}
