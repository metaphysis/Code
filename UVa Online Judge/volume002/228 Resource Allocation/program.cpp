// Resource Allocation
// UVa IDs: 228
// Verdict: Accepted
// Submission Date: 2016-06-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int d, p, b, n, k;
int option[25][15][15], programmer[25][15], budget[25][15];
int visited[25], used[25][15][15];
map<int, pair<int, int>> path, best;
int max_code_lines, max_programmer, max_budget;

void dfs(int current_programmer, int current_budget, int current_code_lines)
{
    if (current_code_lines > max_code_lines)
    {
        max_code_lines = current_code_lines;
        max_programmer = current_programmer;
        max_budget = current_budget;
        best.clear();
        for (auto p : path)
            best.insert(p);
    }
    
    for (int i = 1; i <= d; i++)
        if (visited[i] == 0)
        {
            visited[i] = 1;
            
            for (int x = 1; x <= programmer[i][0]; x++)
                for (int y = 1; y <= budget[i][0]; y++)
                {
                    if (used[i][x][y] == 1) continue;
                    if (current_programmer + programmer[i][x] > p) continue;
                    if (current_budget + budget[i][y] > b) continue;
                    
                    used[i][x][y] = 1;
                    path[i] = make_pair(x, y);
                    dfs(current_programmer + programmer[i][x], current_budget + budget[i][y], current_code_lines + option[i][x][y]);
                    path.erase(i);
                    used[i][x][y] = 0;
                }
            
            visited[i] = 0;
        }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> d, d > 0)
    {
        cin >> p >> b;
        
        for (int i = 1; i <= d; i++)
        {
            cin >> n;
            programmer[i][0] = n;
            for (int j = 1; j <= n; j++)
                cin >> programmer[i][j];
                
            cin >> k;
            budget[i][0] = k;
            for (int j = 1; j <= k; j++)
                cin >> budget[i][j];
            
            for (int x = 1; x <= n; x++)
                for (int y = 1; y <= k; y++)
                    cin >> option[i][x][y];
        }
        
        if (cases)
            cout << endl << endl;
        cout << "Optimal resource allocation problem #" << ++cases << endl;

        memset(visited, 0, sizeof(visited));
        memset(used, 0, sizeof(used));
        max_code_lines = 0, max_programmer = 0, max_budget = 0;
        dfs(0, 0, 0);
        
        cout << endl;
        cout << "Total budget: $" << max_budget << endl;
        cout << "Total new programmers: " << max_programmer << endl;
        cout << "Total productivity increase: " << max_code_lines << endl;
        
        for (int i = 1; i <= d; i++)
        {
            cout << endl;
            cout << "Division #" << i << " resource allocation:" << endl;
            cout << "Budget:  $" << budget[i][best[i].second] << endl;
            cout << "Programmers: " << programmer[i][best[i].first] << endl;
            cout << "Incremental lines of code: " << option[i][best[i].first][best[i].second]<< endl;
        }
    }
    
	return 0;
}
