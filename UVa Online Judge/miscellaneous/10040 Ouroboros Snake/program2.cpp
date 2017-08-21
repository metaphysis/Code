// Ouroboros Snake
// UVa ID: 10040
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

int n, k;
int used[1 << 21], sequence[1 << 21], top;
int bits, mask;

void hierholzer(int u)
{
    stack<int> path; path.push(u);
    vector<int> circuit;

    int current = u;
    while (!path.empty())
    {
        if (edges[current].size())
        {
            path.push(current);
            int next = edges[current].front();
            edges[current].erase(edges[current].begin());
            current = next;
        }
        else
        {
            circuit.push_back(current);
            current = path.top();
            path.pop();
        }
    }

    for (int i = circuit.size() - 1; i > 0; i--)
        printTrail(circuit[i], circuit[i - 1]);
}

int main(int argc, char *argv[])
{
    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;

        bits = 1 << n, mask = (1 << (n - 1)) - 1;
        
        hierholzer(0);
    }

    return 0;
}
