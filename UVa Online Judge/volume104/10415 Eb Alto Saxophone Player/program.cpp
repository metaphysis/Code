// Eb Alto Saxophone Player
// UVa ID: 10415
// Verdict: Accepted
// Submission Date: 2017-12-30
// UVa Run Time: 0.010s
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

    map<char, vector<int>> press = {
        {'c', {0, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
        {'d', {0, 1, 1, 1, 0, 0, 1, 1, 1, 0}},
        {'e', {0, 1, 1, 1, 0, 0, 1, 1, 0, 0}},
        {'f', {0, 1, 1, 1, 0, 0, 1, 0, 0, 0}},
        {'g', {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}},
        {'a', {0, 1, 1, 0, 0, 0, 0, 0, 0, 0}},
        {'b', {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}},
        {'C', {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}},
        {'D', {1, 1, 1, 1, 0, 0, 1, 1, 1, 0}},
        {'E', {1, 1, 1, 1, 0, 0, 1, 1, 0, 0}},
        {'F', {1, 1, 1, 1, 0, 0, 1, 0, 0, 0}},
        {'G', {1, 1, 1, 1, 0, 0, 0, 0, 0, 0}},
        {'A', {1, 1, 1, 0, 0, 0, 0, 0, 0, 0}},
        {'B', {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}}
    };
    
    int cases;
    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        string line;
        getline(cin, line);
        int cnt[10] = {0};
        if (line.length())
        {
            for (int i = 0; i < 10; i++)
                cnt[i] += press[line[0]][i];
        }
        for (int i = 1; i < line.length(); i++)
        {
            for (int j = 0; j < 10; j++)
                if (press[line[i]][j] && !press[line[i - 1]][j])
                    cnt[j]++;
        }
        for (int i = 0; i < 10; i++)
        {
            if (i) cout << ' ';
            cout << cnt[i];
        }
        cout << '\n';
    }

    return 0;
}
