#include <bits/stdc++.h>
using namespace std;

vector<complex<double>> pointList;
vector<double> segLen;
double baseLen, totalLen;
int pointCount;

complex<double> getPos(int dep, double f, complex<double> org, complex<double> mul) {
    int i;
    double target, cur, part, local;
    complex<double> q, edge, newOrg, newMul;
    if (dep == 1) {
        target = f * totalLen;
        cur = 0;
        for (i = 0; i < pointCount - 1; i++) {
            if (i == pointCount - 2 || target <= cur + segLen[i]) {
                part = segLen[i] == 0 ? 0 : (target - cur) / segLen[i];
                q = pointList[i] + (pointList[i + 1] - pointList[i]) * part;
                return org + mul * (q - pointList[0]);
            }
            cur += segLen[i];
        }
    }
    cur = 0;
    for (i = 0; i < pointCount - 1; i++) {
        part = segLen[i] / baseLen;
        if (i == pointCount - 2 || f <= cur + part) {
            local = part == 0 ? 0 : (f - cur) / part;
            edge = pointList[i + 1] - pointList[i];
            newOrg = org + mul * (pointList[i] - pointList[0]);
            newMul = mul * edge / (pointList[pointCount - 1] - pointList[0]);
            return getPos(dep - 1, local, newOrg, newMul);
        }
        cur += part;
    }
    return org + mul * (pointList[pointCount - 1] - pointList[0]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount, d, i, x, y;
    double f;
    complex<double> ans;
    cin >> caseCount;
    cout << fixed << setprecision(10);
    while (caseCount--) {
        cin >> pointCount;
        pointList.resize(pointCount);
        segLen.resize(pointCount - 1);
        for (i = 0; i < pointCount; i++) {
            cin >> x >> y;
            pointList[i] = complex<double>(x, y);
        }
        baseLen = 0;
        for (i = 0; i < pointCount - 1; i++) {
            segLen[i] = abs(pointList[i + 1] - pointList[i]);
            baseLen += segLen[i];
        }
        totalLen = baseLen;
        cin >> d >> f;
        ans = getPos(d, f, pointList[0], complex<double>(1, 0));
        if (abs(ans.real()) < 1e-12) ans.real(0);
        if (abs(ans.imag()) < 1e-12) ans.imag(0);
        cout << "(" << ans.real() << ", " << ans.imag() << ")\n";
    }
    return 0;
}
