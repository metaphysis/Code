// Bankrupt Baker
// UVa ID: 11308
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.040s
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

struct recipe
{
    string name;
    int cost;
    
    bool operator < (const recipe &r) const
    {
        if (cost != r.cost) return cost < r.cost;
        return name < r.name;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int C = 1; C <= cases; C++)
    {
        string title;
        
        cin.ignore(1024, '\n');
        getline(cin, title);
        for (int i = 0; i < title.length(); i++)
            title[i] = toupper(title[i]);

        int m, n, b;
        cin >> m >> n >> b;
        
        map<string, int> price;
        string ingredient;
        int c;

        for (int i = 1; i <= m; i++)
        {
            cin >> ingredient >> c;
            price[ingredient] = c;
        }

        string name;
        int k;
        
        vector<recipe> rs;
        for (int i = 1; i <= n; i++)
        {
            cin.ignore(1024, '\n');
            getline(cin, name);

            recipe r = recipe{name, 0};

            cin >> k;
            for (int j = 1; j <= k; j++)
            {
                cin >> ingredient >> c;
                r.cost += price[ingredient] * c;
            }
            if (r.cost <= b) rs.push_back(r);
        }
        
        sort(rs.begin(), rs.end());
        
        cout << title << '\n';
        if (rs.size() == 0) cout << "Too expensive!\n";
        else
        {
            for (auto r : rs) cout << r.name << '\n';
        }
        cout << '\n';
    }

    return 0;
}
