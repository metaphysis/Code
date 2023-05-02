// Cheapest Way
// UVa ID: 10436
// Verdict: Accepted
// Submission Date: 2023-05-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
struct edge {
    int v, w;
    bool operator<(const edge &e) const { return w > e.w; } 
};
vector<edge> g[32];
map<string, int> cityIndex;
vector<string> cityName;
int pay[32];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++) {
        if (cs) cout << '\n';
        cout << "Map #" << cs + 1 << '\n';
        int n, m;
        cin >> n;
        cityIndex.clear();
        cityName.clear();
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name >> pay[i];
            cityIndex[name] = i;
            cityName.push_back(name);
        }
        for (int i = 0; i < 20; i++) g[i].clear();
        cin >> m;
        for (int i = 0; i < m; i++) {
            string name1, name2;
            int money;
            cin >> name1 >> name2 >> money;
            int u = cityIndex[name1], v = cityIndex[name2];
            g[u].push_back(edge{v, 2 * money});
            g[v].push_back(edge{u, 2 * money});
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            string name1, name2;
            int passengers;
            cin >> name1 >> name2 >> passengers;
            int s = cityIndex[name1], t = cityIndex[name2];
            int d[32], p[32];
            memset(d, 0x3f, sizeof d);
            d[s] = pay[s];
            p[s] = -1;
            priority_queue<edge> q;
            q.push(edge{s, d[s]});
            while (!q.empty()) {
                edge e1 = q.top(); q.pop();
                for (auto e2 : g[e1.v])
                    if (d[e2.v] > d[e1.v] + e2.w + pay[e2.v]) {
                        p[e2.v] = e1.v;
                        d[e2.v] = d[e1.v] + e2.w + pay[e2.v];
                        q.push(edge{e2.v, d[e2.v]});
                    }
            }
            double average = d[t] * 1.1 / passengers;
            cout << "Query #" << i + 1 << '\n';
            vector<string> path;
            while (t != s) {
                path.insert(path.begin(), cityName[t]);
                t = p[t];
            }
            path.insert(path.begin(), cityName[t]);
            for (int j = 0; j < path.size(); j++) {
                if (j) cout << ' ';
                cout << path[j];
            }
            cout << '\n';
            cout << "Each passenger has to pay : ";
            cout << fixed << setprecision(2) << average << " taka\n";
        }
    }
    return 0;
}
