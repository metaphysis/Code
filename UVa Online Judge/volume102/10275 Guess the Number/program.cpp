// Guess the Number
// UVa ID: 10275
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const string tableOfPow[] = {
    "1", "4", "27", "256", "3125", "46656", "823543", "16777216",
    "387420489", "10000000000", "285311670611", "8916100448256",
    "302875106592253", "11112006825558016", "437893890380859375"
};

// 大数除法：a / b，返回商和余数
pair<string, int> divide(const string& a, int b) {
    string result;
    long long remainder = 0;
    for (char digit : a) {
        remainder = remainder * 10 + (digit - '0');
        int quotient = remainder / b;
        remainder %= b;
        if (!result.empty() || quotient != 0)
            result += char(quotient + '0');
    }
    if (result.empty()) result = "0";
    return {result, (int)remainder};
}

// 计算 n^n 的位数
int countDigits(int n) { return floor(n * log10(n)) + 1; }

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int length = s.size();
        
        // 对于小数字，直接查表
        if (length < 20) {
            bool found = false;
            for (int i = 0; i < 16; i++)
                if (s == tableOfPow[i]) {
                    found = true;
                    cout << (i + 1) << '\n';
                }
            if (!found) cout << -1 << '\n';
            continue;
        }
        
        // 通过位数估算 N
        int low = 1, high = 1000000;
        while (low <= high) {
            int middle = (low + high) / 2;
            countDigits(middle) < length ? low = middle + 1 : high = middle - 1;
        }
        
        // 在估算值附近检查候选
        bool found = false;
        for (int n = low - 3; n <= low + 3; n++) {
            if (countDigits(n) != length) continue;
            auto [quotient, remainder] = divide(s, n);
            if (!remainder) {
                found = true;
                cout << n << '\n';
                break;
            }
        }
        if (!found) cout << -1 << '\n';
    }
    return 0;
}
