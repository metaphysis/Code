// 列主元高斯消元法求解线性方程组Ax=b。
bool gaussianElimination(vector<vector<double>> &A, vector<double> &b)
{
    // 把b存放在A的右边以方便后续处理。
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
    {
        // 为减少误差，将正在处理的未知元系数的绝对值最大的方程式与第i个方程式交换。
        int pivot = i;
        for (int j = i; j < n; j++)
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        swap(A[i], A[pivot]);

        // 方程组无解或具有无穷多个解。
        if (fabs(A[i][i]) < EPSICON) return false;

        // 把正在处理的未知元的系数变为1。
        for (int j = i + 1; j <= n; j++) A[i][j] /= A[i][i];

        // 从第j个式子中消去第i个未知元。
        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++) A[j][k] -= A[j][i] * A[i][k];
    }

    // 存放在矩阵A最右边的元素即为解。
    for (int i = 0; i < n; i++) b[i] = A[i][n];
    
    return true;
}
