#include <bits/stdc++.h>

using namespace std;

struct edge { int u, v, w; } edges[1010];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    int n, m;
    for (int cs = 1; cs <= 1; cs++) {
        n = rand() % 15 + 1;
        m = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                edges[m++] = edge{i, j, rand() % 1000 + 1};
        for (int i = 1; i <= n; i++)
            edges[m++] = edge{0, i, rand() % 1000 + 1};
        for (int i = 1; i <= n; i++)
            edges[m++] = edge{i, n + 1, rand() % 1000 + 1};
        cout << n << ' ' << m << '\n';
        for (int i = 0; i < m; i++) cout << edges[i].u << ' ' << edges[i].v << ' ' << edges[i].w << '\n';
    }
    return 0;
}
