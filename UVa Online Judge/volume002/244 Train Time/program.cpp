// Train Time
// UVa ID: 244
// Verdict: Accepted
// Submission Date: 2016-06-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int cases = 0;
vector < double >distances_from_start;
double v, s, m;

struct station
{
    double arrived_time, departure_time;
};

void process()
{
    if (cases > 0)
        cout << endl;

    cout << "Scenario #" << ++cases << ":" << endl;
    if (distances_from_start.size() == 1)
    {
        double meet_time = distances_from_start.front() * 5280.0 / v + v / s;
        cout << "   Meeting time: ";
        cout << fixed << setprecision(1) << meet_time / 2.0 << " minutes" << endl;
        cout << "   Meeting distance: ";
        cout << fixed << setprecision(3) << distances_from_start.front() / 2.0;
        cout << " miles from metro center hub" << endl;
        return;
    }

    vector < double >distances(distances_from_start);
    distances.insert(distances.begin(), 0.0);
    for (int i = 0; i < distances.size() - 1; i++)
        distances[i] = (distances[i + 1] - distances[i]) * 5280.0;
    distances.erase(distances.end() - 1);

    distances_from_start.insert(distances_from_start.begin(), 0.0);

    vector < double >schedule;
    for (int i = 0; i < distances.size(); i++)
        schedule.push_back(distances[i] / v + v / s);

    vector < station > left_train, right_train;

    left_train.push_back((station)
        {
        0.0, 0.0});
    double time_elapsed = 0.0;
    for (int i = 0; i < schedule.size(); i++)
    {
        station aStation;
        aStation.arrived_time = time_elapsed + schedule[i];
        aStation.departure_time = aStation.arrived_time + m;
        left_train.push_back(aStation);
        time_elapsed = aStation.departure_time;
    }

    right_train.push_back((station)
        {
        0.0, 0.0});
    time_elapsed = 0.0;
    for (int i = schedule.size() - 1; i >= 0; i--)
    {
        station aStation;
        aStation.arrived_time = time_elapsed + schedule[i];
        aStation.departure_time = aStation.arrived_time + m;
        right_train.insert(right_train.begin(), aStation);
        time_elapsed = aStation.departure_time;
    }

    //for (int i = 0; i < left_train.size(); i++)
    //{
    //cout << i << " " << left_train[i].arrived_time << " " << left_train[i].departure_time;
    //cout << " " << right_train[i].arrived_time << " " << right_train[i].departure_time << endl;
    //}

    for (int i = 0; i < left_train.size(); i++)
    {
        // meet in station
        if (left_train[i].arrived_time >= right_train[i].arrived_time &&
            left_train[i].arrived_time <= right_train[i].departure_time)
        {
            cout << "   Meeting time: ";
            cout << fixed << setprecision(1) << left_train[i].arrived_time << " minutes" << endl;
            cout << "   Meeting distance: ";
            cout << fixed << setprecision(3) << distances_from_start[i];
            cout << " miles from metro center hub, in station " << i << endl;
            return;
        }

        // meet in station
        if (right_train[i].arrived_time >= left_train[i].arrived_time &&
            right_train[i].arrived_time <= left_train[i].departure_time)
        {
            cout << "   Meeting time: ";
            cout << fixed << setprecision(1) << right_train[i].arrived_time << " minutes" << endl;
            cout << "   Meeting distance: ";
            cout << fixed << setprecision(3) << distances_from_start[i];
            cout << " miles from metro center hub, in station " << i << endl;
            return;
        }
    }

    for (int i = 0; i < left_train.size() - 1; i++)
    {
        // meet between station i and i + 1
        if (left_train[i].departure_time < right_train[i].arrived_time &&
            right_train[i + 1].departure_time < left_train[i + 1].arrived_time)
        {
            double distance_traveled =
                (fabs(left_train[i].departure_time - right_train[i + 1].departure_time) -
                v / s) * v + 2.0 * v * v / s;
            double traveled_time = v / s + (distances[i] - distance_traveled) / (2.0 * v);
            cout << "   Meeting time: ";
            double meet_time =
                max(left_train[i].departure_time,
                right_train[i + 1].departure_time) + traveled_time;
            cout << fixed << setprecision(1) << meet_time << " minutes" << endl;
            cout << "   Meeting distance: ";

            // may in accelerate or decelerate stage
            time_elapsed = meet_time - left_train[i].departure_time;
            double accelerate_time = v / s;
            double meet_distance = distances_from_start[i];

            if (time_elapsed <= accelerate_time)
            {
                meet_distance += s * time_elapsed * time_elapsed / 10560.0;
            }
            else if (time_elapsed <= (schedule[i] - accelerate_time))
            {
                meet_distance += v * v / s / 10560.0;
                meet_distance += (time_elapsed - accelerate_time) * v / 5280.0;
            }
            else
            {
                time_elapsed = schedule[i] - time_elapsed;
                meet_distance =
                    distances_from_start[i + 1] - s * time_elapsed * time_elapsed / 10560.0;
            }

            cout << fixed << setprecision(3) << meet_distance;
            cout << " miles from metro center hub" << endl;
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    double d;
    while (cin >> d, d > 0.0)
    {
        distances_from_start.clear();
        distances_from_start.push_back(d);
        while (cin >> d, d > 0.0)
            distances_from_start.push_back(d);
        cin >> v >> s >> m;
        process();
    }

    return 0;
}
