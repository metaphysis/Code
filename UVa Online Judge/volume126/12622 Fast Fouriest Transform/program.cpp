#include <bits/stdc++.h>
using namespace std;

int getFourCount(long long num, long long base) {
    int fourCount = 0;
    while (num > 0) {
        if (num % base == 4)
            fourCount++;
        num /= base;
    }
    return fourCount;
}

void updateAnswer(long long num, long long base, int &bestCount, long long &bestBase) {
    int fourCount = getFourCount(num, base);
    if (fourCount > bestCount || fourCount == bestCount && base < bestBase) {
        bestCount = fourCount;
        bestBase = base;
    }
}

void solveCase(long long value) {
    long long num = value >= 0 ? value : -value;
    if (num == 4) {
        cout << value << " 1 5" << endl;
        return;
    }
    int bestCount = -1;
    long long bestBase = -1, limit = sqrt(static_cast<double>(num));
    while ((limit + 1) * (limit + 1) <= num)
        limit++;
    while (limit * limit > num)
        limit--;
    for (long long base = 5; base <= limit; base++)
        updateAnswer(num, base, bestCount, bestBase);
    long long startBase = max(5LL, limit + 1), highBase = max(startBase, num / 5 + 1), highLimit = num / 4;
    if (highBase <= highLimit)
        updateAnswer(num, highBase, bestCount, bestBase);
    long long remain = num - 4;
    if (remain > 0) {
        for (long long divisor = 1; divisor * divisor <= remain; divisor++) {
            if (remain % divisor != 0)
                continue;
            long long other = remain / divisor;
            if (divisor >= startBase)
                updateAnswer(num, divisor, bestCount, bestBase);
            if (other != divisor && other >= startBase)
                updateAnswer(num, other, bestCount, bestBase);
        }
    }
    if (bestCount <= 0)
        cout << value << " is infuriable." << endl;
    else
        cout << value << " " << bestCount << " " << bestBase << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        long long value;
        cin >> value;
        solveCase(value);
    }
    return 0;
}
