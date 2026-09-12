#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> par, siz;
    Dsu(int n) {
        par.resize(n);
        siz.assign(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
        return true;
    }
};

struct Needle {
    int a, b, c, d, e, f;
};

int getId(unordered_map<int, int> &mp, int key) {
    auto it = mp.find(key);
    if (it != mp.end()) return it->second;
    int id = mp.size();
    mp[key] = id;
    return id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    while (cin >> k) {
        vector<Needle> needles(k);
        unordered_map<int, int> pointMap, floorMap;
        int i, x1, y1, z1, x2, y2, z2;
        for (i = 0; i < k; i++) {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            int p1 = (x1 * 1000 + y1) * 1000 + z1, p2 = (x2 * 1000 + y2) * 1000 + z2;
            int q1 = x1 * 1000 + y1, q2 = x2 * 1000 + y2;
            needles[i].a = getId(pointMap, p1);
            needles[i].b = getId(pointMap, p2);
            needles[i].c = getId(floorMap, q1);
            needles[i].d = getId(floorMap, q2);
        }
        Dsu trueDsu(pointMap.size()), floorDsu(floorMap.size());
        unordered_set<long long> seen;
        bool trueAns = false, floorAns = false;
        for (i = 0; i < k; i++) {
            if (!trueDsu.unite(needles[i].a, needles[i].b)) trueAns = true;
            if (needles[i].c == needles[i].d) continue;
            int u = min(needles[i].c, needles[i].d), v = max(needles[i].c, needles[i].d);
            long long key = 1LL * u * 1000000 + v;
            if (!seen.insert(key).second) continue;
            if (!floorDsu.unite(u, v)) floorAns = true;
        }
        if (trueAns) cout << "True closed chains\n";
        else cout << "No true closed chains\n";
        if (floorAns) cout << "Floor closed chains\n";
        else cout << "No floor closed chains\n";
    }
    return 0;
}
