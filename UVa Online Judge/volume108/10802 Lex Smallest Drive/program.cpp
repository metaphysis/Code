// Lex Smallest Drive
// UVa ID: 10802
// Verdict: Accepted
// Submission Date: 2018-08-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, s;
int g[110][110], walk[256], sink, moves;

bool dfs(int previous, int u){
	if (u == sink)	return true;
	if (moves >= 200)	return false;
	for (int v = 0; v < n; v++)
	{
		if (v == previous || !g[u][v])	continue;
		walk[moves++] = v;
		if (dfs(u, v)) return true;
		if (moves >= 200) return false;
		moves--;
	}
	return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m >> s;
        memset(g, 0, sizeof(g));
        for (int u, v, i = 0; i < m; i++)
        {
            cin >> u >> v;
            g[u][v] = g[v][u] = 1;
        }

        cout << "Case #" << cs << ":\n";
        for (int i = 0; i < n; i++)
        {
			moves = 0;
			walk[moves++] = s;
			sink = i;
			if (dfs(-1, s)){
				cout << s;
				for (int j = 1; j < moves; j++)
					cout << ' ' << walk[j];
				cout << '\n';
			}
			else
				cout << "No drive.\n";
        }
        cout << '\n';
    }

    return 0;
}
