// Bonus Bonds
// UVa IDs: 182
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>

using namespace std;

string numberText, positionText;
long long number, position;

void calculate()
{
    int region = numberText[2] - '0';
    numberText.erase(numberText.begin() + 2);
    number = stoll(numberText);
    position = stoll(positionText);
    
    if (position == 3)
    {
        for (int i = 0; i <= 9; i++)
        {
            long long result = 0;
            if (i == region)
                result = number;
            cout << right << setw(11) << result << "\n";
        }
    }
    else
    {
        
    }
}

int main(int argc, char *argv[])
{
    bool blankLinePrinted = false;
    while (cin >> numberText >> positionText)
    {
        if (blankLinePrint)
            cout << "\n";
            
        if (blankLinePrint == false)
            blankLinePrint = true;
                        
        if (positionText == "0")
            break;
            
        calculate();
    }
    
	return 0;
}
