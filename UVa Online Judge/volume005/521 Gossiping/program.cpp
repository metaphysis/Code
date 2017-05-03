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
    int stopi, stopj, start;
    
    bool operator < (const driver &d) const
    {
        if (stopi != d.stopi) return stopi < d.stopi;
        else return stopj < d.stopj;
    }
};

driver drivers[40];
bool connected[40][40];
int n, d, s;
int stopi, stopj, tempj;
int si, di;
istringstream iss;
string line;

bool exchanged(int i, int j)
{
    if (i > j) swap(i, j);

    if (i == j) return true;
    else
    {
        if (drivers[i].stopj < drivers[j].stopi) return false;
        if (drivers[i].stopi == drivers[j].stopi && drivers[i].stopj == drivers[j].stopj)
            return abs(drivers[i].start - drivers[j].start) % 2 == 1;
        if (drivers[i].stopj >= drivers[j].stopi && drivers[i].stopi <= drivers[j].stopi)
            if (drivers[i].stopj - drivers[i].stopi == drivers[j].stopj - drivers[j].stopi)
                return (drivers[i].start - drivers[i].stopi) == (drivers[j].start - drivers[j].stopi);
        return true;
    }
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
            iss >> stopi;
            while (iss >> tempj) stopj = tempj;

            getline(cin, line);
            iss.clear(); iss.str(line);
            while (iss >> si >> di)
                drivers[di] = driver{stopi, stopj, si};
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
