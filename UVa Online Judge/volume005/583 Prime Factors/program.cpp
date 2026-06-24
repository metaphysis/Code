// Prime Factors
// UVa ID: 583
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.330s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 70000;

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int primes[MAXN + 1] = { 0 }, pcnt = 0, fcnt;
    long long int factors[40];
    primes[pcnt++] = 2;
    for (int i = 3; i <= MAXN; i += 2)
        if (primes[i] == 0) {
            for (int j = 2 * i; j <= MAXN; j += i) primes[j] = -1;
            primes[pcnt++] = i;
        }
    long long int n, temp;
    while (cin >> n) {
        if (n == 0) break;
        temp = n;
        bool negative = false;
        if (temp < 0) {
            temp = abs(n);
            negative = true;
        }
        fcnt = 0;
        while (temp > 1) {
            bool divided = false;
            for (int i = 0; i < pcnt; i++)
                if (temp % primes[i] == 0) {
                    factors[fcnt++] = primes[i];
                    temp /= primes[i];
                    divided = true;
                    break;
                }
            if (!divided) {
                factors[fcnt++] = temp;
                break;
            }
        }
        cout << n << " = ";
        if (negative) cout << "-1 x " << factors[0];
        else cout << factors[0];
        for (int i = 1; i < fcnt; i++) cout << " x " << factors[i];
        cout << '\n';
    }
    return 0;
}
