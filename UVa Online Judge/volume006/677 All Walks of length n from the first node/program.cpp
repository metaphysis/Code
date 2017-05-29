// All Walks of length n from the first node
// UVa ID: 677
// Verdict: Accepted
// Submission Date: 2017-05-29
// UVa Run Time: 0.000s
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
#include <vector>

using namespace std;

int nodes, walks, solutions;
int linked[20][20], used[20], selected[20], sorted[20];

void dfs(int depth)
{
    if (depth == walks)
    {
        solutions++;
        cout << "(1";
        for (int i = 1; i < walks; i++)
            cout << ',' << selected[i];
        cout << ")\n";
    }
    else
    {
        for (int i = 2; i <= nodes; i++)
            if (!used[i] && linked[selected[depth - 1]][i])
            {
                used[i] = 1;
                selected[depth] = i;
                dfs(depth + 1);
                used[i] = 0;
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int cases = 0;
    while (cin >> nodes >> walks)
    {
        if (cases++ > 0) cout << '\n';

        for (int i = 1; i <= nodes; i++)
            for (int j = 1; j <= nodes; j++)
                cin >> linked[i][j];

        cin >> solutions;

        memset(used, 0, sizeof(used));
        solutions = 0, selected[0] = 1, used[1] = 1, walks += 1;

        dfs(1);

        if (solutions == 0) cout << "no walk of length " << (walks - 1) << '\n';
    }
    
    return 0;
}
