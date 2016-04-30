// Getting in Line
// UVa IDs: 216
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.000s
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

struct point
{
    int x, y;
};

vector <point> network;
int cases = 0, computers;
double matrix[8][8];

double distances(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void calculate()
{
    for (int i = 0; i < computers; i++)
        for (int j = 0; j < computers; j++)
            matrix[i][j] = distances(network[i], network[j]);
            
    vector <int> permutation;
    for (int i = 0; i < computers; i++)
        permutation.push_back(i);
    
    vector <int> best(permutation.size());
    double minimum = numeric_limits<int>::max();
    do
    {
        double currentLength = 0.0;
        for (int i = 0; i < computers - 1; i++)
            currentLength += matrix[permutation[i]][permutation[i + 1]];
        if (currentLength < minimum)
        {
            minimum = currentLength;
            copy(permutation.begin(), permutation.end(), best.begin());
        }
    } while (next_permutation(permutation.begin(), permutation.end()));

    cases++;
    
    cout << "**********************************************************" << endl;
    cout << "Network #" << cases << endl;
    double length = 0.0;
    for (int i = 0; i < best.size() - 1; i++)
    {
        cout << "Cable requirement to connect (";
        cout << network[best[i]].x << "," << network[best[i]].y << ") to (";
        cout << network[best[i + 1]].x << "," << network[best[i + 1]].y << ") is ";
        double cable = matrix[best[i]][best[i + 1]] + 16.0;
        cout << fixed << setprecision(2) << cable;
        cout << " feet." << endl;
        length += cable;
    }
    
    cout << "Number of feet of cable required is ";
    cout << fixed << setprecision(2) << length;
    cout << "." << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    while (cin >> computers, computers)
    {
        network.clear();
        for (int i = 1; i <= computers; i++)
        {
            point dot;
            cin >> dot.x >> dot.y;
            network.push_back(dot);
        }
        calculate();
    }
    
	return 0;
}
