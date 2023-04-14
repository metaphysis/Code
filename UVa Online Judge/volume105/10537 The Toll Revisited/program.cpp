// The Toll Revisited
// UVa ID: 10537
// Verdict: Accepted
// Submission Date: 2023-04-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long get(long long p) {
    long long low = 1, high = 2 * p, r, middle;
    while (low <= high) {
        long long middle = (low + high) >> 1;
        if (middle - (middle + 19) / 20 >= p) { r = middle; high = middle - 1; }
        else low = middle + 1;
    }
    return r;
}

int main(int argc, char *argv[]) {
    int n, cases = 1;
    vector<int> g[256];
    while (cin >> n) {
        if (n == -1) break;
        cout << "Case " << cases++ << ":\n";
        for (int i = 'A'; i <= 'Z'; i++) g[i].clear();
        for (int i = 'a'; i <= 'z'; i++) g[i].clear();
        char u, v;
        for (int i = 0; i < n; i++) {
            cin >> u >> v;
            g[(int)u].push_back((int)v);
            g[(int)v].push_back((int)u);
	    }
        for (int i = 'A'; i <= 'Z'; i++) sort(g[i].begin(), g[i].end());
        for (int i = 'a'; i <= 'z'; i++) sort(g[i].begin(), g[i].end());
        long long p;
        cin >> p >> u >> v;
        if (u == v) {
            cout << p << '\n';
            cout << u << '\n';
            continue;
        }
        int s = (int)u, e = (int)v;
        long long d[256];
        memset(d, 0x3f, sizeof d);
        int nxt[256];
        queue<pair<int, long long>> q;
        if ('A' <= v && v <= 'Z') d[e] = get(p);
        else d[e] = p + 1;
        q.push(make_pair(e, d[e]));
        nxt[e] = e;
        while (!q.empty()) {
            pair<int, long long> pr = q.front(); q.pop();
            for (auto v : g[pr.first]) {
                if (v == s) {
                    if (d[s] > pr.second) {
                        d[s] = pr.second;
                        nxt[s] = pr.first;
                    } else if (d[s] == pr.second) {
                        if (pr.first < nxt[s]) nxt[s] = pr.first;
                    }
                } else {
                    if ('A' <= v && v <= 'Z') {
                        long long pp = get(pr.second);
                        if (d[v] > pp) {
                            d[v] = pp;
                            nxt[v] = pr.first;
                            q.push(make_pair(v, d[v]));
                        } else if (d[v] == pp) {
                            if (pr.first < nxt[v]) nxt[v] = pr.first;
                        }
                    } else {
                        if (d[v] > pr.second + 1) {
                            d[v] = pr.second + 1;
                            nxt[v] = pr.first;
                            q.push(make_pair(v, d[v]));
                        } else if (d[v] == pr.second + 1) {
                            if (pr.first < nxt[v]) nxt[v] = pr.first;
                        }
                    }
                }
            }
        }
        cout << d[s] << '\n';
        cout << u;
        while (s != nxt[s]) {
            cout << '-';
            cout << (char)nxt[s];
            s = nxt[s];
        }
        cout << '\n';
    }
    return 0;
}
