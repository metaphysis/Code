#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const double eps = 1e-8;

ll powInt(ll a, int n) {
    ll ret = 1;
    while (n--) ret *= a;
    return ret;
}

struct Point {
    int x, y;
    double dx, dy, dis;
    Point() : x(0), y(0), dx(0), dy(0), dis(0) {}
    Point(double x0, double y0) : x(x0), y(y0), dx(x0), dy(y0), dis(0) {}
    void init(int n) {
        dx *= powInt(3, n) - 1;
        dy *= powInt(3, n) - 1;
        x = dx;
        y = dy;
    }
    void findNearest(Point &src) {
        double tmp;
        src.x = src.dx = modf(dx, &tmp) <= 0.5 + eps ? floor(dx) : ceil(dx);
        src.y = src.dy = modf(dy, &tmp) <= 0.5 + eps ? floor(dy) : ceil(dy);
        double gx = src.dx - dx, gy = src.dy - dy;
        dis = sqrt(gx * gx + gy * gy);
    }
};

const int stepOrder[3][3] = {
    {8, 3, 2},
    {7, 4, 1},
    {6, 5, 0}
};

const int sNext[3][3] = {
    {0, 2, 0},
    {1, 3, 1},
    {0, 2, 0}
};

const int zNext[3][3] = {
    {1, 3, 1},
    {0, 2, 0},
    {1, 3, 1}
};

ll getIndex(int n, const Point &rs, const Point &re, int type, const Point &s) {
    if (n == 0) return 0;
    ll unitLen = powInt(9, n - 1) - 1;
    int unit = (re.x - rs.x + 1) / 9;
    int x = (s.x - rs.x) / ((re.x - rs.x + 1) / 3), y = (s.y - rs.y) / ((re.y - rs.y + 1) / 3);
    Point ns(rs.x + unit * 3 * x, rs.y + unit * 3 * y);
    Point ne(rs.x + unit * 3 * (x + 1) - 1, rs.y + unit * 3 * (y + 1) - 1);
    switch (type) {
        case 0:
            return getIndex(n - 1, ns, ne, sNext[x][y], s) + stepOrder[x][y] * (unitLen + 1);
        case 1:
            return getIndex(n - 1, ns, ne, zNext[x][y], s) + stepOrder[x][2 - y] * (unitLen + 1);
        case 2:
            return getIndex(n - 1, ns, ne, 3 - zNext[x][y], s) + (8 - stepOrder[x][2 - y]) * (unitLen + 1);
        default:
            return getIndex(n - 1, ns, ne, 3 - sNext[x][y], s) + (8 - stepOrder[x][y]) * (unitLen + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNum = 1;
    while (cin >> n && n) {
        if (caseNum != 1) cout << '\n';
        Point sp, ep;
        cin >> sp.dx >> sp.dy >> ep.dx >> ep.dy;
        sp.init(n);
        ep.init(n);
        Point csp, cep;
        sp.findNearest(csp);
        ep.findNearest(cep);
        ll side = powInt(3, n) - 1;
        Point begin(0, 0), end(side, side);
        ll startIdx = getIndex(n, begin, end, 0, csp), endIdx = getIndex(n, begin, end, 0, cep);
        double ans = (abs(startIdx - endIdx) + sp.dis + ep.dis) / side;
        cout << "Case " << caseNum << ".  Distance is " << fixed << setprecision(4) << ans << '\n';
        ++caseNum;
    }
    return 0;
}
