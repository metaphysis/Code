// Rename
// UVa ID: 282
// Verdict: Accepted
// Submission Date: 2016-06-06
// UVa Run Time: 0.120s
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

string firstpart, secondpart, command, from, to;

void match(string& filename)
{
    int i = 0;
    while (i < from.length() && i < filename.length() && from[i] == filename[i] && from[i] != '*')
        i++;
            
    int j = filename.length() - 1, k = from.length() - 1;
    while (j >= 0 && k >= 0 && filename[j] == from[k] && from[k] != '*')
        j--, k--;

    if (from[i] != '*' || from[k] != '*' || i > j + 1)
        return;
        
    cout << "mv " << filename << " ";
    cout << firstpart;
    for (int k = i; k <= j; k++)
        cout << filename[k];
    cout << secondpart << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string line;
    vector <string> filenames;
    
    while (cin >> line)
    {
        if (line != "end")
            filenames.push_back(line);
        else
        {
            while (cin >> command, command != "end")
            {
                cin >> from >> to;
                cout << command << " " << from << " " << to << endl;
                
                firstpart.clear();
                secondpart.clear();
                
                for (int i = 0; i < to.length() && to[i] != '*'; i++)
                    firstpart += to[i];
                for (int j = to.length() - 1; j >= 0 && to[j] != '*'; j--)
                    secondpart.insert(secondpart.begin(), to[j]);
                    
                for (int i = 0; i < filenames.size(); i++)
                    match(filenames[i]);
            }
            
            cout << endl;
            
            filenames.clear();
        }
    }
    
	return 0;
}
