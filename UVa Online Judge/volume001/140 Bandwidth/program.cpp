// Bandwidth
// UVa ID: 140
// Verdict: Accepted
// Submission Date: 2016-01-19
// UVa Run Time: 0.079s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string nodes;
map<char, string> neighbours;

int getBandwidth()
{
    int minBandwidth = 1;
    for (int i = 0; i < nodes.length() - 1; i++)
        for (int j = i + 1; j < nodes.length(); j++)
            if (neighbours[nodes[i]].find(nodes[j]) != string::npos)
                if (abs(i - j) > minBandwidth)
                    minBandwidth = abs(i - j);
    return minBandwidth;
}

void getNeighbours(string record)
{
    for (int i = 2; i < record.length(); i++)
    {
        neighbours[record[0]] += record[i];
        neighbours[record[i]] += record[0];
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line), line != "#")
    {
        nodes.clear();
        neighbours.clear();

        for (int i = 0; i < line.length(); i++)
            if (isalpha(line[i]) && nodes.find(line[i]) == nodes.npos)
                nodes += line[i];

        while (line.find(';') != line.npos)
        {
            getNeighbours(line.substr(0, line.find(';')));
            line = line.substr(line.find(';') + 1);
        }
        getNeighbours(line);

        sort(nodes.begin(), nodes.end());

        int minBandwidth = 7;
        string minSequences;
        minSequences.assign(nodes);

        do
        {
            int bandwidth = getBandwidth();
            if (bandwidth < minBandwidth)
            {
                minSequences.assign(nodes);
                minBandwidth = bandwidth;
            }
        }
        while (next_permutation(nodes.begin(), nodes.end()));

        for (int i = 0; i < minSequences.length(); i++)
            cout << minSequences[i] << " ";
        cout << "-> " << minBandwidth << "\n";
    }

    return 0;
}
