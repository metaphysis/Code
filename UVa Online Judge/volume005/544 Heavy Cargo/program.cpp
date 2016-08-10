// Heavy Cargo
// UVa ID: 544
// Verdict: Accepted
// Submission Date: 2016-08-10
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

    int n, r, weight[201][201], cases = 0;
    while (cin >> n >> r, n && r)
    {
        map<string, int> cities;
        string start, end;
        int tons, count = 1;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                weight[i][j] = weight[j][i] = -1;
                
        for (int i = 1; i <= r; i++)
        {
            cin >> start >> end >> tons;
            if (cities.find(start) == cities.end())
                cities[start] = count++;
            if (cities.find(end) == cities.end())
                cities[end] = count++;
            if (tons > weight[cities[start]][cities[end]])
            {
                weight[cities[start]][cities[end]] = tons;
                weight[cities[end]][cities[start]] = tons;
            }
        }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (weight[i][k] != -1 && weight[k][j] != -1)
                        weight[i][j] = max(weight[i][j], min(weight[i][k], weight[k][j]));
        
        cin >> start >> end;            
        cout << "Scenario #" << ++cases << '\n';
        cout << weight[cities[start]][cities[end]] << " tons\n\n";
    }
    
	return 0;
}
