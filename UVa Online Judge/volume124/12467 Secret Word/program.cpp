// Secret Word
// UVa ID: 12467
// Verdict: Accepted
// Submission Date: 2018-11-27
// UVa Run Time: 0.100s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, z[MAXN];
    string A, S;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> A;
        S = A;
        S += '$';
        for (int i = A.length() - 1; i >= 0; i--)
            S += A[i];
        int n = S.length(), longest = 0;
        z[0] = n;
        for (int i = 1, j = 1, k; i < n; i = k)
        {
            if (j < i) j = i;
            while (j < n && S[j] == S[j - i]) j++;
            z[i] = j - i;
            k = i + 1;
            while (k + z[k - i] < j) z[k] = z[k - i], k++;
            if (i > A.length() && z[i] > longest) longest = z[i];
        }
        for (int i = longest - 1; i >= 0; i--)
            cout << A[i];
        cout << '\n';
    }

    return 0;
}
