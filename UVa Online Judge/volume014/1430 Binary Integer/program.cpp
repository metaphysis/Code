#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
const int maxSwitch = 10000;
const int maxK = 20;
const int maxN = 40;

int bigComb[maxSwitch + 1][maxK + 1], smallComb[maxN + 1][maxN + 1];

int modPow(int base, int power) {
    int result = 1;
    while (power > 0) {
        if (power & 1) result = result * base % mod;
        base = base * base % mod;
        power >>= 1;
    }
    return result;
}

int getThreeCount(int n) {
    if (n < 3) return 0;
    return n * (n - 1) * (n - 2) / 6;
}

int getCoefficient(int positiveCount, int negativeCount, int k) {
    int result = 0;
    for (int i = 0; i <= k; i++) {
        if (i > positiveCount || k - i > negativeCount) continue;
        int value = bigComb[positiveCount][i] * bigComb[negativeCount][k - i] % mod;
        if ((k - i) & 1) result = (result - value + mod) % mod;
        else result = (result + value) % mod;
    }
    return result;
}

int getCharacterSum(int n, int oneCount, int weight) {
    int result = 0;
    for (int j = 0; j <= weight; j++) {
        if (j > oneCount || weight - j > n - oneCount) continue;
        int value = smallComb[oneCount][j] * smallComb[n - oneCount][weight - j] % mod;
        if (j & 1) result = (result - value + mod) % mod;
        else result = (result + value) % mod;
    }
    return result;
}

int solveCase(int n, int k, const string &s, const string &t) {
    int differentCount = 0;
    for (int i = 0; i < n; i++)
        if (s[i] != t[i]) differentCount++;
    int totalSwitch = getThreeCount(n), result = 0;
    for (int weight = 0; weight <= n; weight++) {
        int negativeCount = weight * getThreeCount(n - weight) / (n - weight == 0 ? 1 : n - weight);
        negativeCount = weight * (n - weight) * (n - weight - 1) / 2 + getThreeCount(weight);
        int positiveCount = totalSwitch - negativeCount;
        int coefficient = getCoefficient(positiveCount, negativeCount, k);
        int characterSum = getCharacterSum(n, differentCount, weight);
        result = (result + coefficient * characterSum) % mod;
    }
    result = (result + mod) % mod;
    result = result * modPow(modPow(2, n), mod - 2) % mod;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i <= maxSwitch; i++) {
        bigComb[i][0] = 1;
        for (int j = 1; j <= maxK; j++) {
            if (i == 0) bigComb[i][j] = 0;
            else bigComb[i][j] = (bigComb[i - 1][j] + bigComb[i - 1][j - 1]) % mod;
        }
    }
    for (int i = 0; i <= maxN; i++) {
        smallComb[i][0] = smallComb[i][i] = 1;
        for (int j = 1; j < i; j++)
            smallComb[i][j] = (smallComb[i - 1][j] + smallComb[i - 1][j - 1]) % mod;
    }
    int n, k, caseNumber = 1;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        string s, t;
        cin >> s >> t;
        cout << "Case #" << caseNumber++ << ": " << solveCase(n, k, s, t) << '\n';
    }
    return 0;
}
