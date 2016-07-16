// The Finite State Text Processing Machine
// UVa ID: 328
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct transition
{
    string next_state, output;
};

map<string, map<string, transition>> machine;

void display(string output, char input)
{
    int position = 0;
    while (position < output.length())
    {
        if (output[position] == '\\')
        {
            if (output[position + 1] == 'b') cout << " ";
            else if (output[position + 1] == 'c') cout << input;
            else if (output[position + 1] == 'n') cout << endl;
            else if (output[position + 1] == '\\') cout << "\\";
            position++;
        }
        else
            cout << output[position];
        position++;
    }
}

string getInput(char input)
{
    if (isblank(input)) return "\\b";
    else if (input == '\n') return "\\n";
    else if (input == '\\') return "\\";
    else return string(1, input);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0, state_number;
    string line, state_name, input, next_state, output;
    
    while (cin >> n)
    {
        if (n == 0) break;

        machine.clear();

        for (int i = 1; i <= n; i++)
        {
            cin >> state_name >> state_number;

            while (cin >> input >> next_state >> output)
            {
                machine[state_name].insert(make_pair(input, (transition){next_state, output}));
                state_number--;
                if (state_number == 0)
                {
                    cin.ignore(1024, '\n');
                    break;
                }
            }
        }

        cout << "Finite State Machine " << ++cases << ":" << endl;
        
        bool exit_processing = false;
        string current_state = "START";

        while (getline(cin, line))
        {
            line += '\n';
            
            for (int i = 0; i < line.length(); i++)
            {
                input = getInput(line[i]);

                if (machine[current_state].count(input))
                {
                    display(machine[current_state][input].output, line[i]);
                    current_state = machine[current_state][input].next_state;
                }
                else
                {
                    bool transitionIsHere = false;
                    for (auto pair : machine[current_state])
                    {
                        int position = pair.first.find(input);
                        if (position != pair.first.npos && (input.length() == 2 || position == 0 || pair.first[position - 1] != '\\'))
                        {
                            transitionIsHere = true;
                            display(pair.second.output, line[i]);
                            current_state = pair.second.next_state;
                            break;
                        }
                    }

                    if (!transitionIsHere)
                    {
                        // it must have \c
                        input = "\\c";
                        if (machine[current_state].count(input))
                        {
                            display(machine[current_state][input].output, line[i]);
                            current_state = machine[current_state][input].next_state;
                        }
                    }
                }
                
                if (current_state == "END")
                {
                    exit_processing = true;
                    break;
                }
            }
            
            if (exit_processing)
                break;
        }
    }

	return 0;
}
