#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct Congruence {
    bool valid;
    int64 rem, mod;
};

int64 modNorm(int64 value, int64 mod) {
    value %= mod;
    if (value < 0) value += mod;
    return value;
}

int64 exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int64 nextX, nextY, gcdValue = exgcd(b, a % b, nextX, nextY);
    x = nextY;
    y = nextX - a / b * nextY;
    return gcdValue;
}

int64 inverseMod(int64 value, int64 mod) {
    if (mod == 1) return 0;
    int64 x, y;
    exgcd(modNorm(value, mod), mod, x, y);
    return modNorm(x, mod);
}

int64 floorDiv(int64 value, int64 divisor) {
    if (value >= 0) return value / divisor;
    return -((-value + divisor - 1) / divisor);
}

Congruence solveAxis(int64 coef, int64 target, int64 mod) {
    if (coef == 0) {
        if (modNorm(target, mod) != 0) return {false, 0, 1};
        return {true, 0, 1};
    }
    int64 gcdValue = __gcd(abs(coef), mod);
    if (target % gcdValue != 0) return {false, 0, 1};
    int64 newMod = mod / gcdValue;
    if (newMod == 1) return {true, 0, 1};
    int64 value = coef / gcdValue, right = target / gcdValue;
    int64 rem = (__int128)modNorm(right, newMod) * inverseMod(value, newMod) % newMod;
    return {true, rem, newMod};
}

Congruence mergeCongruence(Congruence first, Congruence second) {
    if (!first.valid || !second.valid) return {false, 0, 1};
    int64 gcdValue = __gcd(first.mod, second.mod), diff = second.rem - first.rem;
    if (diff % gcdValue != 0) return {false, 0, 1};
    int64 unit = second.mod / gcdValue;
    int64 step = 0;
    if (unit != 1) {
        int64 value = first.mod / gcdValue, right = diff / gcdValue;
        step = (__int128)modNorm(right, unit) * inverseMod(value, unit) % unit;
    }
    int64 lcmValue = first.mod / gcdValue * second.mod;
    int64 rem = (first.rem + (__int128)first.mod * step) % lcmValue;
    return {true, rem, lcmValue};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 s, x1, y1, x2, y2;
    int caseId = 0;
    while (cin >> s >> x1 >> y1 >> x2 >> y2) {
        if (s == 0 && x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) break;
        int64 dx = x2 - x1, dy = y2 - y1, gcdValue = __gcd(abs(dx), abs(dy));
        int64 a = dx / gcdValue, b = dy / gcdValue, mod = 2 * s;
        int64 bestTime = LLONG_MAX;
        for (int sx : {0, 1}) {
            for (int sy : {0, 1}) {
                int64 targetX = sx == 0 ? 0 : -2 * x1;
                int64 targetY = sy == 0 ? 0 : -2 * y1;
                Congruence xCon = solveAxis(a, targetX, mod);
                Congruence yCon = solveAxis(b, targetY, mod);
                Congruence result = mergeCongruence(xCon, yCon);
                if (!result.valid) continue;
                int64 time = result.rem;
                if (time == 0) time = result.mod;
                bestTime = min(bestTime, time);
            }
        }
        int64 endX = x1 + a * bestTime, endY = y1 + b * bestTime;
        int64 verticalHits = abs(floorDiv(endX, s));
        int64 horizontalHits = abs(floorDiv(endY, s));
        cout << "Case " << ++caseId << ": " << verticalHits + horizontalHits << '\n';
    }
    return 0;
}
