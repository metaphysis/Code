// Charles Frédéric Gros
// UVa ID: 1140
// Verdict: Accepted
// Submission Date: 2026-10-03
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long SQUARE_CHECK_LIMIT = 10000;

long long getSqrt(long long x) {
    long long y = sqrt(x);
    while (1LL * (y + 1) * (y + 1) <= x) ++y;
    while (1LL * y * y > x) --y;
    return y;
}

vector<int> getPrimes(int limit) {
    vector<char> composite(limit + 1, false);
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (composite[i]) continue;
        primes.push_back(i);
        if (1LL * i * i <= limit)
            for (int j = i * i; j <= limit; j += i)
                composite[j] = true;
    }
    return primes;
}

vector<char> getBad(long long left, long long right, const vector<int> &primes) {
    if (left > right) return {};
    vector<char> bad(right - left + 1, false);
    for (int p : primes) {
        long long square = 1LL * p * p;
        if (square > right) break;
        long long start = (left + square - 1) / square * square;
        for (long long value = start; value <= right; ) {
            bad[value - left] = true;
            if (value > right - square) break;
            value += square;
        }
    }
    return bad;
}

long long getSquareFreePart(long long x, const vector<int> &primes) {
    long long result = 1;
    for (int p : primes) {
        long long prime = p;
        if (prime * prime > x)
            break;
        int exponent = 0;
        while (x % prime == 0) {
            x /= prime;
            ++exponent;
        }
        if (exponent & 1) result *= prime;
    }
    if (x > 1) result *= x;
    return result;
}

int getClassNumber(long long d) {
    int answer = 0;
    long long maxA = getSqrt(d / 3);
    for (long long a = 1; a <= maxA; ++a) {
        long long minValue = 4LL * a * a - d;
        long long minB = 1;
        if (minValue > 0) {
            minB = getSqrt(minValue);
            if (1LL * minB * minB < minValue)
                ++minB;
        }
        if ((minB & 1LL) == 0) ++minB;
        for (long long b = minB; b <= a; b += 2) {
            long long value = d + b * b;
            long long divisor = 4LL * a;
            if (value % divisor != 0) continue;
            long long c = value / divisor;
            if (c < a) continue;
            if (a == b || a == c) ++answer;
            else answer += 2;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long dMin, dMax, k;
    vector<int> primes = getPrimes(46340);
    unordered_map<long long, int> classCache;
    classCache.reserve(4096);
    bool firstCase = true;
    while (cin >> dMin >> dMax >> k) {
        long long checkedRight = min(dMax, SQUARE_CHECK_LIMIT - 1);
        vector<char> bad;
        if (dMin <= checkedRight) bad = getBad(dMin, checkedRight, primes);
        if (!firstCase) cout << '\n';
        firstCase = false;
        bool found = false;
        for (long long d = dMin; d <= dMax; d += 4) {
            if (d < SQUARE_CHECK_LIMIT && bad[d - dMin]) continue;
            long long classArgument;
            if (d < SQUARE_CHECK_LIMIT) classArgument = d;
            else classArgument = getSquareFreePart(d, primes);
            int h;
            auto it = classCache.find(classArgument);
            if (it != classCache.end()) h = it->second;
            else {
                h = getClassNumber(classArgument);
                classCache.emplace(classArgument, h);
            }
            long long root = getSqrt(d);
            long long f = 1000LL * h / root;
            if (f < k) continue;
            cout << d << ' ' << h << ' ' << f << '\n';
            found = true;
        }
        if (!found) cout << "empty\n";
    }
    return 0;
}
