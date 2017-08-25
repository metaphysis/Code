// Back to Kernighan-Ritchie
// UVa ID: 10828
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const double EPSILON = 10e-6;
const int MAXN = 110;

int n, q;
vector<int> in[MAXN];
int out[MAXN], inf[MAXN];

void print(vector<vector<double>> A)
{
    for (auto u : A)
    {
        for (auto v : u)
            cout << v << ' ';
        cout << '\n';
    }
    cout << '\n';
}

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

        if (fabs(A[i][i]) < EPSILON) continue;
        
        for (int j = i + 1; j <= n; j++) A[i][j] /= A[i][i];

        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++) A[j][k] -= A[j][i] * A[i][k];

        print(A);
    }

    for (int i = 0; i < n; i++) b[i] = A[i][n];

    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cout.setf(ios::fixed);
    cout.precision(3);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
            in[i].clear();
        memset(out, 0, sizeof(out));

        int from, to;
        while (cin >> from >> to)
        {
            if (!from) break;
            out[from]++;
            in[to].push_back(from);
        }

        vector<vector<double>> A(n, vector<double>(n, 0.0));
        for (int u = 1; u <= n; u++)
        {
            for (auto v : in[u])
                A[u - 1][v - 1] += 1.0 / (double)(out[v]);
            A[u - 1][u - 1] = -1.0;
        }

        vector<double> b(n, 0.0);
        b[0] = -1.0;

        gaussianElimination(A, b);

        memset(inf, 0, sizeof(inf));
        for (int i = 0; i < n; i++)
        {
            if (fabs(A[i][i]) < EPSILON) inf[i] = 1;
            for (int j = i + 1; j < n; j++)
                if (fabs(A[i][j]) > EPSILON && inf[i]) inf[j] = 1;
        }
        
        cout << "Case #" << ++cases << ":\n";

        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> from;
            if (inf[from - 1]) cout << "infinity\n";
            else cout << b[from - 1] << '\n';
        }
        cout << '\n';
    }

    return 0;
}
