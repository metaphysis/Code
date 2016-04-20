// Running Lights Visibility Calculator
// UVa IDs: 203
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

const double PI = 3.141592653589793, EPSILON = 1E-7;

struct ship
{
    string name;
    double x, y, course, speed, x1, y1;
    double bearing, distance, bearing1, distance1;
};

string scenario;
vector < ship > ships;

double roundedBearing(double bearing)
{
    // bearing = bearing * 180 / PI;
    int rounded = (int)(bearing * 100 + 0.5);
    if (rounded == 36000)
        rounded = 0;
    return (double)rounded / 100.0;
}

double getBearing(ship ownship, ship othership)
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

string getLights(ship ownship, ship othership)
{
    bool green = false, red = false, masthead = false, stern = false;
    
    // green
    if (othership.bearing >= 357.5 || othership.bearing <= 115.0)
        green = true;  
    // red
    if (othership.bearing >= 245.0 || othership.bearing <= 2.5)
        red = true;
    // stern
    if (othership.bearing >= 110.0 && othership.bearing <= 250.0)
        stern = true;
    // masthead is allways visible when distance less than 10.0
    masthead = true;
    
    string lights;
    if (fabs(othership.bearing) <= EPSILON ||
        fabs(360.0 - othership.bearing) <= EPSILON ||
        fabs(othership.bearing - 180.0) <= EPSILON)
    {
        lights += green ? "Green " : "";
        lights += masthead ? "Masthead " : "";
        lights += red ? "Red " : "";
        lights += stern ? "Stern " : "";
    }
    else if (othership.bearing > 0.0 && othership.bearing < 180.0)
    {
        lights += stern ? "Stern " : "";
        lights += masthead ? "Masthead " : "";
        lights += green ? "Green " : "";
        lights += red ? "Red " : "";
    }
    else
    {
        lights += green ? "Green " : "";
        lights += red ? "Red " : "";
        lights += masthead ? "Masthead " : "";
        lights += stern ? "Stern " : "";
    }
    
    lights.erase(lights.end() - 1);
        
    return lights;
}

void calculate()
{
    // display the header
    cout << "Scenario: " << scenario << endl << endl;
    cout << setw(16) << left << "Boat ID";
    cout << setw(7) << right << "Bearing";
    cout << setw(14) << right << "Distance";
    cout << string(3, ' ');;
    cout << setw(23) << left << "Lights (left to right)" << endl;
    cout << string(63, '-') << endl;
    
    // calculate the initially bearing and distance between ownship and others ships
    ship ownship = ships[0];
    for (int i = 1; i < ships.size(); i++)
    {
        cout << setw(16) << left << ships[i].name;
        ships[i].bearing = getBearing(ownship, ships[i]);
        ships[i].distance = sqrt(pow(ownship.x - ships[i].x, 2) + pow(ownship.y - ships[i].y, 2));
        cout << setw(7) << right << setprecision(2) << fixed << roundedBearing(ships[i].bearing);
        cout << setw(12) << right << setprecision(2) << fixed << ships[i].distance;
        cout << string(5, ' ');
        
        // get the lights configuration
        if (ships[i].distance > 10.0)
            cout << setw(23) << left << "Lights not visible" << endl;
        else
        {
            cout << setw(23) << left << getLights(ownship, ships[i]) << endl;
        }
    }
    
    // recalculate the position of ship
    for (int i = 0; i < ships.size(); i++)
    {
        double angle = ships[i].course;
        
        if (angle >= 0.0 && angle <= 90.0)
            angle = 90.0 - angle;
        else if (angle > 90.0 && angle <= 180.0)
            angle = 270.0 + (180.0 - angle);
        else if (angle > 180.0 && angle <= 270.0)
            angle = 180.0 + (270.0 - angle);
        else 
            angle = 90.0 + (360.0 - angle);
                
        ships[i].x1 = ships[i].x + ships[i].speed / 20.0 * cos(angle * PI / 180.0);
        ships[i].y1 = ships[i].y + ships[i].speed / 20.0 * sin(angle * PI / 180.0);
        
    }
    
    // recalculate the bearing and distance after 3 minutes
    ownship = ships[0];
    for (int i = 1; i < ships.size(); i++)
    {
        ships[i].bearing1 = getBearing(ownship, ships[i]);
        ships[i].distance1 = sqrt(pow(ownship.x1 - ships[i].x1, 2) + pow(ownship.y1 - ships[i].y1, 2));
        
        if (ships[i].distance < 10.0 && ships[i].distance1 < ships[i].distance)
        {
            // the difference of first bearing and second within 2 degree
            double difference = fabs(ships[i].bearing - ships[i].bearing1);
            if (difference < 2.0 || difference > 358.0)
            cout << "** Collision warning -->" << ships[i].name << ": Distance = "
                 << setprecision(2) << fixed << setw(5) << right << ships[i].distance1 << endl;
        }  
    }
    
    // display the footer
    cout << string(63, '*') << endl;
}

int main(int argc, char *argv[])
{
    int shipNumber;
    string line;
    while (getline(cin, scenario))
    {
        getline(cin, line);
        shipNumber = stoi(line);

        ships.resize(shipNumber + 1);
        for (int i = 0; i <= shipNumber; i++)
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
