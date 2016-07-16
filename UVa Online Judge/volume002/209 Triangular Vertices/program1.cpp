// Triangular Vertices
// UVa ID: 209
// Verdict: Accepted
// Submission Date: 2016-05-03
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

vector < int > vertices;
vector < point > locations;
point coordinates[33000];

double distances(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void initialize()
{
    point start;
    start.x = 0.0;
    start.y = 0.0;
    
    for (int n = 1, step = 1; n < 32767; n += step, step++)
    {
        coordinates[n].x = start.x;
        coordinates[n].y = start.y;
        
        for (int i = 1; i < step; i++)
        {
            coordinates[n + i].x = coordinates[n + i - 1].x + 2.0;
            coordinates[n + i].y = start.y;
        }
        
        start.x -= 1.0;
        start.y -= sqrt(3.0);
    }
}

bool triangle()
{
    if (abs(locations[0].y - locations[1].y) <= EPSILON ||
        abs(locations[1].y - locations[2].y) <= EPSILON)
    {
        double side1 = distances(locations[0], locations[1]);
        double side2 = distances(locations[0], locations[2]);
        double side3 = distances(locations[1], locations[2]);

        if (abs(side1 - side2) > EPSILON || abs(side2 - side2) > EPSILON)
            return false;
        return true;
    }
    return false;
}

bool parallelogram()
{
    if ((abs(locations[0].y - locations[1].y) <= EPSILON &&
        abs(locations[2].y - locations[3].y) <= EPSILON) ||
        abs(locations[1].y - locations[2].y) <= EPSILON)
    {
        double side1 = distances(locations[0], locations[1]);
        double side2 = distances(locations[0], locations[2]);
        double side3 = distances(locations[2], locations[3]);
        if (abs(side1 - side2) > EPSILON || abs(side2 - side3) > EPSILON ||
            abs(side1 - side3) > EPSILON)
            return false;
        return true;
    }
    return false;
}

bool hexagon()
{
    if (abs(locations[0].y - locations[1].y) <= EPSILON &&
        abs(locations[2].y - locations[3].y) <= EPSILON &&
        abs(locations[4].y - locations[5].y) <= EPSILON)
    {
        double side1 = distances(locations[0], locations[1]);
        double side2 = distances(locations[0], locations[2]);
        double side3 = distances(locations[1], locations[3]);
        double side4 = distances(locations[2], locations[4]);
        double side5 = distances(locations[3], locations[5]);
        double side6 = distances(locations[4], locations[5]);
        double side7 = distances(locations[2], locations[3]);
        
        if (abs(side1 - side2) > EPSILON || abs(side2 - side3) > EPSILON ||
            abs(side3 - side4) > EPSILON || abs(side4 - side5) > EPSILON ||
            abs(side5 - side6) > EPSILON || abs(side7 - side1 * 2.0) > EPSILON)
            return false;
        return true;        
    }
    return false;
}

void analyze(string line)
{
    cout << line;

    locations.clear();
    for (int i = 0; i < vertices.size(); i++)
        locations.push_back(coordinates[vertices[i]]);

    if (vertices.size() == 3 && triangle())
        cout << " are the vertices of a triangle\n";
    else if (vertices.size() == 4 && parallelogram())
        cout << " are the vertices of a parallelogram\n";
    else if (vertices.size() == 6 && hexagon())
        cout << " are the vertices of a hexagon\n";
    else
        cout << " are not the vertices of an acceptable figure\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    initialize();
    
    string line;
    while (getline(cin, line))
    {
        vertices.clear();

        int index;
        istringstream iss(line);
        while (iss >> index)
            vertices.push_back(index);

        sort(vertices.begin(), vertices.end());
        int n = unique(vertices.begin(), vertices.end()) - vertices.begin();

        if (n != vertices.size())
            cout << line << " are not the vertices of an acceptable figure\n";
        else
            analyze(line);
    }

    return 0;
}
