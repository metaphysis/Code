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

list<int> edges[1010];
int t;
int maxLength;
int visited[1010];

void dfs(int u, int length)
{
    if (u == t && length > maxLength) maxLength = length;
    if (u == t) return;
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v, length + 1);
    visited[u] = 0;
}

int main(int argc, char *argv[])
{
    t = 10, maxLength = 0;
    memset(visited, 0, sizeof(visited));
    dfs(0, 0);
    cout << "maxLength = " << maxLength << '\n';

    return 0;
}
