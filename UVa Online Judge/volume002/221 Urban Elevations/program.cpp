// Urban Elevations
// UVa IDs: 221
// Verdict: 
// Submission Date: 2016-05-15
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

struct building
{
    int index;
    double x, y, width, depth, height;
    
    bool operator<(building another) const
    {
        if (x != another.x)
            return x < another.x;
        else
            return y < another.y;
    }
};

vector < building > buildings;

void findVisibleBuilding()
{
    
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int n, first = 1;
    while (cin >> n, n)
    {
        building.clear();
        
        double x, y, width, depth, height;
        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y >> width >> depth >> heigth;
            buildings.push_back((building){i, x, y, width, depth, height});
        }
        
        if (first)
            first = 0;
        else
            cout << endl;
            
        findVisibleBuilding();
    }
    
	return 0;
}
