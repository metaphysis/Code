#include <bits/stdc++.h>
using namespace std;

const int maxN = 200100;

int n, q, width;
long long ans[maxN];
int posState[maxN];
vector<pair<int, int>> queries[maxN];
vector<int> graph[maxN];
char text[maxN];

struct SuffixAutomaton {
    int last, total, link[maxN], nextState[maxN][26], length[maxN];
    void init() {
        for (int i = 1; i <= total; ++i) {
            link[i] = length[i] = 0;
            memset(nextState[i], 0, sizeof(nextState[i]));
        }
        last = total = 1;
    }
    void extend(int c) {
        int cur = ++total, p = last;
        length[cur] = length[p] + 1;
        last = cur;
        for (; p && !nextState[p][c]; p = link[p]) nextState[p][c] = cur;
        if (!p) {
            link[cur] = 1;
            return;
        }
        int q = nextState[p][c];
        if (length[q] == length[p] + 1) {
            link[cur] = q;
            return;
        }
        int clone = ++total;
        link[clone] = link[q];
        length[clone] = length[p] + 1;
        memcpy(nextState[clone], nextState[q], sizeof(nextState[clone]));
        link[cur] = link[q] = clone;
        for (; p && nextState[p][c] == q; p = link[p]) nextState[p][c] = clone;
    }
} sam;

namespace Fenwick {
    long long bitA[maxN], bitB[maxN];
    void init() {
        for (int i = 1; i <= n; ++i) bitA[i] = bitB[i] = 0;
    }
    void add(int x, long long value) {
        for (int i = x; i <= n; i += i & -i) {
            bitA[i] += value;
            bitB[i] += x * value;
        }
    }
    void add(int left, int right, long long value) {
        add(left, value);
        add(right + 1, -value);
    }
    long long sum(int x) {
        long long result = 0;
        for (int i = x; i; i -= i & -i) result += bitA[i] * (x + 1) - bitB[i];
        return result;
    }
    long long sum(int left, int right) {
        return sum(right) - sum(left - 1);
    }
}

int parentState[maxN], sizeState[maxN], depthState[maxN], heavySon[maxN];
int topState[maxN], dfn[maxN], rankState[maxN], timer;

int buildTree(int u, int parent, int depth) {
    parentState[u] = parent;
    sizeState[u] = 1;
    depthState[u] = depth;
    int maxSize = -1;
    for (int v : graph[u]) {
        if (v == parent) continue;
        sizeState[u] += buildTree(v, u, depth + 1);
        if (sizeState[v] > maxSize) {
            heavySon[u] = v;
            maxSize = sizeState[v];
        }
    }
    return sizeState[u];
}

void decompose(int u, int top) {
    topState[u] = top;
    dfn[u] = ++timer;
    rankState[timer] = u;
    if (!heavySon[u]) return;
    decompose(heavySon[u], top);
    for (int v : graph[u]) if (!dfn[v]) decompose(v, v);
}

struct Segment {
    int left, right, pos;
    Segment(int left = 0, int right = 0, int pos = 0) : left(left), right(right), pos(pos) {}
};

vector<Segment> segments[maxN];

void update(int u, int pos) {
    Fenwick::add(1, pos, 1);
    while (u) {
        while (!segments[topState[u]].empty()) {
            Segment segment = segments[topState[u]].back();
            segments[topState[u]].pop_back();
            if (segment.right <= dfn[u]) {
                int left = sam.length[sam.link[rankState[segment.left]]] + 1;
                int right = sam.length[rankState[segment.right]];
                Fenwick::add(segment.pos - right + 1, segment.pos - left + 1, -1);
                if (segment.right == dfn[u]) break;
            } else {
                int left = sam.length[sam.link[rankState[segment.left]]] + 1;
                int right = sam.length[u];
                Fenwick::add(segment.pos - right + 1, segment.pos - left + 1, -1);
                segments[topState[u]].emplace_back(dfn[u] + 1, segment.right, segment.pos);
                break;
            }
        }
        segments[topState[u]].emplace_back(dfn[topState[u]], dfn[u], pos);
        u = parentState[topState[u]];
    }
}

void solve() {
    timer = 0;
    n = strlen(text + 1);
    sam.init();
    for (int i = 1; i <= n; ++i) {
        sam.extend(text[i] - 'a');
        posState[i] = sam.last;
    }
    for (int i = 1, left; i <= q; ++i) {
        scanf("%d", &left);
        queries[left + width - 1].emplace_back(left, i);
    }
    for (int i = 2; i <= sam.total; ++i) graph[sam.link[i]].emplace_back(i);
    buildTree(1, 0, 1);
    decompose(1, 1);
    Fenwick::init();
    for (int i = 1; i <= n; ++i) {
        update(posState[i], i);
        for (pair<int, int> query : queries[i]) ans[query.second] = Fenwick::sum(query.first, i);
        vector<pair<int, int>>().swap(queries[i]);
    }
    for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
    for (int i = 1; i <= sam.total; ++i) {
        parentState[i] = sizeState[i] = heavySon[i] = depthState[i] = dfn[i] = topState[i] = 0;
        vector<int>().swap(graph[i]);
        vector<Segment>().swap(segments[i]);
    }
}

int main() {
    while (scanf("%s%d%d", text + 1, &q, &width) == 3) solve();
    return 0;
}
