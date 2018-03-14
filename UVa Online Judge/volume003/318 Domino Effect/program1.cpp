// Domino Effect
// UVa ID: 318
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long long int MAX_INT = numeric_limits<int>::max();

struct edge
{
    int to;
    long long int weight;
    
    bool operator<(edge x) const
    {
        return weight > x.weight;
    }
};

struct link
{
    int from, to;
    long long int seconds;
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n, m, cases = 0;
    int from, to, seconds;
    long long int distances[510];

    while (cin >> n >> m, n)
    {
        fill(distances, distances + 510, MAX_INT);

        vector<vector<edge>> edges(n + 1);
        vector<link> links;

        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to >> seconds;
            edges[from].push_back((edge){to, seconds});
            edges[to].push_back((edge){from, seconds});
            links.push_back((link){from, to, seconds});
        }

        distances[1] = 0;
        priority_queue<edge> unvisited;
        unvisited.push((edge){1, 0});

        while (!unvisited.empty())
        {
            edge v = unvisited.top();
            unvisited.pop();
            
            for (auto e : edges[v.to])
                if (distances[v.to] + e.weight < distances[e.to])
                {
                    distances[e.to] = distances[v.to] + e.weight;
                    unvisited.push((edge){e.to, distances[e.to]});
                }
        }

        int startKey = 1, endKey = 1;
        long long int maxWastedTime = 0;
        for (int i = 1; i <= n; i++)
            if (2 * distances[i] > maxWastedTime)
            {
                startKey = endKey = i;
                maxWastedTime = 2 * distances[i];
            }

        for (auto l : links)
        {
            long long int wastedSeconds = distances[l.from] + distances[l.to] + l.seconds;
            if (wastedSeconds > maxWastedTime)
            {
                startKey = min(l.from, l.to);
                endKey = max(l.from, l.to);
                maxWastedTime = wastedSeconds;
            }
        }
 
        cout << "System #" << ++cases << endl;
        cout << "The last domino falls after " << maxWastedTime / 2;
        cout << (maxWastedTime % 2 ? ".5" : ".0") << " seconds, ";
        if (startKey == endKey)
            cout << "at key domino " << endKey << "." << endl;
        else
            cout << "between key dominoes " << startKey << " and " << endKey << "." << endl;
        cout << endl;
    }

	return 0;
}
