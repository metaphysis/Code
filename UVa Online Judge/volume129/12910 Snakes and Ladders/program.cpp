// Snakes and Ladders
// UVa ID: 12910
// Verdict: Accepted
// Submission Date: 2019-04-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 160;
const double EPSILON = 1e-7;

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int W, H, S;
    int advanced[MAXN];

    while (cin >> W >> H >> S)
    {
        vector<vector<double>> A;
        vector<double> b(W * H, 0);

        iota(advanced, advanced + MAXN, 0);
        for (int i = 1, ui, vi; i <= S; i++)
        {
            cin >> ui >> vi;
            ui--, vi--;
            advanced[ui] = vi;
        }

        for (int i = 0; i <= W * H - 2; i++)
        {
            vector<double> a(W * H, 0);
            a[i] = 1.0;
            for (int j = 1; j <= 6; j++)
            {
                int next = i + j;
                if (next >= W * H) next = 2 * (W * H - 1) - next;
                a[advanced[next]] -= 1.0 / 6;
            }
            b[i] = 1;
            A.push_back(a);
        }
        vector<double> a(W * H, 0);
        a[W * H - 1] = 1, b[W * H - 1] = 0;
        A.push_back(a);

        gaussianElimination(A, b);

        cout << fixed << setprecision(8) << b[0] << '\n';
    }

    return 0;
}
