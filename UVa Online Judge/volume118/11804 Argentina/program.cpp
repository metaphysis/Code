// Argentina
// UVa ID: 11804
// Verdict: Accepted
// Submission Date: 2017-11-09
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct player
{
    string name;
    int attack, defence;
};

bool cmp1(player a, player b)
{
    if (a.attack != b.attack) return a.attack > b.attack;
    if (a.defence != b.defence) return a.defence < b.defence;
    return a.name < b.name;
}

bool cmp2(player a, player b)
{
    return a.name < b.name;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    player players[10];
    
    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 10; i++)
            cin >> players[i].name >> players[i].attack >> players[i].defence;
        
        sort(players, players + 10, cmp1);
        sort(players, players + 5, cmp2);
        sort(players + 5, players + 10, cmp2);
        
        cout << "Case " << c << ":\n";
        
        cout << '(';
        for (int i = 0; i < 5; i++)
        {
            if (i) cout << ", ";
            cout << players[i].name;
        }
        cout << ")\n";

        cout << '(';
        for (int i = 5; i < 10; i++)
        {
            if (i - 5) cout << ", ";
            cout << players[i].name;
        }
        cout << ")\n";
    }
    
    return 0;
}
