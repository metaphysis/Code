// Radio Direction Finder
// UVa IDs: 217
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <set>

using namespace std;

const double PI = 3.14159265358979323846, EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct boat
{
    double course, speed;
};

struct reading
{
    string name;
    double time, angle;
};

map <string, point> beacons;
reading reading1, reading2;
boat mine;

void calculate()
{
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int counter, cases = 0;
    while (cin >> counter)
    {
        beacons.clear();
        for (int i = 1; i <= counter; i++)
        {
            string name;
            double x, y;
            cin >> name >> x >> y;
            
            point location;
            location.x = x;
            location.y = y;
            
            beacons.insert(make_pair(name, location));
        }
        
        cin >> counter;
        for (int i = 1; i <= counter; i++)
        {
            cin >> mine.course >> mine.speed;
            cin >> reading1.time >> reading1.name >> reading1.angle;
            cin >> reading2.time >> reading2.name >> reading2.angle;
            
            cases++;
            cout << "Scenario " << cases << ": Position ";
            calculate();
            cout << endl;
        }
    }
    
	return 0;
}
