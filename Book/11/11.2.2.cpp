#include <bits/stdc++.h>

using namespace std;

int matrixChainMultiplication(vector<int> &dimensions, int i, int j)
{
    if (i == j) return 0;
    int min_count = numeric_limits<int>::max();
    for (int k = i; k <= j - 1; k++)
    {
        int count = matrixChainMultiplication(dimensions, i, k) +
            matrixChainMultiplication(dimensions, k + 1, j) +
            dimensions[i - 1] * dimensions[k] * dimensions[j];
        min_count = min(min_count, count);
    }
    return min_count;
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        vector<int> dimensions(n + 1, 0);
        for (int i = 0; i <= n; i++)
            cin >> dimensions[i];
        cout << matrixChainMultiplication(dimensions, 1, n) << endl;
    }
    
    return 0;
}
