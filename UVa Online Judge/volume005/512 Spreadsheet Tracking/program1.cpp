// Spreadsheet Tracking
// UVa ID: 512
// Verdict: Accepted
// Submission Date: 2016-12-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    int r, c, n, A, q, originalR, originalC, nextR, nextC;
    int x[10], z[60];
    string command;
    pair<int, int> grid[60][60];

    while (cin >> r >> c, r > 0)
    {
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                grid[i][j] = make_pair(i, j);
                
        cin >> n;
        for (int k = 1; k <= n; k++)
        {
            cin >> command;
            if (command == "DR" || command == "DC" || command == "IR" || command == "IC")
            {
                cin >> A;
                for (int i = 0; i < A; i++) cin >> x[i];

                sort(x, x + A);

                if (command == "DR" || command == "DC")
                {
                    for (int i = 1; i <= 50; i++)
                    {
                        if (binary_search(x, x + A, i))
                            z[i] = i;
                        else
                            z[i] = upper_bound(x, x + A, i) - x;
                    }

                    if (command == "DR")
                    {
                        for (int i = 1; i <= r; i++)
                            for (int j = 1; j <= c; j++)
                                if (grid[i][j].first > 0 && grid[i][j].second > 0)
                                    grid[i][j].first -= z[grid[i][j].first];
                    }
                    else
                    {
                        for (int i = 1; i <= r; i++)
                            for (int j = 1; j <= c; j++)
                                if (grid[i][j].first > 0 && grid[i][j].second > 0)
                                    grid[i][j].second -= z[grid[i][j].second];
                    }
                }
                else
                {
                    for (int i = 1; i <= 50; i++)
                        z[i] = upper_bound(x, x + A, i) - x;

                    if (command == "IR")
                    {
                        for (int i = 1; i <= r; i++)
                            for (int j = 1; j <= c; j++)
                                if (grid[i][j].first > 0 && grid[i][j].second > 0)
                                    grid[i][j].first += z[grid[i][j].first];
                    }
                    else
                    {
                        for (int i = 1; i <= r; i++)
                            for (int j = 1; j <= c; j++)
                                if (grid[i][j].first > 0 && grid[i][j].second > 0)
                                    grid[i][j].second += z[grid[i][j].second];
                    }
                }
            }
            else
            {
                cin >> originalR >> originalC >> nextR >> nextC;
                for (int i = 1; i <= r; i++)
                    for (int j = 1; j <= c; j++)
                    {
                        if (grid[i][j].first == originalR && grid[i][j].second == originalC)
                            grid[i][j] = make_pair(nextR, nextC);
                        else if (grid[i][j].first == nextR && grid[i][j].second == nextC)
                            grid[i][j] = make_pair(originalR, originalC);
                    }
            }
        }
        
        if (cases > 0) cout << '\n';
        cout << "Spreadsheet #" << ++cases << '\n';
                
        cin >> q;
        for (int k = 1; k <= q; k++)
        {
            cin >> r >> c;
            
            cout << "Cell data in (" << r << ',' << c << ") ";
            if (grid[r][c].first > 0 && grid[r][c].second > 0)
            {
                cout << "moved to (";
                cout << grid[r][c].first << ',' << grid[r][c].second << ")\n";
            }
            else
                cout << "GONE\n";
        }
    }
    
	return 0;
}
