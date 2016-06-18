// Department of Redundancy Department
// UVa IDs: 219
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

vector<pair<int, int>> fd;
vector<bool> visited(110);
vector<int> path(110);

bool isRedundant(int valueOr, int index)
{
    vector<bool> used(110);
    fill(used.begin(), used.end(), false);
    bool updated;
    do
    {
        updated = false;
        for (int i = 0; i < fd.size(); i++)
        {
            if (visited[i] || used[i]) continue;
            if ((valueOr & fd[i].first) != fd[i].first) continue;
            
            used[i] = true;
            valueOr |= fd[i].second;
            updated = true; 
        }
    } while (updated);
    
    return (valueOr | fd[index].second) == valueOr;
}

void shrink(int step, int index)
{
    vector<int> shortest;
    for (int i = 0; i < step; i++)
        shortest.push_back(path[i]);
    
    while (true)
    {
        int forbidden = 0;
        bool updated = false;
        while (forbidden < shortest.size())
        {
            int left = fd[index].first;
            for (int i = 0; i < shortest.size(); i++)
            {
                if (i == forbidden)
                    continue;
                if ((left & fd[shortest[i]].first) == fd[shortest[i]].first)
                    left |= fd[shortest[i]].second;
            }
            
            if ((left & fd[index].second) == fd[index].second)
            {
                shortest.erase(shortest.begin() + forbidden);
                updated = true;
                break;
            }
                
            forbidden++;
        }
        
        if (!updated)
            break;
    }
    
    cout << "     FD " << (index + 1) << " is redundant using FDs:";
    for (int i = 0; i < shortest.size(); i++)
        cout << " " << (shortest[i] + 1);
    cout << endl;
}

bool backtrack(int step, int valueOr, int index)
{
    if ((valueOr & fd[index].second) == fd[index].second)
    {
        shrink(step, index);
        return true;
    }

    for (int i = 0; i < fd.size(); i++)
    {
        if (visited[i]) continue;
        if ((valueOr & fd[i].first) != fd[i].first) continue;
        if ((valueOr | fd[i].second) == valueOr) continue;

        visited[i] = true;
        if (backtrack(step, valueOr, index)) return true;
        path[step] = i;
        if (backtrack(step + 1, valueOr | fd[i].second, index)) return true;
        visited[i] = false;
    }
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

        fd.clear();
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            int index = line.find("->");

            int first = 0;
            for (auto c:line.substr(0, index)) first |= (1 << (c - 'A'));

            int second = 0;
            for (auto c:line.substr(index + 2)) second |= (1 << (c - 'A'));

            fd.push_back(make_pair(first, second));
        }

        if (cases)
            cout << endl;
        cout << "Set number " << ++cases << endl;

        vector<int> redundant;
        for (int i = 0; i < fd.size(); i++)
        {
            fill(visited.begin(), visited.end(), false);
            visited[i] = true;
            if (isRedundant(fd[i].first, i))
                redundant.push_back(i);
        }
        
        if (redundant.size() == 0)
        {
            cout << "     No redundant FDs." << endl;
            continue;
        }
        
        bool isAllRedundant = (redundant.size() == fd.size());
        for (int i = 0; i < redundant.size(); i++)
        {
            fill(visited.begin(), visited.end(), false);
            
            visited[redundant[i]] = true;
            
            if (!isAllRedundant)
            {
                for (int j = 0; j < redundant.size(); j++)
                    visited[redundant[j]] = true;
            }

            backtrack(0, fd[redundant[i]].first, redundant[i]);
        }
    }

    return 0;
}
