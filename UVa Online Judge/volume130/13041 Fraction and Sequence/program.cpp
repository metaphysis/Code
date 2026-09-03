#include <bits/stdc++.h>
using namespace std;

long long floorSum(long long n, long long m, long long a, long long b) {
    long long answer = 0;
    while (true) {
        if (a >= m) {
            answer += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            answer += n * (b / m);
            b %= m;
        }
        long long yMax = a * n + b;
        if (yMax < m) break;
        n = yMax / m;
        b = yMax % m;
        swap(m, a);
    }
    return answer;
}

long long sumFloorRange(long long left, long long right, long long base) {
    if (left > right) return 0;
    long long count = right - left + 1;
    long long firstValue = base - 81 * right;
    return floorSum(count, 11, 81, firstValue);
}

long long sumPart(long long k0, long long offset, long long maxT, long long maxI) {
    long long x0 = k0 + offset;
    if (x0 < 0) return 0;
    long long endT = min(maxT, x0 / 81);
    long long answer = 0;
    if (x0 >= 11 * maxI) {
        long long fullEnd = min(endT, (x0 - 11 * maxI) / 81);
        answer += (fullEnd + 1) * (maxI + 1);
        long long left = fullEnd + 1;
        if (left <= endT) {
            answer += sumFloorRange(left, endT, x0) + (endT - left + 1);
        }
    } else {
        answer += sumFloorRange(0, endT, x0) + (endT + 1);
    }
    return answer;
}

long long countCase(long long p, long long q, long long limit) {
    if (729 % q != 0) return 0;
    long long target = 729 / q * p;
    long long a0 = (target % 9 * 5) % 9;
    if (a0 > limit) return 0;
    long long maxI = (limit - a0) / 9;
    long long answer = 0;
    for (long long r = 0; r < 9; r++) {
        if (r > limit) continue;
        long long maxT = (limit - r) / 9;
        long long numerator = target - 81 * r - 11 * a0;
        if (numerator < 0 || numerator % 9 != 0) continue;
        long long k0 = numerator / 9;
        if (k0 < 0) continue;
        maxT = min(maxT, k0 / 81);
        answer += sumPart(k0, 0, maxT, maxI);
        answer -= sumPart(k0, -limit - 1, maxT, maxI);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseIndex = 1; caseIndex <= testCount; caseIndex++) {
        long long p, q, limit;
        cin >> p >> q >> limit;
        cout << "Case " << caseIndex << ": " << countCase(p, q, limit) << '\n';
    }
    return 0;
}
