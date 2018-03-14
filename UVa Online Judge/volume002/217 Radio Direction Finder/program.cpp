// Radio Direction Finder
// UVa ID: 217
// Verdict: Accepted
// Submission Date: 2016-06-16
// UVa Run Time: 0.070s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0), EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct line
{
    double a, b, c;
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

map<string, point> beacons;
reading reading1, reading2;
boat mine;

double getAngle(double angle)
{
    if (angle <= 90.0 + EPSILON)
        return (90.0 - angle);
    else if (angle <= 270.0 + EPSILON)
        return -(angle - 90.0);
    else
        return 180.0 - (angle - 270.0);
}

line getLine(reading data)
{
    line lr;
    
    double angle = getAngle(mine.course + data.angle);
    if (fabs(fabs(angle) - 90.0) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -beacons[data.name].x;
    }
    else
    {
        lr.a = -tan(angle * PI / 180.0);
        lr.b = 1.0;
        lr.c = -(lr.a * beacons[data.name].x + lr.b * beacons[data.name].y);
    }
    
    return lr;
}

void calculate()
{
    double traveled = (reading2.time - reading1.time) * mine.speed;
    line line1 = getLine(reading1), line2 = getLine(reading2);
    
    double boatAngle = mine.course * PI / 180.0;
    double x1 = line1.c * line2.b - line1.b * line2.c -
        line1.b * line2.b * traveled * cos(boatAngle) -
        line1.b * line2.a * traveled * sin(boatAngle);
    x1 = x1 / (line1.b * line2.a - line1.a * line2.b);
    
    double y1 = line1.c * line2.a - line1.a * line2.c -
        line1.a * line2.a * traveled * sin(boatAngle) -
        line1.a * line2.b * traveled * cos(boatAngle);
    y1 = y1 / (line1.a * line2.b - line1.b * line2.a);
    
    cout << ": Position is (";
    cout << fixed << setprecision(2) << (x1 + traveled * sin(boatAngle)) << ", ";
    cout << fixed << setprecision(2) << (y1 + traveled * cos(boatAngle)) << ")" << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
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
            
            cout << "Scenario " << ++cases;
            if (fabs(reading1.angle - reading2.angle) <= EPSILON ||
                fabs(fabs(reading1.angle - reading2.angle) - 180.0) <= EPSILON)
            {
                cout << ": Position cannot be determined" << endl;
                continue;
            }
            
            calculate();
        }
    }
    
	return 0;
}
