// Next Same-Factored
// UVa ID: 11099
// Verdict: Accepted
// Submission Date: 2023-04-21
// UVa Run Time: 0.150s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int primes[1010], cnt = 0;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    for (int i = 2; i < 1001; i++) {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < 1001; j++) {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    int n;
    while (cin >> n) {
        if (n == 1) { cout << "Not Exist!\n"; continue; }
        int nn = n;
        set<int> p;
        for (int i = 0; i < cnt; i++)
            while (nn % primes[i] == 0) {
                p.insert(primes[i]);
                nn /= primes[i];
            }
        if (nn > 1) p.insert(nn);
        long long r = 1LL;
        for (auto v : p) r *= v;
        priority_queue<long long, vector<long long>, greater<long long>> q;
        q.push(r);
        r = -1;
        while (!q.empty()) {
            long long u = q.top(); q.pop();
            if (u > n) { r = u; break; }
            for (auto v : p)
                if (u * v < 2000000LL)
                    q.push(u * v);
        }
        if (r == -1) cout << "Not Exist!\n";
        else cout << r << '\n';
    }
    return 0;
}
