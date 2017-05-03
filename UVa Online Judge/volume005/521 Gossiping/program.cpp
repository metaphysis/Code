// Gossiping
// UVa ID: 521
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

struct driver
{
    int from, to, stop;
    
    bool operator < (const driver &d) const
    {
        if (from != d.from) return from < d.from;
        else return to < d.to;
    }
};

driver drivers[40];
bool connected[40][40];
int n, d, s;
int from, to, stop;
int si, di;
istringstream iss;
string line;

bool exchanged(int a, int b)
{
    vector<int> stop1;
    for (int i = drivers[a].stop; i < drivers[a].to; i++)
        stop1.push_back(i);
    while (stop1.size() <= 2000)
    {
        for (int i = drivers[a].to; i > drivers[a].from; i--)
            stop1.push_back(i);
        for (int i = drivers[a].from; i < drivers[a].to; i++)
            stop1.push_back(i);
    }
    
    vector<int> stop2;
    for (int i = drivers[b].stop; i < drivers[b].to; i++)
        stop2.push_back(i);
    while (stop2.size() <= 2000)
    {
        for (int i = drivers[b].to; i > drivers[b].from; i--)
            stop2.push_back(i);
        for (int i = drivers[b].from; i < drivers[b].to; i++)
            stop2.push_back(i);
    }
    
    for (int i = 0; i <= 2000; i++)
        if (stop1[i] == stop2[i])
            return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (getline(cin, line))
    {
        iss.clear(); iss.str(line);
        iss >> n >> d >> s;

        if (n == 0) break;

        memset(connected, false, sizeof(connected));

        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            iss.clear(); iss.str(line);
            iss >> from;
            while (iss >> stop) to = stop;

            getline(cin, line);
            iss.clear(); iss.str(line);
            while (iss >> si >> di)
                drivers[di] = driver{from, to, si};
        }

        sort(drivers, drivers + d);

        for (int i = 1; i <= d; i++)
            for (int j = i; j <= d; j++)
                connected[i][j] = connected[j][i] = exchanged(i, j);

        for (int k = 1; k <= d; k++)
            for (int i = 1; i <= d; i++)
                for (int j = 1; j <= d; j++)
                    connected[i][j] = connected[i][k] && connected[k][j];

        bool allConnected = true;
        for (int i = 1; i <= d; i++)
            if (!connected[1][i])
            {
                allConnected = false;
                break;
            }

        cout << (allConnected ? "Yes" : "No") << '\n';
    }
    
    return 0;
}
