#include <bits/stdc++.h>
using namespace std;

int roomSize;
long long limitK;

long long floorDiv(long long a, long long b) {
    if (a >= 0) return a / b;
    return -((-a + b - 1) / b);
}

long long ceilDiv(long long a, long long b) {
    return -floorDiv(-a, b);
}

long long exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcdValue = exGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return gcdValue;
}

long long getMaxDot(int a, int b) {
    if (1LL * roomSize * (a + b) <= limitK) return -1;
    if (a == 0 || b == 0) return -1;
    long long x, y;
    if (exGcd(a, b, x, y) != 1) return -1;
    long long maxDot = -1;
    for (int sign = -1; sign <= 1; sign += 2) {
        long long c0 = -1LL * sign * y, d0 = 1LL * sign * x;
        long long lowT = max(ceilDiv(-c0, a), ceilDiv(-d0, b));
        long long highT = min(floorDiv(roomSize - c0, a), floorDiv(roomSize - d0, b));
        if (lowT > highT) continue;
        long long c = c0 + highT * a, d = d0 + highT * b;
        maxDot = max(maxDot, 1LL * a * c + 1LL * b * d);
    }
    return maxDot;
}

bool isTroublesome(int a, int b) {
    return getMaxDot(a, b) > limitK;
}

void solve() {
    long long answer = 0;
    long long minSum = limitK / roomSize + 1;
    for (int x = 0; x <= roomSize; x++) {
        long long startY = max(0LL, max(minSum - x, minSum - (roomSize - x)));
        if (startY > roomSize) continue;
        for (int y = static_cast<int>(startY); y <= roomSize; y++) {
            if (y == 0 && (x == 0 || x == roomSize)) continue;
            if (isTroublesome(x, y) && isTroublesome(roomSize - x, y)) answer++;
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    while (testCases--) {
        cin >> roomSize >> limitK;
        solve();
    }
    return 0;
}
