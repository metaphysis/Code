// The Trip II
// UVa ID: 10638
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int parseMoney(const string& value) {
    size_t point = value.find('.');
    int dollars = stoi(value.substr(0, point));
    int cents = 0;
    if (point != string::npos) {
        string part = value.substr(point + 1);
        if (part.size() == 1)
            cents = (part[0] - '0') * 10;
        else
            cents = stoi(part.substr(0, 2));
    }
    return dollars * 100 + cents;
}

int getMinPayments(const vector<int>& expense, int highCount, int base) {
    int personCount = expense.size();
    int answer = INT_MAX;
    for (int highMask = 0; highMask < (1 << personCount); ++highMask) {
        if (__builtin_popcount(highMask) != highCount)
            continue;
        vector<int> balance;
        for (int i = 0; i < personCount; ++i) {
            int target = base + ((highMask >> i) & 1);
            int value = expense[i] - target;
            if (value != 0)
                balance.push_back(value);
        }
        int count = balance.size();
        int stateCount = 1 << count;
        vector<long long> subsetSum(stateCount, 0);
        for (int mask = 1; mask < stateCount; ++mask) {
            int bit = mask & -mask;
            int index = __builtin_ctz(bit);
            subsetSum[mask] = subsetSum[mask ^ bit] + balance[index];
        }
        vector<int> dp(stateCount, 0);
        for (int mask = 1; mask < stateCount; ++mask) {
            int lowBit = mask & -mask;
            dp[mask] = dp[mask ^ lowBit];
            for (int sub = mask; sub; sub = (sub - 1) & mask) {
                if ((sub & lowBit) && subsetSum[sub] == 0)
                    dp[mask] = max(dp[mask], dp[mask ^ sub] + 1);
            }
        }
        answer = min(answer, count - dp[stateCount - 1]);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int personCount;
    while (cin >> personCount && personCount != 0) {
        vector<int> expense(personCount);
        int total = 0;
        for (int i = 0; i < personCount; ++i) {
            string value;
            cin >> value;
            expense[i] = parseMoney(value);
            total += expense[i];
        }
        int base = total / personCount;
        int highCount = total % personCount;
        cout << getMinPayments(expense, highCount, base) << '\n';
    }
    return 0;
}
