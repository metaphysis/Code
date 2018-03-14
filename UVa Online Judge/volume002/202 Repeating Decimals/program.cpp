// Repeating Decimals
// UVa ID: 202
// Verdict: Accepted
// Submission Date: 2016-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cycleLength;
string cycleText, startText;
int maxLength = 6000;

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
            
            if (good && length < m)
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
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int n, m;
    
    while (cin >> n >> m)
    {
        if (n % m == 0)
        {
            cout << n << "/" << m << " = " << (n / m) << ".(0)\n";
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
                
            cout << ")\n";
            cout << "   " << cycleLength;
        }
        
        cout << " = number of digits in repeating cycle\n\n";
    }
    
	return 0;
}
