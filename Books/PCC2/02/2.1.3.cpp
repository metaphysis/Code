#include <bits/stdc++.h>
using namespace std;

// 打印矩阵
void printMatrix(const vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << setw(4) << mat[i][j];
        cout << '\n';
    }
}

// (1) 上下对换
void flipUpDown(vector<vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < n / 2; i++) swap(mat[i], mat[n - 1 - i]);
}

// (2) 左右对换
void flipLeftRight(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m / 2; j++)
            swap(mat[i][j], mat[i][m - 1 - j]);
}

// (3) 以主对角线为对称轴对换（转置）
void transposeMainDiag(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    // 方阵可以直接原地交换，非方阵则需要重新分配空间
    if (n == m) {
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < m; j++)
                swap(mat[i][j], mat[j][i]);
    } else {
        // 非方阵：创建新矩阵
        vector<vector<int>> result(m, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                result[j][i] = mat[i][j];
        mat = move(result);
    }
}

// (4) 以副对角线为对称轴对换
void transposeAntiDiag(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[n - 1 - j][n - 1 - i] = mat[i][j];
    mat = move(result);
}

// (5) 顺时针旋转90度
void rotate90Clockwise(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    // 旋转后新矩阵大小为 m x n
    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[j][n - 1 - i] = mat[i][j];
    mat = move(result);
}

// (6) 顺时针旋转180度（等价于上下翻转+左右翻转）
void rotate180(vector<vector<int>>& mat) {
    flipUpDown(mat);
    flipLeftRight(mat);
}

// (7) 顺时针旋转270度（逆时针90度）
void rotate270Clockwise(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    // 旋转后新矩阵大小为 m x n
    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[m - 1 - j][i] = mat[i][j];
    mat = move(result);
}

// 演示所有变换
int main() {
    // 示例矩阵 4x4
    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    cout << "原始矩阵：" << endl;
    printMatrix(matrix);

    auto mat1 = matrix;
    flipUpDown(mat1);
    cout << "\n(1) 上下对换：" << endl;
    printMatrix(mat1);

    auto mat2 = matrix;
    flipLeftRight(mat2);
    cout << "\n(2) 左右对换：" << endl;
    printMatrix(mat2);

    auto mat3 = matrix;
    transposeMainDiag(mat3);
    cout << "\n(3) 主对角线对换（转置）：" << endl;
    printMatrix(mat3);

    auto mat4 = matrix;
    transposeAntiDiag(mat4);
    cout << "\n(4) 副对角线对换：" << endl;
    printMatrix(mat4);

    auto mat5 = matrix;
    rotate90Clockwise(mat5);
    cout << "\n(5) 顺时针旋转90度：" << endl;
    printMatrix(mat5);

    auto mat6 = matrix;
    rotate180(mat6);
    cout << "\n(6) 顺时针旋转180度：" << endl;
    printMatrix(mat6);

    auto mat7 = matrix;
    rotate270Clockwise(mat7);
    cout << "\n(7) 顺时针旋转270度：" << endl;
    printMatrix(mat7);

    return 0;
}
