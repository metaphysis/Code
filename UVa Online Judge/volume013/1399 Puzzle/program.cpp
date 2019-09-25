// Puzzle
// UVa ID: 1399
// Verdict: Accepted
// Submission Date: 2019-09-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50010, CHARSET = 26, FAIL = -1;

int T, N, S;
int cnt, root;
int go[MAXN][CHARSET], fail[MAXN];
vector<string> keywords;
int output[MAXN];

void buildGotoFunction()
{
    for (int i = 0; i < keywords.size(); i++)
    {
        int *current = &root;
        for (int j = 0; j < keywords[i].length(); j++)
        {
            int c = keywords[i][j] - 'A';
            current = &go[*current][c];
            if (*current == FAIL)
            {
                *current = ++cnt;
                memset(go[cnt], FAIL, sizeof(go[cnt]));
                output[cnt] = 0;
            }
        }
        output[*current] = 1;
    }
    for (int i = 0; i < CHARSET; i++)
        if (go[0][i] == FAIL)
            go[0][i] = 0;
}

void buildFailureFunction()
{
    queue<int> q;
    for (int i = 0; i < CHARSET; i++)
        if (go[0][i] != 0) {
            q.push(go[0][i]);
            fail[go[0][i]] = 0;
        }
    while (!q.empty())
    {
        int r = q.front(); q.pop();
        for (int i = 0; i < CHARSET; i++)
            if (go[r][i] != FAIL)
            {
                int s = go[r][i], f = fail[r];
                q.push(s);
                while (go[f][i] == FAIL) f = fail[f];
                fail[s] = go[f][i];
                output[s] |= output[fail[s]];
            }
            else go[r][i] = go[fail[r]][i];
    }
}

void initialize()
{
    root = cnt = 0;
    keywords.clear();
    memset(go[0], FAIL, sizeof(go[0]));
    memset(output, 0, sizeof(output));
}

void add(string s) { keywords.push_back(s); }

int dp[MAXN], successor[MAXN], visited[MAXN];

int dfs(int u)
{
    if (visited[u]) return -1;
    if (~dp[u]) return dp[u];
    visited[u] = 1;
    int r = 0;
    for (int c = N - 1; c >= 0; c--)
    {
        int v = go[u][c];
        if (output[v]) continue;
        int tmp = dfs(v);
        if (tmp == -1) return -1;
        if (tmp + 1 > r) r = tmp + 1, successor[u] = c;
    }
    visited[u] = 0;
    return dp[u] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string key;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        initialize();
        cin >> N >> S;
        for (int i = 0; i < S; i++) {
            cin >> key;
            add(key);
        }
        buildGotoFunction();
        buildFailureFunction();
        memset(visited, 0, sizeof(visited));
        memset(dp, -1, sizeof(dp));
        int r = dfs(0);
        if (r <= 0) cout << "No\n";
        else
        {
            int u = 0;
            for (int i = 0; i < r; i++)
            {
                cout << (char)(successor[u] + 'A');
                u = go[u][successor[u]];
            }
            cout << '\n';
        }
    }

    return 0;
}
