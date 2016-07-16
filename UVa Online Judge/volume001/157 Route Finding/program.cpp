// Route Finding
// UVa ID: 157
// Verdict: Accepted
// Submission Date: 2016-02-05
// UVa Run times: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <map>
#include <iomanip>
#include <vector>

using namespace std;

const int MAXINT = numeric_limits<int>::max();

map<string, string> graph;
map<string, string> parent;
map<string, bool> visited;
map<string, int> times;
string start, end, path;

void dijkstra(void)
{
    for (map<string, string>::iterator it = graph.begin(); it != graph.end(); it++)
    {
        visited[it->first] = false;
        times[it->first] = MAXINT;
        parent[it->first].clear();
    }
    
    times[start] = 0;
    string station = start;
    
    while (visited[station] == false)
    {
        visited[station] = true;
        for (int i = 0; i < graph[station].length(); i += 2)
        {
            string next = graph[station].substr(i, 2);
            int weight = station[0] == next[0] ? 1 : 3;
            if (times[next] > (times[station] + weight))
            {
                times[next] = times[station] + weight;
                parent[next] = station;
            }
        }
        
        int maxTime = MAXINT;
        station = start;
        for (map<string, string>::iterator it = graph.begin(); it != graph.end(); it++)
            if (visited[it->first] == false && maxTime > times[it->first])
            {
                maxTime = times[it->first];
                station = it->first;
            }
    }
}

char routeCode;
void findPath(string first, string last)
{
    if (first == last)
    {
        routeCode = first[0];
        path += first;
    }
    else
    {
        findPath(first, parent[last]);
        if (routeCode == last[0])
            path += last[1];
        else
        {
            path += "=";
            path += last;
            routeCode = last[0];
        }
    }
}

string trim(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    return line;
}

int main(int argc, char *argv[])
{
    string line;
    int routes;
    
    getline(cin, line);
    istringstream iss(line);
    iss >> routes;

    // 构建交通连接图
    while (routes--)
    {
        getline(cin, line);
        
        line = trim(line);
        
        for (int i = line.length() - 1; i >= 0; i--)
            if (line[i] == '=')
                line.erase(line.begin() + i);
        
        string route;
        int index = 2;
        while (index < line.length())
        {
            if (islower(line[index]))
            {
                route += line[0];
                route += line[index++];
            }
            else
            {
                route += line[index++];
                route += line[index++];
            }
        }
        
        index = 0;        
        while (index < route.length() - 2)
        {
            vector < string > station;
            station.push_back(route.substr(index, 2));
            
            while (index < route.length() - 2)
            {
                index += 2;
                string next = route.substr(index, 2);
                station.push_back(next);
                
                if (next[0] == station[0][0])
                    break;
            }
            
            graph[station[0]] += station[station.size() - 1];
            graph[station[station.size() - 1]] += station[0];
            
            for (int i = 0; i <= (int)station.size() - 3; i++)
                for (int j = i + 1; j <= (int)station.size() - 2; j++)
                {
                    graph[station[i]] += station[j];
                    graph[station[j]] += station[i];
                }
        }
    }
    
    // 查找是否有未添加的换乘点
    while (true)
    {
        int totalChanges = 0;
        vector<string> stations;
        for (map<string, string>::iterator it = graph.begin(); it != graph.end(); it++)
            stations.push_back(it->first);

        for (int i = 0; i < stations.size(); i++)
        {
            string station = stations[i];
            string next = graph[station];
            for (int j = 0; j < next.length(); j += 2)
            {
                string near = next.substr(j, 2);
                if (near[0] == station[0])
                    continue;
                    
                string nearNext = graph[near];
                for (int k = 0; k < nearNext.length(); k += 2)
                {
                    string some = nearNext.substr(k, 2);
                    if (near[0] != some[0] && some != station)
                    {
                        if (graph[station].find(some) == next.npos)
                        {
                            graph[station] += some;
                            totalChanges++;
                        }
                    }
                }
            }
        }
        
        if (totalChanges == 0)
            break;
    }
                
    while (getline(cin, line), line[0] != '#')
    {
        line = trim(line);
        
        start = line.substr(0, 2);
        end = line.substr(2, 2);
        
        dijkstra();
        
        cout << setw(3) << right << times[end] << ": ";
        
        path.clear();
        findPath(start, end);
        cout << path << endl;
    }
    
	return 0;
}
