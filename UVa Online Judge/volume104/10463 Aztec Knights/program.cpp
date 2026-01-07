// Aztec Knights
// UVa ID: 10463
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 素数表
vector<bool> getPrimeTable(int maxN) {
    vector<bool> isPrime(maxN + 1, true);
    if (maxN >= 0) isPrime[0] = false;
    if (maxN >= 1) isPrime[1] = false;
    for (int i = 2; i * i <= maxN; ++i)
        if (isPrime[i])
            for (int j = i * i; j <= maxN; j += i)
                isPrime[j] = false;
    return isPrime;
}

// Aztec Knight 的移动偏移量：移动3步和1步的组合
const int dx[] = {3, 3, -3, -3, 1, 1, -1, -1};
const int dy[] = {1, -1, 1, -1, 3, -3, 3, -3};

struct State {
    int x, y, steps;
    State(int x, int y, int steps) : x(x), y(y), steps(steps) {}
};

int main() {
    int m, n, srow, scol, drow, dcol;
    int caseNo = 0;
    vector<bool> isPrime = getPrimeTable(250);
    
    while (cin >> m >> n >> srow >> scol >> drow >> dcol) {
        caseNo++;
        // 特殊情况：起点就是终点
        if (srow == drow && scol == dcol) {
            cout << "CASE# " << caseNo << ": ";
            // 根据题目示例，0步视为合数
            cout << "The knight takes 0 composite move(s)." << '\n';
            continue;
        }
        // 第一次BFS：寻找素数步数
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<State> q;
        q.push(State(srow, scol, 0));
        visited[srow][scol] = true;
        int primeResult = -1;
        bool foundPrime = false;
        while (!q.empty() && !foundPrime) {
            State cur = q.front(); q.pop();
            for (int i = 0; i < 8; ++i) {
                int nx = cur.x + dx[i], ny = cur.y + dy[i];
                int nextSteps = cur.steps + 1;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    if (nx == drow && ny == dcol) {
                        if (isPrime[nextSteps]) {
                            primeResult = nextSteps;
                            foundPrime = true;
                            break;
                        }
                        // 如果是合数步到达目标，不停止，继续搜索
                        // 也不标记visited，因为可能以素数步再次到达
                    } else if (!visited[nx][ny]) {
                        visited[nx][ny] = true;
                        q.push(State(nx, ny, nextSteps));
                    }
                }
            }
        }
        // 输出结果
        cout << "CASE# " << caseNo << ": ";
        if (foundPrime) cout << "The knight takes " << primeResult << " prime moves." << '\n';
        else {
            // 第二次BFS：寻找合数步数
            visited = vector<vector<bool>>(m, vector<bool>(n, false));
            queue<State> q2;
            q2.push(State(srow, scol, 0));
            visited[srow][scol] = true;
            int compositeResult = -1;
            bool foundComposite = false;
            while (!q2.empty() && !foundComposite) {
                State cur = q2.front(); q2.pop();
                for (int i = 0; i < 8; ++i) {
                    int nx = cur.x + dx[i], ny = cur.y + dy[i];
                    int nextSteps = cur.steps + 1;
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                        if (nx == drow && ny == dcol) {
                            // 合数步到达目标，记录并停止
                            compositeResult = nextSteps;
                            foundComposite = true;
                            break;
                        } else if (!visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q2.push(State(nx, ny, nextSteps));
                        }
                    }
                }
            }
            if (foundComposite) cout << "The knight takes " << compositeResult << " composite move(s)." << endl;
            else cout << "Destination is not reachable." << endl;
        }
    }
    return 0;
}
