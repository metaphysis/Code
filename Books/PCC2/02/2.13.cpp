// Sparse Table
#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 20), K = 24;

int N, A[MAXN], log2t[MAXN + 1] = {}, st[MAXN][K] = {};

void prepare()
{
    log2t[1] = 0;
    for (int i = 2; i <= N; i++) log2t[i] = log2t[i / 2] + 1;
    for (int i = 0; i < N; i++) st[i][0] = A[i];
    for (int j = 1; j < K; j++)
	    for (int i = 0; i + (1 << j) <= N; i++)
		    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

// min
int query1(int L, int R)
{
    int j = log2t[R - L + 1];
    return min(st[L][j], st[R - (1 << j) + 1][j]);
}

// sum
int query2(int L, int R)
{
    int sum = 0;
    for (int j = K; j >= 0; j--)
	    if ((1 << j) <= R - L + 1) {
		    sum += st[L][j];
		    L += 1 << j;
	    }
}

int main(int argc, char *argv[])
{
    //srand(time(NULL));
    
    N = 128;
    for (int i = 0; i < N; i++) A[i] = rand() % MAXN;

    prepare();

    for (int i = 0; i < 10; i++)
    {
        int L = rand() % N, R = rand() % N;
        if (L > R) swap(L, R);
        cout << "[" << L << ", " << R << "] = " << query(L, R) << '\n';
    }
    return 0;
}
