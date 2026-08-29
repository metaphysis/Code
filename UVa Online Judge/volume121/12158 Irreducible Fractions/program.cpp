#include <bits/stdc++.h>
using namespace std;

const long long maxValue = 10000000;

long long gcdValue(long long a, long long b) {
    while (b != 0)
        a %= b, swap(a, b);
    return a;
}

long long extGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long nextX, nextY, result;
    result = extGcd(b, a % b, nextX, nextY);
    x = nextY;
    y = nextX - (a / b) * nextY;
    return result;
}

long long floorDiv(long long a, long long b) {
    if (a >= 0)
        return a / b;
    return -((-a + b - 1) / b);
}

long long ceilDiv(long long a, long long b) {
    if (a >= 0)
        return (a + b - 1) / b;
    return -((-a) / b);
}

long long countEquation(long long u, long long v, long long c) {
    if (v == 0)
        return c == 1 ? maxValue + 1 : 0;
    long long inv, temp, x0, y0, low, high;
    extGcd(u, v, inv, temp);
    inv = (inv % v + v) % v;
    x0 = ((c % v + v) % v * inv) % v;
    y0 = (u * x0 - c) / v;
    low = max(0LL, ceilDiv(-y0, u));
    high = min((maxValue - x0) / v, floorDiv(maxValue - y0, u));
    if (low > high)
        return 0;
    return high - low + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, g, u, v, answer;
    while (cin >> a >> b && (a != 0 || b != 0)) {
        if (a == 0 || b == 0) {
            cout << maxValue + 1 << '\n';
            continue;
        }
        g = gcdValue(a, b);
        u = b / g;
        v = a / g;
        answer = countEquation(u, v, 1) + countEquation(u, v, -1);
        cout << answer << '\n';
    }
    return 0;
}
