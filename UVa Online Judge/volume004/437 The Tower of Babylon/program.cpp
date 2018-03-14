// The Tower of Babylon
// UVa ID: 437
// Verdict: Accepted
// Submission Date: 2016-07-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct block
{
    int x, y, z;
    
    bool operator<(const block& another) const
    {
        if (x != another.x) return x < another.x;
        if (y != another.y) return y < another.y;
        return z < another.z;
    }
    
    bool operator==(const block& another) const
    {
        return x == another.x && y == another.y && z == another.z;
    }
};

vector<block> blocks;
map<int, int> memoization;
int n, max_height = 0;

bool smaller(int length, int width, int next_length, int next_width)
{
    return (next_length < length && next_width < width) || (next_length < width && next_width < length);
}

void backtrack(int id, int length, int width, int height)
{
    for (int i = 0; i < n; i++)
    {
        if (smaller(length, width, blocks[i].x, blocks[i].y))
        {
            int next_id = blocks[i].x * 1000 + blocks[i].y;
            if (memoization[next_id] > 0)
            {
                if (height + memoization[next_id] > max_height) max_height = height + memoization[next_id];
                if (height + memoization[next_id] > memoization[id]) memoization[id] = height + memoization[next_id];
            }
            else
                backtrack(id, blocks[i].x, blocks[i].y, height + blocks[i].z);
        }
    }
    
    if (height > max_height) max_height = height;
    if (height > memoization[id]) memoization[id] = height;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, x, y, z;
    while (cin >> n, n)
    {
        blocks.clear();
        memoization.clear();

        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y >> z;

            if (x < y) swap(x, y);
            if (x < z) swap(x, z);
            if (y < z) swap(y, z);
            blocks.push_back((block){x, y, z});
            blocks.push_back((block){x, z, y});
            blocks.push_back((block){y, z, x});
        }
        
        sort(blocks.begin(), blocks.end());
        n = unique(blocks.begin(), blocks.end()) - blocks.begin();
        max_height = 0;
        for (int i = 0; i < n; i++)
            backtrack(blocks[i].x * 1000 + blocks[i].y, blocks[i].x, blocks[i].y, blocks[i].z);
        
        cout << "Case " << ++cases << ": maximum height = " << max_height << '\n';
    }
    
	return 0;
}
