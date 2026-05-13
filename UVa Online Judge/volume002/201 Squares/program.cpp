// Squares
// UVa ID: 201
// Verdict: Accepted
// Submission Date: 2016-03-23
// UVa Run Time: 0.022s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int row[10][10][10];     // row[i][j][k]: 第 i 行中，点 (i,j) 到 (i,k) 是否有连续水平线段
int column[10][10][10];  // column[i][j][k]: 第 i 列中，点 (j,i) 到 (k,i) 是否有连续垂直线段
int n;                   // 网格每行/每列的点数

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    char line;            // 线段类型：'H' 或 'V'
    int m, start, end;    // m 为线段数量，start 和 end 为坐标
    int counter = 0;      // 记录当前是第几个问题
    bool printAsterisks = false;  // 控制是否打印分隔符
    
    while (cin >> n) {
        // 如果不是第一组数据，则输出分隔符（前后各有一个空行）
        if (printAsterisks) {
            cout << "\n";
            cout << "**********************************\n";
            cout << "\n";
        }

        if (printAsterisks == false) printAsterisks = true;

        counter++;
        
        // 初始化线段数组
        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));

        cin >> m;
        while (m--) {
            cin >> line >> start >> end;
            if (line == 'H')
                // 水平线段：第 start 行，连接列 end 和 end+1
                row[start][end][end + 1] = 1;
            else
                // 垂直线段：第 start 列，连接行 end 和 end+1
                column[start][end][end + 1] = 1;
        }

        // 预处理：合并连续的线段，得到任意两点间是否连续连通
        // 例如：第 k 行中，若从 i 到 j-1 有线段，且从 j-1 到 j 有线段，则从 i 到 j 有线段
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n - 2; i++)
                for (int j = i + 2; j <= n; j++) {
                    if (row[k][i][j - 1] && row[k][j - 1][j]) row[k][i][j] = 1;
                    if (column[k][i][j - 1] && column[k][j - 1][j]) column[k][i][j] = 1;
                }

        // 输出问题标题，UVa 格式要求后面空一行
        cout << "Problem #" << counter << "\n";
        cout << endl;

        bool outputed = false;  // 标记是否有输出任何正方形

        // 枚举边长 k，从 1 到 n-1
        for (int k = 1; k <= n - 1; k++) {
            int total = 0;
            // 枚举左上角顶点 (i, j)
            for (int i = 1; i <= n - k; i++)
                for (int j = 1; j <= n - k; j++)
                    // 判断正方形的四条边是否都存在
                    if (row[i][j][j + k] && row[i + k][j][j + k] &&
                        column[j][i][i + k] && column[j + k][i][i + k])
                            total++;

             if (total > 0) {
                cout << total << " square (s) of size " << k << "\n";
                outputed = true;
             }            
        }

        // 如果没有找到任何正方形，输出提示信息
        if (outputed == false) cout << "No completed squares can be found." << "\n";     
    }

    return 0;
}
