// Substring
// UVa ID: 11468
// Verdict: Accepted
// Submission Date: 2019-09-24
// UVa Run Time: 0.330s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 510, CHARSET = 128, FAIL = -1;

int T, K, N, L;
int cnt, root;
int go[MAXN][CHARSET], fail[MAXN];
char alpha[CHARSET];
double ps[CHARSET];
vector<string> keywords;
int output[MAXN];

void buildGotoFunction()
{
    for (int i = 0; i < keywords.size(); i++) {
        int *current = &root;
        for (auto c : keywords[i]) {
            current = &go[*current][c];
            if (*current == FAIL) {
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
    while (!q.empty()) {
        int r = q.front(); q.pop();
        for (int i = 0; i < CHARSET; i++)
            if (go[r][i] != FAIL) {
                int s = go[r][i], f = fail[r];
                q.push(s);
                while (go[f][i] == FAIL) f = fail[f];
                fail[s] = go[f][i];
                output[s] |= output[fail[s]];
            }
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

double dp[510][110];

double dfs(int current, int length)
{
    if (length == L) return 0;
    if (dp[current][length] > -1) return dp[current][length];
    double r = 0;
    for (int i = 0; i < N; i++)
    {
        char c = alpha[i];
        int next = current;
        while (go[next][c] == FAIL) next = fail[next];
        next = go[next][c];
        if (output[next]) r += ps[i];
        else r += ps[i] * dfs(next, length + 1);
    }
    return dp[current][length] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string key;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        initialize();
        cin >> K;
        for (int i = 0; i < K; i++) {
            cin >> key;
            add(key);
        }
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> alpha[i] >> ps[i];
        cin >> L;
        buildGotoFunction();
        buildFailureFunction();
        for (int i = 0; i <= cnt; i++)
            for (int j = 0; j <= L; j++)
                dp[i][j] = -1;
        cout << "Case #" << cs << ": ";
        cout << fixed << setprecision(6) << (1.0 - dfs(0, 0)) << '\n';
    }

    return 0;
}
