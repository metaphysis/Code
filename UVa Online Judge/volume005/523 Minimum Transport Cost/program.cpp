// Minimum Transport Cost
// UVa ID: 523
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.020s
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

int cost[100][100], path[100][100], tax[100], cities;

void findPath(int from, int to)
{
    if (path[from][to] > 0)
    {
        int k = path[from][to];
        findPath(from, k);
        cout << "-->" << k;
        findPath(k, to);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1)
            cout << '\n';
            
        getline(cin, line);
        istringstream iss(line);
        int value;
        cities = 0;
        while (iss >> value)
            cost[1][++cities] = value;

        for (int i = 2; i <= cities; i++)
        {
            getline(cin, line);
            iss.clear();
            iss.str(line);
            int counter = 0;
            while (iss >> value)
                cost[i][++counter] = value;
        }

        getline(cin, line);
        iss.clear();
        iss.str(line);
        int counter = 1;
        while (iss >> value)
            tax[counter++] = value;

        memset(path, 0, sizeof(path));

        //floyd-warshall
        for (int k = 1; k <= cities; k++)
            for (int i = 1; i <= cities; i++)
                for (int j = 1; j <= cities; j++)
                    if (cost[i][k] >= 0 && cost[k][j] >= 0 &&
                        (cost[i][j] == -1 || cost[i][k] + cost[k][j] + tax[k] < cost[i][j]))
                    {
                        cost[i][j] = cost[i][k] + cost[k][j] + tax[k];
                        path[i][j] = k;
                    }

        bool first_line = true;            
        while (getline(cin, line), line.length() > 0)
        {
            if (first_line)
                first_line = false;
            else
                cout << '\n';

            int from, to;
            iss.clear();
            iss.str(line);
            iss >> from >> to;

            cout << "From " << from << " to " << to << " :\n";
            cout << "Path: " << from;
            findPath(from, to);
            if (from != to)
                cout << "-->" << to;
            cout << '\n';
            cout << "Total cost : " << cost[from][to] << '\n';
        }
    }

	return 0;
}
