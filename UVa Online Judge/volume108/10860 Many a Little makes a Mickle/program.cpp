// Many a Little makes a Mickle
// UVa ID: 10860
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;
    cin.ignore(); // 忽略换行符

    for (int setNum = 1; setNum <= S; setNum++) {
        string P;
        getline(cin, P);
        int lenP = P.length();

        int N;
        cin >> N;
        cin.ignore();

        vector<string> patterns;
        for (int i = 0; i < N; i++) {
            string pat;
            getline(cin, pat);
            patterns.push_back(pat);          // 加入原串
            string revPat = pat;
            reverse(revPat.begin(), revPat.end());
            patterns.push_back(revPat);       // 加入反转串
        }

        // DP数组：dp[i]表示到达位置i所需的最少短串数量
        vector<int> dp(lenP + 1, INT_MAX);
        dp[0] = 0; // 起点不需要任何短串

        // 遍历每个位置
        for (int i = 0; i < lenP; i++) {
            if (dp[i] == INT_MAX) continue; // 该位置不可达，跳过
            
            // 尝试所有模式串（原串和反转串）
            for (const string& pat : patterns) {
                int lenPat = pat.length();
                // 检查模式串是否匹配P从i开始的子串
                if (i + lenPat <= lenP && P.compare(i, lenPat, pat) == 0) {
                    // 更新到达位置i+lenPat的最小值
                    dp[i + lenPat] = min(dp[i + lenPat], dp[i] + 1);
                }
            }
        }

        // 输出结果
        if (dp[lenP] != INT_MAX) {
            cout << "Set " << setNum << ": " << dp[lenP] << ".\n";
        } else {
            cout << "Set " << setNum << ": Not possible.\n";
        }
    }

    return 0;
}
