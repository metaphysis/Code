// Majoring in Scales
// UVa ID: 449
// Verdict: Accepted
// Submission Date: 2016-08-06
// UVa Run Time: 0.020s
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    // C/B# C#/Db D D#/Eb E/Fb F/E# F#/Gb G G#/Ab A A#/Bb B/Cb
    // C, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B

    map<string, int> directions = {
        {"UP", 1}, {"DOWN", -1}
    };

    map<string, int> intervals = {
        {"SECOND", 2}, {"THIRD", 3}, {"FOURTH", 4}, {"FIFTH", 5},
        {"SIXTH", 6}, {"SEVENTH", 7}, {"OCTAVE", 8}
    };

    map<string, vector<string>> scales = {
        {"C", {"C", "D", "E", "F", "G", "A", "B"}},
        {"Db", {"Db", "Eb", "F", "Gb", "Ab", "Bb", "C"}},
        {"D", {"D", "E", "F#", "G", "A", "B", "C#"}},
        {"Eb", {"Eb", "F", "G", "Ab", "Bb", "C", "D"}},
        {"E", {"E", "F#", "G#", "A", "B", "C#", "D#"}},
        {"F", {"F", "G", "A", "Bb", "C", "D", "E"}},    // "Bb" not "A#", why?
        {"Gb", {"Gb", "Ab", "Bb", "Cb", "Db", "Eb", "F"}},
        {"G", {"G", "A", "B", "C", "D", "E", "F#"}},
        {"Ab", {"Ab", "Bb", "C", "Db", "Eb", "F", "G"}},
        {"A", {"A", "B", "C#", "D", "E", "F#", "G#"}},
        {"Bb", {"Bb", "C", "D", "Eb", "F", "G", "A"}},
        {"B", {"B", "C#", "D#", "E", "F#", "G#", "A#"}}
    };
    
    string line;
    while (getline(cin, line))
    {
        string key;
        istringstream iss(line);
        iss >> key;
        
        cout << "Key of " << key << '\n';
        
        getline(cin, line);
        iss.clear(); iss.str(line);
        
        string block, tone, direction, interval;
        while (getline(iss, block, ';'))
        {
            istringstream cmd(block);
            cmd >> tone >> direction >> interval;
            cout << tone << ": ";
            
            bool found = false;
            for (int i = 0; i < scales[key].size(); i++)
                if (scales[key][i] == tone)
                {
                    cout << direction << ' ' << interval << " > ";
                    string next_tone = scales[key][(i + directions[direction] * (intervals[interval] - 1) + 7) % 7];
                    cout << next_tone << '\n';
                    found = true;
                    break;
                }
            
            if (found == false)
                cout << "invalid note for this key\n";
        }
        cout << '\n';
    }
    
	return 0;
}
