// File Mapping
// UVa ID: 645
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string line;
    while (getline(cin, line))
    {
        if (line == "#") break;

        if (cases++ > 0) cout << '\n';
        cout << "DATA SET " << cases << ":\n"; 
        cout << "ROOT\n";

        int idx = 0;
        vector<int> indexer;
        map<int, string> dirs;
        map<int, set<string>> files;
        dirs[idx] = "ROOT";
        indexer.push_back(idx++);

        do
        {
            if (line == "*") break;
            if (line.front() == 'f')
            {
                files[indexer.back()].insert(line);
            }
            else if (line.front() == 'd')
            {
                dirs[idx] = line;
                indexer.push_back(idx++);
                for (int i = 1; i < indexer.size(); i++)
                    cout << "|     ";
                cout << dirs[indexer.back()] << '\n';
            }
            else
            {
                for (auto f : files[indexer.back()])
                {
                    for (int i = 1; i < indexer.size(); i++)
                        cout << "|     ";
                    cout << f << '\n';
                }
                indexer.pop_back();
            }
        } while ((getline(cin, line)));

        for (auto f : files[0])
            cout << f << '\n';
        
    }

    return 0;
}
