// Eeny Meeny
// UVa ID: 180
// Verdict: Accepted
// Submission Date: 2016-02-22
// UVa Run Time: 0.035s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

int lower, upper, m = 15;
int chiefCW[1000010], chiefCCW[1000010], safe[1000010];

int findChief()
{
    fill(chiefCW, chiefCW + 1000010, 0);
    fill(chiefCCW, chiefCCW + 1000010, 0);

    int select = 0;
    chiefCW[1] = 0;
    for (int j = 2; j <= 1000000; j++)
    {
        select = (select + m) % j;
        chiefCW[j] = select;
        chiefCCW[j] = (j - select) % j;
    }
}

bool findFirstSafePosition()
{
    fill(safe, safe + upper, 1);

    for (int i = lower; i <= upper; i++)
    {
        safe[chiefCW[i]] = 0;
        safe[chiefCCW[i]] = 0;
    }

    for (int i = 1; i < lower / 2; i++)
        if (safe[i] == 1)
        {
            cout << i << "\n";
            return true;
        }

    cout << "Better estimate needed\n";
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    findChief();

    while (cin >> lower >> upper, lower || upper)
    {
        if (lower > upper)
            swap(lower, upper);

        findFirstSafePosition();
    }

    return 0;
}
