// Of(f) Course!
// UVa ID: 267
// Verdict: Accepted
// Submission Date: 2016-05-27
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <set>

using namespace std;

const double PI = 2.0 * acos(0.0), EPSILON = 1E-7;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    double wind_speed, wind_direction, air_speed, desired_course;
    while (cin >> wind_speed >> wind_direction >> desired_course >> air_speed)
    {
        cout.precision(2);
        cout.setf(ios::fixed);
        
        cout << "WIND SPEED " << wind_speed << "\n";
        cout << "WIND DIRECTION " << wind_direction << "\n";
        cout << "DESIRED COURSE " << desired_course << "\n";
        cout << "TRUE AIRSPEED " << air_speed << "\n";
        
        double angle = fabs(wind_direction - desired_course);
        if (angle <= EPSILON)
        {
            cout << "AIRCRAFT HEADING " << desired_course << "\n";
            cout << "GROUND SPEED " << (air_speed - wind_speed) << "\n";
            cout << "\n";
            continue;
        }
        else if (fabs(angle - 180.0) <= EPSILON)
        {
            cout << "AIRCRAFT HEADING " << desired_course << "\n";
            cout << "GROUND SPEED " << (air_speed + wind_speed) << "\n";
            cout << "\n";
            continue;
        }
        else if (angle > 180.0)
        {
            angle = 360.0 - angle;
        }
        
        double angle_of_air_speed = 180.0 - angle;
        angle_of_air_speed = angle_of_air_speed / 180.0 * PI;
       
        double ground_speed = sqrt(pow(air_speed, 2) - pow(wind_speed, 2) +
            pow(wind_speed * cos(angle_of_air_speed), 2)) + wind_speed * cos(angle_of_air_speed);
        
        double bias = acos((pow(air_speed, 2) + pow(ground_speed, 2) -
            pow(wind_speed, 2)) / (2.0 * air_speed * ground_speed));
        
        bias = bias / PI * 180.0;
        if (fabs(wind_direction - desired_course) > 180.0)
        {
            if (desired_course > wind_direction)
                desired_course += bias;
            else
                desired_course -= bias;
        }
        else
        {
            if (desired_course > wind_direction)
                desired_course -= bias;
            else
                desired_course += bias;
        }
            
        if (desired_course >= 360.0)
            desired_course -= 360.0;
        if (desired_course < 0.0)
            desired_course += 360.0;
        
        //stringstream ss;
        //ss << fixed << setprecision(2) << desired_course;
        //string desired_course_text;
        //ss >> desired_course_text;
        //if (desired_course_text == "360.00")
            //desired_course_text = "0.00";
            
        //cout << "AIRCRAFT HEADING " << desired_course_text << "\n";
        
        cout << "AIRCRAFT HEADING " << desired_course << "\n";
        cout << "GROUND SPEED " << ground_speed << "\n";
        cout << "\n";
    }
    
	return 0;
}
