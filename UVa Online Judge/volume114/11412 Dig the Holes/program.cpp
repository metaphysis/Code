// Dig the Holes
// UVa ID: 11412
// Verdict: Accepted
// Submission Date: 2017-11-11
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

int truth[4], guessa[4], guessb[4], a, b;
int test[4], guess[4];

void cmp()
{
    a = b = 0;

    for (int i = 0; i < 4; i++)
    {
        if (guess[i] == test[i])
        {
            a++;
            guess[i] = test[i] = -1;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (guess[i] == -1) continue;
        for (int j = 0; j < 4; j++)
        {
            if (test[j] == -1) continue;
            if (guess[i] == test[j])
            {
                b++;
                test[j] == -1;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int code[256];
    string color = "RGBYOV";

    for (int i = 0; i < color.length(); i++)
        code[color[i]] = i;

    int cases, a1, b1, a2, b2;
    char c;

    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        for (int i = 0; i < 4; i++)
        {
            cin >> c;
            guessa[i] = code[c];
        }
        cin >> a1 >> b1;

        for (int i = 0; i < 4; i++)
        {
            cin >> c;
            guessb[i] = code[c];
        }
        cin >> a2 >> b2;

        bool matched = false;
        vector<int> coins(6);
        iota(coins.begin(), coins.end(), 0);
        do
        {
            for (int i = 0; i < 4; i++) truth[i] = coins[i];

            memcpy(test, truth, sizeof(truth));
            memcpy(guess, guessa, sizeof(guessa));
            cmp();
            if (a != a1 || b != b1) continue;

            memcpy(test, truth, sizeof(truth));
            memcpy(guess, guessb, sizeof(guessb));
            cmp();
            if (a != a2 || b != b2) continue;

            matched = true;
            break;
        } while(next_permutation(coins.begin(), coins.end()));
                    
        print:
        if (matched) cout << "Possible\n";
        else cout << "Cheat\n";
    }

    return 0;
}
