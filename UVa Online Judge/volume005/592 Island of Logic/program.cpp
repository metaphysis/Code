// Island of Logic
// UVa ID: 592
// Verdict: Accepted
// Submission Date: 2017-04-23
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
#include <vector>

using namespace std;

vector<string> statements;

const int DAY = 1, NIGHT = 2;
const int DIVINE = 1, EVIL = 2, HUMAN = 3;

int facts[8] = { 0 }, presented[8] =

{
0};
int result[8] = { 0 }, accepted;
string kinds[] = { "divine", "evil", "human", "lying" };

bool matched()
{
  for (auto s:statements)
    {
        int someone = s.front() - 'A' + 1, other = s[3] - 'A' + 1;

        if (s.find("am lying") != s.npos)
        {
            return false;
        }
        // "I am not lying." is good for everyone no matter day or night.
        else if (s.find("day") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[0] == DAY) || (facts[someone] == EVIL
                        && facts[0] == NIGHT) || facts[someone] == HUMAN))
                return false;
        }
        else if (s.find("night") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[0] == NIGHT) || (facts[someone] == EVIL
                        && facts[0] == DAY)))
                return false;
        }
        else if (s.find("am divine") != s.npos)
        {
            if (!(facts[someone] == DIVINE || facts[someone] == EVIL || (facts[someone] == HUMAN
                        && facts[0] == NIGHT)))
                return false;
        }
        else if (s.find("am not divine") != s.npos)
        {
            if (!(facts[someone] == HUMAN && facts[0] == DAY))
                return false;
        }
        else if (s.find("am evil") != s.npos)
        {
            if (!(facts[someone] == HUMAN && facts[0] == NIGHT))
                return false;
        }
        else if (s.find("am not evil") != s.npos)
        {
            if (!(facts[someone] == DIVINE || facts[someone] == EVIL || (facts[someone] == HUMAN
                        && facts[0] == DAY)))
                return false;
        }
        else if (s.find("am human") != s.npos)
        {
            if (!(facts[someone] == EVIL || (facts[someone] == HUMAN && facts[0] == DAY)))
                return false;
        }
        else if (s.find("am not human") != s.npos)
        {
            if (!(facts[someone] == DIVINE || (facts[someone] == HUMAN && facts[0] == NIGHT)))
                return false;
        }
        else if (s.find("is divine") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] == DIVINE) ||
                    (facts[someone] == EVIL && facts[other] != DIVINE) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] == DIVINE) || (facts[0] == NIGHT
                                && facts[other] != DIVINE)))))
                return false;
        }
        else if (s.find("is evil") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] == EVIL) ||
                    (facts[someone] == EVIL && facts[other] != EVIL) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] == EVIL) || (facts[0] == NIGHT
                                && facts[other] != EVIL)))))
                return false;
        }
        else if (s.find("is human") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] == HUMAN) ||
                    (facts[someone] == EVIL && facts[other] != HUMAN) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] == HUMAN) || (facts[0] == NIGHT
                                && facts[other] != HUMAN)))))
                return false;
        }
        else if (s.find("is lying") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] == EVIL) ||
                    (facts[someone] == DIVINE && facts[other] == HUMAN && facts[0] == NIGHT) ||
                    (facts[someone] == EVIL && facts[other] == DIVINE) ||
                    (facts[someone] == EVIL && facts[other] == HUMAN && facts[0] == DAY) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] == EVIL) || (facts[0] == NIGHT
                                && facts[other] == DIVINE)))))
                return false;
        }
        else if (s.find("is not divine") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] != DIVINE) ||
                    (facts[someone] == EVIL && facts[other] == DIVINE) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] != DIVINE) || (facts[0] == NIGHT
                                && facts[other] == DIVINE)))))
                return false;
        }
        else if (s.find("is not evil") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] != EVIL) ||
                    (facts[someone] == EVIL && facts[other] == EVIL) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] != EVIL) || (facts[0] == NIGHT
                                && facts[other] == EVIL)))))
                return false;
        }
        else if (s.find("is not human") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] != HUMAN) ||
                    (facts[someone] == EVIL && facts[other] == HUMAN) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] != HUMAN) || (facts[0] == NIGHT
                                && facts[other] == HUMAN)))))
                return false;
        }
        else if (s.find("is not lying") != s.npos)
        {
            if (!((facts[someone] == DIVINE && facts[other] == DIVINE) ||
                    (facts[someone] == DIVINE && facts[other] == HUMAN && facts[0] == DAY) ||
                    (facts[someone] == EVIL && facts[other] == EVIL) ||
                    (facts[someone] == EVIL && facts[other] == HUMAN && facts[0] == NIGHT) ||
                    (facts[someone] == HUMAN &&
                        ((facts[0] == DAY && facts[other] != EVIL) || (facts[0] == NIGHT
                                && facts[other] != DIVINE)))))
                return false;
        }
    }

    return true;
}

void backtrack(int depth)
{
    if (depth == 6)
    {
        if (matched())
        {
            if (accepted == 0)
            {
                for (int i = 0; i < 6; i++)
                    result[i] = facts[i];
            }
            else
            {
                // get the union of two possible answer.
                for (int i = 0; i < 6; i++)
                    if (result[i] > 0 && facts[i] > 0 && result[i] != facts[i])
                        result[i] = 0;
            }
            accepted++;
        }
    }
    else
    {
        // day or night
        if (depth == 0)
        {
            for (int j = 1; j <= 2; j++)
            {
                facts[depth] = j;
                backtrack(depth + 1);
                facts[depth] = 0;
            }
        }
        // divine, evil, human
        else
        {
            if (presented[depth])
            {
                for (int j = 1; j <= 3; j++)
                {
                    facts[depth] = j;
                    backtrack(depth + 1);
                    facts[depth] = 0;
                }
            }
            else
                backtrack(depth + 1);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    string line;

    while (cin >> n, n > 0)
    {
        statements.clear();
        memset(presented, 0, sizeof(presented));

        cin.ignore(1024, '\n');
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            statements.push_back(line);

            for (char c = 'A'; c <= 'E'; c++)
                if (line.find(c) != line.npos)
                    presented[c - 'A' + 1] = 1;
        }

        accepted = 0;
        memset(facts, 0, sizeof(facts));
        memset(result, -1, sizeof(result));

        backtrack(0);

        cout << "Conversation #" << ++cases << '\n';
        if (accepted == 0)
            cout << "This is impossible.\n";
        else if (accepted == 1)
        {
            for (int i = 1; i < 6; i++)
                if (result[i] > 0)
                    cout << (char)('A' + i - 1) << " is " << kinds[result[i] - 1] << ".\n";
            cout << "It is " << ((result[0] == 1) ? "day" : "night") << ".\n";
        }
        else
        {
            bool exist = false;
            for (int i = 0; i < 6; i++)
                if (result[i] > 0)
                {
                    exist = true;
                    break;
                }

            if (!exist)
                cout << "No facts are deducible.\n";
            else
            {
                for (int i = 1; i < 6; i++)
                    if (result[i] > 0)
                        cout << (char)('A' + i - 1) << " is " << kinds[result[i] - 1] << ".\n";
                if (result[0] > 0)
                    cout << "It is " << ((result[0] == 1) ? "day" : "night") << ".\n";
            }
        }
        cout << '\n';
    }

    return 0;
}
