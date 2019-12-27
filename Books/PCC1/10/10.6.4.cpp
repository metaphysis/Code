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
