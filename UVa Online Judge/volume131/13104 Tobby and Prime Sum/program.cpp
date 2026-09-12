// Tobby and Prime Sum
// UVa ID: 13104
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxLen = 505;
const int maxSum = 9 * maxLen;

int primeWays[maxLen][maxSum + 1];
bool isPrime[maxSum + 1];

string decOne(string num) {
    int pos = num.size() - 1;
    while (pos >= 0 && num[pos] == '0') {
        num[pos] = '9';
        pos--;
    }
    if (pos >= 0) num[pos]--;
    int start = 0;
    while (start + 1 < (int)num.size() && num[start] == '0') start++;
    return num.substr(start);
}

void init() {
    fill(isPrime, isPrime + maxSum + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= maxSum; i++)
        if (isPrime[i])
            for (int j = i * i; j <= maxSum; j += i)
                isPrime[j] = false;
    for (int sum = 0; sum <= maxSum; sum++)
        primeWays[0][sum] = isPrime[sum];
    for (int len = 1; len < maxLen; len++)
        for (int sum = 0; sum + 9 * len <= maxSum; sum++)
            for (int digit = 0; digit <= 9; digit++)
                primeWays[len][sum] = (primeWays[len][sum] + primeWays[len - 1][sum + digit]) % mod;
}

int countPrime(const string &num) {
    if (num == "0") return 0;
    int ans = 0, prefix = 0, len = num.size();
    for (int i = 0; i < len; i++) {
        int cur = num[i] - '0';
        int remain = len - i - 1;
        for (int digit = 0; digit < cur; digit++) {
            int sum = prefix + digit;
            ans += primeWays[remain][sum];
            if (ans >= mod) ans -= mod;
        }
        prefix += cur;
    }
    if (isPrime[prefix]) {
        ans++;
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    string left, right;
    while (cin >> left >> right) {
        string before = decOne(left);
        int ans = countPrime(right) - countPrime(before);
        if (ans < 0) ans += mod;
        cout << ans << '\n';
    }
    return 0;
}
