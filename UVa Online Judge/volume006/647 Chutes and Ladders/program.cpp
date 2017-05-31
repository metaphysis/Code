// Chutes and Ladders
// UVa ID: 647
// Verdict: Accepted
// Submission Date: 2017-05-31
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

struct square
{
    int lose_turn, extra_turn, ladder_end, chute_end;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> throwings;

    int number;
    while (cin >> number, number > 0) throwings.push_back(number);

    int players;
    while (cin >> players, players > 0)
    {
        square squares[110];

        memset(squares, 0, sizeof(squares));

        int start, end;
        while (cin >> start >> end)
        {
            if (start == 0 && end == 0) break;

            if (start < end)
                squares[start].ladder_end = end;
            else
                squares[start].chute_end = end;
        }

        while (cin >> start, start != 0)
        {
            if (start > 0)
                squares[start].extra_turn = 1;
            else
                squares[abs(start)].lose_turn = 1;
        }

        // simulation
        int position[8] = {0}, miss_turn[8] = {0}, idx = 0;

        while (idx < throwings.size())
        {
            for (int i = 1; i <= players; i++)
            {
                int current = i;

                if (miss_turn[i])
                {
                    miss_turn[i] = 0, idx++;
                    continue;
                }

                int die = throwings[idx];
                if (position[i] >= 95 && position[i] + die > 100) continue;

                int next = position[i] + die;
                position[i] = next;

                if (squares[next].ladder_end > 0) position[i] = squares[next].ladder_end;
                if (squares[next].chute_end > 0) position[i] = squares[next].chute_end;
                if (squares[next].lose_turn) position[i] = next, miss_turn[i] = 1;
                if (squares[next].extra_turn) position[i] = next, i -= 1;

                if (position[current] == 100)
                {
                    cout << current << '\n';
                    idx = throwings.size();
                    break;
                }

                idx++;
            }
        }
    }

    return 0;
}
