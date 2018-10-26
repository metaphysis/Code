// Erasing and Winning
// UVa ID: 11491
// Verdict: Accepted
// Submission Date: 2018-10-26
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, D;
string A;

struct NODE
{
    int field, idx;
};

const int MAXN = (1 << 18), K = 18;

int log2t[MAXN + 1] = {};
NODE st[MAXN][K];

NODE maxSelf(NODE x, NODE y)
{
    if (x.field != y.field) return x.field > y.field ? x : y;
    return x.idx < y.idx ? x : y;
}

void prepare()
{
    log2t[1] = 0;
    for (int i = 2; i <= N; i++) log2t[i] = log2t[i / 2] + 1;
    for (int i = 0; i < N; i++) st[i][0].field = A[i] - '0', st[i][0].idx = i;
    for (int j = 1; j < K; j++)
	    for (int i = 0; i + (1 << j) <= N; i++)
		    st[i][j] = maxSelf(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

NODE query(int L, int R)
{
    int j = log2t[R - L + 1];
    return maxSelf(st[L][j], st[R - (1 << j) + 1][j]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> N >> D)
    {
        if (N == 0) break;
        cin >> A;
        prepare();
        D = N - D;
        for (int d = D, S = 0; d >= 1; d--)
        {
            NODE r = query(S, N - d);
            cout << r.field;
            S = r.idx + 1;
        }
        cout << '\n';
    }

    return 0;
}
