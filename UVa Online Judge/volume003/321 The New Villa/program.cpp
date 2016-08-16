// The New Villa
// UVa ID: 321
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int r, d, s, connected[11][11], switchs[11][11];

struct state
{
    bitset<11> visited;
    vector<int> sequences;
};

bool solved(state current)
{
    for (int i = 1; i < current.sequences.size(); i++)
    {
        int in_room = current.sequences[i];

        bool can_turn_on = false;
        for (int j = 0; j < i; j++)
        {
            int pre_room = current.sequences[j];
            if (switchs[pre_room][in_room])
            {
                can_turn_on = true;
                break;
            }
        }
        if (!can_turn_on)
            return false;
    }
    
    for (int i = 0; i < current.sequences.size() - 1; i++)
    {
        int pre_room = current.sequences[i];

        bool can_turn_off = false;
        for (int j = i + 1; j < current.sequences.size(); j++)
        {
            int in_room = current.sequences[j];
            if (switchs[in_room][pre_room])
            {
                can_turn_off = true;
                break;
            }
        }
        
        if (!can_turn_off)
            return false;
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> r >> d >> s)
    {
        if (r == 0)
            break;

        memset(connected, 0, sizeof(connected));
        memset(switchs, 0, sizeof(switchs));

        int from, to;   
        for (int i = 1; i <= d; i++)
        {
            cin >> from >> to;
            connected[from][to] = connected[to][from] = 1;
        }
        
        for (int i = 1; i <= s; i++)
        {
            cin >> from >> to;
            switchs[from][to] = 1;
        }
        
        state start = (state){bitset<11>(0), vector<int>()};
        start.visited.set(1);
        start.visited.set(r);
        start.sequences.push_back(1);
        start.sequences.push_back(r);
        
        queue<state> unvisited;
        unvisited.push(start);
        
        bool solution_exist = false;
        vector<int> solution;
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            if (solved(current))
            {
                solution.assign(current.sequences.begin(), current.sequences.end());
                solution_exist = true;
                break;
            }
            
            int last_room = current.sequences[current.sequences.size() - 2];
            for (int i = 2; i < r; i++)
            {
                if (current.visited.test(i))
                    continue;
                if (connected[last_room][i] == 0)
                    continue;

                bool can_turn_on = false;
                for (int j = 0; j < current.sequences.size() - 1; j++)
                    if (switchs[current.sequences[j]][i])
                    {
                        can_turn_on = true;
                        break;
                    }
                if (!can_turn_on)
                    continue;

                current.visited.set(i);
                current.sequences.insert(current.sequences.end() - 1, i);
                unvisited.push(current);
            }
        }
        
        cout << "Villa #" << ++cases << '\n';
        if (solution_exist)
        {
            vector<string> actions;

            set<int> light_off, light_on;
            for (int i = 1; i < solution.size(); i++)
                light_off.insert(solution[i]);
            for (int i = 0; i < solution.size() - 1; i++)
                light_on.insert(solution[i]);

            for (int i = 0; i < solution.size(); i++)
            {
                int in_room = solution[i];
                for (int j = i + 1; j < solution.size(); j++)
                {
                    int next_room = solution[j];
                    if (light_off.find(next_room) != light_off.end() && switchs[in_room][next_room])
                    {
                        actions.push_back("- Switch on light in room " + to_string(next_room) + ".");
                        light_off.erase(next_room);
                    }
                }

                if (i > 0)
                    actions.push_back("- Move to room " + to_string(in_room) + ".");

                for (int j = 0; j < i; j++)
                {
                    int pre_room = solution[j];
                    if (light_on.find(pre_room) != light_on.end() && switchs[in_room][pre_room])
                    {
                        actions.push_back("- Switch off light in room " + to_string(pre_room) + ".");
                        light_on.erase(pre_room);
                    }
                }
            }
            
            cout << "The problem can be solved in " << actions.size() << " steps:\n";
            for (auto action : actions)
                cout << action << '\n';
        }
        else
            cout << "The problem cannot be solved.\n";
        cout << '\n';
    }
    
	return 0;
}
