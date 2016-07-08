// Bingo
// UVa IDs: 370
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

pair<int, int> location[100][30];
int original[5][5], backup[5][5], counter[100] = { };

bool isBingo()
{
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int number;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            cin >> number;
            ogriginal[i][j] = number;
            backup[i][j] = original[i][j];
            location[number][counter[number]++] = make_pair(i, j);
        }
        
    if (isBingo() == false)
    {
        int called;
        while (cin >> called, called)
        {
            for (int i = 0; i < counter[called]; i++)
            {
                if (isBingo()) return 0;
            }
        }
        
        cout << "No BINGO on this card." << endl;
    }
    
	return 0;
}
