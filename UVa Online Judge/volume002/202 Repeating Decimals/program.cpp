// Repeating Decimals
// UVa IDs: 202
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int cycleLength;
string cycleText, startText;
int maxLength = 10000;

void findCycle(int n, int m)
{
    string digits;
    while (digits.length() < maxLength)
    {
        n *= 10;
        while (n < m && digits.length() < maxLength)
        {
            n *= 10;
            digits.push_back('0');
        }
        
        digits.push_back(n / m + '0');
        n %= m;
    }
    
    int start = 0;
    while (start < maxLength)
    {
        int length = 1;
        while (length < maxLength / 2)
        {
            int tempStart = start;
            int tempEnd = (maxLength - start) / length * length + start;
            
            bool good = true;
            while (tempStart + 2 * length <= tempEnd)
            {
                if (digits.substr(tempStart, length) ==
                    digits.substr(tempStart + length, length))
                    tempStart += length;
                else
                {
                    good = false;
                    break;
                }
            }
            
            if (good && length < maxLength / 2)
            {
                cycleText = digits.substr(start, length);
                cycleLength = length;
                startText = digits.substr(0, start);
                return;
            }
            
            length++;
        }
        
        start++;
    }
}

int main(int argc, char *argv[])
{
    int n, m;
    
    while (cin >> n >> m)
    {
        if (n % m == 0)
        {
            cout << n << "/" << m << " = " << (n / m) << ".(0)" << endl;
            cout << "   1";
        }
        else
        {
            findCycle(n % m, m);
            
            cout << n << "/" << m << " = " << (n / m) << "." << startText << "(";
            
            if ((cycleLength + startText.length()) > 50)
            {
                cout << cycleText.substr(0, 50 - startText.length());
                cout << "...";
            }
            else
                cout << cycleText;
                
            cout << ")" << endl;
            cout << "   " << cycleLength;
        }
        
        cout << " = number of digits in repeating cycle" << endl;
        cout << endl;
    }
    
	return 0;
}
