// Ahoy, Pirates!
// UVa ID: 11402
// Verdict: Accepted
// Submission Date: 2017-10-31
// UVa Run Time: 0.930s
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

const int MAXV = 1024000;
struct node { int bu, ba, tag; } st[4 * MAXV];
int pirates[MAXV];

void pushUp(int p)
{
    st[p].bu = st[(p << 1) + 1].bu + st[(p + 1) << 1].bu;
    st[p].ba = st[(p << 1) + 1].ba + st[(p + 1) << 1].ba;    
}

void commit(int p, int tag)
{
    if (st[p].tag == 1 && (tag == 2 || tag == 3))
        st[p].tag = 2;
    else if (st[p].tag == 2 && (tag == 1 || tag == 3))
        st[p].tag = 1;
    else if (st[p].tag == 3 && tag == 3) 
        st[p].tag = 0;
    else
        st[p].tag = tag;
    
    if (tag == 1) st[p].bu += st[p].ba, st[p].ba = 0;
    else if (tag == 2) st[p].ba += st[p].bu, st[p].bu = 0;
    else if (tag == 3) swap(st[p].bu, st[p].ba);
}

void pushDown(int p)
{
    if (st[p].tag)
    {
        commit((p << 1) + 1, st[p].tag);
        commit((p + 1) << 1, st[p].tag);
        st[p].tag = 0;
    }
}

void build(int p, int left, int right)
{
    st[p].tag = 0;
    if (left == right) st[p].bu = pirates[left], st[p].ba = 1 - pirates[left];
    else
    {
        int middle = (left + right) >> 1;
        build((p << 1) + 1, left, middle);
        build((p + 1) << 1, middle + 1, right);
        pushUp(p);
    }
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (qleft > right || qright < left) return 0;
    if (qleft <= left && qright >= right) return st[p].bu;

    pushDown(p);
    
    int middle = (left + right) >> 1;
    int q = query((p << 1) + 1, left, middle, qleft, qright);
    q += query((p + 1) << 1, middle + 1, right, qleft, qright);
    return q;
}

void update(int p, int left, int right, int uleft, int uright, int utag)
{
    if (uleft > right || uright < left) return;
    if (uleft <= left && uright >= right)
    {
        commit(p, utag);
        return;
    }

    pushDown(p);
    
    int middle = (left + right) >> 1;
    update((p << 1) + 1, left, middle, uleft, uright, utag);
    update((p + 1) << 1, middle + 1, right, uleft, uright, utag);

    pushUp(p);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, M, R, N, Q, q, a, b;
    string P, A;

    cin >> T;
    for (int c = 1; c <= T; c++)
    {
        N = 0;
        cin >> M;
        for (int i = 1; i <= M; i++)
        {
            cin >> R >> P;
            for (int j = 1; j <= R; j++)
                for (int k = 0; k < P.length(); k++)
                    pirates[N++] = P[k] - '0';
        }

        build(0, 0, N - 1);
        
        cout << "Case " << c << ":\n";
        q = 0;

        cin >> Q;
        for (int i = 1; i <= Q; i++)
        {
            cin >> A >> a >> b;
            if (A == "F")       update(0, 0, N - 1, a, b, 1);
            else if (A == "E")  update(0, 0, N - 1, a, b, 2);
            else if (A == "I")  update(0, 0, N - 1, a, b, 3);
            else
            {
                cout << 'Q' << ++q << ": ";
                cout << query(0, 0, N - 1, a, b) << '\n';
            }
        }
    }
    
    return 0;
}
