// All-Pair Farthest Points
// UVa ID: 12311
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
double px[100000], py[100000];
    
double f(int i, int j)
{
    return pow(px[i] - px[j], 2) + pow(py[i] - py[j], 2);
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
        for (int i = 0; i < n; i++)
        {
            // ternary search.
            int left = i + 1, right = i + n - 1, r;
            while (left <= right)
            {
                int leftThird = left + (right - left) / 3;
                int rightThird = right - (right - left) / 3;
                if (f(i, leftThird) >= f(i, rightThird)) r = leftThird, right = rightThird - 1;
                else r = rightThird, left = leftThird + 1;
            }
            r %= n;
            if (r && f(i, r - 1) >= f(i, r)) r -= 1;
            cout << (r + 1) << '\n';
        }
    }

    return 0;
}
