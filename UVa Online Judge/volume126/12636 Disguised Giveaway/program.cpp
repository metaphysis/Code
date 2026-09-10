#include <bits/stdc++.h>
using namespace std;

using unsignedLongLong = unsigned long long;
using signedLongLong = long long;
using unsignedInt128 = __uint128_t;

mt19937_64 randomGenerator(chrono::steady_clock::now().time_since_epoch().count());

signedLongLong getGcd(signedLongLong firstNumber, signedLongLong secondNumber) {
    while (secondNumber != 0) {
        signedLongLong remainder = firstNumber % secondNumber;
        firstNumber = secondNumber;
        secondNumber = remainder;
    }
    return firstNumber;
}

signedLongLong multiplyMod(signedLongLong firstNumber, signedLongLong secondNumber, signedLongLong modulo) {
    return (unsignedInt128)firstNumber * secondNumber % modulo;
}

signedLongLong powerMod(signedLongLong baseNumber, signedLongLong exponent, signedLongLong modulo) {
    signedLongLong result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = multiplyMod(result, baseNumber, modulo);
        baseNumber = multiplyMod(baseNumber, baseNumber, modulo);
        exponent >>= 1;
    }
    return result;
}

bool isPrime(signedLongLong number) {
    if (number < 2) return false;
    for (signedLongLong primeNumber : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (number % primeNumber == 0) return number == primeNumber;
    }
    signedLongLong oddPart = number - 1;
    int powerCount = 0;
    while ((oddPart & 1) == 0) {
        oddPart >>= 1;
        ++powerCount;
    }
    for (signedLongLong baseNumber : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (baseNumber % number == 0) continue;
        signedLongLong currentValue = powerMod(baseNumber % number, oddPart, number);
        if (currentValue == 1 || currentValue == number - 1) continue;
        bool passedTest = false;
        for (int i = 1; i < powerCount; ++i) {
            currentValue = multiplyMod(currentValue, currentValue, number);
            if (currentValue == number - 1) {
                passedTest = true;
                break;
            }
        }
        if (!passedTest) return false;
    }
    return true;
}

signedLongLong getPollardFactor(signedLongLong number) {
    if (number % 2 == 0) return 2;
    if (number % 3 == 0) return 3;
    while (true) {
        signedLongLong constant = randomGenerator() % (number - 1) + 1;
        signedLongLong currentValue = randomGenerator() % (number - 2) + 2;
        signedLongLong nextValue = currentValue;
        signedLongLong divisor = 1;
        auto nextFunction = [&](signedLongLong value) {
            return (multiplyMod(value, value, number) + constant) % number;
        };
        while (divisor == 1) {
            currentValue = nextFunction(currentValue);
            nextValue = nextFunction(nextFunction(nextValue));
            signedLongLong difference = currentValue > nextValue ? currentValue - nextValue : nextValue - currentValue;
            divisor = getGcd(difference, number);
        }
        if (divisor != number) return divisor;
    }
}

void factorize(signedLongLong number, map<signedLongLong, int>& factorMap) {
    if (number == 1) return;
    if (isPrime(number)) {
        ++factorMap[number];
        return;
    }
    signedLongLong divisor = getPollardFactor(number);
    factorize(divisor, factorMap);
    factorize(number / divisor, factorMap);
}

void generateDivisors(
    const vector<pair<signedLongLong, int>>& factorList,
    int index,
    signedLongLong currentValue,
    vector<signedLongLong>& divisors
) {
    if (index == (int)factorList.size()) {
        divisors.push_back(currentValue);
        return;
    }
    signedLongLong primeNumber = factorList[index].first;
    int exponent = factorList[index].second;
    signedLongLong powerValue = 1;
    for (int i = 0; i <= exponent; ++i) {
        generateDivisors(factorList, index + 1, currentValue * powerValue, divisors);
        powerValue *= primeNumber;
    }
}

bool tryRecover(
    signedLongLong firstNumber,
    const vector<signedLongLong>& products,
    signedLongLong firstProduct,
    vector<signedLongLong>& answer
) {
    signedLongLong secondNumber = firstProduct / firstNumber;
    if (firstNumber < 2 || firstNumber >= secondNumber || secondNumber > 1000000000LL) return false;
    multiset<signedLongLong> remainingProducts(products.begin(), products.end());
    auto firstIterator = remainingProducts.find(firstProduct);
    if (firstIterator == remainingProducts.end()) return false;
    remainingProducts.erase(firstIterator);
    vector<signedLongLong> currentAnswer = {firstNumber, secondNumber};
    while ((int)currentAnswer.size() < (int)((1 + sqrt(1 + 8.0 * products.size())) / 2)) {
        if (remainingProducts.empty()) return false;
        signedLongLong smallestProduct = *remainingProducts.begin();
        if (smallestProduct % firstNumber != 0) return false;
        signedLongLong nextNumber = smallestProduct / firstNumber;
        if (nextNumber <= currentAnswer.back() || nextNumber > 1000000000LL) return false;
        vector<signedLongLong> neededProducts;
        for (signedLongLong oldNumber : currentAnswer) {
            neededProducts.push_back(oldNumber * nextNumber);
        }
        for (signedLongLong neededProduct : neededProducts) {
            auto productIterator = remainingProducts.find(neededProduct);
            if (productIterator == remainingProducts.end()) return false;
            remainingProducts.erase(productIterator);
        }
        currentAnswer.push_back(nextNumber);
    }
    if (!remainingProducts.empty()) return false;
    answer = currentAnswer;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; ++testCase) {
        int numberCount;
        cin >> numberCount;
        int productCount = numberCount * (numberCount - 1) / 2;
        vector<signedLongLong> products(productCount);
        for (signedLongLong& product : products) cin >> product;
        signedLongLong firstProduct = *min_element(products.begin(), products.end());
        map<signedLongLong, int> factorMap;
        factorize(firstProduct, factorMap);
        vector<pair<signedLongLong, int>> factorList(factorMap.begin(), factorMap.end());
        vector<signedLongLong> divisors;
        generateDivisors(factorList, 0, 1, divisors);
        sort(divisors.begin(), divisors.end());
        vector<signedLongLong> bestAnswer;
        for (signedLongLong firstNumber : divisors) {
            if (firstNumber * firstNumber >= firstProduct) continue;
            vector<signedLongLong> currentAnswer;
            if (!tryRecover(firstNumber, products, firstProduct, currentAnswer)) continue;
            if (bestAnswer.empty() || currentAnswer < bestAnswer) bestAnswer = currentAnswer;
        }
        cout << "Case " << testCase << ":";
        for (signedLongLong number : bestAnswer) cout << ' ' << number;
        cout << '\n';
    }
    return 0;
}
