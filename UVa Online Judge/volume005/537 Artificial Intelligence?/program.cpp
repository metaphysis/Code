// Artificial Intelligence?
// UVa ID: 537
// Verdict: Accepted
// Submission Date: 2016-08-10
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int n = stoi(line);

    for (int cases = 1; cases <= n; cases++)
    {
        cout << "Problem #" << cases << '\n';

        vector<char> keys = {'P', 'U', 'I'};
        map<char, double> values = {{'P', -1.0}, {'U', -1.0}, {'I', -1.0}};
        map<char, double> units = {{'m', 0.001}, {'k', 1000.0}, {'M', 1000000.0}};

        getline(cin, line);
        for (auto key : keys)
        {
            string target = "=";
            target.insert(target.begin(), key);

            int start = line.find(target);
            if (start != line.npos)
            {
                string block;
                for (int i = start; i < line.length(); i++)
                {
                    if (!isblank(line[i]))
                        block += line[i];
                    else
                        break;
                }

                string number;
                for (int i = 2; i < block.length(); i++)
                    if (isdigit(block[i]) || block[i] == '.' || block[i] == '+' || block[i] == '-')
                        number += block[i];
                    else
                        break;

                values[key] = stod(number);
                for (auto unit : units)
                    if (block.find(unit.first) != block.npos)
                    {
                        values[key] *= unit.second;
                        break;
                    }
            }
        }

        if (values['P'] >= 0 && values['U'] > 0)
            cout << "I=" << fixed << setprecision(2) << (values['P'] / values['U']) << "A\n\n";
        else if (values['P'] >= 0 && values['I'] > 0)
            cout << "U=" << fixed << setprecision(2) << (values['P'] / values['I']) << "V\n\n";
        else
            cout << "P=" << fixed << setprecision(2) << (values['U'] * values['I']) << "W\n\n";
    }
    
	return 0;
}
