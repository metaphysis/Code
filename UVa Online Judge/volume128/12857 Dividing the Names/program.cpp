#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[26], cnt;
    Node() {
        memset(ch, -1, sizeof(ch));
        cnt = 0;
    }
};

int n;
vector<Node> trie;

int addNode() {
    trie.push_back(Node());
    return (int)trie.size() - 1;
}

void insertName(const string &s) {
    int u = 0, id, v;
    trie[u].cnt++;
    for (char c : s) {
        id = c - 'A';
        if (trie[u].ch[id] == -1) {
            v = addNode();
            trie[u].ch[id] = v;
        }
        u = trie[u].ch[id];
        trie[u].cnt++;
    }
}

vector<long long> solveDfs(int u, bool isRoot) {
    bool isLeaf = true;
    int c;
    for (c = 0; c < 26; c++)
        if (trie[u].ch[c] != -1) isLeaf = false;
    if (isLeaf) return vector<long long>(2, 0);
    vector<long long> dp(1, 0);
    for (c = 0; c < 26; c++) {
        if (trie[u].ch[c] == -1) continue;
        int v = trie[u].ch[c], lim;
        vector<long long> cur = solveDfs(v, false);
        lim = min(n, (int)dp.size() + (int)cur.size() - 2);
        vector<long long> ndp(lim + 1, (long long)4e18);
        for (int i = 0; i < (int)dp.size(); i++) {
            for (int j = 0; j < (int)cur.size() && i + j <= n; j++)
                ndp[i + j] = min(ndp[i + j], dp[i] + cur[j]);
        }
        dp = ndp;
    }
    if (!isRoot) {
        for (int k = 0; k < (int)dp.size(); k++) {
            int a = k, b = trie[u].cnt - k;
            if (a >= 2) dp[k] += a;
            if (b >= 2) dp[k] += b;
        }
    }
    return dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        string s;
        trie.clear();
        trie.push_back(Node());
        for (int i = 0; i < 2 * n; i++) {
            cin >> s;
            insertName(s);
        }
        vector<long long> dp = solveDfs(0, true);
        cout << 1LL * n * (2LL * n + dp[n]) << '\n';
    }
    return 0;
}
