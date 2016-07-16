// Processing MX Records
// UVa ID: 335
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.170s
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

map<string, bool> status;
map<string, int> indexer;
map<string, multimap<int, string>> records;

inline bool isMachineLive(string machine)
{
    return (status.find(machine) != status.end() && status[machine]);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, second_field;
    string line, last_first_field, first_field, third_field, machine;
    istringstream iss;

    getline(cin, line); n = stoi(line);

    for (int i = 1; i <= n; i++)
    {
        getline(cin, line); iss.clear(); iss.str(line);
        
        if (line.front() != ' ')
        {
            iss >> first_field >> second_field >> third_field;
            last_first_field = first_field;
        }
        else
        {
            iss >> second_field >> third_field;
            first_field = last_first_field;
        }

        records[first_field].insert(make_pair(second_field, third_field));
        indexer[first_field] = i;
        status[first_field] = true;
        status[third_field] = true;
    }

    char action;
    while (getline(cin, line), line.front() != 'X')
    {
        iss.clear(); iss.str(line); iss >> action >> machine;

        if (action == 'U' || action == 'D')
        {
            if (status.find(machine) != status.end())
                status[machine] = action == 'U';
            else if (status.find("*." + machine) != status.end())
                status["*." + machine] = action == 'U';
        }
        else if (action == 'A')
        {
            // NOTE: 
            // 1. always choose the machine which is up and with the minimum preference.
            // 2. find the machine level by level.
            
            cout << machine << " =>";
            
            bool flag = false; int minPreference; string destination;

            for (auto record : records[machine])
                if (isMachineLive(record.second))
                {
                    minPreference = record.first;
                    destination = record.second;
                    flag = true;
                    break;
                }

            for (int start = machine.find('.', 0); start != machine.npos; start += 1, start = machine.find('.', start))
            {
                string next_machine = "*" + machine.substr(start);
                for (auto record : records[next_machine])
                {
                    if (isMachineLive(record.second))
                    {
                        if (flag == false)
                        {
                            minPreference = record.first;
                            destination = record.second;
                            flag = true;
                        }
                        else if (record.first < minPreference)
                        {
                            minPreference = record.first;
                            destination = record.second;
                        }
                    }
                }
            }
            
            if (flag) cout << " " << destination;
            cout << endl;
        }
    }

	return 0;
}
