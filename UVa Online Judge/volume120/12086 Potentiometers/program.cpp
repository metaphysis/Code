// Potentiometers
// UVa ID: 12086
// Verdict: Accepted
// Submission Date: 2017-10-29
// UVa Run Time: 0.220s
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

const int MAXV = 200010;
int st[4 * MAXV], potmeter[MAXV];

void build(int p, int left, int right)
{
    if (left == right) st[p] = potmeter[left];
    else {
        int middle = (left + right) >> 1;
        build((p << 1) + 1, left, middle);
        build((p + 1) << 1, middle + 1, right);
        st[p] = st[(p << 1) + 1] + st[(p + 1) << 1];
    }
}

void update(int p, int left, int right, int index, int value)
{
    if (left == right && left == index) st[p] = value;
    else {
        int middle = (left + right) >> 1;
        if (index <= middle) update((p << 1) + 1, left, middle, index, value);
        else update((p + 1) << 1, middle + 1, right, index, value);
        st[p] = st[(p << 1) + 1] + st[(p + 1) << 1];
    }
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (qright < left || right < qleft) return 0;
    if (qleft <= left && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    return query((p << 1) + 1, left, middle, qleft, qright) +
        query((p + 1) << 1, middle + 1, right, qleft, qright);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n > 0) {
        for (int i = 0; i < n; i++) cin >> potmeter[i];

        build(0, 0, n - 1);

        if (cases) cout << '\n';
        cout << "Case " << ++cases << ":\n";

        int x, y, r;
        string action;
        while (cin >> action, action != "END") {
            if (action == "S") {
                cin >> x >> r;
                update(0, 0, n - 1, x - 1, r);
            }
            else {
                cin >> x >> y;
                cout << query(0, 0, n - 1, x - 1, y - 1) << '\n';
            }
        }
    }

    return 0;
}
