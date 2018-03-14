// Average Speed
// UVa ID: 10281
// Verdict: Accepted
// Submission Date: 2018-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    char seperator;
    int hour, minute, second, last, elapsed;
    double lastTravelled = 0, travelled = 0, speed = 0, km = 0;

    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> hour >> seperator >> minute >> seperator >> second;
        elapsed = hour * 3600 + minute * 60 + second;
        travelled = lastTravelled + (elapsed - last) * speed / 3600.0;
        if (iss >> km) 
        {
            speed = km;
            last = elapsed;
            lastTravelled = travelled;
        }
        else
        {
            cout << setw(2) << setfill('0') << right << hour << ':';
            cout << setw(2) << setfill('0') << right << minute << ':';
            cout << setw(2) << setfill('0') << right << second << ' ';
            cout << fixed << setprecision(2) << travelled << " km\n";
        }
    }

    return 0;
}
