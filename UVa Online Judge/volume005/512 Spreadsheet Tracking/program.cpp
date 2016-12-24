// Spreadsheet Tracking
// UVa ID: 512
// Verdict: Accepted
// Submission Date: 2016-12-23
// UVa Run Time: 0.040s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    int r, c, n, A, q, originalR, originalC, nextR, nextC;
    string command;
    vector<vector<pair<int, int>>> grid;

    while (cin >> r >> c, r > 0)
    {
        grid.clear();
        
        for (int i = 1; i <= r; i++)
        {
            vector<pair<int, int>> row;
            for (int j = 1; j <= c; j++)
                row.push_back(make_pair(i, j));
            grid.push_back(row);
        }
                
        cin >> n;
        
        for (int k = 1; k <= n; k++)
        {
            cin >> command;
            if (command == "DR" || command == "DC" || command == "IR" || command == "IC")
            {
                cin >> A;
                
                vector<int> x(A);
                for (int i = 1; i <= A; i++)
                    cin >> x[i - 1];
                sort(x.begin(), x.end());
                
                if (command == "DR")
                {
                    for (int i = x.size() - 1; i >= 0; i--)
                        grid.erase(grid.begin() + x[i] - 1);

                    //cout << "DR OK" << endl;
                }
                else if (command == "DC")
                {
                    for (int i = x.size() - 1; i >= 0; i--)
                        for (int j = 0; j < grid.size(); j++)
                            grid[j].erase(grid[j].begin() + x[i] - 1);

                    //cout << "DC OK" << endl;
                }
                else if (command == "IR")
                {
                    for (int i = x.size() - 1; i >= 0; i--)
                        grid.insert(grid.begin() + x[i] - 1, vector<pair<int, int>>(grid.front().size(), make_pair(0, 0)));

                    //cout << "IR OK" << endl;
                }
                else if (command == "IC")
                {
                    for (int i = x.size() - 1; i >= 0; i--)
                        for (int j = 0; j < grid.size(); j++)
                            grid[j].insert(grid[j].begin() + x[i] - 1, make_pair(0, 0));

                    //cout << "IC OK" << endl;
                }
            }
            else
            {
                cin >> originalR >> originalC >> nextR >> nextC;
                swap(grid[originalR - 1][originalC - 1], grid[nextR - 1][nextC - 1]);

                //cout << "EX OK" << endl;
            }
            
            while (grid.size() < 50)
                grid.push_back(vector<pair<int, int>>(grid.front().size(), make_pair(0, 0)));
                
            if (grid.front().size() < 50)
            {
                for (int i = 0; i < grid.size(); i++)
                    for (int j = grid[i].size(); j <= 50; j++)
                        grid[i].push_back(make_pair(0, 0));
            }
        }
        
        if (cases > 0) cout << '\n';
        cout << "Spreadsheet #" << ++cases << '\n';
        
        pair<int, int> last[60][60];

        for (int i = 0; i <= r; i++)
            for (int j = 0; j <= c; j++)
                last[i][j] = make_pair(0, 0);

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                last[grid[i][j].first][grid[i][j].second] = make_pair(i + 1, j + 1);
                
        cin >> q;
        for (int k = 1; k <= q; k++)
        {
            cin >> r >> c;
            
            cout << "Cell data in (" << r << ',' << c << ") ";
            if (last[r][c].first > 0)
            {
                cout << "moved to (";
                cout << last[r][c].first << ',' << last[r][c].second << ")\n";
            }
            else
                cout << "GONE\n";
        }
    }
    
	return 0;
}
