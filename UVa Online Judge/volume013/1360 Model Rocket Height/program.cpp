#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
int shotCount;
double hA, hB, alpha, beta, gma, delta;

int solve() {
    double aRad, bRad, gRad, dRad, aX, aY, aZ, bX, bY, bZ, dX, dY, dZ, uX, uY, uZ, vX, vY, vZ, dotUv, dotDu, dotDv, denominator, t, s, pointAX, pointAY, pointAZ, pointBX, pointBY, pointBZ, midZ;
    aRad = alpha * pi / 180.0;
    bRad = beta * pi / 180.0;
    gRad = gma * pi / 180.0;
    dRad = delta * pi / 180.0;
    aX = 0.0;
    aY = 0.0;
    aZ = hA;
    bX = 100.0;
    bY = 0.0;
    bZ = hB;
    dX = aX - bX;
    dY = aY - bY;
    dZ = aZ - bZ;
    uX = cos(aRad) * cos(gRad);
    uY = cos(aRad) * sin(gRad);
    uZ = sin(aRad);
    vX = cos(bRad) * cos(dRad);
    vY = cos(bRad) * sin(dRad);
    vZ = sin(bRad);
    dotUv = uX * vX + uY * vY + uZ * vZ;
    dotDu = dX * uX + dY * uY + dZ * uZ;
    dotDv = dX * vX + dY * vY + dZ * vZ;
    denominator = 1.0 - dotUv * dotUv;
    t = (dotUv * dotDv - dotDu) / denominator;
    s = (dotDv - dotUv * dotDu) / denominator;
    pointAX = aX + t * uX;
    pointAY = aY + t * uY;
    pointAZ = aZ + t * uZ;
    pointBX = bX + s * vX;
    pointBY = bY + s * vY;
    pointBZ = bZ + s * vZ;
    midZ = (pointAZ + pointBZ) / 2.0;
    return (int)floor(midZ + 0.5);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> shotCount >> hA >> hB;
    for (int shotId = 1; shotId <= shotCount; shotId++) {
        cin >> alpha >> beta >> gma >> delta;
        cout << shotId << ": " << solve() << '\n';
    }
    return 0;
}
