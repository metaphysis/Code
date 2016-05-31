// Department of Redundancy Department
// UVa IDs: 219
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
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <set>

using namespace std;

vector <bool> visited;
vector <int> parent;

bool contains(string first, string second)
{
    for (int i = 0; i < second.length(); i++)
        if (first.find(second[i]) != first.npos)
            return true;
    return false;
}

void getPath(int end, int start)
{
    if (end != start)
        getPath(parent[end], start);
    cout << " " << (end + 1);
}

int main(int argc, char *argv[])
{
    int cases = 0;
    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        if (n == 0)
            break;
        
        vector < pair<string, string> > fd;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            int index = line.find("->");
            fd.push_back(make_pair(line.substr(0, index), line.substr(index + 2)));
        }
        
        if (cases)
            cout << endl;
        cout << "Set number " << ++cases << endl;
        
        vector < vector<int> > edges(fd.size());
        for (int i = 0; i < fd.size(); i++)
            for (int j = 0; j < fd.size(); j++)
            {
                if (i == j)
                    continue;
                    
                if (contains(fd[i].second, fd[j].first))
                    edges[i].push_back(j);
            }
        
        bool found = false;            
        for (int i = 0; i < fd.size(); i++)
        {
            visited.resize(fd.size());
            parent.resize(fd.size());
            
            for (int j = 0; j < fd.size(); j++)
            {
                if (i == j)
                    continue;
                    
                if (!contains(fd[j].first, fd[i].first))
                    continue;
                
                string target = fd[i].second;
   
                fill(parent.begin(), parent.end(), -1);
                fill(visited.begin(), visited.end(), false);

                queue <int> unvisited;
                unvisited.push(j);
                visited[i] = true;
                visited[j] = true;
                
                while (!unvisited.empty())
                {
                    int k = unvisited.front();
                    unvisited.pop();

                    if (contains(fd[k].second, target))
                    {
                        for (int x = 0; x < fd[k].second.length(); x++)
                            for (int y = target.length() - 1; y >= 0; y--)
                                if (target[y] == fd[k].second[x])
                                    target.erase(target.begin() + y);
                            
                        if (target.length() == 0)
                        {
                            found = true;
                            cout << "     FD " << (i + 1) << " is redundant using FDs:";
                            getPath(k, j);
                            cout << endl;
                            break;
                        }
                    }
                    
                    for (int m = 0; m < edges[k].size(); m++)
                        if (visited[edges[k][m]] == false)
                        {
                            parent[edges[k][m]] = k;
                            visited[edges[k][m]] = true;
                            unvisited.push(edges[k][m]);
                        }
                }
                
                if (found)
                    break;
            }
        }
        
        if (found == false)
            cout << "     No redundant FDs." << endl;
    }
    
	return 0;
}
