#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1.0L);

struct Vec {
    long double x, y, z;
};

struct Mat {
    long double a[3][3];
};

Mat mulMat(const Mat &a, const Mat &b) {
    Mat c = {};
    int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                c.a[i][j] += a.a[i][k] * b.a[k][j];
    return c;
}

Vec mulVec(const Mat &a, const Vec &v) {
    Vec r;
    r.x = a.a[0][0] * v.x + a.a[0][1] * v.y + a.a[0][2] * v.z;
    r.y = a.a[1][0] * v.x + a.a[1][1] * v.y + a.a[1][2] * v.z;
    r.z = a.a[2][0] * v.x + a.a[2][1] * v.y + a.a[2][2] * v.z;
    return r;
}

Mat eyeMat() {
    Mat a = {};
    a.a[0][0] = a.a[1][1] = a.a[2][2] = 1;
    return a;
}

Mat rotMat(long double x, long double y, long double z, int deg) {
    Mat r;
    long double len = sqrtl(x * x + y * y + z * z), u, v, w, ang, cs, sn, k;
    u = x / len;
    v = y / len;
    w = z / len;
    ang = deg * pi / 180.0L;
    cs = cosl(ang);
    sn = sinl(ang);
    k = 1 - cs;
    r.a[0][0] = cs + u * u * k;
    r.a[0][1] = u * v * k - w * sn;
    r.a[0][2] = u * w * k + v * sn;
    r.a[1][0] = v * u * k + w * sn;
    r.a[1][1] = cs + v * v * k;
    r.a[1][2] = v * w * k - u * sn;
    r.a[2][0] = w * u * k - v * sn;
    r.a[2][1] = w * v * k + u * sn;
    r.a[2][2] = cs + w * w * k;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, t, i, j;
    cin >> n >> m >> t;
    vector<Vec> points(n);
    vector<array<long double, 4>> planes(m);
    for (i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y >> points[i].z;
    for (i = 0; i < m; i++)
        cin >> planes[i][0] >> planes[i][1] >> planes[i][2] >> planes[i][3];
    Mat mat = eyeMat(), invTrans = eyeMat(), opMat;
    Vec shift = {0, 0, 0}, opVec, newShift, normal;
    string op;
    for (i = 0; i < t; i++) {
        cin >> op;
        if (op == "TRANSLATE") {
            cin >> opVec.x >> opVec.y >> opVec.z;
            opMat = eyeMat();
            newShift = mulVec(opMat, shift);
            newShift.x += opVec.x;
            newShift.y += opVec.y;
            newShift.z += opVec.z;
            shift = newShift;
        } else if (op == "ROTATE") {
            int deg;
            cin >> opVec.x >> opVec.y >> opVec.z >> deg;
            opMat = rotMat(opVec.x, opVec.y, opVec.z, deg);
            mat = mulMat(opMat, mat);
            invTrans = mulMat(opMat, invTrans);
            shift = mulVec(opMat, shift);
        } else {
            long double sx, sy, sz;
            cin >> sx >> sy >> sz;
            opMat = {};
            opMat.a[0][0] = sx;
            opMat.a[1][1] = sy;
            opMat.a[2][2] = sz;
            mat = mulMat(opMat, mat);
            for (j = 0; j < 3; j++) {
                invTrans.a[0][j] /= sx;
                invTrans.a[1][j] /= sy;
                invTrans.a[2][j] /= sz;
            }
            shift = mulVec(opMat, shift);
        }
    }
    cout << fixed << setprecision(2);
    for (i = 0; i < n; i++) {
        points[i] = mulVec(mat, points[i]);
        points[i].x += shift.x;
        points[i].y += shift.y;
        points[i].z += shift.z;
        cout << points[i].x << ' ' << points[i].y << ' ' << points[i].z << '\n';
    }
    for (i = 0; i < m; i++) {
        normal.x = planes[i][0];
        normal.y = planes[i][1];
        normal.z = planes[i][2];
        normal = mulVec(invTrans, normal);
        long double len = sqrtl(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        long double d = planes[i][3] - (normal.x * shift.x + normal.y * shift.y + normal.z * shift.z);
        cout << normal.x / len << ' ' << normal.y / len << ' ' << normal.z / len << ' ' << d / len << '\n';
    }
    return 0;
}
