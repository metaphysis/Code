// Password Suspects
// UVa ID: 1076
// Verdict: Accepted
// Submission Date: 2019-09-27
// UVa Run Time: 0.370s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 128, CHARSET = 26;

int N, M;
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
            int c = keywords[i][j] - 'a';
            current = &go[*current][c];
            if (!*current)
            {
                *current = ++cnt;
                memset(go[cnt], 0, sizeof(go[cnt]));
                output[cnt] = 0;
            }
        }
        output[*current] |= (1 << i);
    }
}

void buildFailureFunction()
{
    queue<int> q;
    for (int i = 0; i < CHARSET; i++)
        if (go[0][i]) {
            q.push(go[0][i]);
            fail[go[0][i]] = 0;
        }
    while (!q.empty())
    {
        int r = q.front(); q.pop();
        for (int i = 0; i < CHARSET; i++)
            if (go[r][i])
            {
                int s = go[r][i], f = fail[r];
                q.push(s);
                while (f && !go[f][i]) f = fail[f];
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
    memset(go[0], 0, sizeof(go[0]));
    memset(output, 0, sizeof(output));
}

void add(string s) { keywords.push_back(s); }

long long dp[32][128][(1 << 11)];

long long dfs(int L, int u, int mask)
{
    if (L == N) return dp[L][u][mask] = (mask == ((1 << M) - 1));
    if (~dp[L][u][mask]) return dp[L][u][mask];
    long long r = 0;
    for (int c = 0; c < CHARSET; c++)
    {
        int v = go[u][c];
        r += dfs(L + 1, v, mask | output[v]);
    }
    return dp[L][u][mask] = r;
}

int password[32];

void backtrack(int L, int u, int mask)
{
    if (L == N)
    {
        for (int i = 0; i < N; i++)
            cout << (char)('a' + password[i]);
        cout << '\n';
        return;
    }
    for (int c = 0; c < CHARSET; c++)
    {
        int v = go[u][c];
        if (dp[L + 1][v][mask | output[v]] > 0)
        {
            password[L] = c;
            backtrack(L + 1, v, mask | output[v]);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string key;
    while (cin >> N >> M)
    {
        if (N == 0) break;

        initialize();
        for (int i = 0; i < M; i++) {
            cin >> key;
            add(key);
        }
        buildGotoFunction();
        buildFailureFunction();

        memset(dp, -1, sizeof(dp));
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= cnt; j++)
                for (int k = 0; k < (1 << M); k++)
                    dp[i][j][k] = -1LL;

        long long r = dfs(0, 0, 0);
        cout << "Case " << ++cases << ": " << r << " suspects\n";
        if (r <= 42LL) backtrack(0, 0, 0);
    }

    return 0;
}
