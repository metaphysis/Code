// Robot Crash
// UVa IDs: 204
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
#include <cmath>

using namespace std;

const double PI = 3.14159265358979323846, EPSILON = 1E-7;

struct robot
{
    double x, y, angle, radian, speed;
};

robot leftrobot, rightrobot;
int cases = 0;

double getLastY(double y, double dy, double angle)
{
    dy += (angle > 0) ? y : (10.0 - y);

    bool up = angle > 0;
    while (dy > 10.0)
    {
        dy -= 10.0;
        up = !up;
    }

    return up ? dy : (10.0 - dy);
}

void calculate()
{
    cases++;
    cout << "Robot Problem #" << cases << ": ";

    if (leftrobot.x >= (rightrobot.x + EPSILON))
    {
        cout << "Robots do not collide.\n\n";
        return;
    }

    if (leftrobot.angle == 0.0 && fabs(rightrobot.angle) == 180.0)
    {
        if (fabs(leftrobot.y - rightrobot.y) < EPSILON)
        {
            double collidex = leftrobot.x + leftrobot.speed *
                (fabs(rightrobot.x - leftrobot.x) / (leftrobot.speed +
                    rightrobot.speed));
            cout << "Robots collide at (";
            cout << fixed << setprecision(2) << collidex;
            cout << "," << fixed << leftrobot.y;
            cout << ")\n\n";
        }
        else
            cout << "Robots do not collide.\n\n";
        return;
    }

    leftrobot.radian = fabs(leftrobot.angle) * PI / 180.0;
    rightrobot.radian = fabs(rightrobot.angle) * PI / 180.0;

    double dx = fabs(rightrobot.x - leftrobot.x);
    double time = dx / (leftrobot.speed * cos(leftrobot.radian) +
        rightrobot.speed * fabs(cos(rightrobot.radian)));

    double leftdy = leftrobot.speed * sin(leftrobot.radian) * time;
    double rightdy = rightrobot.speed * sin(rightrobot.radian) * time;

    leftdy = getLastY(leftrobot.y, leftdy, leftrobot.angle);
    rightdy = getLastY(rightrobot.y, rightdy, rightrobot.angle);

    cout << leftdy << " : " << rightdy << " ";
    
    if (fabs(leftdy - rightdy) < EPSILON)
    {
        cout << "Robots collide at (";
        cout << fixed << setprecision(2) << (leftrobot.x +
            leftrobot.speed * cos(leftrobot.radian) * time);
        cout << ",";
        cout << fixed << setprecision(2) << leftdy;
        cout << ")\n\n";
    }
    else
    {
        cout << "Robots do not collide.\n\n";
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> leftrobot.x >> leftrobot.y >>
            leftrobot.angle >> leftrobot.speed;
        
        cout << leftrobot.x << " " << leftrobot.y << " " << leftrobot.angle << " " << leftrobot.speed << endl;
        
        getline(cin, line);
        iss.clear();
        iss.str(line);
        iss >> rightrobot.x >> rightrobot.y >>
            rightrobot.angle >> rightrobot.speed;

        cout << rightrobot.x << " " << rightrobot.y << " " << rightrobot.angle << " " << rightrobot.speed << endl;
        
        calculate();
    }

    return 0;
}
