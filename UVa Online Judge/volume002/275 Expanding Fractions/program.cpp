// Expanding Fractions
// UVa ID: 275
// Verdict: Accepted
// Submission Date: 2016-05-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cycleLength;
string cycleText, startText;
int maxLength = 2000;

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
    
    while (cin >> n >> m, n && m)
    {
        // check m divide n
        bool divided = false;
        
        long long nn = n * 10;
        string resultText = ".";
        int countOfTry = 0;
        
        while (nn < m)
        {
            nn *= 10;
            resultText += '0';
            countOfTry++;
        }
        
        while (countOfTry < 10 && divided == false)
        {
            if (nn % m == 0)
            {
                resultText += to_string(nn / m);
                cout << resultText << "\n";
                cout << "This expansion terminates.\n\n";
                divided = true;
                break;
            }
            
            nn *= 10;
            countOfTry++;
        }
        
        if (divided)
            continue;
     
        // find repeat decimal
        findCycle(n, m);
        
        resultText = ".";
        resultText += startText + cycleText;
        
        int index = 0;
        while ((resultText.length() - index) >= 50)
        {
            cout << resultText.substr(index, 50);
            index += 50;
            if (index < resultText.length())
                cout << "\n";
        }
        
        if (index < resultText.length())
            cout << resultText.substr(index);
            
        cout << "\nThe last " << cycleLength << " digits repeat forever.\n\n";
    }
    
	return 0;
}
