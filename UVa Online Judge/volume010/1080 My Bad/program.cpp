// My Bad
// UVa ID: 1080
// Verdict: Accepted
// Submission Date: 2026-03-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Gate { char type; vector<string> ins; };

int N, G, U;
vector<Gate> gates;
vector<int> outs;
vector<vector<int>> inObs, outObs;

int getVal(const string& s, const vector<int>& inV, const vector<int>& gateV) {
    return s[0] == 'i' ? inV[stoi(s.substr(1)) - 1] : gateV[stoi(s.substr(1)) - 1];
}

vector<int> topoOrder() {
    vector<int> deg(G, 0);
    vector<vector<int>> adj(G);
    for (int i = 0; i < G; ++i)
        for (const string& in : gates[i].ins)
            if (in[0] == 'g') {
                int from = stoi(in.substr(1)) - 1;
                adj[from].push_back(i);
                deg[i]++;
            }
    queue<int> q;
    for (int i = 0; i < G; ++i) if (deg[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--deg[v] == 0) q.push(v);
    }
    return order;
}

vector<int> compute(const vector<int>& inV, int fgate = -1, int ftype = -1) {
    vector<int> gateV(G, 0);
    vector<int> order = topoOrder();
    for (int idx : order) {
        Gate& g = gates[idx];
        int normal;
        if (g.type == 'n') normal = !getVal(g.ins[0], inV, gateV);
        else {
            int v1 = getVal(g.ins[0], inV, gateV), v2 = getVal(g.ins[1], inV, gateV);
            if (g.type == 'a') normal = v1 & v2;
            else if (g.type == 'o') normal = v1 | v2;
            else normal = v1 ^ v2;
        }
        if (idx == fgate) {
            if (ftype == 0) gateV[idx] = !normal;
            else if (ftype == 1) gateV[idx] = 0;
            else gateV[idx] = 1;
        } else gateV[idx] = normal;
    }
    vector<int> res(U);
    for (int i = 0; i < U; ++i) res[i] = gateV[outs[i] - 1];
    return res;
}

int main() {
    int caseNo = 1;
    while (cin >> N >> G >> U, N || G || U) {
        gates.resize(G);
        for (int i = 0; i < G; ++i) {
            cin >> gates[i].type;
            int cnt = gates[i].type == 'n' ? 1 : 2;
            gates[i].ins.resize(cnt);
            for (int j = 0; j < cnt; ++j) cin >> gates[i].ins[j];
        }
        outs.resize(U);
        for (int i = 0; i < U; ++i) cin >> outs[i];
        int B; cin >> B;
        inObs.assign(B, vector<int>(N));
        outObs.assign(B, vector<int>(U));
        for (int i = 0; i < B; ++i) {
            for (int j = 0; j < N; ++j) cin >> inObs[i][j];
            for (int j = 0; j < U; ++j) cin >> outObs[i][j];
        }
        
        bool ok = true;
        for (int i = 0; i < B && ok; ++i) if (compute(inObs[i]) != outObs[i]) ok = false;
        if (ok) { cout << "Case " << caseNo++ << ": No faults detected\n"; continue; }
        
        vector<pair<int, int>> cand;
        for (int g = 0; g < G; ++g) for (int t = 0; t < 3; ++t) {
            bool match = true;
            for (int i = 0; i < B && match; ++i)
                if (compute(inObs[i], g, t) != outObs[i]) match = false;
            if (match) cand.emplace_back(g, t);
        }
        
        if (cand.size() == 1) {
            auto [g, t] = cand[0];
            cout << "Case " << caseNo++ << ": Gate " << g + 1 << " is failing; output ";
            if (t == 0) cout << "inverted\n";
            else if (t == 1) cout << "stuck at 0\n";
            else cout << "stuck at 1\n";
        } else cout << "Case " << caseNo++ << ": Unable to totally classify the failure\n";
    }
    return 0;
}
