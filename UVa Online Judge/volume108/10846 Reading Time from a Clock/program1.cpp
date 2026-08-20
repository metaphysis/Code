#include <bits/stdc++.h>
using namespace std;

struct Time {
    long long num, den;
};

long long parseNumber(const string &str, size_t left, size_t right) {
    long long value = 0;
    for (size_t i = left; i < right; i++)
        value = value * 10 + str[i] - '0';
    return value;
}

Time readTime(long long n) {
    string timeStr, fractionStr;
    cin >> timeStr >> fractionStr;
    size_t colonPos = timeStr.find(':'), slashPos = fractionStr.find('/');
    long long hour = parseNumber(timeStr, 0, colonPos), minute = parseNumber(timeStr, colonPos + 1, timeStr.size());
    long long num = parseNumber(fractionStr, 0, slashPos), den = parseNumber(fractionStr, slashPos + 1, fractionStr.size());
    return {(hour * n + minute) * den + num, den};
}

long long countLessEqual(const Time &time, long long m, long long n) {
    long long base = m * m - 1, totalMinutes = m * n;
    long long point = time.num * base / (time.den * totalMinutes);
    return point - point / (m + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m, n, nq;
    int caseNum = 1;
    bool firstCase = true;
    while (cin >> m >> n >> nq) {
        if (m == 0 && n == 0 && nq == 0) break;
        if (!firstCase) cout << '\n';
        firstCase = false;
        cout << "Planet " << caseNum++ << ":\n";
        for (long long i = 0; i < nq; i++) {
            Time leftTime = readTime(n), rightTime = readTime(n);
            if (m == 1) {
                cout << "0\n";
                continue;
            }
            long long leftCount = countLessEqual(leftTime, m, n);
            long long rightCount = countLessEqual(rightTime, m, n);
            cout << rightCount - leftCount << '\n';
        }
    }
    return 0;
}
