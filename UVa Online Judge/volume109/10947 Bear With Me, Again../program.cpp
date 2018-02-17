// Bear With Me, Again..
// UVa ID: 10947
// Verdict: Accepted
// Submission Date: 2018-02-17
// UVa Run Time: 0.200s
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

struct island
{
    int x, y, r;
    island (int x = 0, int y = 0, int r = 0): x(x), y(y), r(r) {}
    double distTo(island &i)
    {
        return sqrt(pow(x - i.x, 2) + pow(y - i.y, 2)) - (r + i.r);
    }
} islands[110];

int K, M, N;
bool linked[110][110];

bool isLinked(island i1, island i2)
{
    return i1.distTo(i2) <= (K * M);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> K >> M)
    {
        cin >> islands[1].x >> islands[1].y >> islands[1].r;
        cin >> islands[2].x >> islands[2].y >> islands[2].r;
        cin >> N;
        N += 2;
        for (int i = 3; i <= N; i++)
            cin >> islands[i].x >> islands[i].y >> islands[i].r;
        memset(linked, false, sizeof(linked));
        for (int i = 1; i <= N; i++)
        {
            for (int j = i + 1; j <= N; j++)
                linked[i][j] = linked[j][i] = isLinked(islands[i], islands[j]);
            linked[i][i] = true;
        }
        for (int k = 1; k <= N; k++)
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    linked[i][j] |= linked[i][k] && linked[k][j];
        if (linked[1][2]) cout << "Larry and Ryan will escape!";
        else cout << "Larry and Ryan will be eaten to death.";
        cout << '\n';
    }

    return 0;
}
