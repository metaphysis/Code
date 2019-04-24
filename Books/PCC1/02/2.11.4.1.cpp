#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 10);

struct FenwickTree
{
    int MAXN;
    vector<int> T;

    void initialize(int n) {
        this->MAXN = n;
        T.assign(n, 0);
    }

    int get(int x)
    {
        int sum = 0;
        for (; x >= 0; x = (x & (x + 1)) - 1)
            sum += T[x];
        return sum;
    }

    void add(int x, int delta)
    {
        for (; x < MAXN; x = x | (x + 1))
            T[x] += delta;
    }

    int sum(int L, int R)
    {
        return get(R) - get(L - 1);
    }

    void prepare(vector<int> A)
    {
        initialize(A.size());
        for (size_t i = 0; i < A.size(); i++)
            add(i, A[i]);
    }
};

inline int lowbit(int x) { return x & (-x); }

int T[MAXN + 16] = {};

void add(int x, int delta)
{
    for (int i = x; i <= MAXN; i += lowbit(i))
        T[i] += delta;
}

int get(int x)
{
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))
        sum += T[i];
    return sum;
}

int main(int argc, char *argv[])
{
    int A[MAXN + 16];
    vector<int> AA;
    for (int i = 1; i <= MAXN; i++)
    {
        A[i] = i;
        AA.push_back(i);
    }

    FenwickTree ft;
    ft.prepare(AA);

    for (int i = 1; i <= MAXN; i++)
        add(i, A[i]);

    for (int cases = 1; cases <= 100; cases++) {
        int L = rand() % MAXN + 1, R = rand() % MAXN + 1;
        if (L > R) swap(L, R);
        cout << "S[" << setw(4) << right << L << ", ";
        cout << setw(4) << right << R << "] => ";
        cout << get(R) - get(L - 1) << " = ";
        cout << ft.sum(L - 1, R - 1);
        cout << " = " << (R + L) * (R - L + 1) / 2 << '\n';
    }

    return 0;
}
