// Palindroms <---> smordnilaP
// UVa ID: 290
// Verdict: Accepted
// Submission Date: 2016-05-14
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    
    while (getline(cin, line))
    {
        string backup = line;
        reverse(line.begin(), line.end());

        vector<int> digits;
        for (int i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
                digits.push_back(line[i] - '0');
            else
                digits.push_back(tolower(line[i]) - 'a' + 10);
        }
        
        int maxDigit = 0;
        for (int i = 0; i < digits.size(); i++)
            maxDigit = max(maxDigit, digits[i]);
                        
        if (backup == line)
        {
            cout << "0";
            
            for (int i = 14; i >= max(2, (maxDigit + 1)); i--)
                cout << " 0";
        
            for (int i = max(2, (maxDigit + 1)) - 1; i >= 2; i--)
                cout << " ?";
            
            cout << endl;
                
            continue;
        }

        bool first = true;
        
        for (int i = 15; i >= (maxDigit + 1); i--)
        {
            vector<int> origin(digits);
            
            int step = 0;
            while (true)
            {
                vector<int> reversed(origin);
                reverse(reversed.begin(), reversed.end());
                
                int carry = 0;
                for (int j = 0; j < origin.size(); j++)
                {
                    carry += origin[j] + reversed[j];
                    origin[j] = carry % i;
                    carry /= i;
                }
                
                if (carry)
                    origin.push_back(carry);
                    
                step++;
                
                bool isPalindrome = true;
                for (int m = 0, n = origin.size() - 1; m < n; m++, n--)
                    if (origin[m] != origin[n])
                    {
                        isPalindrome = false;
                        break;
                    }
                    
                if (isPalindrome)
                {
                    if (first)
                        first = false;
                    else
                        cout << " ";
                        
                    cout << step;
                    break;
                }
            }
        }
        
        for (int i = maxDigit; i >= 2; i--)
            cout << " ?";
        
        cout << endl;
    }
    
	return 0;
}
