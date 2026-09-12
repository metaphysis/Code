#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const int dy[4] = {1, -1, 0, 0};
const int dx[4] = {0, 0, 1, -1};

struct Zone {
    int id, area;
    vector<int> out;
    double inRate, level, maxLevel;
};

int rows, cols, faucetR, faucetC;
double cell[20][20];
Zone *zoneAt[20][20];
vector<Zone *> zones;

bool cmpZone(Zone *a, Zone *b) {
    return a->level > b->level;
}

bool inside(int r, int c) {
    return r >= 1 && r <= rows && c >= 1 && c <= cols;
}

Zone *makeZone(int r, int c);

void clearZones() {
    int i;
    for (i = 0; i < (int)zones.size(); ++i)
        delete zones[i];
    zones.clear();
    memset(zoneAt, 0, sizeof(zoneAt));
}

void dfs(Zone *zone, int r, int c) {
    if (zoneAt[r][c] != NULL) return;
    zoneAt[r][c] = zone;
    ++zone->area;
    int i;
    for (i = 0; i < 4; ++i) {
        int nr = r + dy[i], nc = c + dx[i];
        if (!inside(nr, nc)) continue;
        if (fabs(cell[nr][nc] - zone->level) < eps)
            dfs(zone, nr, nc);
        else if (cell[nr][nc] < zone->level)
            zone->out.push_back(makeZone(nr, nc)->id);
        else
            zone->maxLevel = min(zone->maxLevel, cell[nr][nc]);
    }
}

Zone *makeZone(int r, int c) {
    if (zoneAt[r][c] != NULL) return zoneAt[r][c];
    Zone *zone = new Zone();
    zone->id = zones.size();
    zone->area = 0;
    zone->inRate = 0.0;
    zone->level = cell[r][c];
    zone->maxLevel = 10.0;
    zones.push_back(zone);
    dfs(zone, r, c);
    return zoneAt[r][c];
}

bool reachesSide() {
    int i, j;
    for (i = 1; i <= rows; ++i)
        for (j = 1; j <= cols; ++j)
            if ((i == 1 || i == rows || j == 1 || j == cols) && zoneAt[i][j] != NULL)
                return true;
    return false;
}

double simulate() {
    double result = 0.0;
    while (true) {
        clearZones();
        makeZone(faucetR, faucetC);
        if (reachesSide()) break;
        vector<Zone *> order = zones;
        sort(order.begin(), order.end(), cmpZone);
        zones[0]->inRate = 1.0;
        int i, j;
        for (i = 0; i < (int)order.size(); ++i) {
            Zone *zone = order[i];
            if (!zone->out.empty()) {
                for (j = 0; j < (int)zone->out.size(); ++j) {
                    Zone *next = zones[zone->out[j]];
                    next->inRate += zone->inRate / zone->out.size();
                }
            }
        }
        double delta = 1e100;
        for (i = 0; i < (int)zones.size(); ++i) {
            Zone *zone = zones[i];
            if (zone->out.empty())
                delta = min(delta, (zone->maxLevel - zone->level) * zone->area / zone->inRate);
        }
        result += delta;
        for (i = 0; i < (int)zones.size(); ++i) {
            Zone *zone = zones[i];
            if (zone->out.empty())
                zone->level += delta * zone->inRate / zone->area;
        }
        for (i = 1; i <= rows; ++i)
            for (j = 1; j <= cols; ++j)
                if (zoneAt[i][j] != NULL)
                    cell[i][j] = zoneAt[i][j]->level;
    }
    clearZones();
    return result;
}

void solve() {
    while (cin >> rows >> cols) {
        if (rows == 0 && cols == 0) break;
        cin >> faucetR >> faucetC;
        int i, j;
        for (i = 1; i <= rows; ++i)
            for (j = 1; j <= cols; ++j)
                cin >> cell[i][j];
        cout << fixed << setprecision(2) << simulate() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
