// Extended Lights Out
// UVa ID: 1560
// Verdict: Accepted
// Submission Date: 2016-11-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// 线性方程组，高斯消元法，模运算。

#include <bits/stdc++.h>

using namespace std;

// 列主元高斯消元法求解线性方程组Ax=b。
void gaussianElimination(vector<vector<int>> &A, vector<int> &b)
{
    // 把b存放在A的右边以方便后续处理。
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
    {
        // 将正在处理的未知元系数的绝对值最大的方程式与第i个方程式交换。
        int pivot = i;
        for (int j = i; j < n; j++)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[i], A[pivot]);

        // 方程组无解或具有无穷多个解。
        if (abs(A[i][i]) == 0) continue;

        // 从第j个式子中消去第i个未知元。
        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++)
                    A[j][k] -= A[j][i] * A[i][k], A[j][k] %= 2;
    }

    // 存放在矩阵A最右边的元素即为解。
    for (int i = 0; i < n; i++) b[i] = A[i][n];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int factor[30][30], switches[30], cases;
    int offset[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "PUZZLE #" << c << '\n';
        
        memset(factor, 0, sizeof(factor));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 6; j++)
            {
                factor[i * 6 + j][i * 6 + j] = 1;
                for (int k = 0; k < 4; k++)
                {
                    int ii = i + offset[k][0], jj = j + offset[k][1];
                    if (ii >= 0 && ii < 5 && jj >= 0 && jj < 6)
                        factor[ii * 6 + jj][i * 6 + j] = 1;
                }
                
                cin >> switches[i * 6 + j];
            }
        
        vector<vector<int>> matrix(30, vector<int>());
        vector<int> constant(30, 0);
        
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 6; j++)
                for (int k = 0; k < 30; k++)
                    matrix[i * 6 + j].push_back(factor[i * 6 + j][k]);

        for (int i = 0; i < 30; i++)
            constant[i] = switches[i];

        gaussianElimination(matrix, constant);
        
        for (int i = 0; i < 30; i++)
        {
            if ((i + 1) % 6 != 1)
                cout << ' ';

            cout << (constant[i] % 2 ? '1' : '0');
                
            if ((i + 1) % 6 == 0)
                cout << '\n';
        }
    }
    
	return 0;
}
