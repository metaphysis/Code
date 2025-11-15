// Learning Vector
// UVa ID: 12589
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Vector {
    int x, y;
    bool operator<(const Vector& other) const {
        return y * other.x > other.y * x;
    }
};

int main() {
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int N, K;
        cin >> N >> K;
        vector<Vector> vectors(N);
        for (int i = 0; i < N; ++i) {
            cin >> vectors[i].x >> vectors[i].y;
        }
        
        // 按斜率降序排序
        sort(vectors.begin(), vectors.end());
        
        // 计算最大可能高度
        int maxHeight = 0;
        for (int i = 0; i < N; ++i) {
            maxHeight += vectors[i].y;
        }
        
        // dp[j][h]: 选择j个向量，总高度为h时的最大两倍面积
        vector<vector<int>> dp(K + 1, vector<int>(maxHeight + 1, -1));
        dp[0][0] = 0;
        
        for (int i = 0; i < N; ++i) {
            int x = vectors[i].x, y = vectors[i].y;
            
            // 从后往前更新，避免重复使用同一个向量
            for (int j = K; j >= 1; --j) {
                for (int h = maxHeight; h >= y; --h) {
                    if (dp[j - 1][h - y] != -1) {
                        int newArea = dp[j - 1][h - y] + 2 * (h - y) * x + x * y;
                        if (dp[j][h] < newArea) {
                            dp[j][h] = newArea;
                        }
                    }
                }
            }
        }
        
        int maxArea = 0;
        for (int h = 0; h <= maxHeight; ++h) {
            if (dp[K][h] > maxArea) {
                maxArea = dp[K][h];
            }
        }
        
        cout << "Case " << caseNum << ": " << maxArea << endl;
    }
    return 0;
}
