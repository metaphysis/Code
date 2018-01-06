// That is Your Queue
// UVa ID: 12207
// Verdict: Accepted
// Submission Date: 2018-01-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    int cases = 0, P, C, X;
    char command;

    while (cin >> P >> C, P > 0)
    {
        cout << "Case " << ++cases << ":\n";

        vector<int> sequence;

        for (int i = 1; i <= min(P, 1024); i++)
            sequence.push_back(i);

        for (int i = 1; i <= C; i++)
        {
            cin >> command;
            if (command == 'N')
            {
                cout << sequence.front() << '\n';
                sequence.push_back(sequence.front());
                sequence.erase(sequence.begin());
            }
            else
            {
                cin >> X;
                auto it = find(sequence.begin(), sequence.end(), X);
                if (it != sequence.end()) sequence.erase(it);
                sequence.insert(sequence.begin(), X);
            }
        }
    }

    return 0;
}
