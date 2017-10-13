// Guardian of Decency
// UVa ID: 12083
// Verdict: Accepted
// Submission Date: 2017-10-13
// UVa Run Time: 0.030s
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

const int MAXV = 510;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    int matches = 0;
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

struct pupil
{
    int height;
    string gender, music, sport;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, number;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        vector<pupil> males, females;

        cin >> number;
        for (int i = 1; i <= number; i++)
        {
            pupil p;
            cin >> p.height >> p.gender >> p.music >> p.sport;
            if (p.gender == "M")
                males.push_back(p);
            else
                females.push_back(p);
        }
        
        memset(g, 0, sizeof g);
        for (int i = 0; i < males.size(); i++)
            for (int j = 0; j < females.size(); j++)
                if (abs(males[i].height - females[j].height) <= 40 &&
                    males[i].music == females[j].music &&
                    males[i].sport != females[j].sport)
                        g[i][j] = 1;

        tx = males.size(), ty = females.size();                
        cout << (males.size() + females.size() - hungarian()) << '\n';
    }
    
    return 0;
}
