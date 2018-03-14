// Updating a Dictionary
// UVa ID: 12504
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    cin >> T; cin.ignore(1024, '\n');
    for (int t = 1; t <= T; t++)
    {
        string line1, line2;

        getline(cin, line1); getline(cin, line2);
        map<string, string> dict1, dict2;

        string replaced = "{},:";
        for (auto r : replaced)
        {
            replace(line1.begin(), line1.end(), r, ' ');
            replace(line2.begin(), line2.end(), r, ' ');
        }

        string key, value;
        istringstream iss1(line1), iss2(line2);
        while (iss1 >> key >> value) dict1[key] = value;
        while (iss2 >> key >> value) dict2[key] = value;

        bool updated = false;
        
        bool added = false;
        for (auto p : dict2)
        {
            if (dict1.find(p.first) == dict1.end())
            {
                if (added) cout << ',';
                else cout << '+';
                cout << p.first;
                updated = added = true;
            }
        }
        if (added) cout << '\n';;

        bool removed = false;
        for (auto p : dict1)
        {
            if (dict2.find(p.first) == dict2.end())
            {
                if (removed) cout << ',';
                else cout << '-';
                cout << p.first;
                updated = removed = true;
            }
        }
        if (removed) cout << '\n';

        bool changed = false;
        for (auto p : dict1)
        {
            if (dict2.find(p.first) != dict2.end() && p.second != dict2[p.first])
            {
                if (changed) cout << ',';
                else cout << '*';
                cout << p.first;
                updated = changed = true;
            }
        }
        if (changed) cout << '\n';

        if (!updated) cout << "No changes\n";
        cout << '\n';
    }

    return 0;
}
