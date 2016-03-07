// 168 Theseus and the Minotaur
// UVa IDs: 168
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

vector < vector < int > > caverns;
bool initialized = false;
int theseus, minotaur, k, lighted[26];

void buildGraph(string line)
{
    if (initialized == false)
    {
        for (int i = 0; i < 26; i++)
        {
            vector < int >connected;
            caverns.push_back(connected);
        }
        initialized = true;
    }
    else
    {
        for (int i = 0; i < caverns.size(); i++)
            caverns[i].clear();
    }

    int index = 0;
    while (true)
    {
        string block;
        while (line[index] != ';' && line[index] != '.')
        {
            if (isalpha(line[index]) || line[index] == ':')
                block += line[index];
            index++;
        }

        //cout << block << endl;

        for (int i = 2; i < block.length(); i++)
            caverns[block[0] - 'A'].push_back(block[i] - 'A');

        if (line[index] == '.')
            break;

        index++;
    }

    index++;
    while (isalpha(line[index]) == false)
        index++;
    minotaur = line[index++] - 'A';

    while (isalpha(line[index]) == false)
        index++;
    theseus = line[index++] - 'A';

    k = 0;
    while (index < line.length())
    {
        if (isdigit(line[index]))
            k = k * 10 + (line[index] - '0');
        index++;
    }

    //cout << "start: " << (char)('A' + theseus);
    //cout << " minotaur: " << (char)('A' + minotaur);
    //cout << " k: " << k << endl;
}

void startPursuit()
{
    fill(lighted, lighted + 26, false);

    int steps = 0;
    while (true)
    {
        bool found = false;
        for (int i = 0; i < caverns[minotaur].size(); i++)
        {
            if (lighted[caverns[minotaur][i]] == false
                && caverns[minotaur][i] != theseus)
            {
                theseus = minotaur;
                minotaur = caverns[minotaur][i];
                found = true;
                break;
            }
        }

        if (found == false)
        {
            cout << "/" << (char)('A' + minotaur) << "\n";
            break;
        }
        else
        {
            steps++;

            //cout << "theseus: " << (char)('A' + theseus);
            //cout << " minotaur: " << (char)('A' + minotaur);
            //cout << " steps: " << steps << endl;

            if (steps == k)
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
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "#")
    {
        buildGraph(line);
        startPursuit();
    }

    return 0;
}
