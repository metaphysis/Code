#include <bits/stdc++.h>
using namespace std;

const int maxC = 1005;
int posId[maxC][maxC], par[100005], siz[100005], posX[100005], posY[100005];
bool active[100005];
int n, m, k, cnt;

int findRoot(int x) {
    if (par[x] == x) return x;
    return par[x] = findRoot(par[x]);
}

void unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) return;
    if (siz[a] < siz[b]) swap(a, b);
    par[b] = a;
    siz[a] += siz[b];
}

void addNode(int id) {
    active[id] = true;
    int x = posX[id], y = posY[id];
    for (int dx = -k; dx <= k; dx++)
        for (int dy = -k; dy <= k; dy++) {
            if (dx * dx + dy * dy > k * k) continue;
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx > n || ny < 0 || ny > m) continue;
            int other = posId[nx][ny];
            if (other != -1 && active[other]) unite(id, other);
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> k >> cnt) {
        fill(&posId[0][0], &posId[0][0] + maxC * maxC, -1);
        fill(active, active + cnt + 2, false);
        for (int i = 0; i <= cnt + 1; i++) {
            par[i] = i;
            siz[i] = 1;
        }
        posX[0] = 0;
        posY[0] = 0;
        posX[cnt + 1] = n;
        posY[cnt + 1] = m;
        posId[0][0] = 0;
        posId[n][m] = cnt + 1;
        for (int i = 1; i <= cnt; i++) {
            cin >> posX[i] >> posY[i];
            posId[posX[i]][posY[i]] = i;
        }
        addNode(0);
        addNode(cnt + 1);
        if (findRoot(0) == findRoot(cnt + 1)) {
            cout << "Never had the chance\n";
            continue;
        }
        bool found = false;
        for (int i = cnt; i >= 1; i--) {
            addNode(i);
            if (findRoot(0) == findRoot(cnt + 1)) {
                cout << posX[i] << ' ' << posY[i] << '\n';
                found = true;
                break;
            }
        }
        if (!found) cout << "Never had the chance\n";
    }
    return 0;
}
