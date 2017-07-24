// Peter's Calculator
// UVa ID: 198
// Verdict: Accepted
// Submission Date: 2016-03-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <set>

using namespace std;

const int VARIABLE = 0, OPERATOR = 1, NUMBER = 2;

struct symbol
{
    string token;
    int operand, category;
};

set<string> undefined;
map<string, vector<symbol>> formula;
map<string, int> priority;

bool calculate(vector < symbol > symbols, int &value)
{
    stack<symbol> operands;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.category == VARIABLE || s.category == NUMBER)
            operands.push(s);
        else
        {
            symbol b = operands.top(); operands.pop();
            symbol a = operands.top(); operands.pop();

            int aa, bb, cc;
            if (a.category == VARIABLE)
            {
                if (undefined.count(a.token) > 0) return false;
                if (formula.count(a.token) == 0) return false;

                undefined.insert(a.token);
                if (calculate(formula[a.token], aa) == false) return false;
                undefined.erase(a.token);
            }
            else
                aa = a.operand;

            if (b.category == VARIABLE)
            {
                if (undefined.count(b.token) > 0) return false;
                if (formula.count(b.token) == 0) return false;
                
                undefined.insert(b.token);    
                if (calculate(formula[b.token], bb) == false) return false;
                undefined.insert(b.token);
            }
            else
                bb = b.operand;

            if (s.token == "+")
                cc = aa + bb;
            else if (s.token == "-")
                cc = aa - bb;
            else if (s.token == "*")
                cc = aa * bb;

            operands.push((symbol){"", cc, NUMBER});
        }
    }

    if (operands.top().category == NUMBER)
    {
        value = operands.top().operand;
        return true;
    }
    else
    {
        string variable = operands.top().token;

        if (undefined.count(variable) > 0) return false;
        if (formula.count(variable) == 0) return false;

        undefined.insert(variable);
        if (calculate(formula[variable], value))
            undefined.erase(variable);
        else
            return false;
    }
}

bool lessPriority(string a, string b)
{
    return priority[a] <= priority[b];
}

vector<symbol> infixToPostfix(vector<symbol> symbols)
{
    stack<symbol> operands, operators;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];

        if (s.category == NUMBER || s.category == VARIABLE)
            operands.push(s);
        else
        {
            if (s.token == "(")
                operators.push(s);
            else if (s.token == ")")
            {
                while (!operators.empty() && operators.top().token != "(")
                {
                    operands.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty()) operators.pop();
            }
            else
            {                
                if (operators.empty() || operators.top().token == "(" ||
                    !lessPriority(s.token, operators.top().token))
                {
                    operators.push(s);
                }
                else
                {
                    while (!operators.empty() && lessPriority(s.token, operators.top().token))
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

    return symbols;
}

void parse(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);

    string left = line.substr(0, line.find(":="));
    line = line.substr(line.find(":=") + 2);

    // change the negative token to _
    int index = line.length() - 1;
    while (index >= 2)
    {
        if (isdigit(line[index]) && line[index - 1] == '-')
        {
            if (line[index - 2] == '+' ||
                line[index - 2] == '-' ||
                line[index - 2] == '(' ||
                line[index - 2] == '*')
            {
                line[index - 1] = '_';
                index -= 2;
            }
        }
        index--;
    }

    if (line.front() == '-') line[0] = '_';

    index = 0;
    vector<symbol> symbols;
    while (index < line.length())
    {
        if ((line[index] >= '0' && line[index] <= '9') || line[index] == '_')
        {
            int sign = line[index] == '_' ? -1 : 1;
            int operands = 0;

            if (line[index] == '_') index++;

            while (index < line.length() && (line[index] >= '0' && line[index] <= '9'))
            {
                operands = operands * 10 + line[index] - '0';
                index++;
            }
            symbols.push_back((symbol){"", operands * sign, NUMBER});
        }
        else if (isalpha(line[index]))
        {
            string block;
            while (index < line.length())
            {
                if (isalpha(line[index]) || isdigit(line[index]))
                {
                    block += line[index];
                    index++;
                }
                else break;
            }

            symbols.push_back((symbol){block, 0, VARIABLE});
        }
        else
        {
            symbols.push_back((symbol){string(1, line[index]), 0, OPERATOR});
            index++;            
        }
    }

    formula[left] = infixToPostfix(symbols);
}

int main(int argc, char *argv[])
{
    priority.insert(pair<string, int>("+", 1));
    priority.insert(pair<string, int>("-", 1));
    priority.insert(pair<string, int>("*", 2));
    priority.insert(pair<string, int>("(", 0));
    priority.insert(pair<string, int>(")", 0));

    string line;
    while (getline(cin, line))
    {
        if (line.find(":=") != line.npos) parse(line);
        else
        {
            if (line.find("PRINT") != line.npos)
            {
                int index = line.length() - 1;
                while (isblank(line[index])) index--;

                string block;
                while (!isblank(line[index]))
                {
                    block += line[index];
                    index--;
                }

                reverse(block.begin(), block.end());

                undefined.clear();
                if (formula.count(block) > 0)
                {
                    undefined.insert(block);
                    int value;
                    if (calculate(formula[block], value))
                        cout << value << endl;
                    else
                        cout << "UNDEF" << endl;
                }    
                else
                    cout << "UNDEF" << endl;
            }
            else
                formula.clear();
        }
    }

	return 0;
}
