// Recycling
// UVa IDs: 154
// Verdict: Accepted
// Submission Date: 2016-02-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

string colours = "roygb";
string wastes = "PGASN";

int matrix[110][5] = { 0 };
int counter[5][5] = { 0 };
int cities = 0;

int getIndex(void)
{
    int minChanges = 0;
    int minIndex = 0;
    for (int i = 0; i < cities; i++)
    {
        int allChanges = 0;
        for (int j = 0; j < 5; j++)
            allChanges += counter[j][matrix[i][j]];
        if (allChanges > minChanges)
        {
            minChanges = allChanges;
            minIndex = i;
        }
    }
    
    cout << (minIndex + 1) << endl;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line), line != "#")
    {
        if (line[0] == 'e')
        {
            getIndex();
            cities = 0;
            memset(counter, 0, sizeof(counter));
            memset(matrix, 0, sizeof(matrix));
        }
        else
        {
            for (int i = line.length() - 1; i >= 0; i--)
                if (line[i] == ' ' || line[i] == '\t')
                    line.erase(line.begin() + i);
            
            for (int i = 0; i < colours.length(); i++)
            {
                size_t colourIndex = line.find(colours[i]);
                size_t wasteIndex = wastes.find(line[colourIndex + 2]);
                counter[i][wasteIndex]++;
                matrix[cities][i] = wasteIndex;
            }
            
            cities++;
        }
    }
    
	return 0;
}
