// Matrix Transpose
// UVa ID: 10895
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct element
{
    int row, column, value;
    bool operator<(const element &e) const
    {
        if (row != e.row) return row < e.row;
        return column < e.column;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int m, n, r, c[1010], v[1010], rt[1010];

    while (cin >> m >> n)
    {
        vector<element> matrix;

        memset(rt, 0, sizeof(rt));

        for (int i = 1; i <= m; i++)
        {
            cin >> r;
            for (int j = 1; j <= r; j++)
                cin >> c[j];
            for (int j = 1; j <= r; j++)
                cin >> v[j];
            for (int j = 1; j <= r; j++)
            {
                matrix.push_back(element{c[j], i, v[j]});
                rt[c[j]]++;
            }
        }
        
        sort(matrix.begin(), matrix.end());

        cout << n << ' ' << m << '\n';
        int ei = 0;
        for (int i = 1; i <= n; i++)
        {
            cout << rt[i];
            for (int j = 0; j < rt[i]; j++)
                cout << ' ' << matrix[ei + j].column;
            cout << '\n';
            for (int j = 0; j < rt[i]; j++)
            {
                if (j) cout << ' ';
                cout << matrix[ei + j].value;
            }
            cout << '\n';
            ei += rt[i];
        }
        
    }

    return 0;
}
