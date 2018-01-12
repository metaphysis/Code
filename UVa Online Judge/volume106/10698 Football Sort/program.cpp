// Football Sort
// UVa ID: 10698
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.000s
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

struct squad
{
    string name, uppered;
    int points, played, scored, suffered, difference;
    
    bool operator < (const squad &s) const
    {
        if (points != s.points) return points > s.points;
        if (difference != s.difference) return difference > s.difference;
        if (scored != s.scored) return scored > s.scored;
        return uppered < s.uppered;
    }
}squads[32];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, G, C, cases = 0;

    while (cin >> T >> G, T > 0)
    {
        map<string, int> indexer;
        
        string name;
        for (int i = 0; i < T; i++)
        {
            cin >> name;
            indexer[name] = i;
            string uppered = name;
            for (int i = 0; i < uppered.length(); i++)
                uppered[i] = toupper(uppered[i]);
            squads[i] = squad{name, uppered, 0, 0, 0, 0, 0};
        }

        string homename, awayname;
        int homegoal, awaygoal;
        char dash;

        for (int i = 1; i <= G; i++)
        {
            cin >> homename >> homegoal >> dash >> awaygoal >> awayname;            
            int homeid = indexer[homename], awayid = indexer[awayname];
            squads[homeid].played++, squads[awayid].played++;
            squads[homeid].scored += homegoal, squads[awayid].scored += awaygoal;
            squads[homeid].suffered += awaygoal, squads[awayid].suffered += homegoal;
            if (homegoal > awaygoal) squads[homeid].points += 3;
            else if (homegoal == awaygoal) squads[homeid].points += 1, squads[awayid].points += 1;
            else squads[awayid].points += 3;
        }
        
        for (int i = 0; i < T; i++)
            squads[i].difference = squads[i].scored - squads[i].suffered;
        
        sort(squads, squads + T);

        if (cases++ > 0) cout << '\n';
        for (int i = 0, showRank = 1, trueRank = 1; i < T; i++, trueRank++)
        {
            bool updated = false;
            if (i)
            {
                if (squads[i].points != squads[i - 1].points ||
                    squads[i].difference != squads[i - 1].difference ||
                    squads[i].scored != squads[i - 1].scored)
                    {
                        showRank = trueRank;
                        updated = true;
                    }
            }
            else updated = true;

            if (updated) cout << setw(2) << right << showRank << '.';
            else cout << "   ";

            cout << setw(16) << right << squads[i].name;
            cout << setw(4) << right << squads[i].points;
            cout << setw(4) << right << squads[i].played;
            cout << setw(4) << right << squads[i].scored;
            cout << setw(4) << right << squads[i].suffered;
            cout << setw(4) << right << squads[i].difference;
            
            if (squads[i].played == 0) cout << setw(7) << right << "N/A";
            else
            {
                cout << setw(7) << right << fixed << setprecision(2);
                cout << (squads[i].points / (squads[i].played * 3.0) * 100.0);
            }
            
            cout << '\n';
        }
    }

    return 0;
}
