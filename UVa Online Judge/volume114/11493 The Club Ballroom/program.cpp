// The Club Ballroom
// UVa ID: 11493
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 尝试覆盖一个方向，返回最少木板数，如果不可能返回-1
int tryDirection(int roomLength, int roomWidth, int L, vector<int>& planks) {
    // 全部转换为厘米
    int lengthCm = roomLength * 100;
    int widthCm = roomWidth * 100;
    
    // 检查木板宽度是否能整除房间宽度
    if (widthCm % L != 0) return -1;
    
    int numLines = widthCm / L;
    
    // 统计木板数量（厘米）
    map<int, int> count;
    for (int len : planks) {
        count[len * 100]++;
    }
    
    map<int, int> tempCount = count;
    int totalUsed = 0;
    
    for (int i = 0; i < numLines; i++) {
        // 优先使用单块完整木板
        if (tempCount[lengthCm] > 0) {
            tempCount[lengthCm]--;
            totalUsed++;
            continue;
        }
        
        // 尝试用两块木板拼接
        bool found = false;
        for (auto& p : tempCount) {
            int a = p.first;
            if (a >= lengthCm) continue;
            
            int b = lengthCm - a;
            if (b <= 0) continue;
            
            if (a == b) {
                if (p.second >= 2) {
                    tempCount[a] -= 2;
                    if (tempCount[a] == 0) tempCount.erase(a);
                    totalUsed += 2;
                    found = true;
                    break;
                }
            } else {
                if (tempCount.find(b) != tempCount.end() && tempCount[b] > 0) {
                    tempCount[a]--;
                    tempCount[b]--;
                    if (tempCount[a] == 0) tempCount.erase(a);
                    if (tempCount[b] == 0) tempCount.erase(b);
                    totalUsed += 2;
                    found = true;
                    break;
                }
            }
        }
        
        if (!found) return -1;
    }
    
    return totalUsed;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M, N || M) {
        int L, K;
        cin >> L >> K;
        vector<int> planks(K);
        for (int i = 0; i < K; i++) cin >> planks[i];
        
        int ans = INT_MAX;
        
        // 方向1：木板横向放置
        int result1 = tryDirection(N, M, L, planks);
        if (result1 != -1) ans = min(ans, result1);
        
        // 方向2：木板纵向放置
        int result2 = tryDirection(M, N, L, planks);
        if (result2 != -1) ans = min(ans, result2);
        
        if (ans == INT_MAX) cout << "impossivel\n";
        else cout << ans << "\n";
    }
    
    return 0;
}
