// Formula 1
// UVa ID: 11835
// Verdict: Accepted
// Submission Date: 2018-01-10
// UVa Run Time: 0.010s
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

    int G, P, S, K, point;
    int race[110][110], score[110];

    while (cin >> G >> P, G > 0)
    {
        memset(race, 0, sizeof(race));

        for (int i = 1; i <= G; i++)
            for (int j = 1; j <= P; j++)
                cin >> race[i][j];
        cin >> S;
        for (int s = 1; s <= S; s++)
        {
            memset(score, 0, sizeof(score));
            cin >> K;
            for (int k = 1; k <= K; k++)
            {
                cin >> point;
                for (int g = 1; g <= G; g++)
                    for (int p = 1; p <= P; p++)
                        if (race[g][p] == k)
                            score[p] += point;
                    
            }
            int maxp = *max_element(score + 1, score + P + 1);
            bool printed = false;
            for (int p = 1; p <= P; p++)
                if (score[p] == maxp)
                {
                    if (printed) cout << ' ';
                    cout << p;
                    printed = true;
                }
            cout << '\n';
        }
    }

    return 0;
}
