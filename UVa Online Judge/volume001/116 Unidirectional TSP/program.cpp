// Unidirectional TSP
// UVa ID: 116
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int m, n, minRow, preRow, minWeight;
int parent[11][101], matrix[11][101];

int main(int ac, char *av[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> m >> n)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];

        // 从右往左进行动态规划，即列优先处理，从倒数第二列开始，因为需要字典序最小
        // 的最小权和路径，如果从左往右处理，可以得到行号最小的权和方案，但是不一定
        // 是字典序最小的。
        for (int j = n - 1; j >= 1; j--)
            for (int i = 1; i <= m; i++)
            {
                minWeight = INT_MAX;

                preRow = (i == 1 ? m : i - 1);
                if (minWeight > matrix[preRow][j + 1])
                {
                    minWeight = matrix[preRow][j + 1];
                    minRow = preRow;
                }
                else if (minWeight == matrix[preRow][j + 1] && minRow > preRow)
                    minRow = preRow;

                if (minWeight > matrix[i][j + 1])
                {
                    minWeight = matrix[i][j + 1];
                    minRow = i;
                }
                else if (minWeight == matrix[i][j + 1] && minRow > i)
                    minRow = i;

                preRow = (i == m ? 1 : i + 1);
                if (minWeight > matrix[preRow][j + 1])
                {
                    minWeight = matrix[preRow][j + 1];
                    minRow = preRow;
                }
                else if (minWeight == matrix[preRow][j + 1] && minRow > preRow)
                    minRow = preRow;

                matrix[i][j] += minWeight;
                parent[i][j] = minRow;
            }

        // 找第一列权和最小的单元格。
        minWeight = INT_MAX;
        for (int i = 1; i <= m; i++)
            if (matrix[i][1] < minWeight)
            {
                minWeight = matrix[i][1];
                minRow = i;
            }

        // 输出路径和最小权和。
        cout << minRow;
        int next = 1, preRow = minRow;
        while (next < n)
        {
            cout << " " << parent[preRow][next];
            preRow = parent[preRow][next];
            next++;
        }
        cout << "\n";
        cout << matrix[minRow][1] << "\n";
    }

    return 0;
}
