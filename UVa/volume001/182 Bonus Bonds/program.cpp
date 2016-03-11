// Bonus Bonds
// UVa IDs: 182
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string numberText, positionText;
long long number, position;

bool calculate()
{
    int region = numberText[2] - '0';
    numberText.erase(numberText.begin() + 2);
    number = stoll(numberText);
    position = stoll(positionText);

    if (number == 0 || (number == 1 && region == 0))
    {
        for (int i = 1; i <= 10; i++)
            cout << right << setw(11) << 0 << endl;
        return true;
    }
        
    cout << "region: " << region << endl;
    cout << "position: " << position << endl;
    cout << "numberText: " << numberText << endl;
    
    vector < int > digits;
    long long temp = number - 1;
    while (temp)
    {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    while (digits.size() < numberText)
        digits.push_back(0);
    reverse(digits.bgin(), digits.end());
    
    else if (position == 3)
    {
        for (int i = 0; i <= 9; i++)
        {
            long long times = 0;
            if (i == region)
                times = number;
            if (i == 0 && region == 0)
                times--;
            cout << right << setw(11) << times << endl;
        }
    }
    else if (position == 1)
    {
        for (int i = 0; i <= 9; i++)
        {
            long long times = 0;
            if (i < digits[0])
                times = pow(10, digits.size() - 1);
            else if (i == digits[0])
            {
                for (int j = 1; j < digits.size(); j++)
                    times = times * 10 + digits[j];
                times += 1;
            }
            if (i == 0 && region == 0)
                times--;
            cout << right << setw(11) << times << endl;
        }
    }
    else if (position == 10)
    {
        for (int i = 0; i <= 9; i++)
        {
            long long times = 0;
            for (int j = 0; j <= 7; j++)
                times += digits[j] * pow(10, 7 - j);
            if (i <= digits[8])
                times++;
            if (i == 0 && region == 0)
                times--;
            cout << right << setw(11) << times << endl;
        }
    }
    else
    {
        
    }
    
    return true;
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
