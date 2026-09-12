#include <bits/stdc++.h>
using namespace std;

using P = pair<int, int>;

vector<vector<vector<P>>> allShape(7);

string getKey(vector<P> a) {
    int minX = a[0].first, minY = a[0].second;
    for (P p : a) {
        minX = min(minX, p.first);
        minY = min(minY, p.second);
    }
    for (P &p : a) {
        p.first -= minX;
        p.second -= minY;
    }
    sort(a.begin(), a.end());
    string res;
    for (P p : a)
        res += to_string(p.first) + "," + to_string(p.second) + ";";
    return res;
}

vector<P> normalize(vector<P> a) {
    int minX = a[0].first, minY = a[0].second;
    for (P p : a) {
        minX = min(minX, p.first);
        minY = min(minY, p.second);
    }
    for (P &p : a) {
        p.first -= minX;
        p.second -= minY;
    }
    sort(a.begin(), a.end());
    return a;
}

void buildShape(int k, vector<P> cur, set<string> &vis) {
    string key = getKey(cur);
    if (vis.count(key)) return;
    vis.insert(key);
    cur = normalize(cur);
    allShape[k].push_back(cur);
    if (k == 6) return;
    set<P> has(cur.begin(), cur.end());
    for (P p : cur) {
        int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            P q = {p.first + dx[i], p.second + dy[i]};
            if (has.count(q)) continue;
            vector<P> nxt = cur;
            nxt.push_back(q);
            buildShape(k + 1, nxt, vis);
        }
    }
}

void init() {
    set<string> vis;
    buildShape(1, {{0, 0}}, vis);
}

long long solve(int n, int m, int k, vector<P> block) {
    long long ans = 0;
    for (vector<P> shape : allShape[k]) {
        int maxX = 0, maxY = 0;
        for (P p : shape) {
            maxX = max(maxX, p.first);
            maxY = max(maxY, p.second);
        }
        int h = maxX + 1, w = maxY + 1;
        if (h > n || w > m) continue;
        set<long long> bad;
        for (P b : block) {
            for (P p : shape) {
                int x = b.first - p.first, y = b.second - p.second;
                if (x >= 1 && x + h - 1 <= n && y >= 1 && y + w - 1 <= m)
                    bad.insert(1LL * x * 2000 + y);
            }
        }
        ans += 1LL * (n - h + 1) * (m - w + 1) - bad.size();
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, m, k, x;
        cin >> n >> m >> k >> x;
        vector<P> block(x);
        for (P &p : block)
            cin >> p.first >> p.second;
        cout << "Case " << cs << ": " << solve(n, m, k, block) << '\n';
    }
    return 0;
}
