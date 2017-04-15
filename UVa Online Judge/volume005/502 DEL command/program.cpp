// DEL command
// UVa ID: 502
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

struct file
{
    string name, extension;
};

vector<file> deleted, reserved;
string longestName, longestExtension, wildcard, mask;

bool matched(string &a, string &b)
{
    if (b.find('*') != b.npos)
    {
        for (int i = 0; i < b.length(); i++)
        {
            if (b[i] == '*')
                break;
            if (i >= a.length())
                return false;
            if (b[i] != '?' && a[i] != b[i])
                return false;
        }
    }
    else
    {
        if (a.length() != b.length())
            return false;
        for (int i = 0; i < b.length(); i++)
            if (b[i] != '?' && a[i] != b[i])
                return false;
    }
    
    return true;
}

bool validate()
{
    mask = wildcard;
    
    //cout << "mask = " << mask << '\n';
    
    int dot = mask.find('.');
    string name = mask.substr(0, dot);
    string extension = mask.substr(dot + 1);
    
    for (int i = 0; i < deleted.size(); i++)
        if (!matched(deleted[i].name, name) || !matched(deleted[i].extension, extension))
            return false;
    
    for (int i = 0; i < reserved.size(); i++)
        if (matched(reserved[i].name, name) && matched(reserved[i].extension, extension))
            return false;

    return true;
}

bool findWildcard()
{
    unordered_set<string> visited;
    queue<string> unvisited;
    
    string pattern;
    for (int i = 0; i < longestName.length(); i++)
        for (int j = 0; j < longestExtension.length(); j++)
        {
            pattern = longestName.substr(0, i) + "." + longestExtension.substr(0, j) + "*";
            unvisited.push(pattern);
            visited.insert(pattern);
            
            pattern = longestName.substr(0, i) + "*." + longestExtension.substr(0, j);
            unvisited.push(pattern);
            visited.insert(pattern);
            
            pattern = longestName.substr(0, i) + "*." + longestExtension.substr(0, j) + "*";
            unvisited.push(pattern);
            visited.insert(pattern);
        }
        
    pattern = longestName + "." + longestExtension;
    unvisited.push(pattern);
    visited.insert(pattern);
    
    while(!unvisited.empty())
    {
        wildcard = unvisited.front();
        unvisited.pop();

        if (validate()) return true;
        
        for (int i = 0; i < wildcard.length(); i++)
            if (wildcard[i] != '.' && wildcard[i] != '*' && wildcard[i] != '?')
            {
                string next(wildcard);
                next[i] = '?';
                if (visited.find(next) == visited.end())
                {
                    unvisited.push(next);
                    visited.insert(next);
                }
            }
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int M = stoi(line);
    
    getline(cin, line);
    for (int c = 1; c <= M; c++)
    {
        if (c > 1) cout << '\n';
        
        deleted.clear(); reserved.clear();
        longestName.clear(); longestExtension.clear();
        
        while (getline(cin, line), line.length() > 0)
        {
            string name = line.substr(1), extension;
            
            int dot = (int)line.find('.');
            if (dot != (int)line.npos)
            {
                name = line.substr(1, dot - 1);
                extension = line.substr(dot + 1);
            }
            file f = file{name, extension};
            
            if (line.front() == '-')
            {
                if (name.length() > longestName.length())
                    longestName = name;
                if (extension.length() > longestExtension.length())
                    longestExtension = extension;
                deleted.push_back(f);
            }
            else
                reserved.push_back(f);
        }

        if (reserved.size() == 0)
            cout << "DEL *.*\n";
        else
        {
            if (findWildcard())
                cout << "DEL " << mask << '\n';
            else
                cout << "IMPOSSIBLE\n";
        }
    }
    
    return 0;
}
