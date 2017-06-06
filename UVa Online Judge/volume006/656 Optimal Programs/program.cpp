// Optimal Programs
// UVa ID: 656
// Verdict: Accepted
// Submission Date: 2017-06-06
// UVa Run Time: 0.260s
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

string commands[] = {"ADD", "DIV", "DUP", "MUL", "SUB"};
int n, source[10], target[10];

struct state
{
    string operations;
    vector<int> operands;
};

bool calculate(vector<int> &result, char operators)
{
    int a, b;
    switch (operators)
    {
        case '0':
            a = result.back(); result.pop_back();
            b = result.back(); result.pop_back();
            if (abs(a + b) > 30000) return false;
            result.push_back(a + b);
            break;
        case '1':
            a = result.back(); result.pop_back();
            b = result.back(); result.pop_back();
            if (a == 0) return false;
            if (abs(b / a) > 30000) return false;
            result.push_back(b / a);
            break;
        case '2':
            result.push_back(result.back());
            break;
        case '3':
            a = result.back(); result.pop_back();
            b = result.back(); result.pop_back();
            if (abs(a * b) > 30000) return false;
            result.push_back(a * b);
            break;
        case '4':
            a = result.back(); result.pop_back();
            b = result.back(); result.pop_back();
            if (abs(b - a) > 30000) return false;
            result.push_back(b - a);
            break;             
    }
    
    return true;
}

bool check(string &operations)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> result;
        result.push_back(source[i]);
        for (int j = 0; j < operations.size(); j++)
            if (!calculate(result, operations[j])) return false;
        if (result.back() != target[i]) return false;
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> source[i];
        for (int i = 0; i < n; i++) cin >> target[i];
        
        string sequence = "Impossible", empty;
        state current, next;
        
        queue<state> unvisited;
        unvisited.push(state{empty, vector<int>(1, source[0])});
        
        while (!unvisited.empty())
        {
            current = unvisited.front();
            unvisited.pop();

            if (current.operations.size() > 10) continue;
            if (current.operands.size() == 1 && current.operands.back() == target[0])
            {
                if (check(current.operations))
                {
                    sequence.clear();
                    for (int i = 0; i < current.operations.size(); i++)
                    {
                        if (i > 0) sequence += ' ';
                        sequence += commands[current.operations[i] - '0'];
                    }
                    if (sequence.length() == 0) sequence = "Empty sequence";
                    break;
                }
            }

            if (current.operands.size() <= 1)
            {
                next = current;
                next.operations += '2', next.operands.push_back(next.operands.back());
                unvisited.push(next);
            }
            else
            {
                for (int i = 0; i < 5; i++)
                {
                    next = current;
                    next.operations += (char)('0' + i);
                    if (!calculate(next.operands, (char)('0' + i))) continue;
                    unvisited.push(next);
                }
            }
        }

        cout << "Program " << ++cases << '\n';
        cout << sequence << "\n\n";
    }
    
    return 0;
}
