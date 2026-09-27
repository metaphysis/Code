// Charles Frédéric Gros
// UVa ID: 1140
// Verdict: Wrong Answer
// Submission Date: 2026-09-27
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<bool> getPrime(int limit) {
    vector<bool> isPrime(limit + 1, true);
    if (limit >= 0)
        isPrime[0] = false;
    if (limit >= 1)
        isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= limit; ++i) {
        if (!isPrime[i])
            continue;
        for (int j = i * i; j <= limit; j += i)
            isPrime[j] = false;
    }
    return isPrime;
}

vector<bool> getEligible(int dMin, int dMax) {
    int count = (dMax - dMin) / 4 + 1;
    vector<bool> eligible(count, true);
    int limit = sqrt(dMax);
    vector<bool> isPrime = getPrime(limit);
    for (int p = 3; p <= limit; p += 2) {
        if (!isPrime[p])
            continue;
        long long square = 1LL * p * p;
        long long inverse = (3 * square + 1) / 4;
        long long residue = (square - (1LL * (dMin % square) * inverse) % square) % square;
        for (long long index = residue; index < count; index += square)
            eligible[index] = false;
    }
    return eligible;
}

vector<int> getClassNumbers(int dMin, int dMax, const vector<bool> &eligible) {
    int count = (dMax - dMin) / 4 + 1;
    vector<int> classNumbers(count, 0);
    int maxA = sqrt(dMax / 3.0);
    while (3LL * (maxA + 1) * (maxA + 1) <= dMax)
        ++maxA;
    while (3LL * maxA * maxA > dMax)
        --maxA;
    for (int a = 1; a <= maxA; ++a) {
        for (int b = 1; b <= a; b += 2) {
            long long bSquare = 1LL * b * b;
            long long cMin = max(1LL * a, (dMin + bSquare + 4LL * a - 1) / (4LL * a));
            long long cMax = (dMax + bSquare) / (4LL * a);
            if (cMin > cMax)
                continue;
            for (long long c = cMin; c <= cMax; ++c) {
                long long d = 4LL * a * c - bSquare;
                if (d < dMin || d > dMax)
                    continue;
                int index = (d - dMin) / 4;
                if (!eligible[index])
                    continue;
                if (a < c && b < a)
                    classNumbers[index] += 2;
                else
                    ++classNumbers[index];
            }
        }
    }
    return classNumbers;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int dMin, dMax, k;
    bool firstCase = true;
    while (cin >> dMin >> dMax >> k) {
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        vector<bool> eligible = getEligible(dMin, dMax);
        vector<int> classNumbers = getClassNumbers(dMin, dMax, eligible);
        int count = (dMax - dMin) / 4 + 1;
        vector<int> squareRoots(count);
        int root = sqrt(dMin);
        for (int i = 0; i < count; ++i) {
            int d = dMin + 4 * i;
            while (1LL * (root + 1) * (root + 1) <= d)
                ++root;
            while (1LL * root * root > d)
                --root;
            squareRoots[i] = root;
        }
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (!eligible[i])
                continue;
            int d = dMin + 4 * i;
            int h = classNumbers[i];
            int f = 1000 * h / squareRoots[i];
            if (f < k)
                continue;
            cout << d << ' ' << h << ' ' << f << '\n';
            found = true;
        }
        if (!found)
            cout << "empty\n";
    }
    return 0;
}
