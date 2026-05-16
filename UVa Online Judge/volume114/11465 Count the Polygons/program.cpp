// Count the Polygons
// UVa ID: 11465
// Verdict: Accepted
// Submission Date: 2026-05-02
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, K;
vector<long long> len;
long long ans;

// 计算组合数
long long C[31][31];
void initC() {
    for (int i = 0; i <= 30; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

void solve() {
    sort(len.begin(), len.end());
    ans = 0;
    
    // 枚举最长边
    for (int maxIdx = K - 1; maxIdx < n; ++maxIdx) {
        long long maxLen = len[maxIdx];
        int m = maxIdx;  // 前面有 m 根棍子
        
        if (m < K - 1) continue;
        
        // 折半
        int mid = m / 2;
        vector<long long> leftArr(len.begin(), len.begin() + mid);
        vector<long long> rightArr(len.begin() + mid, len.begin() + m);
        
        // 枚举左半所有子集 (cnt, sum)
        vector<pair<int, long long>> leftSub;
        int leftSz = leftArr.size();
        for (int mask = 0; mask < (1 << leftSz); ++mask) {
            int cnt = 0;
            long long sum = 0;
            for (int j = 0; j < leftSz; ++j) if (mask >> j & 1) {
                cnt++;
                sum += leftArr[j];
            }
            leftSub.emplace_back(cnt, sum);
        }
        
        // 枚举右半所有子集 (cnt, sum)，并按 cnt 分组
        int rightSz = rightArr.size();
        vector<vector<long long>> rightSumByCnt(K + 1);
        for (int mask = 0; mask < (1 << rightSz); ++mask) {
            int cnt = 0;
            long long sum = 0;
            for (int j = 0; j < rightSz; ++j) if (mask >> j & 1) {
                cnt++;
                sum += rightArr[j];
            }
            if (cnt <= K - 1) rightSumByCnt[cnt].push_back(sum);
        }
        
        // 对每组排序，便于二分
        for (int c = 0; c <= K - 1; ++c)
            sort(rightSumByCnt[c].begin(), rightSumByCnt[c].end());
        
        // 统计
        for (auto &p : leftSub) {
            int cntL = p.first;
            long long sumL = p.second;
            int need = K - 1 - cntL;
            if (need < 0 || need > rightSz) continue;
            
            auto &vec = rightSumByCnt[need];
            long long target = maxLen - sumL;
            // 找第一个 > target 的位置
            int pos = upper_bound(vec.begin(), vec.end(), target) - vec.begin();
            ans += (vec.size() - pos);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    initC();
    
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        cin >> n >> K;
        len.resize(n);
        for (int i = 0; i < n; ++i) cin >> len[i];
        
        solve();
        
        cout << "Case " << caseNo << ": " << ans << "\n";
    }
    return 0;
}
