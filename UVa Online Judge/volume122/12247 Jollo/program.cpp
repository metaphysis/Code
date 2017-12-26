// Jollo
// UVa ID: 12247
// Verdict: Accepted
// Submission Date: 2017-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

    int A, B, C, X, Y;
    int used[60];
    vector<int> p1, p2;

    while (cin >> A >> B >> C >> X >> Y, A > 0)
    {
        memset(used, 0, sizeof(used));
        used[A] = used[B] = used[C] = used[X] = used[Y] = 1;
        p1.clear(); p2.clear();
        p1.push_back(A); p1.push_back(B); p1.push_back(C);
        p2.push_back(X); p2.push_back(Y);        
        
        bool found = false;
        for (int i = 1; i <= 52; i++)
        {
            if (used[i]) continue;
            p2.push_back(i);
            sort(p1.begin(), p1.end());
            bool good = true;
            do
            {
                int win = 0;
                for (int j = 0; j < 3; j++)
                    if (p1[j] > p2[j])
                        win++;
                if (win >= 2)
                {
                    good = false;
                    break;
                }
            } while (next_permutation(p1.begin(), p1.end()));
            if (good)
            {
                cout << i << '\n';
                found = true;
                break;
            }
            p2.pop_back();
        }
        if (!found) cout << "-1\n";
    }

    return 0;
}
