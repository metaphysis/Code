// Flip Sort
// UVa ID: 10327
// Verdict: Accepted
// Submission Date: 2018-02-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, number[1010];
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
            cin >> number[i];
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 1; j < n - i; j++)
                if (number[j - 1] > number[j])
                {
                    swap(number[j - 1], number[j]);
                    cnt++;
                }
        cout << "Minimum exchange operations : " << cnt << '\n';
    }

    return 0;
}
