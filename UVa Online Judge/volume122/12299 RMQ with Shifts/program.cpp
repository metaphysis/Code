// RMQ with Shifts
// UVa ID: 12299
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, INF = 0x7f7f7f7f;

#define LCHILD(x) ((x << 1) | 1)
#define RCHILD(x) ((x + 1) << 1)

int data[MAXN], st[4 * MAXN];

void build(int p, int left, int right)
{
    if (left == right) st[p] = data[left];
    else {
        int middle = (left + right) >> 1;
        build(LCHILD(p), left, middle);
        build(RCHILD(p), middle + 1, right);
        st[p] = min(st[LCHILD(p)], st[RCHILD(p)]);
    }
}

void update(int p, int left, int right, int index, int value)
{
    if (left == right) st[p] = value;
    else {
        int middle = (left + right) >> 1;
        if (index <= middle)
            update(LCHILD(p), left, middle, index, value);
        else
            update(RCHILD(p), middle + 1, right, index, value);
        st[p] = min(st[LCHILD(p)], st[RCHILD(p)]);
    } 
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft) return INF;
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    int q1 = query(LCHILD(p), left, middle, qleft, qright);
    int q2 = query(RCHILD(p), middle + 1, right, qleft, qright);
    return min(q1, q2);
}

vector<int> parse(string line)
{
    vector<int> range;
    for (int i = 0; i < line.length(); )
    {
        if (isdigit(line[i]))
        {
            int n = 0;
            while (i < line.length() && isdigit(line[i]))
            {
                n = n * 10 + line[i] - '0';
                i++;
            }
            range.push_back(n);
        }
        else i++;
    }
    return range;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> data[i];
    build(0, 0, n - 1);
    
    cin.ignore(256, '\n');
    string line;
    for (int i = 0; i < q; i++)
    {
        getline(cin, line);
        vector<int> range = parse(line);
        if (line.front() == 'q')
            cout << query(0, 0, n - 1, range.front() - 1, range.back() - 1) << '\n';
        else
        {
            int backup = data[range.front() - 1];
            for (int j = 0; j < range.size() - 1; j++)
            {
                update(0, 0, n - 1, range[j] - 1, data[range[j + 1] - 1]);
                data[range[j] - 1] = data[range[j + 1] - 1];
            }
            update(0, 0, n - 1, range.back() - 1, backup);
            data[range.back() - 1] = backup;
        }
    }

    return 0;
}
