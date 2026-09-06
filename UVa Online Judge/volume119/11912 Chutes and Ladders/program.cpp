#include <bits/stdc++.h>
using namespace std;

int getNext(int pos, int roll, int jump[]) {
    if (pos + roll > 100) return pos;
    return jump[pos + roll];
}

bool isDegenerate(bool reachable[], bool canFinish[]) {
    for (int i = 0; i <= 100; i++)
        if (reachable[i] && !canFinish[i]) return true;
    return false;
}

long double getAverage(bool reachable[], long double prob[], int jump[]) {
    int id[101], varCount = 0;
    fill(id, id + 101, -1);
    for (int i = 0; i < 100; i++)
        if (reachable[i]) id[i] = varCount++;
    vector<vector<long double>> mat(varCount, vector<long double>(varCount + 1, 0));
    for (int s = 0; s < 100; s++) {
        if (!reachable[s]) continue;
        int row = id[s];
        mat[row][row] = 1;
        mat[row][varCount] = 1;
        for (int k = 1; k <= 20; k++) {
            if (prob[k] == 0) continue;
            int to = getNext(s, k, jump);
            if (to != 100) mat[row][id[to]] -= prob[k];
        }
    }
    for (int col = 0; col < varCount; col++) {
        int pivot = col;
        for (int row = col + 1; row < varCount; row++)
            if (fabsl(mat[row][col]) > fabsl(mat[pivot][col])) pivot = row;
        swap(mat[col], mat[pivot]);
        long double div = mat[col][col];
        for (int j = col; j <= varCount; j++) mat[col][j] /= div;
        for (int row = 0; row < varCount; row++) {
            if (row == col) continue;
            long double factor = mat[row][col];
            if (fabsl(factor) < 1e-18L) continue;
            for (int j = col; j <= varCount; j++)
                mat[row][j] -= factor * mat[col][j];
        }
    }
    return mat[id[0]][varCount];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        long double prob[21];
        int jump[101], dist[101];
        bool reachable[101], canFinish[101];
        fill(prob, prob + 21, 0);
        for (int i = 1; i <= n; i++) cin >> prob[i];
        for (int i = 0; i <= 100; i++) jump[i] = i;
        jump[1] = 38;
        jump[4] = 14;
        jump[9] = 31;
        jump[21] = 42;
        jump[28] = 84;
        jump[36] = 44;
        jump[51] = 67;
        jump[71] = 91;
        jump[80] = 100;
        jump[16] = 6;
        jump[47] = 26;
        jump[49] = 11;
        jump[56] = 53;
        jump[62] = 19;
        jump[64] = 60;
        jump[87] = 24;
        jump[93] = 73;
        jump[95] = 75;
        jump[98] = 78;
        fill(reachable, reachable + 101, false);
        queue<int> que;
        reachable[0] = true;
        que.push(0);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (int k = 1; k <= n; k++) {
                if (prob[k] == 0) continue;
                int to = getNext(cur, k, jump);
                if (!reachable[to]) {
                    reachable[to] = true;
                    que.push(to);
                }
            }
        }
        vector<int> reverseGraph[101];
        for (int s = 0; s < 100; s++) {
            for (int k = 1; k <= n; k++) {
                if (prob[k] == 0) continue;
                int to = getNext(s, k, jump);
                reverseGraph[to].push_back(s);
            }
        }
        fill(canFinish, canFinish + 101, false);
        canFinish[100] = true;
        que.push(100);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (int from : reverseGraph[cur]) {
                if (!canFinish[from]) {
                    canFinish[from] = true;
                    que.push(from);
                }
            }
        }
        if (isDegenerate(reachable, canFinish)) {
            cout << "Bad die!\n";
            continue;
        }
        fill(dist, dist + 101, -1);
        dist[0] = 0;
        que.push(0);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (int k = 1; k <= n; k++) {
                if (prob[k] == 0) continue;
                int to = getNext(cur, k, jump);
                if (dist[to] == -1) {
                    dist[to] = dist[cur] + 1;
                    que.push(to);
                }
            }
        }
        long double average = getAverage(reachable, prob, jump);
        long long roundedAverage = (long long)floorl(average + 0.5L);
        cout << dist[100] << ' ' << roundedAverage << '\n';
    }
    return 0;
}
