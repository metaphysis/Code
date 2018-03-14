// Equation Elation
// UVa ID: 397
// Verdict: Accepted
// Submission Date: 2016-07-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int cases = 0;
    
    string line;
    while (getline(cin, line))
    {
        // remove blank
        for (int i = line.length() - 1; i >= 0; i--)
            if (isblank(line[i]))
                line.erase(line.begin() + i);

        vector<string> equation;
        
        // parse
        int position = 0;
        while (position < line.length())
        {
            if (line[position] == '*' || line[position] == '/')
            {
                equation.push_back(string(1, line[position++]));

                string value;
                value += line[position++];
                while (position < line.length())
                {
                    if (isdigit(line[position]))
                        value += line[position];
                    else
                        break;
                    position++;
                }
                
                equation.push_back(value);
            }
            else if (line[position] == '+' || line[position] == '-')
            {
                if (position == 0)
                {
                    string value;
                    value += line[position++];
                    while (position < line.length())
                    {
                        if (isdigit(line[position]))
                            value += line[position];
                        else
                            break;
                        position++;
                    }
                
                    equation.push_back(to_string(stoi(value)));
                }
                else
                {
                    equation.push_back(string(1, line[position]));
                    position++;
                    
                    string value;
                    value += line[position++];
                    while (position < line.length())
                    {
                        if (isdigit(line[position]))
                            value += line[position];
                        else
                            break;
                        position++;
                    }
                
                    equation.push_back(to_string(stoi(value)));
                }
            }
            else if (line[position] == '=')
            {
                equation.push_back("=");
                string variable;
                while (position < line.length())
                {
                    if (isalpha(line[position]))
                        variable += line[position];
                    position++;
                }
                equation.push_back(variable);
            }
            else if (isdigit(line[position]))
            {
                string value;
                while (position < line.length())
                {
                    if (isdigit(line[position]))
                        value += line[position];
                    else
                        break;
                    position++;
                }
                equation.push_back(to_string(stoi(value)));
            }
        }
        
        if (cases++ > 0)
            cout << endl;
            
        // calculate
        while (equation.size() > 3)
        {
            for (int i = 0; i < equation.size(); i++)
            {
                if (i > 0)
                    cout << " ";
                cout << equation[i];
            }
            cout << "\n";
            
            bool updated = false;
            for (int i = 0; i < equation.size(); i++)
                if (equation[i] == "*" || equation[i] == "/")
                {
                    updated = true;
                    int number1 = stoi(equation[i - 1]), number2 = stoi(equation[i + 1]);
                    int result;
                    if (equation[i] == "*") result = number1 * number2;
                    if (equation[i] == "/") result = number1 / number2;
                    equation[i - 1] = to_string(result);
                    equation.erase(equation.begin() + i);
                    equation.erase(equation.begin() + i);
                    break;
                }
            
            if (updated == false)
            {
                for (int i = 0; i < equation.size(); i++)
                    if (equation[i] == "+" || equation[i] == "-")
                    {
                        int number1 = stoi(equation[i - 1]), number2 = stoi(equation[i + 1]);
                        int result;
                        if (equation[i] == "+") result = number1 + number2;
                        if (equation[i] == "-") result = number1 - number2;
                        equation[i - 1] = to_string(result);
                        equation.erase(equation.begin() + i);
                        equation.erase(equation.begin() + i);
                        break;
                    }
            }
        }
        
        for (int i = 0; i < equation.size(); i++)
        {
            if (i > 0)
                cout << " ";
            cout << equation[i];
        }
        cout << "\n";
    }
    
	return 0;
}
