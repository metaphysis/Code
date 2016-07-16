// Egyptian Multiplication
// UVa ID: 276
// Verdict: Accepted
// Submission Date: 2016-05-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map < char, int > value;

void initialize()
{
    value.insert(make_pair('|', 1));
    value.insert(make_pair('n', 10));
    value.insert(make_pair('9', 100));
    value.insert(make_pair('8', 1000));
    value.insert(make_pair('r', 10000));
}

int getNumber(string text)
{
    int number = 0;
    string digits;
    istringstream iss(text);
    while (iss >> digits)
        number += digits.length() * value[digits.front()];
    return number;
}

string displayNumber(int number)
{
    string digits = "|n98r", text;
    int index = 0;
    bool first = true;
    while (number > 0)
    {
        int digitsCount = number % 10;
        if (digitsCount > 0)
        {
            for (int i = 1; i <= digitsCount; i++)
                text += digits[index];
            text += " ";
        }
        number /= 10;
        index++;
    }
    return text;
}

void multiplicate(string first, string second)
{
    int a, b;
    
    a = getNumber(first);
    b = getNumber(second);
    
    int leftNumber = 1, rightNumber = a, result = (a * b) % 100000;
    while (b > 0)
    {
        int bit = b % 2;
        
        string text = displayNumber(leftNumber);
        if (bit > 0)
            text += "*";
        cout << setw(34) << left << text;
        
        cout << displayNumber(leftNumber * rightNumber) << endl;
        
        leftNumber *= 2;
        b /= 2;
    }
    
    cout << "The solution is: " << displayNumber(result) << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    initialize();
    
    string first, second;
    while (getline(cin, first), first.length() > 0)
    {
        getline(cin, second);
        multiplicate(first, second);
    }
    
	return 0;
}
