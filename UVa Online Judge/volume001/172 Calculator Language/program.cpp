// Calculator Language
// UVa ID: 172
// Verdict: Accepted
// Submission Date: 2016-02-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int VARIABLE = 0, OPERATOR = 1, NUMBER = 2;

struct symbol
{
    int token, category;
};

int original[26] = { 0 };
int now[26] = { 0 };

vector<symbol> symbols;

void calculate()
{
    stack<symbol> operands;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.category == VARIABLE || s.category == NUMBER)
            operands.push(s);
        else
        {
            symbol a = operands.top(); operands.pop();
            symbol b = operands.top(); operands.pop();

            int aa, bb, cc;
            if (a.category == VARIABLE)
                aa = now[a.token - 'A'];
            else
                aa = a.token;
                
            if (b.category == VARIABLE)
                bb = now[b.token - 'A'];
            else
                bb = b.token;
                
            switch (s.token)
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
                    now[a.token - 'A'] = bb;
                    break;
                default:
                    break;
            }
            
            operands.push((symbol){cc, NUMBER});
        }
    }
}

void infixToPostfix()
{
    reverse(symbols.begin(), symbols.end());

    for (int i = 0; i < symbols.size(); i++)
        if (symbols[i].category == OPERATOR)
        {
            if (symbols[i].token == ')')
                symbols[i].token = '(';
            else if (symbols[i].token == '(')
                symbols[i].token = ')';
        }
        
    stack<symbol> operands, operators;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
            
        if (s.category == NUMBER || s.category == VARIABLE)
        {
            operands.push(s);
        }
        else
        {
            if (s.token == '(')
            {
                operators.push(s);
            }
            else if (s.token == ')')
            {
                while (!operators.empty() && operators.top().token != '(')
                {
                    operands.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                    operators.pop();
            }
            else
            {                
                if (operators.empty() || operators.top().token == '(')
                {
                    operators.push(s);
                }
                else
                {
                    while (!operators.empty() && operators.top().token != '(')
                    {
                        operands.push(operators.top());
                        operators.pop();
                    }

                    operators.push(s);
                }
            }
        }
    }

    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }
    
    symbols.clear();
    while (!operands.empty())
    {
        symbols.insert(symbols.begin(), operands.top());
        operands.pop();
    }
}

void parse(string line)
{
    // trim out the space
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    
    symbols.clear();
    
    int index = 0;
    while (index < line.length())
    {
        if ((line[index] >= '0' && line[index] <= '9') || line[index] == '_')
        {
            int sign = line[index] == '_' ? -1 : 1;
            int operands = 0;
            if (line[index] == '_')
                index++;
                
            while (index < line.length() &&
                (line[index] >= '0' && line[index] <= '9'))
            {
                operands = operands * 10 + line[index] - '0';
                index++;
            }
            symbols.push_back((symbol){operands * sign, NUMBER});
        }
        else if (line[index] >= 'A' && line[index] <= 'Z')
        {
            symbols.push_back((symbol){line[index], VARIABLE});
            index++;
        }
        else
        {
            symbols.push_back((symbol){line[index], OPERATOR});
            index++;            
        }
    }
    
    infixToPostfix();
    calculate();
    
    // output the operands
    vector < int > operands;
    for (int i = 0; i < 26; i++)
        if (now[i] != original[i])
            operands.push_back(i);

    if (operands.size() > 0)
    {
        for (int i = 0; i < operands.size(); i++)
        {
            cout << (char)('A' + operands[i]) << " = " << now[operands[i]];
            if (i < operands.size() - 1)
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
