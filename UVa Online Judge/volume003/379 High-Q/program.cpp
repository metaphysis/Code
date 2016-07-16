// High-Q
// UVa ID: 379
// Verdict: Accepted
// Submission Date: 2016-07-04
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
#include <vector>

using namespace std;

struct jump
{
    int from, middle, to;
    bool operator<(const jump &another) const
    {
        if (to != another.to)
            return to > another.to;
        else
            return from > another.from;
    }
};

int board[7][7] = {
    {0, 0, 1, 2, 3, 0, 0}, {0, 0, 4, 5, 6, 0, 0}, {7, 8, 9, 10, 11, 12, 13},
    {14, 15, 16, 17, 18, 19, 20}, {21, 22, 23, 24, 25, 26, 27},
    {0, 0, 28, 29, 30, 0, 0}, {0, 0, 31, 32, 33, 0, 0}
};

int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    vector<jump> jumps;
    
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            if (board[i][j])
            {
                for (int k = 0; k < 4; k++)
                {
                    int next_i = i + offset[k][0], next_j = j + offset[k][1];
                    int next_next_i = next_i + offset[k][0], next_next_j = next_j + offset[k][1];
                    
                    if (next_i >= 0 && next_i < 7 && next_j >= 0 && next_j < 7 &&
                        next_next_i >= 0 && next_next_i < 7 && next_next_j >= 0 && next_next_j < 7 &&
                        board[next_i][next_j] && board[next_next_i][next_next_j])
                        jumps.push_back((jump){board[i][j], board[next_i][next_j], board[next_next_i][next_next_j]});
                }
            }
    
    sort(jumps.begin(), jumps.end());
    
    //for (int i = 0; i < jumps.size(); i++)
        //cout << jumps[i].from << " " << jumps[i].middle << " " << jumps[i].to << endl;
        
    int N, hole, holes[40];
    cin >> N;
    
    cout << "HI Q OUTPUT" << endl;
    for (int i = 1; i <= N; i++)
    {
        memset(holes, 0, sizeof(holes));
        while (cin >> hole, hole)
            holes[hole] = 1;
        
        while (true)
        {
            bool updated = false;
            for (auto j : jumps)
                if (holes[j.from] && holes[j.middle] && !holes[j.to])
                {
                    updated = true;
                    holes[j.from] = 0;
                    holes[j.middle] = 0;
                    holes[j.to] = 1;
                    break;
                }
            if (updated == false)
                break;
        }
        
        int sumOfHoles = 0;
        for (int i = 1; i <= 33; i++)
            if (holes[i]) sumOfHoles += i;
            
        cout << sumOfHoles << endl;
    }
    cout << "END OF OUTPUT" << endl;
        
	return 0;
}
