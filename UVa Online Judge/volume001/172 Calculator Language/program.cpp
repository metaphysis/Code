// Calculator Language
// UVa ID: 172
// Verdict: Accepted
// Submission Date: 2016-02-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;

const int VARIABLE = 0, OPERATOR = 1, NUMBER = 2;
struct symbol
{
    char character;
    int number;
    int category;
};

int original[26] = { 0 };
int now[26] = { 0 };

vector < symbol > symbols;

void calculate()
{
    stack<symbol> result;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.category == VARIABLE || s.category == NUMBER)
            result.push(s);
        else
        {
            symbol a = result.top();
            result.pop();
            symbol b = result.top();
            result.pop();

            int aa, bb, cc;
            if (a.category == VARIABLE)
                aa = now[a.character - 'A'];
            else
                aa = a.number;
                
            if (b.category == VARIABLE)
                bb = now[b.character - 'A'];
            else
                bb = b.number;
                
            switch (s.character)
            {
                case '+':
                    cc = aa + bb;
                    break;
                case '-':
                    cc = aa - bb;
                    break;
                case '*':
                    cc = aa * bb;
                    break;
                case '/':
                    cc = aa / bb;
                    break;
                case '=':
                    cc = bb;
                    now[a.character - 'A'] = bb;
                    break;
                default:
                    break;
            }
            
            result.push((symbol){0, cc, NUMBER});
        }
    }
}

void infixToPostfix()
{
    reverse(symbols.begin(), symbols.end());

    for (int i = 0; i < symbols.size(); i++)
        if (symbols[i].category == OPERATOR)
        {
            if (symbols[i].character == ')')
                symbols[i].character = '(';
            else if (symbols[i].character == '(')
                symbols[i].character = ')';
        }
    
    //for (int i = 0; i < symbols.size(); i++)
        //if (symbols[i].category == VARIABLE || symbols[i].category == OPERATOR)
            //cout << symbols[i].character;
        //else
            //cout << symbols[i].number;
    //cout << endl;
        
    stack<symbol> number, operators;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        
        //cout << "current symbol: ";
        //if (s.category == NUMBER)
           //cout << s.number << endl;
        //else
            //cout << s.character << endl;
            
        if (s.category == NUMBER || s.category == VARIABLE)
        {
            //if (s.category == NUMBER)
                //cout << "push number " << s.number << " to number stack." << endl;
            //else
               //cout << "push variable " << s.character << " to number stack." << endl;
            number.push(s);
        }
        else
        {
            if (s.character == '(')
            {
                //cout << "push left bracket " << s.character << " to operator stack." << endl;
                operators.push(s);
            }
            else if (s.character == ')')
            {
                //cout << "counter right bracket " << s.character << endl;
                while (!operators.empty() && operators.top().character != '(')
                {
                    //cout << "pop operator stack to number stack. ";
                    //symbol t = operators.top();
                    //cout << "top of operator stack is: ";
                    
                    //if (t.category == NUMBER)
                        //cout << t.number;
                    //else
                        //cout << t.character;
                    //cout << endl;
                    
                    number.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                {
                    //symbol t = operators.top();
                    //cout << "pop the last symbol in operator stack: ";
                    //cout << t.character << endl;
                    
                    operators.pop();
                }
            }
            else
            {                
                if (operators.empty() || operators.top().character == '(')
                {
                    //cout << "push operator " << s.character << " to operator stack." << endl;
                    operators.push(s);
                }
                else
                {
                    while (!operators.empty() && operators.top().character != '(')
                    {
                        //cout << "pop top of operator stack to number stack: ";
                        //symbol t = operators.top();
                        //cout << t.character << endl;
                        
                        number.push(operators.top());
                        operators.pop();
                    }
                    
                    //cout << "push operator " << s.character << " to operator stack." << endl;
                    operators.push(s);
                }
            }
        }
    }

    while (!operators.empty())
    {
        number.push(operators.top());
        operators.pop();
    }
    
    symbols.clear();
    while (!number.empty())
    {
        symbols.insert(symbols.begin(), number.top());
        number.pop();
    }
    
    //for (int i = 0; i < symbols.size(); i++)
        //if (symbols[i].category == VARIABLE || symbols[i].category == OPERATOR)
            //cout << symbols[i].character;
        //else
            //cout << symbols[i].number;
    //cout << endl;
}

void parse(string line)
{
    // trim out the space
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    
    //cout << line << endl;
    
    symbols.clear();
    
    int index = 0;
    while (index < line.length())
    {
        if ((line[index] >= '0' && line[index] <= '9') || line[index] == '_')
        {
            int sign = line[index] == '_' ? -1 : 1;
            int number = 0;
            if (line[index] == '_')
                index++;
                
            while (index < line.length() &&
                (line[index] >= '0' && line[index] <= '9'))
            {
                number = number * 10 + line[index] - '0';
                index++;
            }
            symbols.push_back((symbol){0, number * sign, NUMBER});
        }
        else if (line[index] >= 'A' && line[index] <= 'Z')
        {
            symbols.push_back((symbol){line[index], 0, VARIABLE});
            index++;
        }
        else
        {
            symbols.push_back((symbol){line[index], 0, OPERATOR});
            index++;            
        }
    }
    
    infixToPostfix();
    calculate();
    
    // output the result
    vector < int > result;
    for (int i = 0; i < 26; i++)
        if (now[i] != original[i])
            result.push_back(i);

    if (result.size() > 0)
    {
        for (int i = 0; i < result.size(); i++)
        {
            cout << (char)('A' + result[i]) << " = " << now[result[i]];
            if (i < result.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
    else
        cout << "No Change" << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "#")
    {
        copy(now, now + 26, original);
        parse(line);
    }
    
	return 0;
}
