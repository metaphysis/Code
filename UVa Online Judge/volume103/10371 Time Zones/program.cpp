// Time Zones
// UVa ID: 10371
// Verdict: Accepted
// Submission Date: 2017-12-28
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

map<string, int> zones = {
    {"UTC", 0}, {"GMT", 0}, {"BST", 60}, {"IST", 60}, {"WET", 0}, {"WEST", 60},
    {"CET", 60}, {"CEST", 120}, {"EET", 120}, {"EEST", 180}, {"MSK", 180},
    {"MSD", 240}, {"AST", -240}, {"ADT", -180}, {"NST", -210}, {"NDT", -150},
    {"EST", -300}, {"EDT", -240}, {"CST", -360}, {"CDT", -300}, {"MST", -420},
    {"MDT", -360}, {"PST", -480}, {"PDT", -420}, {"HST", -600}, {"AKST", -540},
    {"AKDT", -480}, {"AEST", 600}, {"AEDT", 660}, {"ACST", 570}, {"ACDT", 630},
    {"AWST", 480}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        string time, postfix, zone1, zone2;
        cin >> time;
        if (time != "midnight" && time != "noon") cin >> postfix;
        cin >> zone1 >> zone2;
        
        int tm1 = 0;
        if (time == "midnight") tm1 = 0;
        else if (time == "noon") tm1 = 720;
        else
        {
            istringstream iss(time);
            string sh, sm;
            getline(iss, sh, ':');
            getline(iss, sm, ':');
            int hh = stoi(sh), mm = stoi(sm);
            if (hh == 12) hh = 0;
            tm1 = hh * 60 + mm;
            if (postfix == "p.m.") tm1 += 720;
        }
        
        int tm2 = tm1 - zones[zone1] + zones[zone2];
        tm2 = (tm2 + 1440) % 1440;
        if (tm2 == 0) cout << "midnight\n";
        else if (tm2 == 720) cout << "noon\n";
        else
        {
            int hh = (tm2 / 60) % 12, mm = tm2 % 60;
            if (hh == 0) hh = 12;
            cout << hh << ':' << setw(2) << setfill('0') << mm;
            if (tm2 < 720) cout << " a.m.\n";
            else cout << " p.m.\n";
        }
    }

    return 0;
}
