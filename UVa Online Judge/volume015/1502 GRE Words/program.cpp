#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 300005;
const int MAXN = 20005;

struct Node { int ch[26], fail; } node[MAXNODE];
vector<int> failTree[MAXNODE];
int n, nodeCnt, dfn, sz;
int in[MAXNODE], out[MAXNODE], lazy[4 * MAXNODE + 5];
int endNode[MAXN], w[MAXN], dp[MAXN];
string words[MAXN];

void insertWord(const string &s, int id) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (!node[u].ch[v]) {
            node[u].ch[v] = ++nodeCnt;
            memset(node[nodeCnt].ch, 0, sizeof(node[nodeCnt].ch));
            node[nodeCnt].fail = 0;
        }
        u = node[u].ch[v];
    }
    endNode[id] = u;
}

void buildAC() {
    queue<int> q;
    for (int c = 0; c < 26; ++c) {
        if (node[0].ch[c]) {
            int u = node[0].ch[c];
            node[u].fail = 0;
            q.push(u);
        } else {
            node[0].ch[c] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int c = 0; c < 26; ++c) {
            int &v = node[u].ch[c];
            if (v) {
                node[v].fail = node[node[u].fail].ch[c];
                q.push(v);
            } else {
                v = node[node[u].fail].ch[c];
            }
        }
    }
}

void dfsFailTree() {
    vector<pair<int,int>> st;
    st.reserve(nodeCnt + 1);
    st.push_back({0, 0});
    dfn = 0;
    while (!st.empty()) {
        int u = st.back().first;
        if (st.back().second == 0) in[u] = ++dfn;
        if (st.back().second < (int)failTree[u].size()) {
            int v = failTree[u][st.back().second++];
            st.push_back({v, 0});
        } else {
            out[u] = dfn;
            st.pop_back();
        }
    }
}

void update(int ql, int qr, int val, int p, int l, int r) {
    if (ql <= l && r <= qr) { if (val > lazy[p]) lazy[p] = val; return; }
    int mid = (l + r) >> 1;
    if (ql <= mid) update(ql, qr, val, p << 1, l, mid);
    if (qr > mid) update(ql, qr, val, p << 1 | 1, mid + 1, r);
}

int query(int pos, int p, int l, int r) {
    int res = lazy[p];
    if (l == r) return res;
    int mid = (l + r) >> 1;
    if (pos <= mid) res = max(res, query(pos, p << 1, l, mid));
    else res = max(res, query(pos, p << 1 | 1, mid + 1, r));
    return res;
}

int solve() {
    scanf("%d", &n);
    nodeCnt = 0;
    memset(node[0].ch, 0, sizeof(node[0].ch));
    node[0].fail = 0;
    for (int i = 1; i <= n; ++i) {
        char buf[300005]; int wi;
        scanf("%s%d", buf, &wi);
        words[i] = buf;
        w[i] = wi;
        insertWord(words[i], i);
    }
    buildAC();
    for (int i = 0; i <= nodeCnt; ++i) failTree[i].clear();
    for (int i = 1; i <= nodeCnt; ++i) failTree[node[i].fail].push_back(i);
    dfsFailTree();
    sz = nodeCnt + 1;
    fill(lazy, lazy + 4 * sz + 5, 0);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int maxVal = 0;
        int u = 0;
        for (char c : words[i]) {
            u = node[u].ch[c - 'a'];
            int cur = query(in[u], 1, 1, sz);
            if (cur > maxVal) maxVal = cur;
        }
        dp[i] = w[i] + maxVal;
        update(in[endNode[i]], out[endNode[i]], dp[i], 1, 1, sz);
        if (dp[i] > ans) ans = dp[i];
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int kase = 1; kase <= t; ++kase) {
        printf("Case #%d: %d\n", kase, solve());
    }
    return 0;
}
