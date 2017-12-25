// Tarot Scores
// UVa ID: 11225
// Verdict: Accepted
// Submission Date: 2017-12-25
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

    int cases, scores[4] = {56, 51, 41, 36};
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n;
        cin >> n;
        cin.ignore(1024, '\n');
        
        int earned = 0, oudlers = 0;
        string card;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, card);

            string number;
            for (int j = 0; j < card.length(); j++)
                if (!isblank(card[j])) number += card[j];
                else break;

            if (number == "fool" || number == "one" || number == "twenty-one")
            {
                oudlers += 1;
                earned += 9;
            }
            else
            {
                if (number == "jack") earned += 3;
                else if (number == "knight") earned += 5;
                else if (number == "queen") earned += 7;
                else if (number == "king") earned += 9;
                else earned += 1;
            }
        }

        if (c > 1) cout << '\n';
        cout << "Hand #" << c << '\n';
        int target = scores[oudlers] * 2;
        if (earned >= target) cout << "Game won by " << (earned - target) / 2 << " point(s).\n";
        else cout << "Game lost by " << (target - earned) / 2 << " point(s).\n";
    }

    return 0;
}
