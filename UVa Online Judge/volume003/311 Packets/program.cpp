// Packets
// UVa ID: 311
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
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
#include <string>
#include <vector>

using namespace std;

vector<int> blocks = {0, 5, 3, 1}, cells = {0, 7, 6, 5};

int main(int argc, char *argv[])
{
    int c1, c2, c3, c4, c5, c6;
    while (cin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6)
    {
        int block = 0, cell = 0;
        
        int parcels = c6;
        
        parcels += c5;
        cell = c5 * 11;
        c1 = (c1 - cell < 0 ? 0 : c1 - cell);
            
        parcels += c4;
        if (c2 > 0)
        {
            if (c2 >= c4 * 5)
                c2 -= c4 * 5;
            else
            {
                cell = (c4 * 5 - c2) * 4;
                c1 = (c1 - cell < 0 ? 0 : c1 - cell);
                c2 = 0;
            }
        }
        else
        {
            cell = c4 * 20;
            c1 = (c1 - cell < 0 ? 0 : c1 - cell);
        }
        
        parcels += c3 / 4;
        if (c3 % 4 > 0)
        {
            parcels += 1;
            block = blocks[c3 % 4], cell = cells[c3 % 4];
            if (c2 >= block)
                c2 -= block;
            else
            {
                cell += (block - c2) * 4;
                c2 = 0;
            }
            c1 = (c1 - cell < 0 ? 0 : c1 - cell);
        }
        
        parcels += c2 / 9;
        if (c2 % 9 > 0)
        {
            parcels += 1;
            cell = (9 - (c2 % 9)) * 4;
            c1 = (c1 - cell < 0 ? 0 : c1 - cell); 
        }
        
        parcels += c1 / 36;
        if (c1 % 36 > 0)
            parcels += 1;
            
        if (parcels == 0)
            break;
            
        cout << parcels << endl;
    }
    
	return 0;
}
