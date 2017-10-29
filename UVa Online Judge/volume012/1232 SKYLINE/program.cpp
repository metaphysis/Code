// SKYLINE
// UVa ID: 1232
// Verdict: Accepted
// Submission Date: 2017-10-29
// UVa Run Time: 0.100s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 100010;
struct node { int high, low, mark; } st[4 * MAXV];
struct building { int left, right, height; } buildings[MAXV];

void build(int p, int left, int right)
{
    st[p].mark = 0;
    if ((left + 1) == right) st[p].high = st[p].low = 0;
    else {
        int middle = (left + right) >> 1;
        build((p << 1) + 1, left, middle);
        build((p + 1) << 1, middle, right);
        st[p].high = max(st[(p << 1) + 1].high, st[(p + 1) << 1].high);
        st[p].low = min(st[(p << 1) + 1].low, st[(p + 1) << 1].low);
    }
}

void propagate(int p)
{
    if (st[p].mark)
    {
        st[(p << 1) + 1].high = st[(p << 1) + 1].low = st[(p << 1) + 1].mark = st[p].mark;
        st[(p + 1) << 1].high = st[(p + 1) << 1].low = st[(p + 1) << 1].mark = st[p].mark;
        st[p].mark = 0;
    }
}

int query(int p, int left, int right, int qleft, int qright, int height)
{
    if (qright <= left || right <= qleft) return 0;
    
    if (qleft <= left && right <= qright)
    {
        if (st[p].high <= height)
        {
            st[p].high = st[p].low = st[p].mark = height;
            return right - left;
        }
        else
        {
            if (height < st[p].low) return 0;
        }
    }

    propagate(p);

    int middle = (left + right) >> 1;
    int q = query((p << 1) + 1, left, middle, qleft, qright, height) +
        query((p + 1) << 1, middle, right, qleft, qright, height);
    
    st[p].high = max(st[(p << 1) + 1].high, st[(p + 1) << 1].high);
    st[p].low = min(st[(p << 1) + 1].low, st[(p + 1) << 1].low);
    
    return q;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
 
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        int minLeft = 100010, maxRight = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> buildings[i].left >> buildings[i].right >> buildings[i].height;
            minLeft = min(minLeft, buildings[i].left);
            maxRight = max(maxRight, buildings[i].right);
        }
        
        build(0, minLeft, maxRight);
        
        int overlapped = 0;
        for (int i = 1; i <= n; i++)
            overlapped += query(0, minLeft, maxRight, buildings[i].left, buildings[i].right, buildings[i].height);;
        cout << overlapped << '\n';
    }

    return 0;
}
