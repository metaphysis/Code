// Genes
// UVa ID: 939
// Verdict: Accepted
// Submission Date: 2017-03-09
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

struct person
{
    string name;
    int status;
    
    bool operator<(const person& p) const
    {
        return name < p.name;
    }
};

vector<person> persons;
vector<vector<int>> edges;
vector<int> visited;

void dfs(int i)
{
    visited[i] = 1;
    
    for (int j = 0; j < edges[i].size(); j++)
    {
        if (!visited[edges[i][j]])
            dfs(edges[i][j]);
    }
    
    if (edges[i].size() == 1)
    {
        if (persons[edges[i][0]].status >= 2)
            persons[i].status = 1;
    }
    
    if (edges[i].size() == 2)
    {
        if (persons[edges[i][0]].status + persons[edges[i][1]].status >= 2)
            persons[i].status = 1;
        if (persons[edges[i][0]].status + persons[edges[i][1]].status >= 3)
            persons[i].status = 2;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    string result[3] = {"non-existent", "recessive", "dominant"};
    unordered_map<string, int> names;
    string firstPart, secondPart;
    
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> firstPart >> secondPart;
        
        if (secondPart == "non-existent" || secondPart == "recessive" || secondPart == "dominant")
        {
            int idx = -1;
            if (names.find(firstPart) == names.end())
            {
                idx = persons.size();
                person p = person{firstPart, 0};
                persons.push_back(p);
                names.insert(make_pair(firstPart, idx));
                edges.push_back(vector<int>());
            }
            idx = names[firstPart];
            if (secondPart == "recessive") persons[idx].status = 1;
            if (secondPart == "dominant") persons[idx].status = 2;
        }
        else
        {
            if (names.find(firstPart) == names.end())
            {
                int idx = persons.size();
                person p = person{firstPart, 0};
                persons.push_back(p);
                names.insert(make_pair(firstPart, idx));
                edges.push_back(vector<int>());
            }
            
            if (names.find(secondPart) == names.end())
            {
                int idx = persons.size();
                person p = person{secondPart, 0};
                persons.push_back(p);
                names.insert(make_pair(secondPart, idx));
                edges.push_back(vector<int>());
            }
            
            edges[names[secondPart]].push_back(names[firstPart]);
        }
    }
    
    vector<int> inDegree(persons.size(), 0);
    for (int i = 0; i < edges.size(); i++)
        for (int j = 0; j < edges[i].size(); j++)
            inDegree[edges[i][j]]++;
    
    visited.assign(persons.size(), 0);
    for (int i = 0; i < inDegree.size(); i++)
        if (inDegree[i] == 0)
            dfs(i);
            
    sort(persons.begin(), persons.end());
    
    for (auto p : persons) cout << p.name << ' ' << result[p.status] << '\n';
    
    return 0;
}
