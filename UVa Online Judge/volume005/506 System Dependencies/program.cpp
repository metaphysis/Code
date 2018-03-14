// System referredencies
// UVa ID: 506
// Verdict: Accepted
// Submission Date: 2017-04-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int indexer = 0;                            // index of items
map<string, bool> explicitly;               // explicitly installed items
map<string, int> installed;                 // installed items include explicitly and implicitly
map<int, string> sequence;                  // installed items with order
map<string, vector<string>> depend;         // item1 depends item2, item3, ...
map<string, set<string>> referencedBy;      // item1 referenced by item2, item3, ...

void install(string software, bool topmost)
{
    for (auto component : depend[software])
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

        if (topmost) explicitly[software] = true;
    }
}

void remove(string software, bool topmost)
{
    if ((topmost || !explicitly[software]) && referencedBy[software].size() == 0)
    {
        cout << "   Removing " << software << '\n';
        sequence.erase(installed[software]);
        installed.erase(software);
        referencedBy.erase(software);
        
        if (topmost) explicitly[software] = false;
        
        for (auto component : depend[software])
        {
            referencedBy[component].erase(software);
            if (referencedBy[software].size() == 0 && !explicitly[software])
                remove(component, false);
        }
    }
}

void parse(string line)
{
    string action, software, component;
    istringstream iss(line);

    iss >> action;
    if (action == "DEPEND")
    {
        iss >> software;
        while (iss >> component) depend[software].push_back(component);
    }
    else if (action == "INSTALL")
    {
        iss >> software;
        if (installed.find(software) != installed.end())
            cout << "   " << software << " is already installed.\n";
        else
            install(software, true);
    }
    else if (action == "REMOVE")
    {
        iss >> software;
        if (installed.find(software) == installed.end())
            cout << "   " << software << " is not installed.\n";
        else
        {
            if (referencedBy[software].size() > 0)
                cout << "   " << software << " is still needed.\n";
            else
                remove(software, true);
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
        depend.clear();
        referencedBy.clear();
    }

    return 0;
}
