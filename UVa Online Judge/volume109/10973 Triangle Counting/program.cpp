// Triangle Counting
// UVa ID: 10973
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.090s
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

int edges[3010][3010], cnt[3010];
    
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int n, m, a, b, flag[3010];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        
        for (int i = 1; i <= n; i++)
            cnt[i] = 0, flag[i] = 0;
        
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> b;
            if (a > b) edges[b][cnt[b]++] = a;
            else edges[a][cnt[a]++] = b;
        }
        
        int count = 0;
        for (int v1 = 1; v1 <= n; v1++)
        {
            for (int v2 = 0; v2 < cnt[v1]; v2++) flag[edges[v1][v2]] = 1;
            for (int v2 = 0; v2 < cnt[v1]; v2++)
                for (int v3 = 0; v3 < cnt[edges[v1][v2]]; v3++)
                    count += flag[edges[edges[v1][v2]][v3]];
            for (int v2 = 0; v2 < cnt[v1]; v2++) flag[edges[v1][v2]] = 0;
        }
        cout << count << '\n';
    }
    
    return 0;
}
