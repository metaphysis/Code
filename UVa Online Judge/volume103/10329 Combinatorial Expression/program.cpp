// Combinatorial Expression
// UVa ID: 10329
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int MAX_N = 5000;

vector<int> primes;
vector<vector<int>> factorialExponents;

void generatePrimesAndFactorials() {
    vector<bool> isPrime(MAX_N + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAX_N; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= MAX_N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    factorialExponents.resize(MAX_N + 1, vector<int>(primes.size(), 0));
    for (int n = 2; n <= MAX_N; n++) {
        factorialExponents[n] = factorialExponents[n - 1];
        int temp = n;
        for (size_t i = 0; i < primes.size() && primes[i] <= temp; i++) {
            int p = primes[i];
            while (temp % p == 0) {
                factorialExponents[n][i]++;
                temp /= p;
            }
        }
    }
}

vector<int> factorizeNcr(int n, int r) {
    vector<int> exp = factorialExponents[n];
    vector<int> expR = factorialExponents[r];
    vector<int> expNR = factorialExponents[n - r];
    
    for (size_t i = 0; i < primes.size(); i++) {
        exp[i] -= (expR[i] + expNR[i]);
    }
    return exp;
}

string multiplyBigInt(const vector<int>& exp) {
    double logSum = 0.0;
    for (size_t i = 0; i < exp.size(); i++) {
        if (exp[i] > 0) {
            logSum += exp[i] * log10(primes[i]);
        }
    }
    
    int estimatedDigits = (int)logSum + 1;
    
    if (estimatedDigits > 100) {
        return "-1";
    }
    
    int maxDigits = 150;
    vector<int> digits(maxDigits, 0);
    digits[0] = 1;
    int length = 1;
    
    for (size_t i = 0; i < exp.size(); i++) {
        if (exp[i] == 0) continue;
        
        int p = primes[i];
        for (int e = 0; e < exp[i]; e++) {
            int carry = 0;
            for (int j = 0; j < length; j++) {
                long long prod = digits[j] * (long long)p + carry;
                digits[j] = prod % 10;
                carry = prod / 10;
            }
            
            while (carry > 0 && length < maxDigits) {
                digits[length] = carry % 10;
                carry /= 10;
                length++;
            }
            
            if (length >= maxDigits && carry > 0) {
                return "-1";
            }
        }
    }
    
    string result;
    for (int i = length - 1; i >= 0; i--) {
        result += to_string(digits[i]);
    }
    
    if (result.length() > 100) {
        return "-1";
    }
    
    return result;
}

int main() {
    generatePrimesAndFactorials();
    int N, M;
    
    while (cin >> N >> M) {
        vector<int> numerator(primes.size(), 0);
        vector<int> denominator(primes.size(), 0);

        for (int i = 0; i < N; i++) {
            int n, r;
            cin >> n >> r;
            vector<int> exp = factorizeNcr(n, r);
            for (size_t j = 0; j < primes.size(); j++) {
                numerator[j] += exp[j];
            }
        }

        for (int i = 0; i < M; i++) {
            int n, r;
            cin >> n >> r;
            vector<int> exp = factorizeNcr(n, r);
            for (size_t j = 0; j < primes.size(); j++) {
                denominator[j] += exp[j];
            }
        }

        bool isInteger = true;
        vector<int> resultExp(primes.size(), 0);
        for (size_t i = 0; i < primes.size(); i++) {
            resultExp[i] = numerator[i] - denominator[i];
            if (resultExp[i] < 0) {
                isInteger = false;
                break;
            }
        }

        if (!isInteger) {
            cout << 0 << endl;
        } else {
            string resultStr = multiplyBigInt(resultExp);
            cout << resultStr << endl;
        }
    }
    
    return 0;
}
