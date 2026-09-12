#include <bits/stdc++.h>
using namespace std;

const int maxN = 50005;
int fa[maxN], sz[maxN], edgeCnt[maxN], vertexCnt[maxN];
int edgeU[maxN], edgeV[maxN];
long long val[maxN];

int findRoot(int x) {
    if (fa[x] == x) return x;
    return fa[x] = findRoot(fa[x]);
}

void mergeSet(int x, int y) {
    x = findRoot(x), y = findRoot(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    fa[y] = x;
    sz[x] += sz[y];
}

bool lessPair(int a, int b, int c, int d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    if (a != c) return a < c;
    return b < d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt, n, i, a, b;
    cin >> testCnt;
    while (testCnt--) {
        cin >> n;
        for (i = 1; i <= n; ++i) {
            fa[i] = i;
            sz[i] = 1;
            edgeCnt[i] = 0;
            vertexCnt[i] = 0;
        }
        for (i = 1; i < n; ++i) {
            cin >> a >> b;
            edgeU[i] = a;
            edgeV[i] = b;
            mergeSet(a, b);
        }
        for (i = 1; i <= n; ++i) cin >> val[i];
        for (i = 1; i <= n; ++i) {
            a = findRoot(i);
            ++vertexCnt[a];
        }
        for (i = 1; i < n; ++i) {
            a = findRoot(edgeU[i]);
            ++edgeCnt[a];
        }
        int treeRoot = -1, treeCnt = 0;
        bool possible = true;
        for (i = 1; i <= n; ++i) {
            if (findRoot(i) != i) continue;
            if (edgeCnt[i] == vertexCnt[i] - 1) {
                treeRoot = i;
                ++treeCnt;
            } else if (edgeCnt[i] != vertexCnt[i]) {
                possible = false;
            }
        }
        if (!possible || treeCnt != 1) {
            cout << "impossible\n";
            continue;
        }
        int maxId1 = -1, maxId2 = -1, outsideId = -1;
        for (i = 1; i <= n; ++i) {
            if (findRoot(i) == treeRoot) {
                if (maxId1 == -1 || val[i] > val[maxId1] || (val[i] == val[maxId1] && i < maxId1)) {
                    maxId2 = maxId1;
                    maxId1 = i;
                } else if (maxId2 == -1 || val[i] > val[maxId2] || (val[i] == val[maxId2] && i < maxId2)) {
                    maxId2 = i;
                }
            } else if (outsideId == -1) {
                outsideId = i;
            }
        }
        if (outsideId == -1) {
            cout << min(maxId1, maxId2) << ' ' << max(maxId1, maxId2) << '\n';
            continue;
        }
        int ansA = min(maxId1, outsideId), ansB = max(maxId1, outsideId);
        if (maxId2 != -1 && val[maxId2] == val[maxId1] && lessPair(maxId1, maxId2, ansA, ansB)) {
            ansA = min(maxId1, maxId2);
            ansB = max(maxId1, maxId2);
        }
        cout << ansA << ' ' << ansB << '\n';
    }
    return 0;
}
