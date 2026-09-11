// Grid Points
// UVa ID: 10676
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct GridChoice {
    long double spacing;
    long long leftIndex;
    long long rightIndex;
    long long count;
    int baseType;
    int exponent;
};

long long parseScaledValue(const string &text) {
    int sign = 1;
    int position = 0;
    if (text[0] == '-') {
        sign = -1;
        position++;
    } else if (text[0] == '+')
        position++;
    long long integerPart = 0;
    while (position < static_cast<int>(text.size()) && text[position] != '.') {
        integerPart = integerPart * 10 + text[position] - '0';
        position++;
    }
    long long fractionalPart = 0;
    int fractionalDigits = 0;
    if (position < static_cast<int>(text.size()) && text[position] == '.') {
        position++;
        while (position < static_cast<int>(text.size()) && fractionalDigits < 5) {
            fractionalPart = fractionalPart * 10 + text[position] - '0';
            fractionalDigits++;
            position++;
        }
    }
    while (fractionalDigits < 5) {
        fractionalPart *= 10;
        fractionalDigits++;
    }
    return sign * (integerPart * 100000LL + fractionalPart);
}

bool isBetter(const GridChoice &current, const GridChoice &best, int desiredCount) {
    long long currentDifference = llabs(current.count - desiredCount);
    long long bestDifference = llabs(best.count - desiredCount);
    if (currentDifference != bestDifference)
        return currentDifference < bestDifference;
    if (current.count != best.count)
        return current.count > best.count;
    return current.spacing < best.spacing;
}

int getPrecision(int baseType, int exponent) {
    if (baseType == 2)
        return max(0, 1 - exponent);
    return max(0, -exponent);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCaseCount;
    cin >> testCaseCount;
    const long double baseValues[4] = {1.0L, 2.0L, 2.5L, 5.0L};
    const long double scale = 100000.0L;
    while (testCaseCount--) {
        int pointCount, desiredCount;
        cin >> pointCount >> desiredCount;
        long long minimumScaled = 0;
        long long maximumScaled = 0;
        for (int i = 0; i < pointCount; i++) {
            string text;
            cin >> text;
            long long value = parseScaledValue(text);
            minimumScaled = min(minimumScaled, value);
            maximumScaled = max(maximumScaled, value);
        }
        long double minimumValue = static_cast<long double>(minimumScaled) / scale;
        long double maximumValue = static_cast<long double>(maximumScaled) / scale;
        GridChoice bestChoice{};
        bool hasBestChoice = false;
        for (int baseType = 0; baseType < 4; baseType++) {
            for (int exponent = -10; exponent <= 10; exponent++) {
                long double spacing = baseValues[baseType] * powl(10.0L, exponent);
                long double leftRatio = minimumValue / spacing;
                long double rightRatio = maximumValue / spacing;
                long double leftError = 1e-12L * max(1.0L, fabsl(leftRatio));
                long double rightError = 1e-12L * max(1.0L, fabsl(rightRatio));
                long long leftIndex = static_cast<long long>(floorl(leftRatio + leftError));
                long long rightIndex = static_cast<long long>(ceill(rightRatio - rightError));
                long long count = rightIndex - leftIndex + 1;
                GridChoice currentChoice{spacing, leftIndex, rightIndex, count, baseType, exponent};
                if (!hasBestChoice || isBetter(currentChoice, bestChoice, desiredCount)) {
                    bestChoice = currentChoice;
                    hasBestChoice = true;
                }
            }
        }
        int precision = getPrecision(bestChoice.baseType, bestChoice.exponent);
        long double unit = powl(10.0L, -precision);
        for (long long index = bestChoice.leftIndex; index <= bestChoice.rightIndex; index++) {
            long double value = index == 0 ? 0.0L : index * bestChoice.spacing;
            if (fabsl(value) < unit / 2)
                value = 0.0L;
            if (index != bestChoice.leftIndex)
                cout << ' ';
            cout << fixed << setprecision(precision) << value;
        }
        cout << '\n';
    }
    return 0;
}
