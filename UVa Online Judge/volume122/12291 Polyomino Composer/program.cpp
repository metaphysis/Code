// Polyomino Composer
// UVa ID: 12291
// Verdict: Accepted
// Submission Date: 2018-01-11
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

    string line;
    char large[32][32], small[16][16], temp[32][32];
    int n, m;

    while (cin >> n >> m, n > 0)
    {
        memset(large, '.', sizeof(large));
        memset(small, '.', sizeof(small));

        int cnt1 = 0, cnt2 = 0;
        
        // WARNING:
        // Some lines of input may contain less character than n or m.
        cin.ignore(1024, '\n');
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            for (int j = 0; j < line.length(); j++)
            {
                large[i][j] = line[j];
                if (large[i][j] == '*') cnt1 += 1;
            }
        }

        int leftx = m, rightx = 0, upy = m, bottomy = 0;
        for (int i = 0; i < m; i++)
        {
            getline(cin, line);
            for (int j = 0; j < line.length(); j++)
            {
                small[i][j] = line[j];
                if (small[i][j] == '*')
                {
                    cnt2 += 1;
                    leftx = min(leftx, j), rightx = max(rightx, j);
                    upy = min(upy, i), bottomy = max(bottomy, i);
                }
            }
        }

        if (cnt1 != 2 * cnt2)
        {
            cout << "0\n";
            continue;
        }

        // First match.
        bool matched = false;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                bool same = true;
                for (int k = upy, y = 0; k <= bottomy; k++, y++)
                    for (int l = leftx, x = 0; l <= rightx; l++, x++)
                        if (large[i + y][j + x] == '.' && small[k][l] == '*')
                        {
                            same = false;
                            break;
                        }
                if (same)
                {
                    // Copy and set.
                    memcpy(temp, large, sizeof(large));

                    for (int k = upy, y = 0; k <= bottomy; k++, y++)
                        for (int l = leftx, x = 0; l <= rightx; l++, x++)
                            if (small[k][l] == '*')
                                temp[i + y][j + x] = '.';

                    // Second match.
                    for (int ii = 0; ii < n; ii++)
                        for (int jj = 0; jj < n; jj++)
                        {
                            bool stillSame = true;
                            for (int k = upy, y = 0; k <= bottomy; k++, y++)
                                for (int l = leftx, x = 0; l <= rightx; l++, x++)
                                    if (temp[ii + y][jj + x] == '.' && small[k][l] == '*')
                                    {
                                        stillSame = false;
                                        break;
                                    }
                            if (stillSame)
                            {
                                matched = true;
                                goto print;
                            }
                        }
                }
            }
            
        print:
        cout << (matched ? 1 : 0) << '\n';
    }

    return 0;
}
