// Traffic Lights
// UVa ID: 162
// Verdict: Accepted
// Submission Date: 2016-02-10
// UVa Run instant: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct instant
{
    int seconds, increment;
    
    bool operator<(instant x) const
    {
        return seconds > x.seconds;
    }
};

int main(int argc, char* argv[])
{
    vector<int> cycles;
    int cycle;
    
    while (true)
    {
        cycles.clear();
        while (cin >> cycle, cycle)
            cycles.push_back(cycle);
            
        if (cycles.size() == 0)
            break;
            
        sort(cycles.begin(), cycles.end());
        
        priority_queue<instant> times;
        for (int i = 0; i < cycles.size(); i++)
            times.push((instant){cycles[i] * 2, cycles[i] * 2});
            
        while (times.empty() == false)
        {
            instant x = times.top();
            times.pop();
            
            int allGreen = true;
            for (int i = 0; i < cycles.size(); i++)
            {
                if ((x.seconds / cycles[i]) % 2 == 0 &&
                    (x.seconds % cycles[i]) < (cycles[i] - 5))
                    continue;
                else
                {
                    allGreen = false;
                    break;
                }
            }
            
            
            if (x.seconds > 18000)
            {
                cout << "Signals fail to synchronise in 5 hours" << endl;
                break;
            }
            else if (allGreen)
            {
                cout << setw(2) << setfill('0') << x.seconds / 3600;
                cout << ":";
                cout << setw(2) << setfill('0') << (x.seconds % 3600) / 60;
                cout << ":";
                cout << setw(2) << setfill('0') << x.seconds % 60;
                cout << endl;
                break;
            }
            else
            {
                x.seconds += x.increment;
                times.push(x);
            }
        }
    }
    
	return 0;
}
