// Network Wars
// UVa ID: 173
// Verdict: Accepted
// Submission Date: 2016-02-21
// UVa Run Time: 0.029s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

vector < vector < int > > nodes;
bool initialized = false;
int paskill, lisper, visited[26];
const int UNVISITED = 0, PASKILL_VISITED = 1, LISPER_VISITED = 2, NONE = -1;

void buildGraph(string line)
{
    if (initialized == false)
    {
        for (int i = 0; i < 26; i++)
        {
            vector < int > connected;
            nodes.push_back(connected);
        }
        initialized = true;
    }
    else
    {
        for (int i = 0; i < nodes.size(); i++)
            nodes[i].clear();
    }
    
    int index = 0;
    while (true)
    {
        string block;
        while (line[index] != ';' && line[index] != '.')
        {
            if (isalpha(line[index]) || line[index] == ':')
                block += line[index];
            index++;
        }
        
        //cout << block << endl;
        
        for (int i = 2; i < block.length(); i++)
        {
            nodes[block[0] - 'A'].push_back(block[i] - 'A');
            nodes[block[i] - 'A'].push_back(block[0] - 'A');
        }
            
        if (line[index] == '.')
            break;
            
        index++;
    }
    
    index++;
    while (isalpha(line[index]) == false)
        index++;
    paskill = line[index++] - 'A';
    
    while (isalpha(line[index]) == false)
        index++;
    lisper = line[index++] - 'A';

    //cout << "start: " << (char)('A' + paskill);
    //cout << " lisper: " << (char)('A' + lisper);
    
    for (int i = 0; i < nodes.size(); i++)
    {
        sort(nodes[i].begin(), nodes[i].end());
        int n = unique(nodes[i].begin(), nodes[i].end()) - nodes[i].begin();
        nodes[i].erase(nodes[i].begin() + n, nodes[i].end());
    }
}

int getNodeForward()
{
    for (int i = 0; i < nodes[paskill].size(); i++)
        if (nodes[paskill][i] > paskill &&
            visited[nodes[paskill][i]] == UNVISITED)
            return nodes[paskill][i];
    
    for (int i = 0; i < nodes[paskill].size(); i++)
        if (visited[nodes[paskill][i]] == UNVISITED)
            return nodes[paskill][i];

    return NONE;
}

int getNodeBackward()
{
    for (int i = nodes[lisper].size() - 1; i >= 0; i--)
        if (nodes[lisper][i] < lisper &&
            (visited[nodes[lisper][i]] == UNVISITED ||
            visited[nodes[lisper][i]] == PASKILL_VISITED))
            return nodes[lisper][i];
    
    for (int i = nodes[lisper].size() - 1; i >= 0; i--)
        if (visited[nodes[lisper][i]] == UNVISITED ||
            visited[nodes[lisper][i]] == PASKILL_VISITED)
            return nodes[lisper][i];

    return NONE;
}

void walk()
{
    fill(visited, visited + 26, UNVISITED);
    
    while (true)
    {
        if (paskill == lisper)
        {
            cout << "Both annihilated in node " << (char)('A' + paskill) << "\n";
            break;
        }
        
        visited[paskill] = PASKILL_VISITED;
        visited[lisper] = LISPER_VISITED;
    
        int paskillNext = getNodeForward();
        int lisperNext = getNodeBackward();
        
        if (paskillNext != NONE && lisperNext != NONE)
        {
            if (paskillNext == lisperNext)
            {
                cout << "Both annihilated in node " << (char)('A' + paskillNext) << "\n";
                break;
            }
            
            if (visited[lisperNext] == PASKILL_VISITED)
            {
                cout << "Lisper destroyed in node " << (char)('A' + lisperNext) << "\n";
                break;
            }
            
            paskill = paskillNext;
            lisper = lisperNext;

            continue;
        }
        
        if (paskillNext == NONE)
        {
            cout << "Paskill trapped in node " << (char)('A' + paskill);
            if (lisperNext == NONE)
                cout << " Lisper trapped in node " << (char)('A' + lisper);
            else if (paskill == lisperNext)
                cout << " Both annihilated in node " << (char)('A' + paskill);
            else if (visited[lisperNext] == PASKILL_VISITED)
                cout << " Lisper destroyed in node " << (char)('A' + lisperNext);
            cout << "\n";
            break;
        }
        
        if (lisperNext == NONE)
        {
            cout << "Lisper trapped in node " << (char)('A' + lisper) << "\n";
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line;
    while (getline(cin, line), line != "#")
    {
        buildGraph(line);
        walk();
    }
    
	return 0;
}
