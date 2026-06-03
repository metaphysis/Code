// Asteroid Rangers
// UVa ID: 1279
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.470s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const int MAXN = 55;
const int MAXE = MAXN * (MAXN - 1) / 2;

int n, eCnt;

struct Point {
    double px, py, pz, vx, vy, vz;
    void get() {
        cin >> px >> py >> pz >> vx >> vy >> vz;
    }
} pts[MAXN];

struct Edge {
    double A, B, C;
    int from, to;
    Edge() {}
    Edge(int f, int t, double a, double b, double c) : from(f), to(t), A(a), B(b), C(c) {}
    bool operator < (const Edge& o) const {
        return C < o.C;
    }
} edges[MAXE];

double square(double x) { return x * x; }

void initEdges() {
    eCnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dx = pts[i].px - pts[j].px;
            double dy = pts[i].py - pts[j].py;
            double dz = pts[i].pz - pts[j].pz;
            double dvx = pts[i].vx - pts[j].vx;
            double dvy = pts[i].vy - pts[j].vy;
            double dvz = pts[i].vz - pts[j].vz;
            double A = square(dvx) + square(dvy) + square(dvz);
            double B = 2 * (dx * dvx + dy * dvy + dz * dvz);
            double C = square(dx) + square(dy) + square(dz);
            edges[eCnt++] = Edge(i, j, A, B, C);
        }
    }
    sort(edges, edges + eCnt);
}

struct Event {
    double time;
    int enter, leave;
    Event(double t = 0, int e = 0, int l = 0) : time(t), enter(e), leave(l) {}
    bool operator < (const Event& o) const {
        return time < o.time;
    }
};

vector<Event> events;

void buildEvents() {
    events.clear();
    for (int i = 0; i < eCnt; ++i) {
        for (int j = i + 1; j < eCnt; ++j) {
            int p = i, q = j;
            if (edges[p].A < edges[q].A) swap(p, q);
            double dA = edges[p].A - edges[q].A;
            double dB = edges[p].B - edges[q].B;
            double dC = edges[p].C - edges[q].C;
            
            if (fabs(dA) < EPS) {
                if (fabs(dB) < EPS) continue;
                if (dB > 0) {
                    swap(p, q);
                    dB = -dB;
                    dC = -dC;
                }
                if (dC > 0) events.push_back(Event(-dC / dB, p, q));
                continue;
            }
            
            double delta = dB * dB - 4 * dA * dC;
            if (delta < EPS) continue;
            delta = sqrt(delta);
            double x1 = (-dB - delta) / (2 * dA);
            double x2 = (delta - dB) / (2 * dA);
            if (x1 > 0) events.push_back(Event(x1, p, q));
            if (x2 > 0) events.push_back(Event(x2, q, p));
        }
    }
    sort(events.begin(), events.end());
}

int dsu[MAXN];

void dsuInit() {
    for (int i = 0; i < n; ++i) dsu[i] = i;
}

int dsuFind(int x) {
    return dsu[x] == x ? x : dsu[x] = dsuFind(dsu[x]);
}

bool dsuMerge(int x, int y) {
    int rx = dsuFind(x), ry = dsuFind(y);
    if (rx == ry) return false;
    dsu[rx] = ry;
    return true;
}

int simulate() {
    int mark[MAXE] = {0};
    int mst[MAXN];
    
    dsuInit();
    int cur = 0;
    for (int i = 0; i < eCnt; ++i) {
        if (dsuMerge(edges[i].from, edges[i].to)) {
            mst[mark[i] = ++cur] = i;
            if (cur == n - 1) break;
        }
    }
    
    int cnt = 1;
    
    for (size_t i = 0; i < events.size(); ++i) {
        int out = events[i].leave;
        int in = events[i].enter;
        
        if (mark[out] && !mark[in]) {
            dsuInit();
            int pos = mark[out];
            
            for (int j = 1; j < n; ++j) {
                if (j != pos) {
                    dsuMerge(edges[mst[j]].from, edges[mst[j]].to);
                }
            }
            
            if (dsuMerge(edges[in].from, edges[in].to)) {
                cnt++;
                mark[in] = pos;
                mst[pos] = in;
                mark[out] = 0;
            }
        }
    }
    
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T = 0;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) pts[i].get();
        initEdges();
        buildEvents();
        cout << "Case " << ++T << ": " << simulate() << "\n";
    }
    return 0;
}
