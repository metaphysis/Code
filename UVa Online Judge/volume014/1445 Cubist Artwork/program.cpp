// Cubist Artwork
// UVa ID: 1445
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, d;
    while (cin >> w >> d && (w || d)) {
        vector<int> front(w), side(d);
        for (int i = 0; i < w; i++) cin >> front[i];
        for (int i = 0; i < d; i++) cin >> side[i];
        
        // 将正视图和侧视图按降序排序
        sort(front.begin(), front.end(), greater<int>());
        sort(side.begin(), side.end(), greater<int>());
        
        int totalCubes = 0;
        int i = 0, j = 0;
        
        // 使用双指针法匹配高度
        while (i < w && j < d) {
            if (front[i] == side[j]) {
                // 高度相等，可以同时满足列和行
                totalCubes += front[i];
                i++;
                j++;
            } else if (front[i] > side[j]) {
                // 正视图高度更大，先满足列要求
                totalCubes += front[i];
                i++;
            } else {
                // 侧视图高度更大，先满足行要求
                totalCubes += side[j];
                j++;
            }
        }
        
        // 处理剩余未匹配的高度
        while (i < w) totalCubes += front[i++];
        while (j < d) totalCubes += side[j++];
        
        cout << totalCubes << endl;
    }
    return 0;
}
