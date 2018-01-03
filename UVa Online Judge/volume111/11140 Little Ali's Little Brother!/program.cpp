// Little Ali's Little Brother!
// UVa ID: 11140
// Verdict: Accepted
// Submission Date: 2018-01-03
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

    char board[60][60], piece[60][60];
    int N, M, S, n, m;
    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> M >> S;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                cin >> board[i][j];

        for (int p = 1; p <= S; p++)
        {
            cin >> n >> m;
            
            int upn = n, leftm = m, bottomn = 1, rightm = 1;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                {
                    cin >> piece[i][j];
                    if (piece[i][j] == '*')
                    {
                        upn = min(upn, i), bottomn = max(bottomn, i);
                        leftm = min(leftm, j), rightm = max(rightm, j);
                    }
                }

            bool found = false;
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= M; j++)
                {
                    if (i + (bottomn - upn) > N) continue;
                    if (j + (rightm - leftm) > M) continue;

                    bool safe = true;
                    for (int x = upn, offsetx = 0; x <= bottomn; x++, offsetx++)
                        for (int y = leftm, offsety = 0; y <= rightm; y++, offsety++)
                            if (piece[x][y] == '*' && board[i + offsetx][j + offsety] == '.')
                            {
                                safe = false;
                                goto next;
                            }
                    next:
                    if (safe)
                    {
                        found = true;
                        goto print;
                    }
                }

            print:
            cout << (found ? "Yes" : "No") << '\n';
        }
        cout << '\n';
    }

    return 0;
}
