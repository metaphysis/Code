// Call Forwarding
// UVa IDs: 380
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
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

struct item
{
    string source, time, duration, target;
    int start, end;
};

map<string, vector<item>> items;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    cout << "CALL FORWARDING OUTPUT" << endl;
    for (int i = 1; i <= cases; i++)
    {
        items.clear();
        
        cout << "SYSTEM " << i << endl;
        string source, time, duration, target, extension;
        int start, end;
        
        while (cin >> source, source != "0000")
        {
            cin >> time >> duration >> target;
            start = stoi(time), end = start + stoi(duration);
            items[source].push_back((item){source, time, duration, target, start, end});
        }
        
        while (cin >> time, time != "9000")
        {
            cin >> extension;
            
            int calling_time = stoi(time);
            string next_extension = extension;
            
            set<string> called;
            while (items.find(next_extension) != items.end())
            {
                bool get_out = true;
                for (auto data : items[next_extension])
                    if (calling_time >= data.start && calling_time <= data.end)
                    {
                        if (called.find(data.target) == called.end())
                        {
                            called.insert(data.target);
                            next_extension = data.target;
                            get_out = false;
                        }
                        else
                        {
                            get_out = true;
                            next_extension = "9999";
                        }
                            
                        break;
                    }
                    
                if (get_out)
                    break;
            }

            cout << "AT " << time << " CALL TO " << extension << " RINGS " << next_extension << endl;
        }
    }
    cout << "END OF OUTPUT" << endl;
    
	return 0;
}
