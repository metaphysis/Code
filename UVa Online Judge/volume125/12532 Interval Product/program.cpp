// Interval Product
// UVa ID: 12532
// Verdict: Accepted
// Submission Date: 2017-11-01
// UVa Run Time: 0.090s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100010;
int st[4 * MAXV], number[MAXV];

int sign(int n)
{
    if (n > 0) return 1;
    if (n < 0) return -1;
    return 0;
}

char symbol(int n)
{
    if (n > 0) return '+';
    if (n < 0) return '-';
    return '0';
}

void build(int p, int left, int right)
{
    if (left == right) st[p] = number[left];
    else {
        int middle = (left + right) >> 1;
        build((p << 1) + 1, left, middle);
        build((p + 1) << 1, middle + 1, right);
        st[p] = st[(p << 1) + 1] * st[(p + 1) << 1];
    }
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (qleft > right || qright < left) return 1;
    if (qleft <= left && qright >= right) return st[p];
    int middle = (left + right) >> 1;
    return query((p << 1) + 1, left, middle, qleft, qright) *
        query((p + 1) << 1, middle + 1, right, qleft, qright);
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
    st[p] = st[(p << 1) + 1] * st[(p + 1) << 1];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, K, I, J, V;
    char command;

    while (cin >> N >> K)
    {
        for (int i = 0; i < N; i++)
        {
            cin >> number[i];
            number[i] = sign(number[i]);
        }
        
        build(0, 0, N - 1);
        
        string result;
        for (int i = 0; i < K; i++)
        {
            cin >> command;
            if (command == 'C')
            {
                cin >> I >> V;
                update(0, 0, N - 1, I - 1, sign(V));
            }
            else
            {
                cin >> I >> J;
                result += symbol(query(0, 0, N - 1, I - 1, J - 1));
            }
        }
        cout << result << '\n';
    }
    
    return 0;
}
