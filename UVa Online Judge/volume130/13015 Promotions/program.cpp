// Promotions
// UVa ID: 13015
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5100;

int in[MAXN], visited[MAXN];
vector<int> g[MAXN];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int A, B, E, P;
    while (cin >> A >> B >> E >> P) {
        for (int i = 0; i < E; i++) {
            g[i].clear();
            in[i] = visited[i] = 0;
        }
        for (int i = 0, u, v; i < P; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            in[v]++;
        }
        int cnt = 0, r1 = 0, r2 = 0, r3 = 0;
        queue<int> q;
        while (true) {
            for (int i = 0; i < E; i++)
                if (!visited[i] && !in[i]) {
                    cnt++;
                    q.push(i);
                    visited[i] = 1;
                }
            if (q.empty()) break;
            if (cnt <= A) r1 = cnt;
            if (cnt <= B) r2 = cnt;
            r3 = E - cnt;
            if (cnt >= B) break;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto v : g[u])
                    in[v]--;
            }
        }
        cout << r1 << '\n' << r2 << '\n' << r3 << '\n';
    }
    return 0;
}
