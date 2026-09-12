#include <bits/stdc++.h>
using namespace std;

long long floorSum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    while (true) {
        if (a >= m) {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        long long yMax = a * n + b;
        if (yMax < m)
            break;
        n = yMax / m;
        b = yMax % m;
        swap(m, a);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int maxLimit = 100000;
    vector<int> mu(maxLimit + 1), primes;
    vector<bool> isComposite(maxLimit + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= maxLimit; ++i) {
        if (!isComposite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0; j < static_cast<int>(primes.size()) && i * primes[j] <= maxLimit; ++j) {
            int value = i * primes[j];
            isComposite[value] = true;
            if (i % primes[j] == 0) {
                mu[value] = 0;
                break;
            }
            mu[value] = -mu[i];
        }
    }
    int n, a, maxV, caseId = 1;
    while (cin >> n >> a >> maxV) {
        if (n == 0 && a == 0 && maxV == 0)
            break;
        int b = n - a;
        long long total = floorSum(maxV, n, b, b) + maxV;
        long long coprime = 0;
        for (int d = 1; d <= maxV; ++d) {
            int limit = maxV / d;
            long long count = floorSum(limit, n, b, b) + limit;
            coprime += 1LL * mu[d] * count;
        }
        cout << "Case " << caseId++ << ": " << coprime << " " << total << '\n';
    }
    return 0;
}
