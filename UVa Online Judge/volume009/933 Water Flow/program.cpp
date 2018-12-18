// Water Flow
// UVa ID: 933
// Verdict: Accepted
// Submission Date: 2018-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, deposit[32], pipe[32];
    char ignore;
    cin >> ignore >> ignore >> N;
    for (int i = 0; i < N; i++)
    {
        if (i) cin >> ignore;
        cin >> ignore >> ignore >> deposit[i];
    }
    for (int i = 0; i < N - 1; i++)
    {
        if (i) cin >> ignore;
        cin >> ignore >> ignore >> pipe[i + 1];
    }

    cout << "  t";
    for (int i = 0; i < N; i++) cout << "   " << (char)('A' + i);
    cout << '\n';
    cout << "---";
    for (int i = 0; i < N; i++) cout << "----";
    cout << '\n';

    int t = 0;
    while (true)
    {
        cout << right << setw(3) << t++;
        for (int i = 0; i < N; i++) cout << right << setw(4) << deposit[i];
        cout << '\n';
        
        bool allZero = true;
        for (int i = 0; i < N - 1; i++)
            if (deposit[i])
            {
                allZero = false;
                break;
            }
        if (allZero) break;
        for (int i = N - 1; i >= 1; i--)
        {
            if (deposit[i - 1] >= pipe[i]) deposit[i - 1] -= pipe[i], deposit[i] += pipe[i];
            else deposit[i] += deposit[i - 1], deposit[i - 1] = 0;
        }
    }

    return 0;
}
