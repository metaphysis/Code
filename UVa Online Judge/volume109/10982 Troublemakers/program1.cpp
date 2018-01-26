// Troublemakers
// UVa ID: 10982
// Verdict: Accepted
// Submission Date: 2018-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int class1[110], class2[110];
    int cases, n, m, a, b;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;

        memset(class1, 0, sizeof(class1));
        memset(class2, 0, sizeof(class2));

        vector<int> A, B;
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> b;
            A.push_back(a), B.push_back(b);
        }

        // https://en.wikipedia.org/wiki/Method_of_conditional_probabilities
        for (int i = 1; i <= n; i++)
        {
            class1[i] = 1;
            int cnt1 = 0;
            for (int j = 0; j < m; j++)
                if (class1[A[j]] && class1[B[j]])
                    cnt1++;
            class1[i] = 0;

            class2[i] = 1;
            int cnt2 = 0;
            for (int j = 0; j < m; j++)
                if (class2[A[j]] && class2[B[j]])
                    cnt2++;
            class2[i] = 0;
            
            if (cnt1 <= cnt2) class1[i] = 1;
            else class2[i] = 1;
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
