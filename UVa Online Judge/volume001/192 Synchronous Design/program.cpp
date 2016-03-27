// Synchronous Design
// UVa IDs: 192
// Verdict: Accepted
// Submission Date: 2016-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INPUT = 0, OUTPUT = 1, SYN = 2, ASYN = 3;
const string typeText = "iosa";

struct vertex
{
	int index, delay, type;
};

vector < vertex > verties;
vector < int > path;
vector < vector < int > > edges;
int maximumDelay;

// topological sorting
bool findCycle()
{
    vector < int > connections;
    connections.resize(verties.size());
    fill(connections.begin(), connections.end(), 0);
    
    for (int i = 0; i < edges.size(); i++)
        for (int j = 0; j < edges[i].size(); j++)
            if (verties[edges[i][j]].type == ASYN)
                connections[edges[i][j]]++;
   
    vector < bool > removed;
    removed.resize(verties.size());
    fill(removed.begin(), removed.end(), false);
    
    bool nodeRemoved = true;
    int numberRemovedNodes = 0;
    
    while (nodeRemoved)
    {
        nodeRemoved = false;
        
        for (int i = 0; i < removed.size(); i++)
        {
            if (removed[i] == false && connections[i] == 0)
            {
                nodeRemoved = true;
                numberRemovedNodes++;
                removed[i] = true;
                
                for (int j = 0; j < edges[i].size(); j++)
                {
                    if (verties[edges[i][j]].type == ASYN)
                        connections[edges[i][j]]--;
                }
            }
        }
    }
    
    return numberRemovedNodes != verties.size();
}

void forward(int v, int index)
{
    path[index] = v;
    
    if (index >= 1 && verties[path[index]].type != ASYN)
    {
        int tempMax = 0;       
        for (int i = 0; i <= index; i++)
            tempMax += verties[path[i]].delay;
        maximumDelay = max(tempMax, maximumDelay);
    }
    else
    {
        for (int i = 0; i < edges[v].size(); i++)
            forward(edges[v][i], index + 1);        
    }
}

void findMaximumDelay()
{
    path.resize(verties.size());
    maximumDelay = 0;
    for (int i = 0; i < verties.size(); i++)
        if (verties[i].type == INPUT || verties[i].type == SYN)
            forward(i, 0);
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
            typeIndex = (int)typeText.find(type);
            if (typeIndex == INPUT || typeIndex == OUTPUT || typeIndex == SYN)
                delay = 0;
            verties.push_back((vertex){i, delay, typeIndex});
        }
        
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> start >> end;
            edges[start].push_back(end);
        }
          
        if (findCycle())
            cout << "Circuit contains cycle." << endl;
        else 
        {
            findMaximumDelay();
            if (maximumDelay > clock)
                cout << "Clock period exceeded." << endl;
            else
                cout << "Synchronous design. Maximum delay: " << maximumDelay << "." << endl;
        }
    }
    
	return 0;
}
