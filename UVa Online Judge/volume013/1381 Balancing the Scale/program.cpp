// Balancing the Scale
// UVa ID: 1381
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 1.960s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

map<int, long long> countAll8Tuples(const vector<int>& nums) {
    map<int, long long> result;
    int n = nums.size();
    
    // leftMap[sum][mask] = count
    map<int, map<int, int>> leftMap;
    
    // 枚举左边 4 个数（权重 4,3,2,1）
    for (int leftMask = 0; leftMask < (1 << n); ++leftMask) {
        if (__builtin_popcount(leftMask) != 4) continue;
        vector<int> leftNums;
        for (int i = 0; i < n; ++i) if (leftMask >> i & 1) leftNums.push_back(nums[i]);
        do {
            int sum = leftNums[0]*4 + leftNums[1]*3 + leftNums[2]*2 + leftNums[3];
            leftMap[sum][leftMask]++;
        } while (next_permutation(leftNums.begin(), leftNums.end()));
    }
    
    // 枚举右边 4 个数（权重 1,2,3,4），与左边配对
    for (int rightMask = 0; rightMask < (1 << n); ++rightMask) {
        if (__builtin_popcount(rightMask) != 4) continue;
        vector<int> rightNums;
        for (int i = 0; i < n; ++i) if (rightMask >> i & 1) rightNums.push_back(nums[i]);
        do {
            int sum = rightNums[0] + rightNums[1]*2 + rightNums[2]*3 + rightNums[3]*4;
            if (leftMap.find(sum) == leftMap.end()) continue;
            for (auto& [leftMask, cnt] : leftMap[sum]) {
                if (leftMask & rightMask) continue;
                int fullMask = leftMask | rightMask;
                result[fullMask] += cnt;
            }
        } while (next_permutation(rightNums.begin(), rightNums.end()));
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> nums(16);
    int caseNum = 1;
    
    while (cin >> nums[0], nums[0]) {
        for (int i = 1; i < 16; ++i) cin >> nums[i];
        sort(nums.begin(), nums.end());
        
        auto xWays = countAll8Tuples(nums);
        
        long long ans = 0;
        for (auto& [maskX, cntX] : xWays) {
            int maskY = ((1 << 16) - 1) ^ maskX;
            if (xWays.find(maskY) != xWays.end()) {
                ans += cntX * xWays[maskY];
            }
        }
        
        // 除以 8 去重（上下对称 2 × x左右镜像 2 × y左右镜像 2）
        ans /= 8;
        
        cout << "Case " << caseNum++ << ": " << ans << "\n";
    }
    return 0;
}
