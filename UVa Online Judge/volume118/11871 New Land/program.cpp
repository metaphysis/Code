// New Land
// UVa ID: 11871
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 0.780s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

void solve(int caseNum) {
    int m, n;
    scanf("%d %d", &m, &n);
    
    // 解码矩阵
    vector<vector<int>> mat(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int k, c;
        scanf("%d %d", &k, &c);
        int col = 0;
        int current = c; // 当前块的值
        for (int j = 0; j < k; ++j) {
            int p;
            scanf("%d", &p);
            for (int t = 0; t < p; ++t) {
                mat[i][col++] = current;
            }
            current = 1 - current; // 切换值
        }
    }
    
    vector<int> height(n, 0); // 每列向上连续0的高度
    int maxArea = 0;
    
    for (int i = 0; i < m; ++i) {
        // 更新高度数组
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 0) height[j] = height[j] + 1;
            else height[j] = 0;
        }
        
        // 单调栈求每行的最大矩形面积
        vector<int> left(n), right(n);
        stack<int> st;
        
        // 计算左边界（左边第一个比当前高度小的位置）
        for (int j = 0; j < n; ++j) {
            while (!st.empty() && height[st.top()] >= height[j]) st.pop();
            left[j] = st.empty() ? 0 : st.top() + 1;
            st.push(j);
        }
        
        while (!st.empty()) st.pop();
        
        // 计算右边界（右边第一个比当前高度小的位置）
        for (int j = n - 1; j >= 0; --j) {
            while (!st.empty() && height[st.top()] >= height[j]) st.pop();
            right[j] = st.empty() ? n - 1 : st.top() - 1;
            st.push(j);
        }
        
        // 计算面积并更新最大值
        for (int j = 0; j < n; ++j) {
            int area = height[j] * (right[j] - left[j] + 1);
            if (area > maxArea) maxArea = area;
        }
    }
    
    printf("Case %d: %d\n", caseNum, maxArea);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
    return 0;
}
