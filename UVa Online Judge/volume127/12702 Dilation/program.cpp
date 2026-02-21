// Dilation
// UVa ID: 12702
// Verdict: Accepted
// Submission Date: 2026-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;  // 测试用例数
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        int m, n;
        cin >> m >> n;  // 图像尺寸
        vector<vector<int>> image(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> image[i][j];  // 读取图像
        
        int q, r;
        cin >> q >> r;  // 结构元素尺寸
        vector<vector<int>> structure(q, vector<int>(r));
        for (int i = 0; i < q; i++)
            for (int j = 0; j < r; j++)
                cin >> structure[i][j];  // 读取结构元素
        
        // 计算结构元素原点
        int originRow = q / 2;
        int originCol = r / 2;
        
        // 初始化输出图像，全0
        vector<vector<int>> output(m, vector<int>(n, 0));
        
        // 遍历原图每个像素
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (image[i][j] == 1) {  // 如果当前像素为1
                    // 将结构元素覆盖到输出图像
                    for (int sr = 0; sr < q; sr++) {
                        for (int sc = 0; sc < r; sc++) {
                            if (structure[sr][sc] == 1) {
                                int ni = i + sr - originRow;
                                int nj = j + sc - originCol;
                                // 检查是否在图像范围内
                                if (ni >= 0 && ni < m && nj >= 0 && nj < n)
                                    output[ni][nj] = 1;
                            }
                        }
                    }
                }
            }
        }
        
        // 输出结果
        cout << "Case " << caseNo << ":\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << output[i][j];
                if (j < n - 1) cout << " ";  // 行末无空格
            }
            cout << "\n";
        }
    }
    return 0;
}
