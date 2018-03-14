// No Rectangles
// UVa ID: 135
// Verdict: Accepted
// Submission Date: 2016-04-05
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int k;
    bool printBlank = false;
    while (cin >> k)
    {
        if (printBlank)
            cout << "\n";
        else
            printBlank = true;

        int m = k - 1;
        for (int i = 0; i < k; i++)
        {
            cout << 1;
            for (int j = 1; j < k; j++)
                cout << ' ' << i * m + j + 1;
            cout << "\n";

        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
            {
                cout << i + 2;
                for (int s = 0; s < m; s++)
                    cout << ' ' << (j + (s * i)) % m + s * m + k + 1;
                cout << "\n";
            }
    }

    return 0;
}
