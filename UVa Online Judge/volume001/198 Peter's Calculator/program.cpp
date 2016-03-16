// Peter's Calculator
// UVa IDs: 198
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
    string letters;
    int number, category;
};

set < string > undefined;
map < string, vector < symbol > > formula;
map<string, int> priority;

bool calculate(vector < symbol > symbols, int &value)
{
    stack < symbol > result;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.category == VARIABLE || s.category == NUMBER)
            result.push(s);
        else
        {
            symbol b = result.top();
            result.pop();
            symbol a = result.top();
            result.pop();

            int aa, bb, cc;
            if (a.category == VARIABLE)
            {
                if (undefined.count(a.letters) > 0)
                    return false;
                
                if (formula.count(a.letters) == 0)
                    return false;
                
                undefined.insert(a.letters);
                if (calculate(formula[a.letters], aa) == false)
                    return false;
                undefined.erase(a.letters);
            }
            else
                aa = a.number;
                
            if (b.category == VARIABLE)
            {
                if (undefined.count(b.letters) > 0)
                    return false;
                
                if (formula.count(b.letters) == 0)
                    return false;
                
                undefined.insert(b.letters);    
                if (calculate(formula[b.letters], bb) == false)
                    return false;
                undefined.insert(b.letters);
            }
            else
                bb = b.number;
            
            if (s.letters == "+")
                cc = aa + bb;
            else if (s.letters == "-")
                cc = aa - bb;
            else if (s.letters == "*")
                cc = aa * bb;
                
            result.push((symbol){"", cc, NUMBER});
        }
    }
    
    if (result.top().category == NUMBER)
    {
        value = result.top().number;
        return true;
    }
    else
    {
        string variable = result.top().letters;
        if (undefined.count(variable) > 0)
            return false;
            
        if (formula.count(variable) == 0)
            return false;
            
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

vector < symbol > infixToPostfix(vector < symbol > symbols)
{
    stack<symbol> number, operators;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        
        if (s.category == NUMBER || s.category == VARIABLE)
            number.push(s);
        else
        {
            if (s.letters == "(")
                operators.push(s);
            else if (s.letters == ")")
            {
                while (!operators.empty() && operators.top().letters != "(")
                {
                    number.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                    operators.pop();
            }
            else
            {                
                if (operators.empty() || operators.top().letters == "(" ||
                    !lessPriority(s.letters, operators.top().letters))
                {
                    operators.push(s);
                }
                else
                {
                    while (!operators.empty() &&
                        lessPriority(s.letters, operators.top().letters))
                    {
                        number.push(operators.top());
                        operators.pop();
                    }
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
    
    return symbols;
}

void parse(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);

    string left = line.substr(0, line.find(":="));
    line = line.substr(line.find(":=") + 2);
    
    // change the negative letters to _
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
    
    if (line.front() == '-')
        line[0] = '_';
    
    //cout << line << endl;
    
    index = 0;
    vector < symbol > symbols;
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
            symbols.push_back((symbol){"", number * sign, NUMBER});
        }
        else if (isalpha(line[index]))
        {
            string block;
            while (index < line.length())
                if (isalpha(line[index]) || isdigit(line[index]))
                {
                    block += line[index];
                    index++;
                }
                else
                    break;
            
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
        if (line.find(":=") != line.npos)
            parse(line);
        else
        {
            if (line.find("PRINT") != line.npos)
            {
                int index = line.length() - 1;
                while (isblank(line[index]))
                    index--;
                    
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
