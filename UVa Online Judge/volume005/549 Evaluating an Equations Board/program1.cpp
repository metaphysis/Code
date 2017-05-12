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

int usedOperands[20], usedOperators[20], nGoal, exist, debug = 0;
string resource, goal, operands, operators;
char expression[20];

int evaluate(int nChosen)
{
    stack<int> result;

    for (int i = 0; i < nChosen; i++)
    {
        if (isdigit(expression[i]))
            result.push(expression[i] - '0');
        else
        {
            int a = result.top(); result.pop();
            int b = result.top(); result.pop();
            switch (expression[i])
            {
                case '+': result.push(a + b); break;
                case '-': result.push(b - a); break;
                case 'x': result.push(a * b); break;
            }
        }
    }
    return result.top();
}

void backtrack(int nChosen, int nNumber, int nOperators)
{
    if (exist) return;

    if (nNumber == 1)
    {
        if (evaluate(nChosen) == nGoal)
        {
            exist = 1;
            if (debug)
            {
                for (int i = 0; i < nChosen; i++)
                    cout << expression[i];
                cout << '\n';
            }
            return;
        }
    }
    
    if (nChosen == 0 || nOperators >= nNumber)
    {
        for (int i = 0; i < operands.length(); i++)
        {
            if (!usedOperands[i] && operands[i] != expression[nChosen])
            {
                usedOperands[i] = 1;
                expression[nChosen] = operands[i];
                backtrack(nChosen + 1, nNumber + 1, nOperators);
                if (exist) return;
                usedOperands[i] = 0;
            }
        }
    }

    if (nNumber >= 2)
    {
        for (int i = 0; i < operators.length(); i++)
        {
            if (!usedOperators[i] && operators[i] != expression[nChosen])
            {
                usedOperators[i] = 1;
                expression[nChosen] = operators[i];
                backtrack(nChosen + 1, nNumber - 1, nOperators - 1);
                if (exist) return;
                usedOperators[i] = 0;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    while (cin >> resource >> goal)
    {
        cases++;

        nGoal = stoi(goal);

        operands.clear(), operators.clear();
        
        sort(resource.begin(), resource.end());

        for (auto c : resource)
        {
            if (isdigit(c)) operands += c;
            else operators += c;
        }
        
        exist = 0;
        memset(usedOperands, 0, sizeof(usedOperands));
        memset(usedOperators, 0, sizeof(usedOperators));
        memset(expression, 0, sizeof(expression));

        backtrack(0, 0, operators.size());
        
        cout << (exist ? "solution" : "no solution") << '\n';
    }
    
    return 0;
}
