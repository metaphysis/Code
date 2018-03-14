// Potentiometers
// UVa ID: 12086
// Verdict: Accepted
// Submission Date: 2017-10-29
// UVa Run Time: 0.220s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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
    if (index < left || index > right) return;
    if (index == left && index == right)
    {
        st[p] = value;
        return;
    }
    int middle = (left + right) >> 1;
    update((p << 1) + 1, left, middle, index, value);
    update((p + 1) << 1, middle + 1, right, index, value);
    st[p] = st[(p << 1) + 1] + st[(p + 1) << 1];
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (qleft > right || qright < left) return 0;
    if (qleft <= left && qright >= right) return st[p];
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
