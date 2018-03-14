// Synching Signals
// UVa ID: 467
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.020s
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    
    string line;
    while (getline(cin, line))
    {
        vector<int> cycles;
        
        int cycle;
        istringstream iss(line);
        while (iss >> cycle)
            cycles.push_back(cycle);
            
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
                if ((x.seconds / cycles[i]) % 2 == 0 && (x.seconds % cycles[i]) < (cycles[i] - 5))
                    continue;
                else
                {
                    allGreen = false;
                    break;
                }
            }
            
            
            if (x.seconds > 3600)
            {
                cout << "Set " << ++cases << " is unable to synch after one hour.\n";
                break;
            }
            else if (allGreen)
            {
                cout << "Set " << ++cases << " synchs again at ";
                cout << x.seconds / 60;
                cout << " minute(s) and ";
                cout << x.seconds % 60;
                cout << " second(s) after all turning green.\n";
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
