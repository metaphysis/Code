// MBone
// UVa ID: 593
// Verdict: Accepted
// Submission Date: 2017-05-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool cmp(pair<int, int> &a, pair<int, int> &b)
{
    return a.first < b.first;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int islands, cases = 0;
    while (cin >> islands, islands)
    {
        // Variables.
        map<string, int> indexer;
        map<int, int> hostInRouter;
        map<int, set<int>> groups;
        map<int, vector<pair<int, int>>> packetReceived;

        char kinds;
        int routerId = 0, datalines, activities;
        int cost, hostId, groupId, packetId, ttl;
        string source, dest;
        int dist[20][20], INF = 1000000;
        
        // Initialization.
        for (int i = 0; i < islands; i++)
        {
            for (int j = 0; j < islands; j++)
                dist[i][j] = INF;
            dist[i][i] = 0;
        }

        // Read input.
        for (int c = 1; c <= islands; c++)
        {
            cin >> source >> datalines;
            
            if (indexer.find(source) == indexer.end())
                indexer[source] = routerId++;

            for (int d = 1; d <= datalines; d++)
            {
                cin >> kinds;
                if (kinds == 'T')
                {
                    cin >> cost >> dest;
                    if (indexer.find(dest) == indexer.end())
                        indexer[dest] = routerId++;
                    dist[indexer[source]][indexer[dest]] = cost;
                }
                else
                {
                    cin >> hostId;
                    hostInRouter[hostId] = indexer[source];
                }
            }
        }

        // Floyd-Warshall.
        for (int k = 0; k < islands; k++)
            for (int i = 0; i < islands; i++)
                for (int j = 0; j < islands; j++)
                {
                    int through = dist[i][k] + dist[k][j];
                    if (dist[i][j] > through) dist[i][j] = through;
                }
        
        // Read activity.
        cin >> activities;
        for (int c = 1; c <= activities; c++)
        {
            cin >> kinds;
            if (kinds == 'J')
            {
                cin >> hostId >> groupId;
                groups[groupId].insert(hostId);
            }
            else if (kinds == 'L')
            {
                cin >> hostId >> groupId;
                groups[groupId].erase(hostId);
            }
            else
            {
                cin >> hostId >> groupId >> packetId >> ttl;
                for (auto host : groups[groupId])
                {
                    int from = hostInRouter[hostId], to = hostInRouter[host];
                    if (ttl >= dist[from][to])
                        packetReceived[host].push_back(make_pair(packetId, ttl - dist[from][to]));
                }
            }
        }
        
        // Output.
        cout << "Network #" << ++cases << '\n';
        for (auto packet : packetReceived)
        {
            sort(packet.second.begin(), packet.second.end(), cmp);
            for (auto data : packet.second)
                cout << packet.first << ' ' << data.first << ' ' << data.second << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}
