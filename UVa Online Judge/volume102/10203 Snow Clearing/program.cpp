// Snow Clearing
// UVa ID: 10203
// Verdict: Accepted
// Submission Date: 2017-08-21
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);

    getline(cin, line);
    for (int c = 0; c < cases; c++)
    {
        getline(cin, line);

        double x1, y1, x2, y2;
        double trail = 0.0;
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            iss >> x1 >> y1 >> x2 >> y2;
            trail += sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        }
        
        double time = trail * 3.0 / 500.0;
        stringstream ss;
        string total;
        ss << fixed << setprecision(0) << time;
        ss >> total;
        
        int minutes = stoi(total);
        int hours = minutes / 60;
        minutes %= 60;
        
        if (c > 0) cout << '\n';
        cout << hours << ':';
        if (minutes < 10) cout << '0';
        cout << minutes << '\n';
    }
    
    return 0;
}
