#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;
const int maxObj = 5;

int tx[maxObj][4], ty[maxObj][4], tz[maxObj][4];
int cx[maxObj], cy[maxObj], cz[maxObj], rad[maxObj];
int tetNum, sphNum;
int ptCnt[maxObj];
double px[maxObj][5], py[maxObj][5], cr[maxObj];

struct Trap {
    double h, t, a;
    int f;
    bool operator < (const Trap& oth) const {
        return t > oth.t;
    }
};

double interp(double x1, double y1, double x2, double y2, double x) {
    return (y1 * (x2 - x) + y2 * (x - x1)) / (x2 - x1);
}

void addSegCross(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, vector<double>& xs) {
    double dx = x2 - x1, dy = y2 - y1, dx1 = x3 - x1, dy1 = y3 - y1, dx2 = x4 - x1, dy2 = y4 - y1;
    if ((dx * dy1 - dx1 * dy) * (dx * dy2 - dx2 * dy) >= 0.0) return;
    dx = x4 - x3;
    dy = y4 - y3;
    dx1 = x1 - x3;
    dy1 = y1 - y3;
    dx2 = x2 - x3;
    dy2 = y2 - y3;
    double c1 = dx * dy1 - dx1 * dy, c2 = dx * dy2 - dx2 * dy;
    if (c1 * c2 >= 0.0) return;
    c1 /= c1 - c2;
    xs.push_back((1.0 - c1) * x1 + c1 * x2);
}

void addSegCircleCross(double x1, double y1, double x2, double y2, int id, vector<double>& xs) {
    double dx = x2 - x1, dy = y2 - y1, len = sqrt(dx * dx + dy * dy);
    if (len < eps) return;
    double vx = cx[id] - x1, vy = cy[id] - y1;
    dx /= len;
    dy /= len;
    double dis = fabs(dx * vy - vx * dy);
    if (dis > cr[id] - eps) return;
    double mid = dx * vx + dy * vy, off = sqrt(max(0.0, cr[id] * cr[id] - dis * dis));
    double p1 = mid - off, p2 = mid + off;
    if (p1 > -eps && p1 < len + eps) xs.push_back(x1 + dx * p1);
    if (p2 > -eps && p2 < len + eps) xs.push_back(x1 + dx * p2);
}

void addCircleCross(int i, int j, vector<double>& xs) {
    double dx = cx[i] - cx[j], dy = cy[i] - cy[j], dis = sqrt(dx * dx + dy * dy);
    if (dis > cr[i] + cr[j] - eps || dis < fabs(cr[i] - cr[j]) + eps) return;
    double cosa = dx / dis, cosb = (cr[j] * cr[j] + dis * dis - cr[i] * cr[i]) / (2.0 * cr[j] * dis);
    double sina = sqrt(max(0.0, 1.0 - cosb * cosb));
    double ss = dy / dis * sina, cc = cosa * cosb;
    xs.push_back(cx[j] + cr[j] * (cc - ss));
    xs.push_back(cx[j] + cr[j] * (cc + ss));
}

void addPolyTrap(int id, double l, double r, vector<Trap>& traps) {
    int cnt = 0;
    double h[2];
    for (int i = 0; i < ptCnt[id]; i++) {
        double x1 = px[id][i], y1 = py[id][i], x2 = px[id][i + 1], y2 = py[id][i + 1];
        if (min(x1, x2) > l + eps || max(x1, x2) < r - eps) continue;
        h[cnt++] = 0.5 * (interp(x1, y1, x2, y2, l) + interp(x1, y1, x2, y2, r));
    }
    if (cnt != 2) return;
    if (h[0] < h[1]) swap(h[0], h[1]);
    traps.push_back({h[0], h[0], 0.0, 1});
    traps.push_back({h[1], h[1], 0.0, -1});
}

void addCircleTrap(int id, double l, double r, vector<Trap>& traps) {
    if (max(fabs(l - cx[id]), fabs(r - cx[id])) > cr[id] + eps) return;
    double d1 = cr[id] * cr[id] - (l - cx[id]) * (l - cx[id]);
    double d2 = cr[id] * cr[id] - (r - cx[id]) * (r - cx[id]);
    d1 = d1 <= 0.0 ? 0.0 : sqrt(d1);
    d2 = d2 <= 0.0 ? 0.0 : sqrt(d2);
    double mid = 0.5 * (l + r), d = cr[id] * cr[id] - (mid - cx[id]) * (mid - cx[id]);
    d = d <= 0.0 ? 0.0 : sqrt(d);
    double ds = ((l - r) * (l - r) + (d1 - d2) * (d1 - d2)) * 0.25;
    double chord = sqrt(ds), hei = sqrt(max(0.0, cr[id] * cr[id] - ds));
    double arc = cr[id] * cr[id] * asin(min(1.0, chord / cr[id])) - chord * hei;
    traps.push_back({cy[id] + 0.5 * (d1 + d2), cy[id] + d, arc, 1});
    traps.push_back({cy[id] - 0.5 * (d1 + d2), cy[id] - d, arc, -1});
}

void buildSection(double h) {
    for (int i = 0; i < tetNum; i++) {
        ptCnt[i] = 0;
        for (int j = 0; j < 4; j++) {
            if (fabs(tz[i][j] - h) < eps) {
                px[i][ptCnt[i]] = tx[i][j];
                py[i][ptCnt[i]++] = ty[i][j];
                continue;
            }
            for (int k = j + 1; k < 4; k++) {
                if (fabs(tz[i][k] - h) < eps) continue;
                double low = min(tz[i][j], tz[i][k]), high = max(tz[i][j], tz[i][k]);
                if (low > h || high < h) continue;
                px[i][ptCnt[i]] = interp(tz[i][j], tx[i][j], tz[i][k], tx[i][k], h);
                py[i][ptCnt[i]++] = interp(tz[i][j], ty[i][j], tz[i][k], ty[i][k], h);
            }
        }
        if (ptCnt[i] < 3) continue;
        if (ptCnt[i] == 4) {
            double dx = px[i][2] - px[i][0], dy = py[i][2] - py[i][0];
            double dx1 = px[i][1] - px[i][0], dy1 = py[i][1] - py[i][0];
            double dx2 = px[i][3] - px[i][0], dy2 = py[i][3] - py[i][0];
            if ((dx * dy1 - dx1 * dy) * (dx * dy2 - dx2 * dy) > 0.0) {
                if ((dx1 * dy - dx * dy1) * (dx1 * dy2 - dx2 * dy1) > 0.0) {
                    swap(px[i][1], px[i][2]);
                    swap(py[i][1], py[i][2]);
                    swap(px[i][2], px[i][3]);
                    swap(py[i][2], py[i][3]);
                } else {
                    swap(px[i][1], px[i][2]);
                    swap(py[i][1], py[i][2]);
                }
            }
        }
        px[i][ptCnt[i]] = px[i][0];
        py[i][ptCnt[i]] = py[i][0];
    }
    for (int i = 0; i < sphNum; i++) {
        double val = rad[i] * rad[i] - (cz[i] - h) * (cz[i] - h);
        cr[i] = val <= 0.0 ? 0.0 : sqrt(val);
    }
}

double getArea(double h) {
    vector<double> xs;
    buildSection(h);
    for (int i = 0; i < tetNum; i++) {
        if (ptCnt[i] < 3) continue;
        for (int j = 0; j < ptCnt[i]; j++) xs.push_back(px[i][j]);
    }
    for (int i = 0; i < sphNum; i++) {
        if (cr[i] <= eps) continue;
        xs.push_back(cx[i] - cr[i]);
        xs.push_back(cx[i]);
        xs.push_back(cx[i] + cr[i]);
    }
    for (int i = 0; i < tetNum; i++) {
        if (ptCnt[i] < 3) continue;
        for (int j = 0; j < ptCnt[i]; j++) {
            for (int k = i + 1; k < tetNum; k++) {
                if (ptCnt[k] < 3) continue;
                for (int p = 0; p < ptCnt[k]; p++) addSegCross(px[i][j], py[i][j], px[i][j + 1], py[i][j + 1], px[k][p], py[k][p], px[k][p + 1], py[k][p + 1], xs);
            }
            for (int k = 0; k < sphNum; k++) {
                if (cr[k] > eps) addSegCircleCross(px[i][j], py[i][j], px[i][j + 1], py[i][j + 1], k, xs);
            }
        }
    }
    for (int i = 0; i < sphNum; i++) {
        if (cr[i] <= eps) continue;
        for (int j = i + 1; j < sphNum; j++) {
            if (cr[j] > eps) addCircleCross(i, j, xs);
        }
    }
    sort(xs.begin(), xs.end());
    double ans = 0.0;
    for (int i = 1; i < (int)xs.size(); i++) {
        double len = xs[i] - xs[i - 1];
        if (len <= eps) continue;
        vector<Trap> traps;
        for (int j = 0; j < tetNum; j++) {
            if (ptCnt[j] > 2) addPolyTrap(j, xs[i - 1], xs[i], traps);
        }
        for (int j = 0; j < sphNum; j++) {
            if (cr[j] > eps) addCircleTrap(j, xs[i - 1], xs[i], traps);
        }
        sort(traps.begin(), traps.end());
        int cover = 0, start = 0;
        for (int j = 0; j < (int)traps.size(); j++) {
            if (cover == 0) start = j;
            cover += traps[j].f;
            if (cover == 0) ans += len * (traps[start].h - traps[j].h) + traps[start].a + traps[j].a;
        }
    }
    return ans;
}

double simpsonRec(double l, double m, double r, double fl, double fm, double fr, double pre, double err, int step) {
    double lm = 0.5 * (l + m), rm = 0.5 * (m + r);
    double flm = getArea(lm), frm = getArea(rm);
    double sl = (fl + 4.0 * flm + fm) * (m - l) / 6.0;
    double sr = (fm + 4.0 * frm + fr) * (r - m) / 6.0;
    double now = sl + sr;
    if (step < 0 && fabs(now - pre) <= 15.0 * err) return now + (now - pre) / 15.0;
    return simpsonRec(l, lm, m, fl, flm, fm, sl, err * 0.5, step - 1) + simpsonRec(m, rm, r, fm, frm, fr, sr, err * 0.5, step - 1);
}

double getVolume() {
    double l = -8.0, r = 8.0, m = 0.5 * (l + r);
    double fl = getArea(l), fm = getArea(m), fr = getArea(r);
    double pre = (fl + 4.0 * fm + fr) * (r - l) / 6.0;
    return simpsonRec(l, m, r, fl, fm, fr, pre, 1e-3, 6);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);
    while (cin >> tetNum >> sphNum) {
        if (tetNum == 0 && sphNum == 0) break;
        for (int i = 0; i < tetNum; i++) {
            for (int j = 0; j < 4; j++) cin >> tx[i][j] >> ty[i][j] >> tz[i][j];
        }
        for (int i = 0; i < sphNum; i++) cin >> cx[i] >> cy[i] >> cz[i] >> rad[i];
        cout << getVolume() << '\n';
    }
    return 0;
}
