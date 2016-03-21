// Synchronous Design
// UVa IDs: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INPUT = 0, OUTPUT = 1, SYN = 2, ASYN = 3;
const int MAX_DELAY = numeric_limits<int>::min();

struct vertex
{
	int index, delay, type;
};

vector < vertex > verties;
vector < int > parent;
vector < bool > discovered;
vector < vector < int > > edges;
int maximumDelay;
bool foundCycle = false;

void dfs(int start, bool detectSYN)
{
    if (foundCycle)
        return;

    discovered[start] = true;
    for (int i = 0; i < edges[start].size(); i++)
    {
        vertex v = verties[edges[start][i]];
        if (v.type == ASYN || (detectSYN && v.type == SYN))
        {
            if (discovered[v.index] == false)
            {
                parent[v.index] = start;
                dfs(v.index, detectSYN);
            }
            else
            {
                if (parent[v.index] != start)
                {
                    foundCycle = true;
                    return;
                }
            }
        }
    }
}

bool findCycle(bool detectSYN)
{
    parent.clear();
    discovered.clear();
    
    parent.resize(verties.size());
    discovered.resize(verties.size());
    
    for (int i = 0; i < verties.size(); i++)
        if (verties[i].type == ASYN || (detectSYN && verties[i].type == SYN))
        {
            foundCycle = false;
            
            fill(parent.begin(), parent.end(), -1);
            fill(discovered.begin(), discovered.end(), false);
            
            dfs(i, detectSYN);
            
            if (foundCycle)
                return true;
        }
}

bool floyd(int clock)
{
    vector < vector < int > > distances;
    
    distances.clear();
    distances.resize(verties.size());
    
    for (int i = 0; i < verties.size(); i++)
        for (int j = 0; j < verties.size(); j++)
            distances[i].push_back(1);
            
    for (int i = 0 ; i < edges.size(); i++)
        for (int j = 0; j < edges[i].size(); j++)
            distances[i][edges[i][j]] = -verties[i].delay;
        
    for (int k = 0; k < verties.size(); k++)
        for (int i = 0; i < verties.size(); i++)
            for (int j = 0; j < verties.size(); j++)
            {
                if (distances[i][k] < 1 && distances[k][j] < 1)
                    if (distances[i][j] > (distances[i][k] + distances[k][j]))
                        distances[i][j] = distances[i][k] + distances[k][j];
            }
    
    maximumDelay = 0;
    for (int i = 0; i < edges.size(); i++)
        for (int j = 0; j < edges.size(); j++)
            if (verties[i].type == SYN && verties[j].type == SYN &&
                distances[i][j] < maximumDelay)
                    maximumDelay = distances[i][j];
    
    return abs(maximumDelay) > clock;
}

int findMaximumDelay()
{
    for (int i = 0; i < verties.size(); i++)
        for (int j = 0; j < verties.size(); j++)
        {
        
        }
}

int main(int argc, char *argv[])
{
    int clock, circuits, delay, nodes, start, end, typeIndex;
    string type;
    cin >> circuits;
    
    while (circuits--)
    {
        cin >> clock >> nodes;
        
        verties.clear();
        edges.clear();
        edges.resize(nodes);
        
        for (int i = 0; i < nodes; i++)
        {
            cin >> type >> delay;
            typeIndex = ASYN;
            if (type == "i" || type == "o" || type == "s")
                typeIndex = SYN;
            verties.push_back((vertex){i, delay, typeIndex});
        }
        
        int m;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> start >> end;
            edges[start].push_back(end);
        }
        
        for (int i = 0; i < edges.size(); i++)
        {
            cout << i;
            for (int j = 0; j < edges[i].size(); j++)
                cout << " " << edges[i][j];
            cout << endl;
        }
          
        if (findCycle(false))
            cout << "Circuit contains cycle." << endl;
        else 
        {
            if (findCycle(true))
            {
                maximumDelay = findMaximumDelay();
                
                if (maximumDelay > clock)
                    cout << "Clock period exceeded." << endl;
                else
                    cout << "Synchronous design. Maximum delay: " << maximumDelay << "." << endl;
            }
            else
            {
                if (floyd(clock))
                    cout << "Clock period exceeded." << endl;
                else
                    cout << "Synchronous design. Maximum delay: " << abs(maximumDelay) << "." << endl;
            }
        }
    }
    
	return 0;
}
