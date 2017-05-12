// Evaluating an Equations Board
// UVa ID: 549
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int usedOperands[20], usedOperators[20];
string resource, goal;
string operands, operators;
char operandsChosen[20], operatorsChosen[20];
int nOperands, nOperators, nGoal;
bool found = false;

int evaluate()
{
    stack<int> result;
    for (int i = 0; i < nOperands; i++)
        result.push(operandsChosen[i] - '0');

    for (int i = 0; i < nOperators; i++)
    {
        int a = result.top(); result.pop();
        int b = result.top(); result.pop();
        switch (operatorsChosen[i])
        {
            case '+': result.push(a + b); break;
            case '-': result.push(b - a); break;
            case 'x': result.push(a * b); break;
        }
    }
    return result.top();
}

void backtrackOperators(int i)
{
    if (found) return;

    if (i == nOperators)
    {
        found = (evaluate() == nGoal);
        return;
    }
    
    for (int j = 0; j < operators.length(); j++)
        if (!usedOperators[j] && operators[j] != operatorsChosen[i])
        {
            usedOperators[j] = 1;
            operatorsChosen[i] = operators[j];
            backtrackOperators(i + 1);
            if (found) return;
            usedOperators[j] = 0;
        }
}

void backtrackOperands(int i)
{
    if (found) return;
    
    if (i == nOperands)
    {
        nOperators = nOperands - 1;
        memset(usedOperators, 0, sizeof(usedOperators));
        memset(operatorsChosen, 0, sizeof(operatorsChosen));
        backtrackOperators(0);
        return;
    }
    
    for (int j = 0; j < operands.length(); j++)
        if (!usedOperands[j] && operands[j] != operandsChosen[i])
        {
            usedOperands[j] = 1;
            operandsChosen[i] = operands[j];
            backtrackOperands(i + 1);
            if (found) return;
            usedOperands[j] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> resource >> goal)
    {
        nGoal = stoi(goal);

        operands.clear(), operators.clear();
        
        sort(resource.begin(), resource.end());

        for (auto c : resource)
        {
            if (isdigit(c)) operands += c;
            else operators += c;
        }
        
        found = false;

        for (int i = 1; i <= operands.length(); i++)
        {
            if ((i - 1) > operators.length()) continue;

            memset(usedOperands, 0, sizeof(usedOperands));
            memset(operandsChosen, 0, sizeof(operandsChosen));
            
            nOperands = i;
            backtrackOperands(0);
            
            if (found) break;
        }
        
        cout << (found ? "solution" : "no solution") << '\n';
    }
    
    return 0;
}
