// Tiling Up Blocks
// UVa ID: 1196
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

struct tile
{
    int l, m;
    bool operator<(const tile &t) const
    {
        if (l != t.l) return l < t.l;
        else return m < t.m;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, left, middle;
    while (cin >> n, n > 0)
    {
        vector<tile> tiles, length(n, 1), index(n);
        for (int i = 0; i < n; i++)
        {
            cin >> left >> middle;
            tiles.push_back(tile{left, middle});
            index[i] = i;
        }
        
        sort(tiles.begin(), tiles.end());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                if (tiles[i].l >= tiles[index[j]].l && tiles[i].m >= tiles[index[j]].m)
                    index[j] = i, length[j] += 1;
        
    }
    
    return 0;
}
