// Zeros and Ones
// UVa ID: 12063
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, K;
    cin >> T;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> K;
        cout << "Case " << cs << ": ";
        if (N % 2 == 1)
        {
            cout << "0\n";
            continue;
        }
    }

    return 0;
}
