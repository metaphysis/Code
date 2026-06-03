// Avaricious Maryanna
// UVa ID: 12009
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> precompute(int maxN) {
    vector<vector<string>> res(maxN + 1);
    res[1] = {"0", "1", "5", "6"};
    
    vector<int> a(maxN + 5, 0);
    a[0] = 5;
    
    for (int N = 1; N < maxN; ++N) {
        int carry = 0;
        for (int i = 0; i <= N; ++i) {
            int sum = carry;
            for (int j = 0; j <= i; ++j)
                sum += a[j] * a[i - j];
            a[i] = sum % 10;
            carry = sum / 10;
        }
        
        string sa(N + 1, '0');
        for (int i = 0; i <= N; ++i)
            sa[N - i] = char(a[i] + '0');
        
        // 计算 b = 10^(N+1) + 1 - a
        // 将a视为N+2位数（高位补0）
        vector<int> bDigits(N + 2, 0);
        int borrow = 0;
        for (int i = 0; i <= N + 1; ++i) {
            int num = 0;
            if (i == 0) num = 1;           // 个位为1
            if (i == N + 1) num = 1;       // 最高位为1
            int sub = borrow;
            if (i <= N) sub += (sa[N - i] - '0');
            int diff = num - sub;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            if (i <= N)
                bDigits[i] = diff;
            else
                bDigits[N + 1] = diff;     // 最高位
        }
        
        string sb(N + 2, '0');
        for (int i = 0; i <= N + 1; ++i)
            sb[N + 1 - i] = char(bDigits[i] + '0');
        
        // 去掉前导零，得到N+1位字符串
        int pos = 0;
        while (pos < (int)sb.length() - 1 && sb[pos] == '0') pos++;
        sb = sb.substr(pos);
        
        if (sa[0] != '0') res[N + 1].push_back(sa);
        if (sb.length() == N + 1 && sb[0] != '0') res[N + 1].push_back(sb);
        
        sort(res[N + 1].begin(), res[N + 1].end());
    }
    
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    auto solutions = precompute(500);
    
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        cout << "Case #" << caseNo << ":";
        for (const string& s : solutions[N]) cout << " " << s;
        cout << "\n";
    }
    
    return 0;
}
