// Password Remembering
// UVa ID: 12212
// Verdict: Accepted
// Submission Date: 2026-08-02
// UVa Run Time: 0.120s

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long Ull;

class Solver {
private:
    Ull dp[3][3][2][2];
    Ull nextDp[3][3][2][2];
    int updRel(int relation, int digit, int boundDigit) {
        if (digit < boundDigit) return 0;
        if (digit > boundDigit) return 2;
        return relation;
    }
    
    int updLowFlag(int flag, int digit, int boundDigit) {
        if (flag == 0) return 0;
        if (digit < boundDigit) return -1;
        if (digit > boundDigit) return 0;
        return 1;
    }
    
    int updUpFlag(int flag, int digit, int boundDigit) {
        if (flag == 0) return 0;
        if (digit > boundDigit) return -1;
        if (digit < boundDigit) return 0;
        return 1;
    }
    
    string getLowBound(const string &value, int length) {
        if ((int)value.size() > length) return "";
        return string(length - (int)value.size(), '0') + value;
    }
    
    string getUpBound(const string &value, int length) {
        if ((int)value.size() > length) return string(length, '9');
        return string(length - (int)value.size(), '0') + value;
    }
    
    Ull countLen(const string &a, const string &b, int length) {
        if ((int)a.size() > length || (int)b.size() < length) return 0;
        string lowBound = getLowBound(a, length);
        string upBound = getUpBound(b, length);
        memset(dp, 0, sizeof(dp));
        dp[1][1][1][1] = 1;
        for (int pos = 0; pos < length; pos++) {
            memset(nextDp, 0, sizeof(nextDp));
            int origPos = length - 1 - pos;
            for (int lowRel = 0; lowRel <= 2; lowRel++) {
                for (int upRel = 0; upRel <= 2; upRel++) {
                    for (int revLowEq = 0; revLowEq <= 1; revLowEq++) {
                        for (int revUpEq = 0; revUpEq <= 1; revUpEq++) {
                            Ull cur = dp[lowRel][upRel][revLowEq][revUpEq];
                            if (cur == 0) continue;
                            int digitStart = 0, digitEnd = 9;
                            if (pos == 0) digitStart = 1;
                            if (revLowEq != 0) digitStart = max(digitStart, lowBound[pos] - '0');
                            if (revUpEq != 0) digitEnd = min(digitEnd, upBound[pos] - '0');
                            for (int digit = digitStart; digit <= digitEnd; digit++) {
                                int nextLowRel = updRel(lowRel, digit, lowBound[origPos] - '0');
                                int nextUpRel = updRel(upRel, digit, upBound[origPos] - '0');
                                int nextRevLowEq = updLowFlag(revLowEq, digit, lowBound[pos] - '0');
                                int nextRevUpEq = updUpFlag(revUpEq, digit, upBound[pos] - '0');
                                if (nextRevLowEq == -1 || nextRevUpEq == -1) continue;
                                nextDp[nextLowRel][nextUpRel][nextRevLowEq][nextRevUpEq] += cur;
                            }
                        }
                    }
                }
            }
            memcpy(dp, nextDp, sizeof(dp));
        }
        Ull ans = 0;
        for (int lowRel = 1; lowRel <= 2; lowRel++) {
            for (int upRel = 0; upRel <= 1; upRel++) {
                ans += dp[lowRel][upRel][0][0];
                ans += dp[lowRel][upRel][0][1];
                ans += dp[lowRel][upRel][1][0];
                ans += dp[lowRel][upRel][1][1];
            }
        }
        return ans;
    }

public:
    Ull solve(const string &a, const string &b) {
        Ull ans = 0;
        for (int len = (int)a.size(); len <= (int)b.size(); len++) ans += countLen(a, b, len);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        string a, b;
        cin >> a >> b;
        Solver solver;
        Ull ans = solver.solve(a, b);
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
