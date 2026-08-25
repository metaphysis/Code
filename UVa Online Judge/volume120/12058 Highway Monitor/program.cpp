#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int x, y;
};

int n, h, k;
vector<Edge> eds;
vector<int> used;
vector<int> ans;

bool dfs(int left) {
    int x = -1, y = -1;
    for (const Edge &e : eds)
        if (!used[e.x] && !used[e.y]) {
            x = e.x;
            y = e.y;
            break;
        }
    if (x == -1)
        return true;
    if (left == 0)
        return false;
    used[x] = 1;
    ans.push_back(x);
    if (dfs(left - 1))
        return true;
    ans.pop_back();
    used[x] = 0;
    used[y] = 1;
    ans.push_back(y);
    if (dfs(left - 1))
        return true;
    ans.pop_back();
    used[y] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        cin >> n >> h >> k;
        eds.clear();
        eds.reserve(h);
        for (int i = 0; i < h; i++) {
            int x, y;
            cin >> x >> y;
            eds.push_back({x, y});
        }
        used.assign(n + 1, 0);
        ans.clear();
        bool ok = dfs(k);
        cout << "Case #" << cs << ":";
        if (!ok) {
            cout << " no\n";
            continue;
        }
        cout << " yes";
        for (int x : ans)
            cout << " " << x;
        cout << "\n";
    }
    return 0;
}
