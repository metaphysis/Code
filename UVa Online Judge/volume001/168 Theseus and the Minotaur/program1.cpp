// Theseus and the Minotaur
// UVa ID: 168
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector < vector < int > > caverns;
bool initialized = false;
int theseus, minotaur, k, lighted[26];

void buildGraph(string line)
{
    for (int i = 0; i < caverns.size(); i++)
        caverns[i].clear();
    
    for (int i = line.length() - 1; i >= 0; i--)
    {
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
        if (line[i] == '.' || line[i] == ';')
            line[i] = ' ';
    }

    istringstream iss(line);
    vector < string > blocks;
    string block;
    while (iss >> block)
        blocks.push_back(block);
        
    for (int i = 0; i < blocks.size() - 1; i++)
        for (int j = 2; j < blocks[i].length(); j++)
            caverns[blocks[i][0] - 'A'].push_back(blocks[i][j] - 'A');
            
    minotaur = blocks.back()[0] - 'A';
    theseus = blocks.back()[1] - 'A';

    k = 0;
    int index = 2;
    while (index < blocks.back().length())
    {
        k = k * 10 + (blocks.back()[index] - '0');
        index++;
    }
}

void startPursuit()
{
    fill(lighted, lighted + 26, false);

    int steps = 0;
    while (true)
    {
        bool trapped = true;
        for (int i = 0; i < caverns[minotaur].size(); i++)
            if (lighted[caverns[minotaur][i]] == false
                && caverns[minotaur][i] != theseus)
            {
                theseus = minotaur;
                minotaur = caverns[minotaur][i];
                trapped = false;
                break;
            }

        if (trapped)
        {
            cout << "/" << (char)('A' + minotaur) << "\n";
            break;
        }
        else
        {
            if (++steps == k)
            {
                cout << (char)('A' + theseus) << " ";
                lighted[theseus] = true;
                steps = 0;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 26; i++)
    {
        vector < int > cavern;
        caverns.push_back(cavern);
    }
        
    string line;
    while (getline(cin, line), line != "#")
    {
        buildGraph(line);
        startPursuit();
    }

    return 0;
}
