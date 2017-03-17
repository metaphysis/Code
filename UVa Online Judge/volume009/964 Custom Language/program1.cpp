// Custom Language
// UVa ID: 964
// Verdict: Accepted
// Submission Date: 2017-03-17
// UVa Run Time: 0.390s
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

const int PUSH = 0, POP = 1, DUP = 2, ADD = 3, SUB = 4, MUL = 5, DIV = 6, READ = 7,
    WRITE = 8, JUMP = 9, JUMPPOS = 10, JUMPZERO = 11;

string category[12] = {"PUSH", "POP", "DUP", "ADD", "SUB", "MUL", "DIV", "READ", "WRITE", "JUMP", "JUMPPOS", "JUMPZERO"};

struct instruction
{
    int operation, value;
    bool isData;
    string variable;
};

vector<instruction> instructions;
vector<int> datas;

bool isNumber(string &variable)
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

bool process()
{
    stack<int> result;
    vector<int> output;
    unordered_map<string, int> variables;
    
    int pointerCode = 1, pointerData = 0;
    while (true)
    {
        if (pointerCode > instructions.size() || pointerCode < 1) goto successed;

        instruction i = instructions[pointerCode - 1];

        if (i.operation == PUSH)
        {     
            if (i.isData) result.push(i.value);
            else
            {
                if (variables.find(i.variable) == variables.end()) goto aborted;
                result.push(variables[i.variable]);
            }
            pointerCode++;
        }
        else if (i.operation == POP)
        {
            if (result.size() == 0) goto aborted;
            variables[i.variable] = result.top();
            result.pop();
            pointerCode++;
        }
        else if (i.operation == DUP)
        {
            if (result.size() == 0) goto aborted;
            result.push(result.top());
            pointerCode++;
        }
        else if (i.operation == ADD)
        {
            if (result.size() < 2) goto aborted;   
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            result.push(value1 + value2);
            pointerCode++;
        }
        else if (i.operation == SUB)
        {
            if (result.size() < 2) goto aborted;  
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            result.push(value1 - value2);
            pointerCode++;
        }
        else if (i.operation == MUL)
        {
            if (result.size() < 2) goto aborted; 
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            result.push(value1 * value2);
            pointerCode++;
        }
        else if (i.operation == DIV)
        {
            if (result.size() < 2) goto aborted;
            int value1 = result.top(); result.pop();
            int value2 = result.top(); result.pop();
            if (value2 == 0) goto aborted;
            result.push(value1 / value2);
            pointerCode++;
        }
        else if (i.operation == READ)
        {
            if (pointerData >= datas.size()) goto aborted;
            result.push(datas[pointerData]);
            pointerData++;
            pointerCode++;
        }
        else if (i.operation == WRITE)
        {
            if (result.size() == 0) goto aborted;
            output.push_back(result.top());
            result.pop();
            pointerCode++;
        }
        else if (i.operation == JUMP)
        {
            if (i.isData)
                pointerCode = i.value;
            else
            {
                if (variables.find(i.variable) == variables.end()) goto aborted;
                pointerCode = variables[i.variable];
            }
        }
        else if (i.operation == JUMPPOS)
        {
            if (result.size() == 0) goto aborted;
            int value = result.top(); result.pop();
            
            if (value <= 0) pointerCode++;
            else
            {
                if (i.isData) pointerCode = i.value;
                else
                {
                    if (variables.find(i.variable) == variables.end()) goto aborted;
                    pointerCode = variables[i.variable];
                }
            }
        }
        else if (i.operation == JUMPZERO)
        {
            if (result.size() == 0) goto aborted;
            int value = result.top(); result.pop();
            
            if (value != 0) pointerCode++;
            else
            {
                if (i.isData) pointerCode = i.value;
                else
                {
                    if (variables.find(i.variable) == variables.end()) goto aborted;
                    pointerCode = variables[i.variable];
                }
            }
        }
        else goto aborted;
    }

  aborted:
    cout << "ABORTED\n#\n";
    return false;
    
  successed:
    for (auto r : output) cout << r << '\n';
    cout << "#" << '\n';
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    
    while (getline(cin, line))
    {
        if (line.front() != '#')
        {
            string operation, variable;

            int c = 0;
            while (isblank(line[c])) c++;
            while (c < line.length() && !isblank(line[c])) operation += line[c++];
            while (c < line.length() && isblank(line[c])) c++;
            while (c < line.length() && !isblank(line[c])) variable += line[c++];
            
            int type = find(category, category + 12, operation) - category;
            bool isData = isNumber(variable);
            int value = -1;
            if (isData) value = stoi(variable);
            instructions.push_back(instruction{type, value, isData, variable});

            continue;
        }

        while (getline(cin, line))
        {
            if (line.front() == '#') break;
            datas.push_back(stoi(line));
        }

        process();

        instructions.clear();
        datas.clear();
    }

    return 0;
}
