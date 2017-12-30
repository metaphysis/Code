// Jingle Composing
// UVa ID: 12195
// Verdict: Accepted
// Submission Date: 2017-12-30
// UVa Run Time: 0.030s
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
    map<char, int> notes = {{'W', 64}, {'H', 32}, {'Q', 16}, {'E', 8}, {'S', 4}, {'T', 2}, {'X', 1}, };

    string line;
    while (getline(cin, line))
    {
        if (line.front() == '*') break;

        string measure;
        istringstream iss(line);

        int cnt = 0, total = 0;
        while (getline(iss, measure, '/'))
        {
            int duration = 0;
            for (int i = 0; i < measure.length(); i++)
                duration += notes[measure[i]];
            if (duration == 64) cnt++;
        }
        cout << cnt << '\n';
    }

    return 0;
}
