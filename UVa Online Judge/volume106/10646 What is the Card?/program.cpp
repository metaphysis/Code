// What is the Card?
// UVa ID: 10646
// Verdict: Accepted
// Submission Date: 2018-01-04
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

    int cases; cin >> cases;
    string cards[52];
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 52; i++) cin >> cards[i];
        int top = 26, Y = 0, X = 0;
        for (int i = 1; i <= 3; i++)
        {
            string card = cards[top];
            if (card.front() >= '2' && card.front() <= '9') X = card.front() - '0';
            else X = 10;
            top -= (11 - X);
            Y += X;
        }
        
        cout << "Case " << c << ": ";
        if (Y - 1 <= top)
            cout << cards[Y - 1] << '\n';
        else
            cout << cards[26 + (Y - 1 - top)] << '\n';
    }

    return 0;
}
