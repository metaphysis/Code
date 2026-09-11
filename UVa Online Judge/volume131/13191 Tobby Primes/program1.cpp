// Tobby Primes
// UVa ID: 13191
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.560s

#include <bits/stdc++.h>
using namespace std;

using unsignedLongLong = unsigned long long;
using unsignedInt128 = __uint128_t;

unsignedLongLong gcdValue(unsignedLongLong firstValue, unsignedLongLong secondValue) {
    while (secondValue != 0) {
        unsignedLongLong remainder = firstValue % secondValue;
        firstValue = secondValue;
        secondValue = remainder;
    }
    return firstValue;
}

unsignedLongLong modularMultiply(unsignedLongLong firstValue, unsignedLongLong secondValue, unsignedLongLong modulus) {
    return static_cast<unsignedLongLong>(static_cast<unsignedInt128>(firstValue) * secondValue % modulus);
}

unsignedLongLong modularPower(unsignedLongLong baseValue, unsignedLongLong exponentValue, unsignedLongLong modulus) {
    unsignedLongLong resultValue = 1;
    baseValue %= modulus;
    while (exponentValue > 0) {
        if (exponentValue & 1) resultValue = modularMultiply(resultValue, baseValue, modulus);
        baseValue = modularMultiply(baseValue, baseValue, modulus);
        exponentValue >>= 1;
    }
    return resultValue;
}

bool isPrime(unsignedLongLong numberValue) {
    if (numberValue < 2) return false;
    for (unsignedLongLong primeValue : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (numberValue % primeValue == 0) return numberValue == primeValue;
    }
    unsignedLongLong oddPart = numberValue - 1;
    int powerOfTwo = 0;
    while ((oddPart & 1) == 0) {
        oddPart >>= 1;
        ++powerOfTwo;
    }
    for (unsignedLongLong baseValue : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (baseValue % numberValue == 0) continue;
        unsignedLongLong currentValue = modularPower(baseValue, oddPart, numberValue);
        if (currentValue == 1 || currentValue == numberValue - 1) continue;
        bool passedTest = false;
        for (int repeatCount = 1; repeatCount < powerOfTwo; ++repeatCount) {
            currentValue = modularMultiply(currentValue, currentValue, numberValue);
            if (currentValue == numberValue - 1) {
                passedTest = true;
                break;
            }
        }
        if (!passedTest) return false;
    }
    return true;
}

unsignedLongLong pollardRho(unsignedLongLong numberValue) {
    if (numberValue % 2 == 0) return 2;
    if (numberValue % 3 == 0) return 3;
    static mt19937_64 randomEngine(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        uniform_int_distribution<unsignedLongLong> valueDistribution(2, numberValue - 2);
        uniform_int_distribution<unsignedLongLong> constantDistribution(1, numberValue - 1);
        unsignedLongLong currentValue = valueDistribution(randomEngine);
        unsignedLongLong nextValue = currentValue;
        unsignedLongLong constantValue = constantDistribution(randomEngine);
        unsignedLongLong divisorValue = 1;
        while (divisorValue == 1) {
            currentValue = (modularMultiply(currentValue, currentValue, numberValue) + constantValue) % numberValue;
            nextValue = (modularMultiply(nextValue, nextValue, numberValue) + constantValue) % numberValue;
            nextValue = (modularMultiply(nextValue, nextValue, numberValue) + constantValue) % numberValue;
            unsignedLongLong differenceValue = currentValue > nextValue ? currentValue - nextValue : nextValue - currentValue;
            divisorValue = gcdValue(differenceValue, numberValue);
        }
        if (divisorValue != numberValue) return divisorValue;
    }
}

void factorNumber(unsignedLongLong numberValue, vector<unsignedLongLong>& primeFactors) {
    if (numberValue == 1) return;
    if (isPrime(numberValue)) {
        primeFactors.push_back(numberValue);
        return;
    }
    unsignedLongLong divisorValue = pollardRho(numberValue);
    factorNumber(divisorValue, primeFactors);
    factorNumber(numberValue / divisorValue, primeFactors);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        unsignedLongLong numberValue;
        cin >> numberValue;
        vector<unsignedLongLong> primeFactors;
        factorNumber(numberValue, primeFactors);
        sort(primeFactors.begin(), primeFactors.end());
        for (size_t index = 0; index < primeFactors.size(); ++index) {
            if (index > 0) cout << ' ';
            cout << primeFactors[index];
        }
        cout << '\n';
    }
    return 0;
}
