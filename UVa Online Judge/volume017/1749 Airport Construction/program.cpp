// Airport Construction
// UVa ID: 1749
// Verdict: Accepted
// Submission Date: 2022-11-21
// UVa Run Time: 0.570s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 205;
const double EPSILON = 1e-9;

int n;
double answer;

int sgn(double x) { return x > EPSILON ? 1 : x < -EPSILON ? -1 : 0; }

struct point {
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) { }
    point operator+(const point & p) { return point(x + p.x, y + p.y); }
    point operator-(const point & p) { return point(x - p.x, y - p.y); }
    double operator*(const point & p) { return x * p.y - y * p.x; }
    double norm() { return sqrt(x * x + y * y); }
} ps[MAXN];

struct line {
    point p, v;
    line(point p, point v) : p(p), v(v) { }
};

double getDist(line a, line b) { return b.v * (a.p - b.p) / (a.v * b.v) * a.v.norm(); }

pair<double, int> ip[MAXN];

void getLength(line l)
{
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int cp1 = sgn(l.v * (ps[i] - l.p)), cp2 = sgn(l.v * (ps[i + 1] - l.p));
        if (cp1 == cp2) continue;
        ip[cnt++] = make_pair(getDist(l, line(ps[i], ps[i + 1] - ps[i])), cp1 - cp2);
    }
    sort(ip, ip + cnt);
    int flag = 0;
    double length = 0;
    for (int i = 0; i < cnt; i++) {
        if (flag) length += ip[i].first - ip[i - 1].first;
        else answer = max(answer, length), length = 0;
        flag += ip[i].second;
    }
    answer = max(answer, length);
}

int main(int argc, char *argv[])
{
    while (cin >> n) {
        answer = 0;
        for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
        ps[n] = ps[0];
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                getLength(line(ps[i], ps[j] - ps[i]));
        cout << fixed << setprecision(9) << answer << '\n';
    }
    return 0;
}
