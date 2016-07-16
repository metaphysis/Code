// Quirksome Squares
// UVa ID: 256
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

vector < vector < string > > numbers(4);

void add(int n, int base)
{
    string first = to_string(n / base), second = to_string(n % base);
    
    int digits = 1;
    while (digits < 5)
    {
        while (first.length() < digits)
            first = '0' + first;
            
        while (second.length() < digits)
            second = '0' + second;
        
        string last = first + second;
        if (n == stoi(last) && last.length() == digits * 2)
        {
            numbers[digits - 1].push_back(last);
        }
               
        digits++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int start = 0, n = 0, up = 100, base = 10;
    for (int i = 0; i < 4; i++)
    {
        while (n < up)
        {
            int temp = n / base + n % base;
            if (temp * temp == n)
                add(n, base);
            n = n + 2 * start + 1;
            start++;        
        }
        
        start = base;
        n = up;
        
        base *= 10;
        up = base * base;
    }
            
    int digits;
    while (cin >> digits)
    {
        digits /= 2;
        digits--;
        
        for (int i = 0; i < numbers[digits].size(); i++)
            cout << numbers[digits][i] << "\n";
    }
    
	return 0;
}
