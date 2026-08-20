#include <bits/stdc++.h>
using namespace std;

long long fastPower(long long base, long long exponent, long long mod) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

int decodeCharacter(char character) {
    if (character == '*') return 0;
    return character - 'a' + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    while (testCases--) {
        int p;
        string message;
        cin >> p >> message;
        int n = message.size();
        vector<long long> values(n);
        for (int i = 0; i < n; ++i) values[i] = decodeCharacter(message[i]);
        vector<long long> answer(n, 0);
        for (int j = 1; j <= n; ++j) {
            vector<long long> basis(n, 0);
            basis[0] = 1;
            int degree = 0;
            long long denominator = 1;
            for (int i = 1; i <= n; ++i) {
                if (i == j) continue;
                denominator = denominator * (j - i) % p;
                vector<long long> nextBasis(n, 0);
                for (int k = 0; k <= degree; ++k) {
                    nextBasis[k] = (nextBasis[k] - basis[k] * i) % p;
                    nextBasis[k + 1] = (nextBasis[k + 1] + basis[k]) % p;
                }
                basis = nextBasis;
                ++degree;
            }
            if (denominator < 0) denominator += p;
            long long inverse = fastPower(denominator, p - 2, p);
            long long factor = values[j - 1] * inverse % p;
            for (int k = 0; k <= degree; ++k) {
                answer[k] = (answer[k] + basis[k] * factor) % p;
                if (answer[k] < 0) answer[k] += p;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
    return 0;
}
