// Fill the Containers
// UVa ID: 11413
// Verdict: Accepted
// Submission Date: 2017-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int partition(int data[], int n, int k)
{
    int left = 0, right = 0;

    for (int i = 0; i < n; i++) right += data[i];
    
    while (left <= right)
    {
        int middle = (left + right) / 2;
        int j = 0, p = 0, sum = 0, ok = 1;

        while (j < n && p <= k)
        {
            if (sum + data[j] <= middle)
            {
                sum += data[j];
                j++;
            }
            else
            {
                sum = 0;
                p++;
            }
        }

        if (sum > 0) p++;

        if (p > k)
            left = middle + 1;
        else
            right = middle - 1;
    }
    
    return left;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int data[1010], n, k;
    while (cin >> n >> k)
    {
        for (int i = 0; i < n; i++)
            cin >> data[i];
        cout << partition(data, n, k) << '\n';
    }

    return 0;
}
