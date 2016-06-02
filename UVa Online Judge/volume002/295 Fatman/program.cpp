// Fatman
// UVa IDs: 295
// Verdict: Accepted
// Submission Date: 2016-06-03
// UVa Run Time: 0.870s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

// http://www.algorithmist.com/index.php/UVa_295

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <set>
#include <vector>

using namespace std;

vector < pair < int, int > > obstacles;
vector < vector < int > > edges;
vector < bool > visited;
int L, W, N, top, bottom;

double distances(pair < int, int > x, pair < int, int > y)
{
    return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

void build(double diameter)
{
    edges.clear();

    for (int i = 0; i < obstacles.size() + 2; i++)
        edges.push_back(vector < int >());

    for (int i = 0; i < obstacles.size(); i++)
    {
        for (int j = i + 1; j < obstacles.size(); j++)
            if (distances(obstacles[i], obstacles[j]) < diameter)
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }

        if (W - obstacles[i].second < diameter)
            edges[top].push_back(i);

        if (obstacles[i].second < diameter)
            edges[i].push_back(bottom);
    }
}

bool dfs(int vertex)
{
    visited[vertex] = true;
    for (int i = 0; i < edges[vertex].size(); i++)
        if (visited[edges[vertex][i]] == false)
            dfs(edges[vertex][i]);
}

bool squeezeThrough(double diameter)
{
    build(diameter);
    fill(visited.begin(), visited.end(), false);
    dfs(top);
    return visited[bottom] == false;
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;

    for (int runs = 1; runs <= cases; runs++)
    {
        cin >> L >> W >> N;

        obstacles.clear();
        for (int i = 1, x, y; i <= N; i++)
        {
            cin >> x >> y;
            obstacles.push_back(make_pair(x, y));
        }

        if (W == 0)
        {
            cout << "Maximum size in test case " << runs << " is ";
            cout << fixed << setprecision(4) << (double)W << "." << endl;
            continue;
        }

        top = obstacles.size();
        bottom = obstacles.size() + 1;
        visited.resize(obstacles.size() + 2);

        // binary search the diameter of fatman
        double high = W, low = 0.0, middle;
        while (fabs(high - low) >= 1E-9)
        {
            middle = (high + low) / 2.0;
            if (squeezeThrough(middle))
                low = middle;
            else
                high = middle;
        }

        cout << "Maximum size in test case " << runs << " is ";
        cout << fixed << setprecision(4) << low << "." << endl;
    }

    return 0;
}
