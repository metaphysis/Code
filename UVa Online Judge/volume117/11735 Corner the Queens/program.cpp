// Corner the Queens
// UVa ID: 11735
// Verdict: Accepted
// Submission Date: 2025-10-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 黄金比例 φ = (1+√5)/2，用于生成Wythoff游戏的P位置
const double goldenRatio = (1.0 + sqrt(5.0)) / 2.0;
// φ² = φ + 1
const double goldenRatioSquared = goldenRatio * goldenRatio;

/**
 * 计算矩形区域内第一种P位置的数量
 * P位置格式: (floor(k*φ), floor(k*φ²)) = (floor(k*φ), floor(k*φ)+k)
 * 这些是先手必败的位置
 */
long long countPrimaryPPositions(long long xMin, long long xMax, long long yMin, long long yMax) {
    // 检查矩形是否有效
    if (xMin > xMax || yMin > yMax) return 0;
    
    // 计算k的取值范围：需要同时满足x和y的约束条件
    long long kLowerBound = max(1LL, (long long)ceil(max(xMin / goldenRatio, yMin / goldenRatioSquared)));
    long long kUpperBound = min((long long)floor((xMax + 1) / goldenRatio - 1e-12), 
                               (long long)floor((yMax + 1) / goldenRatioSquared - 1e-12));
    
    // 如果无有效k值，返回0
    if (kLowerBound > kUpperBound) return 0;
    
    // 返回满足条件的k值数量
    return kUpperBound - kLowerBound + 1;
}

/**
 * 计算矩形区域内第二种P位置的数量（对称情况）
 * P位置格式: (floor(k*φ²), floor(k*φ)) = (floor(k*φ)+k, floor(k*φ))
 * 这些也是先手必败的位置
 */
long long countSymmetricPPositions(long long xMin, long long xMax, long long yMin, long long yMax) {
    // 检查矩形是否有效
    if (xMin > xMax || yMin > yMax) return 0;
    
    // 计算k的取值范围：交换x和y的角色
    long long kLowerBound = max(1LL, (long long)ceil(max(yMin / goldenRatio, xMin / goldenRatioSquared)));
    long long kUpperBound = min((long long)floor((yMax + 1) / goldenRatio - 1e-12), 
                               (long long)floor((xMax + 1) / goldenRatioSquared - 1e-12));
    
    // 如果无有效k值，返回0
    if (kLowerBound > kUpperBound) return 0;
    
    // 返回满足条件的k值数量
    return kUpperBound - kLowerBound + 1;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int testCaseCount;
    cin >> testCaseCount;
    
    for (int caseIndex = 1; caseIndex <= testCaseCount; caseIndex++) {
        long long xMin, yMin, xMax, yMax;
        cin >> xMin >> yMin >> xMax >> yMax;
        
        // 处理无效矩形（输入保证有效，但为了健壮性保留）
        if (xMin > xMax || yMin > yMax) {
            cout << "Board " << caseIndex << ": 0 / 1\n";
            continue;
        }
        
        // 计算矩形内总格子数
        long long totalCells = (xMax - xMin + 1) * (yMax - yMin + 1);
        
        // 处理空矩形情况
        if (totalCells == 0) {
            cout << "Board " << caseIndex << ": 0 / 1\n";
            continue;
        }
        
        // 计算所有P位置（先手必败位置）的数量
        long long pPositionCount = countPrimaryPPositions(xMin, xMax, yMin, yMax) + 
                                  countSymmetricPPositions(xMin, xMax, yMin, yMax);
        
        // 计算先手必胜位置的数量
        long long winningPositionCount = totalCells - pPositionCount;
        
        // 约分分数
        long long commonDivisor = __gcd(winningPositionCount, totalCells);
        
        // 输出结果
        cout << "Board " << caseIndex << ": " << winningPositionCount / commonDivisor 
             << " / " << totalCells / commonDivisor << "\n";
    }
    
    return 0;
}
