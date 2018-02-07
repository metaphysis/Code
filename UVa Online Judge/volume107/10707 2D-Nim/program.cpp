// 2D-Nim
// UVa ID: 10707
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int board1[110][110], board2[110][110];
int x1[110], y1[110], x2[110], y2[110];
int H, W, n;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> W >> H >> n;
        for (int i = 0; i < n; i++)
            cin >> x1[i] >> y1[i];
        for (int i = 0; i < n; i++)
            cin >> x2[i] >> y2[i];
    }

    return 0;
}
