// Bonus Bonds
// UVa IDs: 182
// Verdict: Accepted
// Submission Date: 2016-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

string numberText, positionText;

void calculate()
{
    int region = numberText[2] - '0';

    numberText.erase(numberText.begin() + 2);
    long long number = stoll(numberText);
    long long position = stoll(positionText);

    if (number == 0 || (number == 1 && region == 0))
    {
        for (int i = 1; i <= 10; i++)
            cout << right << setw(11) << 0 << endl;
        return;
    }

    vector < int >digits;
    long long temp = number - 1;
    while (temp)
    {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    while (digits.size() < numberText.length())
        digits.push_back(0);
    reverse(digits.begin(), digits.end());

    for (int i = 0; i <= 9; i++)
    {
        long long times = 0;

        if (position == 3)
        {
            if (i == region)
                times = number;
        }
        else if (position == 1)
        {
            if (i < digits[0])
                times = pow(10, digits.size() - 1);
            else if (i == digits[0])
            {
                for (int j = 1; j < digits.size(); j++)
                    times = times * 10 + digits[j];
                times += 1;
            }
        }
        else if (position == 10)
        {
            for (int j = 0; j <= 7; j++)
                times += digits[j] * pow(10, 7 - j);
            if (i <= digits[8])
                times++;
        }
        else
        {
            int tempPosition = position;
            if (tempPosition > 3)
                tempPosition--;
            tempPosition--;

            for (int j = 0; j < tempPosition; j++)
                times += digits[j] * pow(10, 7 - j);
            if (i < digits[tempPosition])
            {
                times += pow(10, digits.size() - (tempPosition + 1));
            }
            else if (i == digits[tempPosition])
            {
                long long temp = 0;
                for (int j = tempPosition + 1; j < digits.size(); j++)
                    temp = temp * 10 + digits[j];
                times += temp;
                times++;
            }
        }

        if (i == 0 && region == 0)
            times--;
        cout << right << setw(11) << times << endl;
    }
}

int main(int argc, char *argv[])
{
    bool printBlankLine = false;
    while (cin >> numberText >> positionText)
    {
        if (positionText == "0")
            break;

        if (printBlankLine)
            cout << "\n";

        if (printBlankLine == false)
            printBlankLine = true;

        calculate();
    }

    return 0;
}
