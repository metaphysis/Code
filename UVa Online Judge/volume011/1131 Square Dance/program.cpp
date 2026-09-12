#include <bits/stdc++.h>
using namespace std;

class Dsu {
private:
    vector<int> parent, size;
public:
    Dsu(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int findRoot(int x) {
        if (parent[x] != x) parent[x] = findRoot(parent[x]);
        return parent[x];
    }
    bool mergeSet(int x, int y) {
        int rx = findRoot(x), ry = findRoot(y);
        if (rx == ry) return false;
        if (size[rx] < size[ry]) swap(rx, ry);
        parent[ry] = rx;
        size[rx] += size[ry];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p, r, caseNum = 0, x, y, ans;
    while (cin >> p >> r) {
        Dsu dsu(p);
        ans = 0;
        for (int i = 0; i < r; i++) {
            cin >> x >> y;
            if (!dsu.mergeSet(x, y)) ans++;
        }
        if (caseNum++) cout << '\n';
        cout << ans << '\n';
    }
    return 0;
}
