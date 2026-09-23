#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1.0L);

struct Vec {
    long double x, y, z;
};

Vec crossVec(const Vec &a, const Vec &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

long double dotVec(const Vec &a, const Vec &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec scaleVec(const Vec &a, long double k) {
    return {a.x * k, a.y * k, a.z * k};
}

void readStation(Vec &pos, Vec &dir) {
    long double lat, lon, angle;
    char latDir, lonDir;
    cin >> lat >> latDir >> lon >> lonDir >> angle;
    if (latDir == 'S') lat = -lat;
    if (lonDir == 'W') lon = -lon;
    lat = lat * pi / 180.0L;
    lon = lon * pi / 180.0L;
    angle = angle * pi / 180.0L;
    pos = {cosl(lat) * cosl(lon), cosl(lat) * sinl(lon), sinl(lat)};
    Vec north = {-sinl(lat) * cosl(lon), -sinl(lat) * sinl(lon), cosl(lat)}, east = {-sinl(lon), cosl(lon), 0.0L};
    dir = {north.x * cosl(angle) + east.x * sinl(angle), north.y * cosl(angle) + east.y * sinl(angle), north.z * cosl(angle) + east.z * sinl(angle)};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(2);
    while (testCount--) {
        Vec posA, dirA, posB, dirB, target;
        readStation(posA, dirA);
        readStation(posB, dirB);
        target = crossVec(crossVec(posA, dirA), crossVec(posB, dirB));
        target = scaleVec(target, 1.0L / sqrtl(dotVec(target, target)));
        if (dotVec(target, dirA) + dotVec(target, dirB) < 0.0L) target = scaleVec(target, -1.0L);
        long double horizontal = sqrtl(target.x * target.x + target.y * target.y), lat = atan2l(target.z, horizontal) * 180.0L / pi, lon = atan2l(target.y, target.x) * 180.0L / pi;
        if (horizontal < 1e-12L) lon = 0.0L;
        long long latVal = llroundl(fabsl(lat) * 100.0L), lonVal = llroundl(fabsl(lon) * 100.0L);
        char latDir = lat < 0.0L && latVal != 0 ? 'S' : 'N', lonDir = lon > 0.0L && lonVal != 0 && lonVal != 18000 ? 'E' : 'W';
        cout << latVal / 100.0L << ' ' << latDir << ' ' << lonVal / 100.0L << ' ' << lonDir << '\n';
    }
    return 0;
}
