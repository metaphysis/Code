// Cops and Robbers
// UVa ID: 361
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.490s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    bool operator<(const point &another) const
    {
        if (x != another.x)
            return x < another.x;
        else
            return y < another.y;
    }
};

vector<point> cops, robbers, citizens;
int c, r, o, minCopsY, maxCopsY, minRobbersY, maxRobbersY;

inline int direction(point &a, point &b, point &c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

bool isSafe(int person)
{
    if (citizens[person].x < cops.front().x) return false;
    if (citizens[person].x > cops.back().x) return false;
    if (citizens[person].y < minCopsY) return false;
    if (citizens[person].y > maxCopsY) return false;
    
    int start = lower_bound(cops.begin(), cops.end(), citizens[person]) - cops.begin();
    for (int i = start; i < cops.size(); i++)
        for (int j = 0; j < i; j++)
            for (int k = j + 1; k < i; k++)
            {
                int d1 = direction(cops[i], cops[j], citizens[person]);
                int d2 = direction(cops[j], cops[k], citizens[person]);
                int d3 = direction(cops[k], cops[i], citizens[person]);
                if (d1 <= 0 && d2 <= 0 && d3 <= 0) return true;
                if (d1 >= 0 && d2 >= 0 && d3 >= 0) return true;
            }
    return false;
}

bool isRobbed(int person)
{
    if (citizens[person].x < robbers.front().x) return false;
    if (citizens[person].x > robbers.back().x) return false;
    if (citizens[person].y < minRobbersY) return false;
    if (citizens[person].y > maxRobbersY) return false;
    
    int start = lower_bound(robbers.begin(), robbers.end(), citizens[person]) - robbers.begin();
    for (int i = start; i < robbers.size(); i++)
        for (int j = 0; j < i; j++)
            for (int k = j + 1; k < i; k++)
            {
                int d1 = direction(robbers[i], robbers[j], citizens[person]);
                int d2 = direction(robbers[j], robbers[k], citizens[person]);
                int d3 = direction(robbers[k], robbers[i], citizens[person]);
                if (d1 <= 0 && d2 <= 0 && d3 <= 0) return true;
                if (d1 >= 0 && d2 >= 0 && d3 >= 0) return true;
            }
    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int cases = 0, x, y;
    while (cin >> c >> r >> o)
    {
        if (c == 0 && r == 0 && o == 0) break;
        
        cops.clear();
        robbers.clear();
        citizens.clear();
        
        minCopsY = 1000, maxCopsY = -1000, minRobbersY = 1000, maxRobbersY = -1000;
        for (int i = 1; i <= c; i++)
        {
            cin >> x >> y;
            cops.push_back((point){x, y});
            minCopsY = min(minCopsY, y);
            maxCopsY = max(maxCopsY, y);
        }
        for (int i = 1; i <= r; i++)
        {
            cin >> x >> y;
            robbers.push_back((point){x, y});
            minRobbersY = min(minRobbersY, y);
            maxRobbersY = max(maxRobbersY, y);
        }
        for (int i = 1; i <= o; i++)
        {
            cin >> x >> y;
            citizens.push_back((point){x, y});
        }
        
        sort(cops.begin(), cops.end());
        sort(robbers.begin(), robbers.end());
        
        cout << "Data set " << ++cases << ":" << endl;
        for (int i = 0; i < citizens.size(); i++)
        {
            cout << "     Citizen at (" << citizens[i].x << "," << citizens[i].y << ") is ";
            if (isSafe(i)) cout << "safe." << endl;
            else if (isRobbed(i)) cout << "robbed." << endl;
            else cout << "neither." << endl;
        }
        
        cout << endl;
    }
    
	return 0;
}
