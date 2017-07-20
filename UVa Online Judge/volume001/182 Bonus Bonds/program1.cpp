// Bonus Bonds
// UVa ID: 182
// Verdict: Accepted
// Submission Date: 2017-07-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

string nextBondNumber, desiredPosition;

void countTimes()
{
    int region = nextBondNumber[2] - '0', position = stoi(desiredPosition);
    nextBondNumber.erase(nextBondNumber.begin() + 2);
    long long number = stoll(nextBondNumber);

    if (number == 0 || (number == 1 && region == 0))
    {
        for (int i = 1; i <= 10; i++) cout << right << setw(11) << 0 << endl;
        return;
    }

    vector<int> bn;
    for (auto c : to_string(number - 1)) bn.push_back(c - '0');
    while (bn.size() < nextBondNumber.length()) bn.insert(bn.begin(), 0);

    for (int i = 0; i <= 9; i++)
    {
        long long total = 0;

        if (position == 3)
        {
            if (i == region) total = number;
        }
        else
        {
            int idx = position > 3 ? position - 2 : position - 1;

            if (idx > 0)
            {
                for (int j = 0; j < idx; j++) total += bn[j] * pow(10, 7 - j);
            }
            if (i < bn[idx]) total += pow(10, bn.size() - idx - 1);
            if (i == bn[idx])
            {
                long long tail = 0;
                for (int j = idx + 1; j < bn.size(); j++) tail = tail * 10 + bn[j];
                total += tail;
                total += 1;
            }
        }
        if (i == 0 && region == 0) total -= 1;

        cout << right << setw(11) << total << '\n';
    }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> nextBondNumber >> desiredPosition) {
        if (desiredPosition == "0") break;
        if (cases++) cout << '\n';
        countTimes();
    }
    return 0;
}
