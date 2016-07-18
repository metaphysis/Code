// The Tower of Babylon
// UVa ID: 437
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct block
{
    int x, y, z;
    
    bool operator < (const block& another) const
    {
        if (x != another.x) return x > another.x;
        else if (y != another.y) return y > another.y;
        else return z > another.z;
    }
};

vector<block> blocks;
vector<block> max_sequence;

int max_height = 0;

bool smaller(int length, int width, int next_length, int next_width)
{
    if (next_length <= length && next_width < width) return true;
    if (next_length < length && next_width <= width) return true;
    if (next_length <= width && next_width < width) return true;
    return false;
}

//void backtrack(int length, int width, int height, vector<block> sequence)
void backtrack(int length, int width, int height)
{
    bool updated = false;
    for (int i = 0; i < blocks.size(); i++)
    {
        if (smaller(length, width, blocks[i].x, blocks[i].y))
        {
            updated = true;
            //vector<block> next(sequence);
            //next.push_back((block){blocks[i].x, blocks[i].y, blocks[i].z});
            //backtrack(blocks[i].x, blocks[i].y, height + blocks[i].z, next);
            backtrack(blocks[i].x, blocks[i].y, height + blocks[i].z);
        }
        if (smaller(length, width, blocks[i].x, blocks[i].z))
        {
            updated = true;
            //vector<block> next(sequence);
            //next.push_back((block){blocks[i].x, blocks[i].z, blocks[i].y});
            //backtrack(blocks[i].x, blocks[i].z, height + blocks[i].y, next);
            backtrack(blocks[i].x, blocks[i].z, height + blocks[i].y);
        }
        if (smaller(length, width, blocks[i].y, blocks[i].z))
        {
            updated = true;
            //vector<block> next(sequence);
            //next.push_back((block){blocks[i].y, blocks[i].z, blocks[i].x});
            //backtrack(blocks[i].y, blocks[i].z, height + blocks[i].x, next);
            backtrack(blocks[i].y, blocks[i].z, height + blocks[i].x);
        }
    }
    
    if (!updated) max_height = max(max_height, height);
    
    //if (!updated)
    //{
    //    if (max_height < height)
    //    {
    //        max_height = max(max_height, height);
    //        max_sequence.clear();
    //        max_sequence.assign(sequence.begin(), sequence.end());
    //    }
    //}
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        blocks.resize(n);
        for (int i = 1; i <= n; i++)
        {
            cin >> blocks[i - 1].x >> blocks[i - 1].y >> blocks[i - 1].z;
            if (blocks[i - 1].x < blocks[i - 1].y) swap(blocks[i - 1].x, blocks[i - 1].y);
            if (blocks[i - 1].x < blocks[i - 1].z) swap(blocks[i - 1].x, blocks[i - 1].z);
            if (blocks[i - 1].y < blocks[i - 1].z) swap(blocks[i - 1].y, blocks[i - 1].z);
        }
        
        sort(blocks.begin(), blocks.end());
        
        block biggest = blocks.front();
        
        max_height = 0;
        //backtrack(biggest.x, biggest.y, biggest.z, vector<block>(1, biggest));
        backtrack(biggest.x, biggest.y, biggest.z);
        //for (auto b : max_sequence)
        //    cout << b.x << ' ' << b.y << ' ' << b.z << '\n';
        
        cout << "Case " << ++cases << ": maximum height = " << max_height << '\n';
    }
    
	return 0;
}
