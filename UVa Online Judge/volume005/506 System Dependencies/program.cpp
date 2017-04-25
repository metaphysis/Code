// System referredencies
// UVa ID: 506
// Verdict: Accepted
// Submission Date: 2017-04-25
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

int indexer = 0;                            // index of item
set<string> explicitly;                     // explicitly installed item
map<string, int> installed;                 // installed items
map<int, string> sequence;                  // installed items with order
map<string, vector<string>> referred;       // item1 referred item2, item3, ...
map<string, set<string>> referencedBy;      // item1 referenced by item2, item3, ...

void install(string software, bool topmost)
{
    for (auto component : referred[software])
    {
        referencedBy[component].insert(software);
        install(component, false);
    }
        
    if (installed.find(software) == installed.end())
    {
        cout << "   Installing " << software << '\n';
        installed.insert(make_pair(software, indexer));
        sequence.insert(make_pair(indexer, software));
        indexer++;

        if (topmost) explicitly.insert(software);
    }
}

void remove(string software, bool topmost)
{
    if ((topmost || explicitly.find(software) == explicitly.end()) && referencedBy[software].size() == 0)
    {
        cout << "   Removing " << software << '\n';
        sequence.erase(installed[software]);
        installed.erase(software);
        referencedBy.erase(software);
        
        if (topmost) explicitly.erase(software);
        
        for (auto component : referred[software])
        {
            referencedBy[component].erase(software);
            if (referencedBy[software].size() == 0 && explicitly.find(software) == explicitly.end())
                remove(component, false);
        }
    }
}

void parse(string line)
{
    string action, component, next;
    istringstream iss(line);

    iss >> action;
    if (action == "DEPEND")
    {
        iss >> component;
        while (iss >> next) referred[component].push_back(next);
    }
    else if (action == "INSTALL")
    {
        iss >> component;
        if (installed.find(component) != installed.end())
            cout << "   " << component << " is already installed.\n";
        else
            install(component, true);
    }
    else if (action == "REMOVE")
    {
        iss >> component;
        if (installed.find(component) == installed.end())
            cout << "   " << component << " is not installed.\n";
        else
        {
            if (referencedBy[component].size() > 0)
                cout << "   " << component << " is still needed.\n";
            else
                remove(component, true);
        }
    }
    else if (action == "LIST")
    {
        for (auto s : sequence)
            cout << "   " << s.second << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line != "END")
        {
            do
            {
                cout << line << '\n';
                if (line == "END") break;
                parse(line);
            } while (getline(cin, line));
        }

        indexer = 0;
        explicitly.clear();
        installed.clear();
        sequence.clear();
        referred.clear();
        referencedBy.clear();
    }

    return 0;
}
