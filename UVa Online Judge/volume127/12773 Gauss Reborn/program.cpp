#include <bits/stdc++.h>
using namespace std;

const long long mod = 71211919;

struct Data {
    int n;
    vector<int> spf;
    vector<long long> c, sc, dc, sumC, sumSc, sumDc;
};

Data buildData(int n) {
    Data data;
    data.n = n;
    data.spf.assign(n + 1, 0);
    data.c.assign(n + 1, 0);
    data.sc.assign(n + 1, 0);
    data.dc.assign(n + 1, 0);
    data.sumC.assign(n + 1, 0);
    data.sumSc.assign(n + 1, 0);
    data.sumDc.assign(n + 1, 0);
    vector<int> mu(n + 1), primes;
    vector<bool> isComp(n + 1, false);
    mu[1] = 1;
    data.spf[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isComp[i]) {
            primes.push_back(i);
            mu[i] = -1;
            data.spf[i] = i;
        }
        for (int p : primes) {
            if (1LL * i * p > n)
                break;
            isComp[i * p] = true;
            data.spf[i * p] = p;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    for (int e = 1; e <= n; e++) {
        if (mu[e] == 0)
            continue;
        long long count = n / e;
        long long x = count % mod;
        long long sum = e * x % mod;
        sum = sum * ((count + 1) % mod) % mod;
        sum = sum * ((mod + 1) / 2) % mod;
        for (int d = e; d <= n; d += e) {
            data.c[d] = (data.c[d] + mu[e] * x) % mod;
            data.sc[d] = (data.sc[d] + mu[e] * sum) % mod;
            if (data.c[d] < 0)
                data.c[d] += mod;
            if (data.sc[d] < 0)
                data.sc[d] += mod;
        }
    }
    for (int d = 1; d <= n; d++)
        data.dc[d] = d * data.c[d] % mod;
    for (int q = 1; q <= n; q++) {
        for (int d = q; d <= n; d += q) {
            data.sumC[q] += data.c[d];
            data.sumSc[q] += data.sc[d];
            data.sumDc[q] += data.dc[d];
            if (data.sumC[q] >= mod)
                data.sumC[q] -= mod;
            if (data.sumSc[q] >= mod)
                data.sumSc[q] -= mod;
            if (data.sumDc[q] >= mod)
                data.sumDc[q] -= mod;
        }
    }
    return data;
}

long long getCoprimeSum(int k, const vector<long long>& values, const vector<int>& spf) {
    vector<int> primes;
    int value = k;
    while (value > 1) {
        int p = spf[value];
        primes.push_back(p);
        while (value % p == 0)
            value /= p;
    }
    int subsetCount = 1 << primes.size();
    long long result = 0;
    for (int mask = 0; mask < subsetCount; mask++) {
        int divisor = 1, bitCount = 0;
        for (int i = 0; i < static_cast<int>(primes.size()); i++) {
            if (mask & (1 << i)) {
                divisor *= primes[i];
                bitCount++;
            }
        }
        if (bitCount & 1)
            result -= values[divisor];
        else
            result += values[divisor];
    }
    result %= mod;
    if (result < 0)
        result += mod;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseId = 1; caseId <= T; caseId++) {
        int n, m;
        cin >> n >> m;
        vector<int> queries(m);
        for (int i = 0; i < m; i++)
            cin >> queries[i];
        Data data = buildData(n);
        cout << "Case " << caseId << ":\n";
        for (int k : queries) {
            long long countD = getCoprimeSum(k, data.sumC, data.spf);
            long long sumCD = getCoprimeSum(k, data.sumSc, data.spf);
            long long sumDCD = getCoprimeSum(k, data.sumDc, data.spf);
            long long tupleCount = data.c[k] * countD % mod;
            long long sumA = data.sc[k] * countD % mod;
            long long sumB = k * tupleCount % mod;
            long long sumC = data.c[k] * sumCD % mod;
            long long sumD = data.c[k] * sumDCD % mod;
            cout << tupleCount << " " << sumA << " " << sumB << " " << sumC << " " << sumD << "\n";
        }
    }
    return 0;
}
