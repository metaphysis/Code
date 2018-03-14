// Through the Desert
// UVa ID: 11935
// Verdict: Accepted
// Submission Date: 2017-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int FUEL = 0, GAS = 1, LEAK = 2, FIX = 3, GOAL = 4;

struct event
{
    int type;
    double d, n;
} events[100];

int cnt;

bool safe(double x)
{
    double fuel = x, leak = 0.0, consume = -1.0, lastd = 0.0;
    for (int i = 0; i < cnt; i++)
    {
        event e = events[i];
        if (consume > 0.0)
        {
            fuel -= (e.d - lastd) * (consume / 100.0 + leak);
        }
        
        if (fuel < 0.0) return false;

        if (e.type == FUEL)
        {
            consume = e.n;
        }
        else if (e.type == GAS)
        {
            fuel = x;
        }
        else if (e.type == LEAK)
        {
            leak += 1.0;
        }
        else if (e.type == FIX)
        {
            leak = 0.0;
        }
        
        lastd = e.d;
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, token;
    double d;
    int n;

    while (getline(cin, line))
    {
        istringstream iss(line);

        iss >> d >> token;
        if (token == "Fuel")
        {
            iss >> token >> n;
            if (n == 0) break;
            events[cnt++] = event{FUEL, d, 1.0 * n};
        }
        else if (token == "Leak")
        {
            events[cnt++] = event{LEAK, d, 0.0};
        }
        else if (token == "Gas")
        {
            events[cnt++] = event{GAS, d, 0.0};
        }
        else if (token == "Mechanic")
        {
            events[cnt++] = event{FIX, d, 0.0};
        }
        else if (token == "Goal")
        {
            events[cnt++] = event{GOAL, d, 0.0};
            
            double left = 0.0, right = 1e9, middle;
            for (int i = 1; i <= 50; i++)
            {
                middle = (left + right) / 2.0;
                if (safe(middle)) right = middle;
                else left = middle;
            }
            cout << fixed << setprecision(3) << middle << '\n';
            cnt = 0;
        }
    }
    
    return 0;
}
