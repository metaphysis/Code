// Image Coding
// UVa ID: 11588
// Verdict: Accepted
// Submission Date: 2018-01-12
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

    int X, R, C, M, N, F[26];
    char letter;

    cin >> X;
    for (int c = 1; c <= X; c++)
    {
        cin >> R >> C >> M >> N;
        memset(F, 0, sizeof(F));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
            {
                cin >> letter;
                F[letter - 'A']++;
            }
        sort(F, F + 26, greater<int>());
        int bytes = M * F[0];
        for (int i = 1; i < 26; i++)
            if (F[i] == F[0])
                bytes += M * F[i];
            else
                bytes += N * F[i];
        cout << "Case " << c << ": " << bytes << '\n';
    }

    return 0;
}
