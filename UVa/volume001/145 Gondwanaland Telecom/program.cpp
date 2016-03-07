// Gondwanaland Telecom
// UVa IDs: 145
// Verdict: Accepted
// Submission Date: 2016-01-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// In description: "Calls less than a minute are not recorded and no call 
// may last more than 24 hours. "
// I miss the case of whole 24 hours! (start time == end time)

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

int getAnd(int start1, int end1, int start2, int end2)
{
    int minutes = 0;
    for (int i = start1; i <= end1; i++)
        if (i >= start2 && i <= end2)
            minutes++;
    return (minutes > 0 ? (minutes - 1) : 0);
    
}

int main(int argc, char *argv[])
{
    string line, distance, number;
    int startHour, startMin, endHour, endMin;
    double cost[5][3] = {
        { 0.10, 0.06, 0.02 }, { 0.25, 0.15, 0.05 },
        { 0.53, 0.33, 0.13 }, { 0.87, 0.47, 0.17 },
        { 1.44, 0.80, 0.30 }
    };
    
    while (getline(cin, line), line != "#")
    {
        istringstream iss(line);
        iss >> distance >> number >> startHour >> startMin >> endHour >> endMin;
        
        startMin += startHour * 60;
        endMin += endHour * 60;
        
        if (endHour < startHour)
            endMin += 1440;
        else if (endHour == startHour && endMin < startMin)
            endMin += 1440;
        else if (endHour == startHour && endMin == startMin)
            endMin += 1440;
            
        double totalCost = 0.0;
        int dayMin = 0, eveningMin = 0, nightMin = 0;
        
        dayMin += getAnd(startMin, endMin, 480, 1080);
        dayMin += getAnd(startMin, endMin, 1920, 2520);
        eveningMin += getAnd(startMin, endMin, 1080, 1320);
        eveningMin += getAnd(startMin, endMin, 2520, 2760);
        nightMin += getAnd(startMin, endMin, 0, 480);
        nightMin += getAnd(startMin, endMin, 1320, 1920);
        nightMin += getAnd(startMin, endMin, 2760, 2880);
            
        totalCost += dayMin * cost[distance[0] - 'A'][0];
        totalCost += eveningMin * cost[distance[0] - 'A'][1];
        totalCost += nightMin * cost[distance[0] - 'A'][2];
        
        cout << setw(10) << right << number;
        cout << setw(6) << right << dayMin;
        cout << setw(6) << right << eveningMin;
        cout << setw(6) << right << nightMin;
        cout << setw(3) << right << distance;
        cout << setw(8) << right << fixed << setprecision(2) << totalCost << endl;
    }
    
	return 0;
}
