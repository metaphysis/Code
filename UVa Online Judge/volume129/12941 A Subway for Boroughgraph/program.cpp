#include <bits/stdc++.h>
using namespace std;

using U64 = uint64_t;

int n;
U64 adj[64];
U64 alive;

U64 bit(int v) { return U64(1) << v; }

int degreeOf(int v) { return __builtin_popcountll(adj[v] & alive); }

U64 greaterThan(int v) {
    if (v + 1 >= n) return 0;
    return (~U64(0)) << (v + 1);
}

void reduceGraph() {
    while (true) {
        U64 removed = 0;
        for (int v = 0; v < n; ++v)
            if ((alive & bit(v)) && degreeOf(v) <= 1)
                removed |= bit(v);
        if (removed) {
            alive &= ~removed;
            for (int v = 0; v < n; ++v) adj[v] &= alive;
            continue;
        }
        bool smoothed = false;
        for (int v = 0; v < n; ++v) {
            if (!(alive & bit(v)) || degreeOf(v) != 2) continue;
            U64 neighbors = adj[v] & alive;
            int u = __builtin_ctzll(neighbors);
            neighbors &= neighbors - 1;
            int w = __builtin_ctzll(neighbors);
            alive &= ~bit(v);
            adj[v] = 0;
            adj[u] &= ~bit(v);
            adj[w] &= ~bit(v);
            adj[u] |= bit(w);
            adj[w] |= bit(u);
            smoothed = true;
            break;
        }
        if (!smoothed) break;
    }
}

bool hasK5() {
    for (int a = 0; a < n; ++a) {
        if (!(alive & bit(a))) continue;
        U64 bs = adj[a] & alive & greaterThan(a);
        while (bs) {
            int b = __builtin_ctzll(bs);
            bs &= bs - 1;
            U64 cs = adj[a] & adj[b] & alive & greaterThan(b);
            while (cs) {
                int c = __builtin_ctzll(cs);
                cs &= cs - 1;
                U64 ds = adj[a] & adj[b] & adj[c] & alive & greaterThan(c);
                while (ds) {
                    int d = __builtin_ctzll(ds);
                    ds &= ds - 1;
                    U64 es = adj[a] & adj[b] & adj[c] & adj[d] & alive & greaterThan(d);
                    if (es) return true;
                }
            }
        }
    }
    return false;
}

bool hasK33() {
    for (int a = 0; a < n; ++a) {
        if (!(alive & bit(a))) continue;
        for (int b = a + 1; b < n; ++b) {
            if (!(alive & bit(b))) continue;
            for (int c = b + 1; c < n; ++c) {
                if (!(alive & bit(c))) continue;
                U64 common = adj[a] & adj[b] & adj[c] & alive;
                common &= ~(bit(a) | bit(b) | bit(c));
                if (__builtin_popcountll(common) >= 3) return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        string line;
        getline(cin, line);
        fill(begin(adj), end(adj), U64(0));
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            stringstream input(line);
            int neighbor;
            while (input >> neighbor) {
                int j = neighbor - 1;
                if (j < 0 || j >= n || j == i) continue;
                adj[i] |= bit(j);
                adj[j] |= bit(i);
            }
        }
        alive = (n == 64) ? ~U64(0) : (bit(n) - 1);
        reduceGraph();
        bool containsForbiddenGraph = hasK5() || hasK33();
        cout << (containsForbiddenGraph ? 'N' : 'Y') << '\n';
    }
    return 0;
}
