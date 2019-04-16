// Carrol's Scrabble
// UVa ID: 13295
// Verdict: Accepted
// Submission Date: 2019-04-16
// UVa Run Time: 0.230s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10010, INF = 0x3f3f3f3f;

struct word
{
    int points;
    string original, sorted;
    bool operator<(const word &w) const
    {
        return original.length() < w.original.length();
    }
} words[MAXN];

struct data
{
    int u, p, w;
    data (int u = 0, int p = 0, int w = 0): u(u), p(p), w(w) {}
};

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
};

vector<edge> g[MAXN];
map<string, int> indexer;
int ps[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int getPoints(string &w)
{
    int points = 0;
    for (auto c : w) points += ps[c - 'a'];
    return points;
}

bool hasEdge(int i, int j)
{
    if (words[i].sorted == words[j].sorted) return true;
    int diff = 0;
    for (int k = 0; k < words[i].original.length() && diff < 2; k++)
        if (words[i].original[k] != words[j].original[k])
            diff++;
    return diff == 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N;
    while (cin >> N)
    {
        string w;
        for (int i = 0; i < N; i++)
        {
            cin >> w;
            words[i].original = w;
            sort(w.begin(), w.end());
            words[i].sorted = w;
            words[i].points = getPoints(w);
        }

        sort(words, words + N);

        indexer.clear();
        for (int i = 0; i < N; i++) g[i].clear();
        for (int i = 0; i < N; i++)
        {
            indexer[words[i].original] = i;
            for (int j = i + 1; j < N; j++)
            {
                if (words[i].original.length() != words[j].original.length())
                    break;
                if (hasEdge(i, j))
                {
                    g[i].push_back(edge(j, words[j].points));
                    g[j].push_back(edge(i, words[i].points));
                }
            }
        }

        int Q;
        cin >> Q;
        string w1, TO, w2;
        int visited[MAXN], P[MAXN], S[MAXN];
        for (int i = 0; i < Q; i++)
        {
            cin >> w1 >> TO >> w2;
            cout << w1 << " TO " << w2 << ' ';
            if (w1.length() != w2.length())
            {
                cout << "IMPOSSIBLE\n";
                continue;
            }
            if (w1 == w2)
            {
                cout << "0 0\n";
                continue;
            }
            int s = indexer[w1], t = indexer[w2];
            memset(visited, 0, sizeof(visited));
            memset(P, 0x3f, sizeof(P));
            memset(S, 0, sizeof(S));
            queue<data> q;
            visited[s] = 1;
            S[s] = 0;
            q.push(data(s, 0, 0));
            int bestPath = INF, bestSum = 0;
            while (!q.empty())
            {
                data d = q.front(); q.pop();
                if (d.p > bestPath) continue;
                if (d.u == t)
                {
                    if (d.p < bestPath || (d.p == bestPath && d.w > bestSum))
                    {
                        bestPath = d.p;
                        bestSum = d.w;
                    }
                }
                else
                {
                    for (auto e : g[d.u])
                        if (!visited[e.v] || (d.p + 1 == P[e.v] && d.w + e.w > S[e.v]))
                        {
                            visited[e.v] = 1;
                            P[e.v] = d.p + 1;
                            S[e.v] = d.w + e.w;
                            q.push(data(e.v, d.p + 1, d.w + e.w));
                        }
                }
            }
            if (bestPath < INF) cout << bestPath << ' ' << bestSum - words[t].points;
            else cout << "IMPOSSIBLE";
            cout << '\n';
        }
    }

    return 0;
}
