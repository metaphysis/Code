// Bits
// UVa ID: 11645
// Verdict: Accepted
// Submission Date: 2025-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

using ll = long long;
using i128 = __int128;

i128 dp[64][2][2][64];
vector<int> digits;

i128 dfs(int pos, int prev, int tight, int cnt) {
    if (pos == (int)digits.size()) {
        return cnt;
    }
    if (dp[pos][prev][tight][cnt] != -1) {
        return dp[pos][prev][tight][cnt];
    }
    i128 res = 0;
    int up = tight ? digits[pos] : 1;
    for (int d = 0; d <= up; d++) {
        int new_cnt = cnt;
        if (prev == 1 && d == 1) {
            new_cnt++;
        }
        res += dfs(pos + 1, d, tight && (d == up), new_cnt);
    }
    return dp[pos][prev][tight][cnt] = res;
}

string i128_to_string(i128 num) {
    if (num == 0) return "0";
    string s;
    bool negative = false;
    if (num < 0) {
        negative = true;
        num = -num;
    }
    while (num > 0) {
        s += '0' + (num % 10);
        num /= 10;
    }
    if (negative) {
        s += '-';
    }
    reverse(s.begin(), s.end());
    return s;
}

i128 solve(ll n) {
    if (n < 0) return 0;
    digits.clear();
    ll temp = n;
    while (temp > 0) {
        digits.push_back(temp & 1);
        temp >>= 1;
    }
    if (digits.empty()) {
        digits.push_back(0);
    }
    reverse(digits.begin(), digits.end());
    memset(dp, -1, sizeof dp);
    return dfs(0, 0, 1, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    int caseNo = 1;
    while (cin >> n) {
        if (n < 0) break;
        i128 result = solve(n);
        cout << "Case " << caseNo++ << ": " << i128_to_string(result) << "\n";
    }
    return 0;
}
