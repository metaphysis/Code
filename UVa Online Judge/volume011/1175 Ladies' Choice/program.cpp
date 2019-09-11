// Ladies' Choice
// UVa ID: 1175
// Verdict: Accepted
// Submission Date: 2019-09-11
// UVa Run Time: 0.170s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int n;
int mList[MAXN][MAXN], wList[MAXN][MAXN];
int mPrefer[MAXN][MAXN], wPrefer[MAXN][MAXN];
int mLast[MAXN], wLast[MAXN];
int mMatched[MAXN], wMatched[MAXN];
int in[MAXN];

void galeShapley()
{
    for (int i = 1; i <= n; i++) wLast[i] = mMatched[i] = in[i] = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
        in[i] = 1;
    }
    while (!q.empty()) {
        int w = q.front(); q.pop();
        in[w] = 0;
        for (wLast[w]++; wLast[w] <= n; wLast[w]++) {
            int m = wList[w][wLast[w]];
            if (!mMatched[m] || (mPrefer[m][w] < mPrefer[m][mMatched[m]])) {
                if (mMatched[m] && !in[mMatched[m]]) {
                    q.push(mMatched[m]);
                    in[mMatched[m]] = 1;
                }
                wMatched[w] = m;
                mMatched[m] = w;
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> wList[i][j];
                wPrefer[i][wList[i][j]] = j;
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> mList[i][j];
                mPrefer[i][mList[i][j]] = j;
            }
        galeShapley();
        if (cs > 1) cout << '\n';
        for (int i = 1; i <= n; i++)
            cout << wMatched[i] << '\n';
    }

    return 0;
}
