// Sheldon Numbers
// UVa ID: 13022
// Verdict: Accepted
// Submission Date: 2026-02-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<unsigned long long> sheldonNumbers; // 存储所有Sheldon数

// 生成所有Sheldon数
void generateSheldonNumbers() {
    for (int N = 1; N <= 64; ++N) { // N: 连续1的个数
        for (int M = 0; M <= 64 - N; ++M) { // M: 连续0的个数，且总长度不超过64位
            int segmentLen = N + M; // 一个完整段(1^N 0^M)的长度
            
            // 模式1: (1^N 0^M)^k, k>=1
            if (segmentLen > 0) { // 防止除零错误
                int maxK1 = 64 / segmentLen; // 最大重复次数
                for (int k = 1; k <= maxK1; ++k) {
                    unsigned long long val = 0;
                    for (int i = 0; i < k; ++i) {
                        // 添加N个1: (1<<N)-1 表示N个1的二进制值
                        val = (val << N) | ((1ULL << N) - 1);
                        // 如果不是最后一次，添加M个0
                        if (i != k - 1 || M > 0) val <<= M;
                    }
                    // 检查是否在范围内
                    if (val > 0 && val <= (1ULL << 63)) {
                        sheldonNumbers.push_back(val);
                    }
                }
            }
            
            // 模式2: (1^N 0^M)^k 1^N, k>=0
            // 总长度 = k*(N+M) + N <= 64
            int maxK2 = (64 - N) / (segmentLen > 0 ? segmentLen : 1);
            for (int k = 0; k <= maxK2; ++k) {
                unsigned long long val = 0;
                // 添加k个 (1^N 0^M)
                for (int i = 0; i < k; ++i) {
                    val = (val << N) | ((1ULL << N) - 1);
                    val <<= M;
                }
                // 最后添加一个 1^N
                val = (val << N) | ((1ULL << N) - 1);
                if (val > 0 && val <= (1ULL << 63)) {
                    sheldonNumbers.push_back(val);
                }
            }
        }
    }
    
    // 去重并排序，便于二分查找
    sort(sheldonNumbers.begin(), sheldonNumbers.end());
    sheldonNumbers.erase(unique(sheldonNumbers.begin(), sheldonNumbers.end()), sheldonNumbers.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 预生成所有Sheldon数
    generateSheldonNumbers();
    
    unsigned long long X, Y;
    while (cin >> X >> Y) {
        // 使用二分查找统计区间[X, Y]内的Sheldon数个数
        auto left = lower_bound(sheldonNumbers.begin(), sheldonNumbers.end(), X);
        auto right = upper_bound(sheldonNumbers.begin(), sheldonNumbers.end(), Y);
        cout << (right - left) << endl;
    }
    
    return 0;
}
