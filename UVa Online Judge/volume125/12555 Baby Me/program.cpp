// Baby Me
// UVa ID: 12555
// Verdict: Accepted
// Submission Date: 2017-12-30
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);
        
        int jin = 0, liang = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] >= '0' && line[i] <= '9') jin = jin * 10 + line[i] - '0';
            else
            {
                for (int j = i + 1; j < line.length(); j++)
                {
                    if (line[j] >= '1' && line[j] <= '9')
                        liang = liang * 10 + line[j] - '0';
                }
                break;
            }
        }

        int kg = jin * 50 + liang * 5;
        cout << "Case " << c << ": ";
        if (kg % 100 == 0)
        {
            cout << kg / 100 << '\n';
        }
        else
        {
            cout << kg / 100 << '.';
            kg %= 100;
            if (kg % 10 == 0)
                cout << kg / 10 << '\n';
            else
                cout << setw(2) << setfill('0') << kg << '\n';
        }
    }
    
    return 0;
}
