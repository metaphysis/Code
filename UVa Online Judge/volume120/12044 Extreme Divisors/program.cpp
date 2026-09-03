#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

const int maxN = 1000000;

vector<int> primeList;
vector<bool> isComposite(maxN + 1);
vector<ULL> divSum(maxN + 1);

ULL getRangeSum(ULL leftValue, ULL rightValue) {
    ULL countValue = rightValue - leftValue + 1;
    ULL sumValue = leftValue + rightValue;
    if ((countValue & 1) == 0) countValue /= 2;
    else sumValue /= 2;
    return countValue * sumValue;
}

ULL getDivSum(ULL value) {
    if (value <= maxN) return divSum[(int)value];
    ULL result = 0, leftValue = 1;
    while (leftValue <= value) {
        ULL quotient = value / leftValue, rightValue = value / quotient;
        result += quotient * (rightValue - leftValue + 1);
        leftValue = rightValue + 1;
    }
    return result;
}

ULL getWeightedDivSum(ULL value) {
    ULL result = 0, leftValue = 1;
    while (leftValue <= value) {
        ULL quotient = value / leftValue, rightValue = value / quotient;
        result += quotient * getRangeSum(leftValue, rightValue);
        leftValue = rightValue + 1;
    }
    return result;
}

vector<pair<int, int>> factorize(int value) {
    vector<pair<int, int>> factors;
    for (int primeValue : primeList) {
        if (1LL * primeValue * primeValue > value) break;
        if (value % primeValue != 0) continue;
        int exponent = 0;
        while (value % primeValue == 0) {
            value /= primeValue;
            ++exponent;
        }
        factors.push_back({primeValue, exponent});
    }
    if (value > 1) factors.push_back({value, 1});
    return factors;
}

ULL getDivisorPrefix(ULL value, int kValue) {
    if (value == 0) return 0;
    vector<pair<int, int>> factors = factorize(kValue);
    int factorCount = factors.size(), subsetCount = 1 << factorCount;
    ULL result = 0;
    for (int mask = 0; mask < subsetCount; ++mask) {
        long long coefficient = 1;
        int subsetProduct = 1;
        for (int i = 0; i < factorCount; ++i) {
            int primeValue = factors[i].first, exponent = factors[i].second;
            if ((mask >> i) & 1) {
                coefficient *= -exponent;
                subsetProduct *= primeValue;
            } else {
                coefficient *= exponent + 1;
            }
        }
        result += (ULL)coefficient * getDivSum(value / subsetProduct);
    }
    return result;
}

ULL getSigmaPrefix(ULL value, int kValue) {
    if (value == 0) return 0;
    vector<pair<int, int>> factors = factorize(kValue);
    int factorCount = factors.size(), subsetCount = 1 << factorCount;
    ULL result = 0;
    for (int mask = 0; mask < subsetCount; ++mask) {
        long long coefficient = 1;
        int subsetProduct = 1;
        for (int i = 0; i < factorCount; ++i) {
            int primeValue = factors[i].first, exponent = factors[i].second;
            ULL primePower = 1, sigmaValue = 1;
            for (int j = 0; j < exponent; ++j) {
                primePower *= primeValue;
                sigmaValue += primePower;
            }
            if ((mask >> i) & 1) {
                coefficient *= (long long)(primePower - sigmaValue);
                subsetProduct *= primeValue;
            } else {
                coefficient *= (long long)sigmaValue;
            }
        }
        ULL quotient = value / subsetProduct;
        result += (ULL)coefficient * (ULL)subsetProduct * getWeightedDivSum(quotient);
    }
    return result;
}

void init() {
    for (int value = 2; value <= maxN; ++value) {
        if (!isComposite[value]) primeList.push_back(value);
        for (int primeValue : primeList) {
            if (1LL * value * primeValue > maxN) break;
            isComposite[value * primeValue] = true;
            if (value % primeValue == 0) break;
        }
    }
    for (int divisor = 1; divisor <= maxN; ++divisor)
        for (int multiple = divisor; multiple <= maxN; multiple += divisor)
            ++divSum[multiple];
    for (int value = 1; value <= maxN; ++value)
        divSum[value] += divSum[value - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int testCount;
    cin >> testCount;
    while (testCount--) {
        ULL aValue, bValue;
        int kValue;
        cin >> aValue >> bValue >> kValue;
        ULL leftValue = (aValue + kValue - 1) / kValue;
        ULL rightValue = bValue / kValue;
        if (leftValue > rightValue) {
            cout << 0 << ' ' << 0 << '\n';
            continue;
        }
        ULL divisorAnswer = getDivisorPrefix(rightValue, kValue) - getDivisorPrefix(leftValue - 1, kValue);
        ULL sigmaAnswer = getSigmaPrefix(rightValue, kValue) - getSigmaPrefix(leftValue - 1, kValue);
        cout << divisorAnswer << ' ' << sigmaAnswer << '\n';
    }
    return 0;
}
