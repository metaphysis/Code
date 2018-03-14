// Troublemakers
// UVa ID: 10982
// Verdict: Accepted
// Submission Date: 2018-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    srand(time(NULL));

    int class1[110], class2[110];
    int cases, n, m, a, b;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;

        vector<int> A, B;
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> b;
            A.push_back(a), B.push_back(b);
        }

        while (true)
        {
            memset(class1, 0, sizeof(class1));
            memset(class2, 0, sizeof(class2));

            for (int i = 1; i <= n; i++)
            {
                // Approximation algorithms.
                // https://en.wikipedia.org/wiki/Maximum_cut 
                if (rand() % 10000 < 5000) class1[i] = 1;
                else class2[i] = 1;
            }

            int cnt1 = 0, cnt2 = 0;
            for (int i = 0; i < m; i++)
            {
                if (class1[A[i]] && class1[B[i]]) cnt1++;
                if (class2[A[i]] && class2[B[i]]) cnt2++;
            }

            if (cnt1 + cnt2 <= m / 2) break;
        }
        
        cout << "Case #" << c << ": " << count(class1, class1 + 110, 1) << '\n';
        bool printed = false;
        for (int i = 0; i <= n; i++)          
            if (class1[i])
            {
                if (printed) cout << ' ';
                cout << i;
                printed = true;
            }
        cout << '\n';
    }

    return 0;
}
