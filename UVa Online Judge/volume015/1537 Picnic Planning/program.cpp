// Picnic Planning
// UVa ID: 1537
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()
#define R(a) ((a)%mod)

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long ll;
typedef vector<ll> VL;
typedef vector<VL> VVL;
typedef vector<VVL> VVVL;
typedef vector<bool> VB;
typedef vector<string> VS;
typedef pair<int, ll> PI;
typedef vector<PI> VPI;
typedef vector<PI> VPI;
typedef vector<VPI> VVPI;
typedef vector<double> VD;
typedef vector<VD> VVD;

struct DisjointSet {
    int n;
    VI rank, parent;

    DisjointSet (int n): n(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
        }
    }

    int Find (int x) {
        return parent[x] == x ? x : (parent[x] = Find(parent[x]));
    }

    bool Union (int x, int y) { // returns false if already connected
        x = Find(x), y = Find(y);
        if (x == y) {
            return false;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[y] = x;
            rank[x] = max(rank[x], rank[y] + 1);
        }
        return true;
    }
};

template <class T> struct Kruskal {
    int n;
    vector <pair <T, PI>> edges;
    DisjointSet *D;

    Kruskal (int n): n(n) {}

    void addEdge (int s, int t, T d) {
        edges.push_back(make_pair(d, make_pair(s, t)));
    }

    T MST (int park, ll mask) {
        T ret = 0;
        D = new DisjointSet(n);
        for (auto e : edges) if (e.y.x != park || (mask & (1LL << e.y.y))) {
                if (D->Union(e.y.x, e.y.y)) {
                    ret += e.x;
                }
            }
        return ret;
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);

    Kruskal<ll> *K;
    int t;
    cin >> t;
    for (int cs = 0; cs < t; ++cs) {
        int m, n = 0;
        cin >> m;
        map<string, int> f;
        vector<pair<ll, pair<int, int>>> edges;
        ll mask = 0;
        for (int i = 0; i < m; ++i) {
            string s, t;
            ll d;
            cin >> s >> t >> d;
            if (t == "Park") {
                swap(s, t);
            }
            if (f.find(s) == f.end()) {
                f[s] = n++;
            }
            if (f.find(t) == f.end()) {
                f[t] = n++;
            }
            edges.push_back(make_pair(d, make_pair(f[s], f[t])));
            if (s == "Park") {
                mask |= 1LL << f[t];
            }
        }
        K = new Kruskal<ll> (n);
        for (auto e : edges) {
            K->addEdge(e.y.x, e.y.y, e.x);
        }
        sort(all(K->edges));
        int maxToPark;
        cin >> maxToPark;
        int direct = __builtin_popcount(mask), park = f["Park"];
        ll ans = numeric_limits<ll>::max();
        for (ll i = mask; i != 0; i = (i - 1LL) & mask) if (__builtin_popcount(i) == min(maxToPark, direct)) {
                ans = min(ans, K->MST(park, i));
            }
        if (cs != 0) {
            cout << endl;
        }
        cout << "Total miles driven: " << ans << endl;
    }


    return 0;
}
