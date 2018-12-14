// Simplified GSM Network
// UVa ID: 1039
// Verdict: Accepted
// Submission Date: 2018-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

struct segment {
    point p1, p2;
};

typedef segment line;

double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - b.x * a.y; }
double norm(point p) { return p.x * p.x + p.y * p.y; };
double abs(point p) { return sqrt(norm(p)); };

double getDist(point a, point b)
{
    return abs(a - b);
}

const int INF = 0x3f3f3f3f;

int B, C, R, Q, D[64][64];
point towers[64], cities[64];

int getSwitchs(int m, int n)
{
    int switches = 0;
    double d;
    point nearest;

    for (int i = 1; i <= B; i++)
    {
        // Get distance between a BTS tower and a road.
        if (dot(cities[n] - cities[m], towers[i] - cities[m]) < 0.0)
        {
            d = getDist(towers[i], cities[m]);
            nearest = cities[m];
        }
        else if (dot(cities[m] - cities[n], towers[i] - cities[n]) < 0.0)
        {
            d = getDist(towers[i], cities[n]);
            nearest = cities[n];
        }
        else
        {
            // Get the project of point on segment.
            segment s;
            s.p1 = cities[m], s.p2 = cities[n];
            point base = s.p2 - s.p1;
            double r = dot(towers[i] - s.p1, base) / norm(base);
            nearest = s.p1 + base * r;
            d = getDist(towers[i], nearest);
        }

        bool best = true;
        for (int j = 1; j <= B; j++)
        {
            if (i == j) continue;
            if (getDist(nearest, towers[j]) < d)
            {
                best = false;
                break;
            }
        }
        if (best) switches++;
    }

    return switches - 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> B >> C >> R >> Q)
    {
        if (B == 0) break;

        for (int i = 1; i <= B; i++) cin >> towers[i].x >> towers[i].y;
        for (int i = 1; i <= C; i++) cin >> cities[i].x >> cities[i].y;
        
        memset(D, INF, sizeof(D));
        for (int i = 1; i <= C; i++) D[i][i] = 0;
        for (int i = 1, m, n; i <= R; i++)
        {
            cin >> m >> n;
            D[m][n] = D[n][m] = getSwitchs(m, n);
        }
        for (int k = 1; k <= C; k++)
            for (int i = 1; i <= C; i++)
                for (int j = 1; j <= C; j++)
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
        cout << "Case " << ++cases << ":\n";
        for (int i = 1, s, d; i <= Q; i++)
        {
            cin >> s >> d;
            if (D[s][d] == INF) cout << "Impossible";
            else cout << D[s][d];
            cout << '\n';
        }
    }

    return 0;
}
