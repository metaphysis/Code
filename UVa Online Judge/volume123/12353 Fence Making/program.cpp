// Fence Making
// UVa ID: 12353
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 1.870s

#include <bits/stdc++.h>
using namespace std;

long long calculateHoles(long long radius, long long distance, long long initialLength) {
    const long double pi = acosl(-1.0L);
    long double pitch = 2.0L * (radius + distance);
    if (initialLength < pitch) return 0;
    long double newLength = pi * radius * radius / (2.0L * (radius + distance));
    long double lengthLoss = pitch - newLength;
    long long rowCount = static_cast<long long>(floorl((initialLength - pitch) / lengthLoss)) + 1;
    return rowCount * 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long rMin, rMax, dMin, dMax, s;
    while (cin >> rMin >> rMax >> dMin >> dMax >> s) {
        if (rMin == 0 && rMax == 0 && dMin == 0 && dMax == 0 && s == 0) break;
        long long answer = 0;
        for (long long radius = rMin; radius <= rMax; radius++)
            for (long long distance = dMin; distance <= dMax; distance++)
                answer += calculateHoles(radius, distance, s);
        cout << answer << '\n';
    }
    return 0;
}
