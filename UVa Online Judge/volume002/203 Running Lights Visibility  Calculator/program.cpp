// Running Lights Visibility Calculator
// UVa ID: 203
// Verdict: Accepted
// Submission Date: 2016-04-20
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const double PI = 3.14159265358979323846, EPSILON = 1E-7;

struct ship
{
    string name;
    double x, y, course, speed;
    double bearing, distance, bearing1, distance1;
};

string scenario;
vector < ship > ships;

string roundedBearing(double bearing)
{
    stringstream ss;
    ss << fixed << setprecision(2) << (bearing + EPSILON);
    string number;
    ss >> number;
    if (number == "360.00")
        number = "0.00";
    return number;
}

double getBearing(ship othership, ship ownship)
{
    // calculate the anlge of vector from A to B
    double bearing = atan2(ownship.y - othership.y, ownship.x - othership.x);
    bearing = bearing * 180.0 / PI;
    
    // calculate the angle relative the true north
    if (bearing < 0.0)
        bearing = -bearing + 90.0;
    else if (bearing > 90.0 && bearing <= 180.0)
        bearing = 270.0 + (180.0 - bearing);
    else if (bearing >= 0.0 && bearing <= 90.0)
        bearing = 90.0 - bearing;
    
    // calculate the relative bearing
    if (bearing > othership.course)
        bearing -= othership.course;
    else
        bearing = 360.0 - fabs(bearing - othership.course);
            
    return bearing;
}

string getLights(double bearing)
{
      if(bearing >= 360.0 - EPSILON || bearing <= 0.0 + EPSILON)
        return "Green Masthead Red";
      else if(bearing > 0.0 + EPSILON && bearing < 2.5 - EPSILON)
        return "Masthead Green Red";
      else if(bearing >= 2.5 - EPSILON && bearing <= 110.0 + EPSILON)
        return "Masthead Green";
      else if(bearing > 110.0 + EPSILON && bearing < 115.0 - EPSILON)
        return "Stern Masthead Green";
      else if(bearing >= 115.0 - EPSILON && bearing < 180.0 - EPSILON)
        return "Stern Masthead";
      else if(bearing >= 180.0 - EPSILON && bearing <= 245.0 + EPSILON)
        return "Masthead Stern";
      else if(bearing > 245.0 + EPSILON && bearing < 250.0 - EPSILON)
        return "Red Masthead Stern";
      else if(bearing >= 250.0 - EPSILON && bearing <= 357.5 + EPSILON)
        return "Red Masthead";
      else if(bearing > 357.5 + EPSILON && bearing < 360.0 - EPSILON)
        return "Green Red Masthead";
}

void calculate()
{
    // display the header
    cout << "Scenario: " << scenario << "\n" << "\n";
    cout << setw(16) << left << "Boat ID";
    cout << setw(7) << right << "Bearing";
    cout << setw(14) << right << "Distance";
    cout << string(3, ' ');;
    cout << "Lights (left to right)" << "\n";
    cout << string(63, '-') << "\n";
    
    // calculate the initially bearing and distance between ownship and others ships
    for (int i = 1; i < ships.size(); i++)
    {
        cout << setw(16) << left << ships[i].name;
        ships[i].bearing = getBearing(ships[i], ships[0]);
        ships[i].distance = sqrt(pow(ships[0].x - ships[i].x, 2) + pow(ships[0].y - ships[i].y, 2));
        cout << setw(7) << right <<  fixed << setprecision(2) << roundedBearing(ships[i].bearing);
        cout << setw(12) << right << fixed << setprecision(2) << (ships[i].distance + EPSILON);
        cout << string(5, ' ');
        
        // get the lights configuration
        if (ships[i].distance <= (10.0 + EPSILON))
            cout << getLights(ships[i].bearing) << "\n";
        else
            cout << "Lights not visible" << "\n";
    }
    
    // recalculate the position of ship
    for (int i = 0; i < ships.size(); i++)
    {
        ships[i].x += ships[i].speed / 20.0 * sin(ships[i].course * PI / 180.0);
        ships[i].y += ships[i].speed / 20.0 * cos(ships[i].course * PI / 180.0);
        
    }
    
    // recalculate the bearing and distance after 3 minutes
    for (int i = 1; i < ships.size(); i++)
    {
        ships[i].bearing1 = getBearing(ships[i], ships[0]);
        ships[i].distance1 = sqrt(pow(ships[0].x - ships[i].x, 2) + pow(ships[0].y - ships[i].y, 2));
        
        if (ships[i].distance <= (10.0 + EPSILON) && ships[i].distance1 < (ships[i].distance - EPSILON))
        {
            // the difference of first bearing and second within 2 degree
            double difference = fabs(ships[i].bearing - ships[i].bearing1);
            if (difference <= 2.0 + EPSILON || difference >= 358.0 + EPSILON)
            cout << "** Collision warning -->" << ships[i].name << ":  Distance =  "
                 << fixed << setprecision(2) << (ships[i].distance1 + EPSILON) << "\n";
        }  
    }
    
    // display the footer
    cout << string(63, '*') << "\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int shipNumber;
    string line;
    while (getline(cin, scenario))
    {
        getline(cin, line);
        shipNumber = stoi(line);

        ships.resize(shipNumber + 1);
        for (int i = 0; i < ships.size(); i++)
        {
            getline(cin, ships[i].name);
            getline(cin, line);
            istringstream iss(line);
            iss >> ships[i].x >> ships[i].y >> ships[i].course >> ships[i].speed;
        }
        
        calculate();
    }
    
	return 0;
}
