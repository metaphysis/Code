bool gaussianElimination(vector<vector<double>> &A, vector<double> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);
    for (int i = 0; i < n; i++)
    {
        int pivot = i;
        for (int j = i; j < n; j++)
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        swap(A[i], A[pivot]);
        if (fabs(A[i][i]) < EPSILON) return false;
        for (int j = i + 1; j <= n; j++) A[i][j] /= A[i][i];
        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++) A[j][k] -= A[j][i] * A[i][k];
    }
    for (int i = 0; i < n; i++) b[i] = A[i][n];
    return true;
}
