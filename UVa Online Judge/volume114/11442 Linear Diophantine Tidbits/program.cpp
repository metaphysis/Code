#include <bits/stdc++.h>
using namespace std;

long long gcdVal(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long edgeGcd(long long x, long long y, long long z) {
    return gcdVal(abs(x), gcdVal(abs(y), abs(z)));
}

__int128 distVal(long long a[3], long long b[3]) {
    long long x = a[0] - b[0], y = a[1] - b[1], z = a[2] - b[2];
    return (__int128)x * x + (__int128)y * y + (__int128)z * z;
}

long long countSol(long long p[3][3]) {
    long long ux = p[1][0] - p[0][0], uy = p[1][1] - p[0][1], uz = p[1][2] - p[0][2];
    long long vx = p[2][0] - p[0][0], vy = p[2][1] - p[0][1], vz = p[2][2] - p[0][2];
    long long crX = uy * vz - uz * vy, crY = uz * vx - ux * vz, crZ = ux * vy - uy * vx;
    long long area = edgeGcd(crX, crY, crZ);
    if (area == 0) {
        int a = 0, b = 1, i, j;
        __int128 best = distVal(p[0], p[1]);
        for (i = 0; i < 3; i++)
            for (j = i + 1; j < 3; j++)
                if (distVal(p[i], p[j]) > best) {
                    best = distVal(p[i], p[j]);
                    a = i;
                    b = j;
                }
        return edgeGcd(p[a][0] - p[b][0], p[a][1] - p[b][1], p[a][2] - p[b][2]) + 1;
    }
    long long bnd = edgeGcd(p[0][0] - p[1][0], p[0][1] - p[1][1], p[0][2] - p[1][2]);
    bnd += edgeGcd(p[1][0] - p[2][0], p[1][1] - p[2][1], p[1][2] - p[2][2]);
    bnd += edgeGcd(p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2]);
    return (area + bnd + 2) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, i, j;
    long long p[3][3];
    cin >> n;
    while (n--) {
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                cin >> p[i][j];
        cout << countSol(p) << '\n';
    }
    return 0;
}
