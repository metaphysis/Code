// All-Pair Farthest Points
// UVa ID: 12311
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, idx[30010];
double px[100000], py[100000];
    
double f(int i, int j)
{
    if (j >= i + n || j < i) return 0;
    return pow(px[i] - px[j], 2) + pow(py[i] - py[j], 2);
}

void dfs(int left, int right, int low, int high)
{
    int middle = (left + right) / 2;
    idx[middle] = low;
    double d1, d2;
    for (int i = low + 1; i <= high; i++)
    {
        d1 = f(middle, i), d2 = f(middle, idx[middle]);
        if (d1 > d2 || (d1 == d2 && (i % n) < (idx[middle] % n)))
            idx[middle] = i;
    }
    if (left < right)
    {
        dfs(left, middle - 1, low, idx[middle]);
        dfs(middle + 1, right, idx[middle], high);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> px[i] >> py[i];
            px[n + i] = px[i], py[n + i] = py[i];          
        }
        dfs(0, n - 1, 0, 2 * n - 1);
        for (int i = 0; i < n; i++) cout << idx[i] % n + 1 << '\n';
    }

    return 0;
}
