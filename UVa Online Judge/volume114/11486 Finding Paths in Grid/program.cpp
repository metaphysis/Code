// Finding Paths in Grid
// UVa ID: 11486
// Verdict: Accepted
// Submission Date: 2018-04-23
// UVa Run Time: 0.120s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 40;

int n;
map<int, set<int>> edges;
long long mod = 1000000007;

struct matrix { long long cell[MAXN][MAXN]; }one;

matrix multiply(const matrix &a, const matrix &b)
{
    matrix r;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            r.cell[i][j] = 0;
            for (int k = 0; k < n; k++)
                r.cell[i][j] += (a.cell[i][k] * b.cell[k][j]) % mod;
            r.cell[i][j] %= mod;
        }
    return r;
}

map<int, matrix> memo;

matrix matrixPow(int k)
{
    if (memo.find(k) != memo.end()) return memo[k];
    if (k == 1) return one;
    matrix r = matrixPow(k >> 1);
    r = multiply(r, r);
    if (k & 1) r = multiply(r, one);
    if (memo.find(k) == memo.end()) memo[k] = r;
    return r;
}

int hasEdge(int i, int j)
{
    return edges[i].find(j) != edges[i].end() ? 1 : 0;
}

void dfs(int i, int j, int depth)
{
    if (depth == 7)
    {
        edges[i].insert(j);
        return;
    }
    
    if (i & (1 << depth))
    {
        if (depth)
        {
            if (!(j & (1 << (depth - 1))))
                dfs(i, j | (1 << (depth - 1)), depth + 1);
        }
        
        if (depth < 6)
        {
            if (!(j & (1 << (depth + 1))))
                dfs(i, j | (1 << (depth + 1)), depth + 1);
        }
    }
    else
        dfs(i, j, depth + 1);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> vertices;
    for (int i = 0; i < 128; i++)
        if (__builtin_popcount(i) == 4)
        {
            dfs(i, 0, 0);
            vertices.push_back(i);
        }
    n = vertices.size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            one.cell[i][j] = hasEdge(vertices[i], vertices[j]);
    
    int cases, N, player;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N;
        int v = 0;
        for (int i = 0; i < 7; i++)
        {
            cin >> player;
            if (player) v |= (1 << (6 - i));
        }
        if (N == 1)
        {
            cout << 1 << '\n';
            continue;
        }

        int row = find(vertices.begin(), vertices.end(), v) - vertices.begin();
        matrix mr = one;
        if (N > 1)
            mr = matrixPow(N - 1);

        long long paths = 0;
        for (int j = 0; j < n; j++)
        {
            paths += (mr.cell[row][j] % mod);
            paths %= mod;
        }
        cout << paths << '\n';
    }

    return 0;
}
