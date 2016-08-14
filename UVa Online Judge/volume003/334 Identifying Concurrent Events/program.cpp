// Identifying Concurrent Events
// UVa ID: 334
// Verdict: Accepted
// Submission Date: 2016-08-14
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int nc, ne, nm, cases = 0;
    while (cin >> nc, nc)
    {
        map<string, int> indexer;
        map<int, string> names;
        int concurrent[210][210], counter = 0;
        string last_event, current_event;
        
        memset(concurrent, 0, sizeof(concurrent));

        for (int i = 1; i <= nc; i++)
        {
            last_event.clear();

            cin >> ne;
            for (int j = 1; j <= ne; j++)
            {
                cin >> current_event;

                if (indexer.find(current_event) == indexer.end())
                {
                    indexer[current_event] = counter;
                    names[counter] = current_event;
                    counter++;
                }
                
                if (last_event.length() > 0)
                    concurrent[indexer[last_event]][indexer[current_event]] = 1;
                last_event = current_event;
            }
        }
        
        cin >> nm;
        for (int j = 1; j <= nm; j++)
        {
            cin >> last_event >> current_event;
            concurrent[indexer[last_event]][indexer[current_event]] = 1;
        }
        
        //for (int i = 0; i < counter; i++)
        //{
        //    for (int j = 0; j < counter; j++)
        //        cout << concurrent[i][j] << ' ';
        //    cout << '\n';
        //}
        
        // floyd-warshall
        for (int k = 0; k < counter; k++)
            for (int i = 0; i < counter; i++)
                for (int j = 0; j < counter; j++)
                    if (concurrent[i][k] && concurrent[k][j])
                        concurrent[i][j] = 1;

        vector<pair<int, int>> concurrent_events;
        int concurrent_events_count = 0;
        for (int i = 0; i < counter; i++)
            for (int j = i + 1; j < counter; j++)
                if (!concurrent[i][j] && !concurrent[j][i])
                {
                    concurrent_events_count++;
                    if (concurrent_events.size() < 2)
                        concurrent_events.push_back(make_pair(i, j));
                }
                
        cout << "Case " << ++cases << ", ";
        if (concurrent_events_count == 0)
            cout << "no concurrent events.\n";
        else
        {
            cout << concurrent_events_count << " concurrent events:\n";
            for (int i = 0; i < concurrent_events.size(); i++)
            {
                cout << '(' << names[concurrent_events[i].first];
                cout << ',' << names[concurrent_events[i].second] << ") ";
            }
            cout << '\n';
        }
    }
    
	return 0;
}
