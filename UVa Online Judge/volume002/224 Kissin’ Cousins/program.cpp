// Kissin' Cousins
// UVa IDs: 224
// Verdict: Accepted
// Submission Date: 2016-06-18
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

struct relation
{
    string name;
    int k;
};

map <string, vector<relation>> child;
map <string, vector<relation>> parent;

void bfs(string start, map <string, int>& distances, map<string, vector<relation>>& edges)
{
    set<string> visited;
    queue<string> unvisited;
    unvisited.push(start);
    visited.insert(start);
    distances[start] = 0;

    while (!unvisited.empty())
    {
        string name = unvisited.front();
        unvisited.pop();

      for (auto r:edges[name])
        {
            if (visited.find(r.name) == visited.end())
            {
                unvisited.push(r.name);
                visited.insert(r.name);
                distances[r.name] = distances[name] + r.k;
            }
        }
    }
}

bool is_descendant(string firstname, string secondname)
{
    map <string, int> first_distances, second_distances;

    bfs(firstname, first_distances, child);
    bfs(secondname, second_distances, child);

    bool flag = false;
    if (first_distances.find(secondname) != first_distances.end())
    {
        flag = true;
        cout << setw(5) << left << firstname;
        cout << " and ";
        cout << setw(5) << left << secondname;
        if (first_distances[secondname] == 0)
            cout << " are cousin-0-0." << endl;
        else
            cout << " are descendant-" << first_distances[secondname] << "." << endl;
    }
    else if (second_distances.find(firstname) != second_distances.end())
    {
        flag = true;
        cout << setw(5) << left << firstname;
        cout << " and ";
        cout << setw(5) << left << secondname;
        if (second_distances[firstname] == 0)
            cout << " are cousin-0-0." << endl;
        else
            cout << " are descendant-" << second_distances[firstname] << "." << endl;
    }

    return flag;
}

bool is_cousin(string firstname, string secondname)
{
    map <string, int> first_distances, second_distances;

    bfs(firstname, first_distances, parent);
    bfs(secondname, second_distances, parent);

    bool flag = false;
    int m, n;
    for (auto p : first_distances)
        if (second_distances.find(p.first) != second_distances.end())
        {
            if (flag == false)
            {
                m = min(p.second, second_distances[p.first]) - 1;
                n = abs(p.second - second_distances[p.first]);
            }
            else
            {
                int mm = min(p.second, second_distances[p.first]) - 1;
                int nn = abs(p.second - second_distances[p.first]);

                if (mm < m || (mm == m && nn < n))
                    m = mm, n = nn;
            }

            flag = true;
        }

    if (flag)
    {
        cout << setw(5) << left << firstname;
        cout << " and ";
        cout << setw(5) << left << secondname;
        cout << " are cousin-" << m << "-" << n << "." << endl;
    }

    return flag;
}

void trim(string & name)
{
    while (isblank(name.front()))
        name.erase(name.begin());
    while (isblank(name.back()))
        name.erase(name.end() - 1);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        trim(line);

        if (line.front() == 'E')
            break;

        if (line.front() == '#')
            continue;

        string firstname, secondname;
        if (line.front() == 'R' || line.front() == 'F')
        {
            for (int i = 1; i <= 5; i++)
                firstname += line[i];
            trim(firstname);

            for (int i = 6; i <= 10 && i < line.length(); i++)
                secondname += line[i];
            trim(secondname);
        }

        if (line.front() == 'R')
        {
            int start = 11;
            while (!isdigit(line[start]))
                start++;

            int k = 0;
            for (int i = start; i < line.length() && isdigit(line[i]); i++)
                k = k * 10 + (line[i] - '0');

            parent[firstname].push_back((relation){secondname, k});
            child[secondname].push_back((relation){firstname, k});
        }

        if (line.front() == 'F')
        {
            if (is_descendant(firstname, secondname))
                continue;
            if (is_cousin(firstname, secondname))
                continue;

            cout << setw(5) << left << firstname;
            cout << " and ";
            cout << setw(5) << left << secondname;
            cout << " are not related." << endl;
        }
    }

    return 0;
}
