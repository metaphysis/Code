// Unique World
// UVa ID: 10448
// Verdict: Accepted
// Submission Date: 2022-12-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 64;
int N, n, m;
vector<int> g[MAXN];
int father[64], weight[64][64], visited[64];
int dp[100010];
int main(int argc, char *argv[])
{
	cin >> N;
	while (N--)	{
	    cin >> n >> m;
	    for (int i = 1; i <= n; i++)
	        g[i].clear();
	    for (int i = 0, id1, id2, c; i < m; i++) {
	        cin >> id1 >> id2 >> c;
	        g[id1].push_back(id2);
	        g[id2].push_back(id1);
	        weight[id1][id2] = weight[id2][id1] = c;
	    }
	    int k;
	    cin >> k;
	    for (int i = 0, s, e, c; i < k; i++) {
	        cin >> s >> e >> c;
	        if (s == e) { cout << "No\n"; continue; }
	        memset(father, 0, sizeof father);
	        memset(visited, 0, sizeof visited);
	        queue<int> q;
	        q.push(s);
	        while (!q.empty()) {
	            int u = q.front(); q.pop();
	            for (int v : g[u])
	                if (!visited[v]) {
	                    visited[v] = 1;
	                    father[v] = u;
	                    q.push(v);
	                }
	        }
	        if (!visited[e]) { cout << "No\n"; continue; }
	        int f = father[e];
	        if (f == s) {
	            if (weight[s][e] != c) cout << "No\n";
	            else cout << "Yes 1\n";
	        } else {
	            int answer = 1;
	            c -= weight[f][e];
	            vector<int> w;
	            while (f != s) {
	                w.push_back(weight[f][father[f]]);
	                c -= weight[f][father[f]];
	                f = father[f];
	                answer += 1;
	            }
	            if (c < 0 || c % 2) cout << "No\n";
	            else {
	                c /= 2;
	                memset(dp, 0x3f, sizeof dp);
	                dp[0] = 0;
	                for (int i = 0; i < w.size(); i++)
	                    for (int j = 0; j + w[i] <= c; j++)
	                        dp[j + w[i]] = min(dp[j + w[i]], dp[j] + 2);
	                if (dp[c] != 0x3f3f3f3f) cout << "Yes " << dp[c] + answer << '\n';
	                else cout << "No\n";
	            }
	        }
	    }
	    if (N) cout << '\n';
	}
	return 0;
}
