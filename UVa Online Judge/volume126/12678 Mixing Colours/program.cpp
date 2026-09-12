#include <bits/stdc++.h>
using namespace std;

int getId(const string &name, unordered_map<string, int> &id) {
    if (id.count(name)) return id[name];
    int cur = id.size();
    id[name] = cur;
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, t;
    bool firstSet = true;
    while (cin >> r) {
        unordered_map<string, int> id;
        vector<tuple<int, int, int>> rules;
        string a, b, c;
        for (int i = 0; i < r; i++) {
            cin >> a >> b >> c;
            int x = getId(a, id), y = getId(b, id), z = getId(c, id);
            rules.push_back(make_tuple(x, y, z));
        }
        int m = id.size();
        vector<int> to(m * m, -1);
        for (auto rule : rules) {
            int x, y, z;
            tie(x, y, z) = rule;
            to[x * m + y] = z;
            to[y * m + x] = z;
        }
        cin >> t;
        if (!firstSet) cout << '\n';
        firstSet = false;
        while (t--) {
            int n;
            cin >> n;
            vector<vector<pair<int, double>>> dp(n * n);
            for (int i = 0; i < n; i++) {
                string name;
                while (cin >> name && name != "END") {
                    double cer;
                    cin >> cer;
                    int color = getId(name, id);
                    dp[i * n + i].push_back(make_pair(color, log(cer)));
                }
            }
            for (int len = 2; len <= n; len++) {
                for (int l = 0; l + len <= n; l++) {
                    int rr = l + len - 1;
                    vector<double> best(m, -numeric_limits<double>::infinity());
                    for (int mid = l; mid < rr; mid++) {
                        vector<pair<int, double>> &left = dp[l * n + mid];
                        vector<pair<int, double>> &right = dp[(mid + 1) * n + rr];
                        for (auto x : left) {
                            for (auto y : right) {
                                int color = to[x.first * m + y.first];
                                if (color != -1) best[color] = max(best[color], x.second + y.second);
                            }
                        }
                    }
                    for (int color = 0; color < m; color++) {
                        if (best[color] != -numeric_limits<double>::infinity())
                            dp[l * n + rr].push_back(make_pair(color, best[color]));
                    }
                }
            }
            double ans = -numeric_limits<double>::infinity();
            int color = -1;
            for (auto cur : dp[n - 1]) {
                if (cur.second > ans) {
                    ans = cur.second;
                    color = cur.first;
                }
            }
            if (color == -1) {
                cout << "GAMEOVER\n";
            } else {
                vector<string> name(m);
                for (auto cur : id) name[cur.second] = cur.first;
                cout << name[color] << '\n';
            }
        }
    }
    return 0;
}
