// System Dependencies
// UVa ID: 506
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

int counter = 0;
set<string> explicitly;
map<string, int> installed;
map<int, string> indexer;
map<string, set<string>> depend;
map<string, int> refered;
vector<string> deleted;

void install(string component)
{
    for (auto d : depend[component])
    {
        install(d);

        refered[d]++;

        if (installed.find(d) == installed.end())
        {
            installed.insert(make_pair(d, counter));
            indexer.insert(make_pair(counter, d));
            counter++;
            cout << "   Installing " << d << '\n';
        }
    }
}

void derefer(string component)
{
    for (auto d : depend[component])
    {
        derefer(d);
        
        refered[d]--;
        if (refered[d] == 0 && explicitly.find(d) == explicitly.end())
            deleted.push_back(d);
    }
}

void parse(string line)
{
    string action, component;
    istringstream iss(line);

    iss >> action;
    if (action == "DEPEND")
    {
        iss >> component;
        string next;
        while (iss >> next) 
        {
            depend[component].insert(next);
            if (depend.find(next) == depend.end())
                depend.insert(make_pair(next, set<string>()));
        }
    }
    else if (action == "INSTALL")
    {
        iss >> component;
        if (installed.find(component) != installed.end())
            cout << "   " << component << " is already installed.\n";
        else
        {
            install(component);

            cout << "   Installing " << component << '\n';

            installed.insert(make_pair(component, counter));
            indexer.insert(make_pair(counter, component));
            counter++;
            refered[component] = 0;
            explicitly.insert(component);
        }
    }
    else if (action == "REMOVE")
    {
        iss >> component;
        if (installed.find(component) == installed.end())
            cout << "   " << component << " is not installed.\n";
        else
        {
            if (refered[component] > 0)
                cout << "   " << component << " is still needed.\n";
            else
            {
                deleted.clear();
                deleted.push_back(component);

                derefer(component);
    
                for (auto d : deleted)
                {
                    cout << "   Removing " << d << '\n';
                    indexer.erase(installed[d]);
                    installed.erase(d);
                    refered.erase(d);
                }

                explicitly.erase(component);
            }
        }
    }
    else
    {
        for (auto i : indexer)
            cout << "   " << i.second << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        cout << line << '\n';
        parse(line);

        while (getline(cin, line), line != "END")
        {
            cout << line << '\n';
            parse(line);
        }
        cout << line << '\n';

        counter = 0;
        explicitly.clear();
        installed.clear();
        indexer.clear();
        depend.clear();
        refered.clear();
    }

    return 0;
}
