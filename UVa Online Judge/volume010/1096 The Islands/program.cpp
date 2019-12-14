// The Islands
// UVa ID: 1096
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    bool operator<(const point &p) const
    {
        return x < p.x;
    }
}ps[110];

int cases, n, b1, b2;
int r[110][110];
double B[110][110];
vector<int> path;

double distTo(int i, int j)
{
    return sqrt(pow(ps[i].x - ps[j].x, 2) + pow(ps[i].y - ps[j].y, 2));
}

void printPath(int i, int j)
{
    if (i < j)
    {
        int k = r[i][j];
        path.push_back(k);
        if (k > 1) printPath(i, k);
    }
    else
    {
        int k = r[j][i];
        if (k > 1) printPath(k, j);
        path.push_back(k);
    }
}

void printTour()
{
    path.push_back(n);
    path.push_back(n - 1);
    int k = r[n - 1][n];
    printPath(k, n - 1);
    path.push_back(k);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> b1 >> b2, n > 0)
    {
        b1++, b2++;
        for (int i = 1; i <= n; i++) cin >> ps[i].x >> ps[i].y;
        B[1][2] = distTo(1, 2);
        for (int j = 3; j <= n; j++)
        {
            for (int i = 1; i < j - 1; i++)
            {
                if (i != b1)
                {
                    B[i][j] = B[i][j - 1] + distTo(j - 1, j);
                    r[i][j] = j - 1;
                }
            }
            B[j - 1][j] = 1e20;
            for (int k = 1; k < j - 1; k++)
            {
                if (k != b2)
                {
                    if (B[k][j - 1] + distTo(k, j) < B[j - 1][j])
                    {
                        B[j - 1][j] = B[k][j - 1] + distTo(k, j);
                        r[j - 1][j] = k;
                    }
                }
            }
        }
        B[n][n] = B[n - 1][n] + distTo(n - 1, n);

        // Get optimal tour.
        path.clear();
        printTour();
        
        cout << "Case " << ++cases << ": ";
        cout << fixed << setprecision(2) << B[n][n] << '\n';
        for (auto p : path) cout << p << ' ';
        cout << '\n';
    }

    return 0;
}
