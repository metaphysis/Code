// Numeric Center
// UVa ID: 12909
// Verdict: Accepted
// Submission Date: 2022-10-15
// UVa Run Time: 0.170s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long r[10000010] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int rc = 0;
    long long n = 2, square_of_n, half_of_square_of_n, square_root;
    while (true)
    {
        square_of_n = 2 * n * n;
        if (square_of_n > 1e15) break;
        square_root = sqrt(square_of_n + 1);
        if (square_root * square_root == square_of_n + 1)
            r[++rc] = square_of_n;
        else
        {
            square_root = sqrt(square_of_n - 1);
            if (square_root * square_root == square_of_n - 1)
                r[++rc] = square_of_n - 1;
        }
        n++;
    }
    
    while (cin >> n, n)
    {
        int left = 0, right = rc, mid, answer;
        while (left <= right)
        {
            mid = (left + right) >> 1;
            if (n >= r[mid]) answer = mid, left = mid + 1;
            else right = mid - 1;
        }
        cout << answer << '\n';
    }

    return 0;
}
