// Custom Language
// UVa ID: 964
// Verdict: Accepted
// Submission Date: 2017-03-17
// UVa Run Time: 1.470s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct instruction
{
    string operation, variable;
};

vector<instruction> instructions;
vector<string> datas;

bool isNumber(string & variable)
{
    if (variable.length() == 0) return false;

    int i = 0;
    if (variable.front() == '-' || variable.front() == '+')
    {
        if (variable.length() == 1) return false;
        i = 1;
    }
    for (; i < variable.length(); i++)
        if (!isdigit(variable[i]))
            return false;

    return true;
}

bool isVariable(string & variable)
{
    if (variable.length() == 0) return false;
    if (!islower(variable.front())) return false;
    for (int i = 1; i < variable.length(); i++)
        if (variable[i] == '0' || (!isdigit(variable[i]) && !islower(variable[i])))
            return false;
    return true;
}

void process()
{
    stack<int> result;
    map<string, int> variables;
    vector<int> outputed;
    
    int pointer = 1, steps = 0;
    while (true)
    {
        if (pointer > instructions.size() || pointer < 1) goto successed;

        instruction i = instructions[pointer - 1];
            
        if (i.operation == "PUSH")
        {     
            if (isNumber(i.variable))
                result.push(stoi(i.variable));
            else
            {
                if (isVariable(i.variable) && variables.find(i.variable) != variables.end())
                    result.push(variables[i.variable]);
                else
                    goto aborted;
            }
            
            pointer++;
        }
        else if (i.operation == "POP")
        {
            if (result.size() == 0) goto aborted;   
            if (!isVariable(i.variable)) goto aborted;    
            if (variables.find(i.variable) == variables.end()) variables[i.variable] = 0;
            variables[i.variable] = result.top();
            result.pop();
            pointer++;
        }
        else if (i.operation == "DUP")
        {
            if (result.size() == 0) goto aborted;
            result.push(result.top());
            pointer++;
        }
        else if (i.operation == "ADD")
        {
            if (result.size() < 2) goto aborted;   
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            result.push(value1 + value2);
            pointer++;
        }
        else if (i.operation == "SUB")
        {
            if (result.size() < 2) goto aborted;  
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            result.push(value1 - value2);
            pointer++;
        }
        else if (i.operation == "MUL")
        {
            if (result.size() < 2) goto aborted; 
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            result.push(value1 * value2);
            pointer++;
        }
        else if (i.operation == "DIV")
        {
            if (result.size() < 2) goto aborted;
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            if (value2 == 0) goto aborted;
            result.push(value1 / value2);
            pointer++;
        }
        else if (i.operation == "READ")
        {
            if (datas.size() == 0) goto aborted;

            string data = datas.front();
            datas.erase(datas.begin());
            
            if (isNumber(data))
                result.push(stoi(data));
            else
            {
                if (isVariable(data))
                {
                    if (variables.find(data) == variables.end()) goto aborted;
                    result.push(variables[data]);
                }
                else
                    goto aborted;
            }
            
            pointer++;
        }
        else if (i.operation == "WRITE")
        {
            if (result.size() == 0) goto aborted;
            outputed.push_back(result.top());
            result.pop();
            pointer++;
        }
        else if (i.operation == "JUMP")
        {
            if (isNumber(i.variable))
                pointer = stoi(i.variable);
            else
            {
                if (isVariable(i.variable))
                {
                    if (variables.find(i.variable) == variables.end()) goto aborted;
                    pointer = variables[i.variable];
                }
                else
                    goto aborted;
            }
        }
        else if (i.operation == "JUMPPOS")
        {
            if (result.size() == 0) goto aborted;
            
            int value = result.top();
            result.pop();
            
            if (value <= 0)
                pointer++;
            else
            {
                if (isNumber(i.variable))
                    pointer = stoi(i.variable);
                else
                {
                    if (isVariable(i.variable))
                    {
                        if (variables.find(i.variable) == variables.end()) goto aborted;
                        pointer = variables[i.variable];
                    }
                    else
                        goto aborted;
                }
            }
        }
        else if (i.operation == "JUMPZERO")
        {
            if (result.size() == 0) goto aborted;

            int value = result.top();
            result.pop();
            
            if (value != 0)
                pointer++;
            else
            {
                if (isNumber(i.variable))
                    pointer = stoi(i.variable);
                else
                {
                    if (isVariable(i.variable))
                    {
                        if (variables.find(i.variable) == variables.end()) goto aborted;
                        pointer = variables[i.variable];
                    }
                    else
                        goto aborted;
                }
            }
        }
        else goto aborted;
    }

  aborted:
    cout << "ABORTED\n#\n";
    return;
    
  successed:
    for (auto r : outputed) cout << r << '\n';
    cout << "#" << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;

    while (getline(cin, line))
    {
        // the termination line of # may with tailing space
        if (line.front() != '#')
        {
            istringstream iss(line);
            string operation, variable;
            iss >> operation >> variable;
            instructions.push_back(instruction{operation, variable});
            continue;
        }

        // data line may with leading space
        while (getline(cin, line))
        {
            if (line.front() == '#') break;
            istringstream iss(line);
            string constant;
            iss >> constant;
            datas.push_back(constant);
        }

        process();

        instructions.clear();
        datas.clear();
    }

    return 0;
}
