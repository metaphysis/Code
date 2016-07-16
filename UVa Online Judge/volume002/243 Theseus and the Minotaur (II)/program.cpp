// Theseus and the Minotaur (II)
// UVa ID: 243
// Verdict: Accepted
// Submission Date: 2016-05-31
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector < vector < int > > caverns;
int theseusFrom, theseusTo, minotaurFrom, minotaurTo, lighted[26], entered[26];
set < string > markedTheseus, markedMinotaur;

// read data
bool buildGraph()
{
    for (int i = 0; i < 26; i++)
        caverns[i].clear();

    string line;
    while (getline(cin, line), line.front() != '@')
    {
        if (line.front() == '#')
            return false;

        for (int i = 2; i < line.length(); i++)
            caverns[line.front() - 'A'].push_back(line[i] - 'A');
    }

    theseusFrom = line[1] - 'A', theseusTo = line[2] - 'A';
    minotaurFrom = line[3] - 'A', minotaurTo = line[4] - 'A';

    return true;
}

// pick a passage
int pickNextPassage(set < string > &marker, bool clockwise, int from, int to)
{
    int index = find(caverns[to].begin(), caverns[to].end(), from) - caverns[to].begin();
    int passage = -1;

    for (int counter = 0; counter < caverns[to].size(); counter++)
    {
        index += (clockwise ? -1 : 1);
        index += (index < 0 ? caverns[to].size() : 0);
        index %= caverns[to].size();

        passage = caverns[to][index];
        string key = to_string(to) + "#" + to_string(passage);

        if (marker.find(key) != marker.end())
            continue;
        else
        {
            marker.insert(key);
            break;
        }
    }

    return passage;
}

// simulation
void startPursuit()
{
    markedTheseus.clear();
    markedMinotaur.clear();

    fill(lighted, lighted + 26, false);
    fill(entered, entered + 26, -1);

    while (true)
    {
        // check
        if (theseusTo == minotaurTo)
        {
            cout << "The Minotaur is slain in " << (char)('A' +
                    theseusTo) << "\n";
            break;
        }
        else if (theseusFrom == minotaurTo && theseusTo == minotaurFrom)
        {
            cout << "Theseus is killed between " << (char)('A' + theseusFrom);
            cout << " and " << (char)('A' + theseusTo) << "\n";
            break;
        }

        // Theseus arrived, this cavern is enter by minotaur?
        if (entered[theseusTo] >= 0)
        {
            lighted[theseusTo] = true;
            theseusFrom = theseusTo, theseusTo = entered[theseusTo];
        }
        else
        {
            int passage = pickNextPassage(markedTheseus, false, theseusFrom, theseusTo);
            if (passage >= 0)
                theseusFrom = theseusTo, theseusTo = passage;
            else
                // Theseus stucks
                theseusFrom = theseusTo, theseusTo = theseusTo;
        }

        // Minotaur arrived, pick next exit
        int passage = pickNextPassage(markedMinotaur, true, minotaurFrom, minotaurTo);
        if (passage >= 0)
        {
            entered[minotaurTo] = passage;

            // Minotaur can go to this cavern?
            if (lighted[passage])
            {
                // check Theueus and Minotaur if meet in passge or not
                if (theseusFrom == passage && theseusTo == minotaurTo)
                {
                    cout << "Theseus is killed between " << (char)('A' + theseusFrom);
                    cout << " and " << (char)('A' + theseusTo) << "\n";
                    break;
                }

                // target canvers lighted, Minotaur flee back
                minotaurFrom = passage, minotaurTo = minotaurTo;
            }
            else
                // go to the passage picked
                minotaurFrom = minotaurTo, minotaurTo = passage;
        }
        else
            // Minotaur stucks
            minotaurFrom = minotaurTo, minotaurTo = minotaurTo;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    // initialize
    for (int i = 0; i < 26; i++)
    {
        vector < int >cavern;
        caverns.push_back(cavern);
    }

    // read data and simulation
    while (buildGraph())
        startPursuit();

    return 0;
}
