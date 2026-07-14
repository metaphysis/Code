// Sentence Generator
// UVa ID: 780
// Verdict: Accepted
// Submission Date: 2026-07-11
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using BigInt = __int128;

enum NodeType { LEAF, OR, AND };

struct Node {
    NodeType type;
    char leafChar;
    vector<int> succ;
    vector<BigInt> suffixProd;
    vector<BigInt> prefixSum;
};

vector<Node> nodes;
vector<BigInt> len;

BigInt getLength(int u) {
    if (len[u] != -1) return len[u];
    if (nodes[u].type == LEAF) return len[u] = 1;
    BigInt res = 0;
    if (nodes[u].type == OR) {
        for (int v : nodes[u].succ) res += getLength(v);
    } else {
        res = 1;
        for (int v : nodes[u].succ) res *= getLength(v);
    }
    return len[u] = res;
}

void preprocess(int u) {
    if (nodes[u].type == OR) {
        vector<BigInt>& ps = nodes[u].prefixSum;
        ps.clear();
        BigInt acc = 0;
        for (int v : nodes[u].succ) {
            acc += getLength(v);
            ps.push_back(acc);
        }
    } else if (nodes[u].type == AND) {
        vector<BigInt>& sp = nodes[u].suffixProd;
        int m = (int)nodes[u].succ.size();
        sp.resize(m);
        BigInt prod = 1;
        for (int i = m - 1; i >= 0; --i) {
            sp[i] = prod;
            prod *= getLength(nodes[u].succ[i]);
        }
    }
    for (int v : nodes[u].succ) preprocess(v);
}

string generate(int u, BigInt idx) {
    if (nodes[u].type == LEAF) return string(1, nodes[u].leafChar);
    if (nodes[u].type == OR) {
        const vector<BigInt>& ps = nodes[u].prefixSum;
        for (int i = 0; i < (int)ps.size(); ++i) {
            if (idx < ps[i]) {
                BigInt offset = (i == 0 ? idx : idx - ps[i - 1]);
                return generate(nodes[u].succ[i], offset);
            }
        }
    } else {
        string res;
        BigInt cur = idx;
        const vector<BigInt>& sp = nodes[u].suffixProd;
        for (int i = 0; i < (int)nodes[u].succ.size(); ++i) {
            BigInt idx_i = cur / sp[i];
            cur %= sp[i];
            res += generate(nodes[u].succ[i], idx_i);
        }
        return res;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        nodes.assign(n, Node());
        len.assign(n, -1);

        for (int i = 0; i < n; ++i) {
            int id;
            string mark;
            cin >> id >> mark;
            if (mark == "*" || mark == "|") {
                int numSucc;
                cin >> numSucc;
                nodes[id].succ.resize(numSucc);
                for (int j = 0; j < numSucc; ++j) cin >> nodes[id].succ[j];
                nodes[id].type = (mark == "*" ? AND : OR);
                nodes[id].leafChar = 0;
            } else {
                nodes[id].type = LEAF;
                nodes[id].leafChar = mark[0];
                nodes[id].succ.clear();
            }
        }

        for (int i = 0; i < n; ++i) getLength(i);
        preprocess(0);

        BigInt cur = 0;
        BigInt total = len[0];

        int k;
        while (cin >> k) {
            cout << k << "\n";
            if (k == 0) break;
            int cnt = abs(k);
            if (k > 0) {
                for (int i = 0; i < cnt; ++i) {
                    cout << generate(0, cur) << "\n";
                    BigInt nxt = cur + 1;
                    cur = (nxt == total ? 0 : nxt);
                }
            } else {
                for (int i = 0; i < cnt; ++i) {
                    BigInt nxt = cur + 1;
                    cur = (nxt == total ? 0 : nxt);
                }
            }
        }
    }
    return 0;
}
