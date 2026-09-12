#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using BigInt = boost::multiprecision::cpp_int;

vector<long long> getDivisors(long long value) {
    vector<long long> divisors;
    for (long long i = 1; i * i <= value; ++i) {
        if (value % i == 0) {
            divisors.push_back(i);
            if (i * i != value)
                divisors.push_back(value / i);
        }
    }
    return divisors;
}

BigInt evaluate(const vector<BigInt>& coef, long long value) {
    BigInt result = 0;
    for (const BigInt& item : coef)
        result = result * value + item;
    return result;
}

vector<BigInt> divideRoot(const vector<BigInt>& coef, long long root) {
    int degree = static_cast<int>(coef.size()) - 1;
    vector<BigInt> quotient(degree);
    quotient[0] = coef[0];
    for (int i = 1; i < degree; ++i)
        quotient[i] = coef[i] + quotient[i - 1] * root;
    return quotient;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    bool firstCase = true;
    while (cin >> n && n != 0) {
        cin >> k;
        vector<long long> value(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> value[i];
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        int degree = n;
        while (degree > 0 && value[degree] == 0)
            --degree;
        int zeroCount = n - degree;
        if (degree == 0) {
            for (int i = 0; i < zeroCount; ++i) {
                if (i > 0)
                    cout << ' ';
                cout << 0;
            }
            cout << '\n';
            continue;
        }
        vector<BigInt> coef(degree + 1);
        coef[0] = 1;
        BigInt power = 1;
        for (int i = 1; i <= degree; ++i) {
            BigInt item = value[i] * power;
            if (i % 2 == 1)
                coef[i] = -item;
            else
                coef[i] = item;
            power *= k;
        }
        long long constantValue = llabs(value[degree]);
        long long leadingValue = llabs(k);
        vector<long long> numeratorDivisors = getDivisors(constantValue);
        vector<long long> denominatorDivisors = getDivisors(leadingValue);
        set<long long> candidates;
        for (long long numerator : numeratorDivisors) {
            for (long long denominator : denominatorDivisors) {
                long long positiveRoot = numerator * k / denominator;
                long long negativeRoot = -positiveRoot;
                candidates.insert(positiveRoot);
                candidates.insert(negativeRoot);
            }
        }
        vector<long long> rationalRoots;
        for (long long root : candidates) {
            if (evaluate(coef, root) != 0)
                continue;
            vector<BigInt> current = coef;
            while (current.size() > 1 && evaluate(current, root) == 0) {
                rationalRoots.push_back(root);
                current = divideRoot(current, root);
            }
        }
        sort(rationalRoots.begin(), rationalRoots.end());
        vector<long long> answer;
        for (int i = 0; i < zeroCount; ++i)
            answer.push_back(0);
        for (long long root : rationalRoots)
            answer.push_back(root);
        sort(answer.begin(), answer.end());
        if (answer.empty()) {
            cout << "No solution.\n";
        } else {
            for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
                if (i > 0)
                    cout << ' ';
                cout << answer[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
