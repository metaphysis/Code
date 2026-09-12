#include <bits/stdc++.h>
using namespace std;

const int base = 1000000000;

int n, m, dfsTime, tag;
vector<int> head, to, nxt, eid, dfn, low, deg, seen, edgeStack;
vector<pair<int, int>> edges;
vector<int> bigNum;
bool bad;

void addEdge(int a, int b) {
    int id = (int)edges.size();
    edges.push_back(make_pair(a, b));
    to.push_back(b);
    eid.push_back(id);
    nxt.push_back(head[a]);
    head[a] = (int)to.size() - 1;
    to.push_back(a);
    eid.push_back(id);
    nxt.push_back(head[b]);
    head[b] = (int)to.size() - 1;
}

void mulBig(vector<int> &num, int x) {
    long long carry = 0;
    for (int i = 0; i < (int)num.size(); ++i) {
        long long cur = 1LL * num[i] * x + carry;
        num[i] = (int)(cur % base);
        carry = cur / base;
    }
    while (carry) {
        num.push_back((int)(carry % base));
        carry /= base;
    }
}

string bigToString(const vector<int> &num) {
    stringstream ss;
    ss << num.back();
    for (int i = (int)num.size() - 2; i >= 0; --i)
        ss << setw(9) << setfill('0') << num[i];
    return ss.str();
}

void dfs(int u, int pe) {
    dfn[u] = low[u] = ++dfsTime;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i], id = eid[i];
        if (id == pe) continue;
        if (!dfn[v]) {
            edgeStack.push_back(id);
            dfs(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                int edgeCnt = 0, verCnt = 0;
                ++tag;
                while (true) {
                    int curId = edgeStack.back();
                    edgeStack.pop_back();
                    ++edgeCnt;
                    int a = edges[curId].first, b = edges[curId].second;
                    if (seen[a] != tag) {
                        seen[a] = tag;
                        ++verCnt;
                    }
                    if (seen[b] != tag) {
                        seen[b] = tag;
                        ++verCnt;
                    }
                    if (curId == id) break;
                }
                if (edgeCnt == 1) {
                    if (edges[id].first == edges[id].second) bad = true;
                } else if (edgeCnt == verCnt) {
                    mulBig(bigNum, edgeCnt + 1);
                } else {
                    bad = true;
                }
            }
        } else if (dfn[v] < dfn[u]) {
            edgeStack.push_back(id);
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> n >> m) {
        head.assign(n + 1, -1);
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        deg.assign(n + 1, 0);
        seen.assign(n + 1, 0);
        edges.clear();
        to.clear();
        nxt.clear();
        eid.clear();
        edgeStack.clear();
        bigNum.clear();
        bigNum.push_back(1);
        dfsTime = 0;
        tag = 0;
        bad = false;
        for (int i = 0; i < m; ++i) {
            int k, a, b;
            cin >> k >> a;
            for (int j = 1; j < k; ++j) {
                cin >> b;
                if (a == b) bad = true;
                addEdge(a, b);
                ++deg[a];
                ++deg[b];
                a = b;
            }
        }
        int start = 1;
        for (int i = 1; i <= n; ++i) {
            if (deg[i] > 0) {
                start = i;
                break;
            }
        }
        dfs(start, -1);
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) bad = true;
        }
        if (!edgeStack.empty()) bad = true;
        if (!firstCase) cout << '\n';
        firstCase = false;
        if (bad) cout << 0 << '\n';
        else cout << bigToString(bigNum) << '\n';
    }
    return 0;
}
