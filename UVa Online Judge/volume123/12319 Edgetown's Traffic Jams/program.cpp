// Edgetown's Traffic Jams
// UVa ID: 12319
// Verdict: Accepted
// Submission Date: 2018-02-17
// UVa Run Time: 0.150s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, u, v, A, B;
    int dist1[110][110], dist2[110][110];
    string line;

    while (cin >> n, n > 0)
    {
        cin.ignore(1024, '\n');

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist1[i][j] = dist2[i][j] = 10000;

        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            iss >> u;
            while (iss >> v) dist1[u][v] = 1;
            dist1[i][i] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            iss >> u;
            while (iss >> v) dist2[u][v] = 1;
            dist2[i][i] = 0;
        }
        cin >> A >> B;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    dist1[i][j] = min(dist1[i][j], dist1[i][k] + dist1[k][j]);
                    dist2[i][j] = min(dist2[i][j], dist2[i][k] + dist2[k][j]);
                }
        bool yes = true;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist2[i][j] > A * dist1[i][j] + B)
                {
                    yes = false;
                    goto print;
                }
        print:
        if (yes) cout << "Yes";
        else cout << "No";
        cout << '\n';
    }

    return 0;
}
