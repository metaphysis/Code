// Cowculations
// UVa ID: 377
// Verdict: Accepted
// Submission Date: 2016-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<char, int> digits;

int getNumber(string& text)
{
    int value = 0;
    for (auto c : text)
        value = value * 4 + digits[c];
    return value;
}

int cowculation(int number1, int number2, string& op)
{
    if (op == "A") return number1 + number2;
    if (op == "R") return number2 / 4;
    if (op == "L") return number2 * 4;
    if (op == "N") return number2;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n;
    string line;
    getline(cin, line);
    n = stoi(line);

    digits['V'] = 0, digits['U'] = 1, digits['C'] = 2, digits['D'] = 3;
    
    cout << "COWCULATIONS OUTPUT" << endl;
    
    string text1, text2, text3, op1, op2, op3;
    for (int i = 1; i <= n; i++)
    {
        getline(cin, text1), getline(cin, text2);
        getline(cin, op1), getline(cin, op2), getline(cin, op3);
        getline(cin, text3);
        
        int number1 = getNumber(text1), number2 = getNumber(text2), number3 = getNumber(text3);

        number2 = cowculation(number1, number2, op1);
        number2 = cowculation(number1, number2, op2);
        number2 = cowculation(number1, number2, op3);

        if (number2 == number3 && text3.length() == 8)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    
    cout << "END OF OUTPUT" << endl;
    
	return 0;
}
