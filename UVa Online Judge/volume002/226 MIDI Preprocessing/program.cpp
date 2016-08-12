// MIDI Preprocessing
// UVa ID: 226
// Verdict: Accepted
// Submission Date: 2016-06-02
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <set>
#include <vector>

using namespace std;

const int ON = 1, OFF  = 0;

// on, 1 = ON, 0 = OFF
struct command
{
    int time_unit, switches, note_number;
    bool valid;

    bool operator<(command x) const
    {
        if (time_unit != x.time_unit)
            return time_unit < x.time_unit;
        else if (switches != x.switches)
            return switches > x.switches;
        else
            return note_number < x.note_number;
    }
};

vector<command> commands;
map<int, vector<command>> buffer;
map<int, int> counter;

void preprocess(vector <command> &program)
{
    vector<pair<command, command>> fixed;
    command empty;

    // pair the on and off command
    for (int i = 0, currentIndex = 0; i < program.size(); i++)
    {
        if (program[i].switches == ON)
            fixed.push_back(make_pair(program[i], empty));
        else
        {
            fixed[currentIndex].second = program[i];
            currentIndex++;
        }
    }

    // fix the program by rules
    for (int i = 1; i < fixed.size(); i++)
    {
        if (fixed[i].first.time_unit <= fixed[i - 1].second.time_unit)
        {
            fixed[i - 1].second.time_unit = fixed[i].first.time_unit;
            fixed[i - 1].second.time_unit--;
            fixed[i - 1].second.switches = OFF;

            fixed[i].first.switches = ON;
        }

        if (fixed[i - 1].second.time_unit == fixed[i - 1].first.time_unit)
        {
            fixed[i - 1].second.valid = false;
            fixed[i].first.valid = false;
        }
    }

    // send valid program item to queue for sorting
    for (int i = 0; i < fixed.size(); i++)
    {
        if (fixed[i].first.valid)
            commands.push_back(fixed[i].first);
        if (fixed[i].second.valid)
            commands.push_back(fixed[i].second);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (true)
    {
        commands.clear(), buffer.clear(), counter.clear();

        int time_unit_in, note_number_in;
        string switches_in;

        while (getline(cin, line), line != "-1" && line != "-2")
        {
            command aCommand;
            istringstream iss(line);
            iss >> time_unit_in >> switches_in >> note_number_in;

            aCommand.time_unit = time_unit_in;
            aCommand.switches = switches_in == "ON";
            aCommand.note_number = note_number_in;
            aCommand.valid = true;

            // if command is OFF, push back and balance it
            if (aCommand.switches == OFF)
            {
                buffer[aCommand.note_number].push_back(aCommand);
                counter[aCommand.note_number]--;
            }
            else
            {
                if (counter[aCommand.note_number] > 0 ||
                    buffer[aCommand.note_number].size() == 0 ||
                    aCommand.time_unit == buffer[aCommand.note_number].back().time_unit)
                {
                    buffer[aCommand.note_number].push_back(aCommand);
                    counter[aCommand.note_number]++;
                }
                else
                {
                    // process and send it to priority queue
                    preprocess(buffer[aCommand.note_number]);

                    // clear buffer
                    buffer[aCommand.note_number].clear();
                    buffer[aCommand.note_number].push_back(aCommand);
                    counter[aCommand.note_number] = 1;
                }
            }
        }

        // process the remaining command
        for (int i = 1; i <= 127; i++)
            if (buffer[i].size() > 0)
                preprocess(buffer[i]);

        sort(commands.begin(), commands.end());
        for (auto it = commands.begin(); it != commands.end(); it++)
        {
            cout << (*it).time_unit << " " << ((*it).switches ? "ON" : "OFF");
            cout << " " << (*it).note_number << "\n";
        }

        cout << line << "\n";

        if (line == "-2")
            break;
    }

    return 0;
}
