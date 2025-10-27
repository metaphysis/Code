// Corner the Queens
// UVa ID: 11735
// Verdict: Accepted
// Submission Date: 2025-10-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int MAXN = 2000005;  // 因为坐标最大10^6，P位置数量大约也是这个量级

vector<int> pX, pY;  // 存储P位置的x坐标和y坐标
bool used[MAXN];     // 标记数字是否已被使用

// 生成所有P位置 (a_k, b_k) 其中 a_k = floor(k*φ), b_k = floor(k*φ²) = a_k + k
void generatePPositions() {
    // 使用近似的黄金比例来生成序列
    // 实际是通过递推关系：每个新P位置 (a, b) 满足 b = a + k
    int k = 1;
    for (int a = 1; a < MAXN; a++) {
        if (used[a]) continue;
        int b = a + k;
        k++;
        
        if (b >= MAXN) break;
        
        used[a] = used[b] = true;
        pX.push_back(a);
        pY.push_back(b);
    }
}

// 计算矩形[x1,x2]×[y1,y2]内P位置的数量
LL countPPositionsInRect(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    
    // 找到第一个满足 pX[i] >= x1 且 pY[i] >= y1 的位置
    int left = max(
        lower_bound(pX.begin(), pX.end(), x1) - pX.begin(),
        lower_bound(pY.begin(), pY.end(), y1) - pY.begin()
    );
    
    // 找到第一个满足 pX[i] > x2 或 pY[i] > y2 的位置
    int right = min(
        upper_bound(pX.begin(), pX.end(), x2) - pX.begin(),
        upper_bound(pY.begin(), pY.end(), y2) - pY.begin()
    );
    
    return (left < right) ? (right - left) : 0;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    // 预处理生成所有P位置
    generatePPositions();
    
    int testCaseCount;
    cin >> testCaseCount;
    
    for (int caseIndex = 1; caseIndex <= testCaseCount; caseIndex++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // 计算矩形内总格子数
        LL totalCells = (LL)(x2 - x1 + 1) * (y2 - y1 + 1);
        
        // 统计P位置数量
        LL pCount = 0;
        
        // 统计 (a_k, b_k) 类型的P位置
        pCount += countPPositionsInRect(x1, x2, y1, y2);
        
        // 统计 (b_k, a_k) 类型的P位置（对称情况）
        pCount += countPPositionsInRect(y1, y2, x1, x2);
        
        // 计算先手必胜位置数量
        LL winningPositions = totalCells - pCount;
        
        // 约分
        LL commonDivisor = __gcd(winningPositions, totalCells);
        
        cout << "Board " << caseIndex << ": " 
             << winningPositions / commonDivisor << " / " 
             << totalCells / commonDivisor << "\n";
    }
    
    return 0;
}
