#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20000 + 5;

int T, caseNo = 0;
vector<pair<int, int>> graph[MAXN];
int num[MAXN];
bool visited[MAXN];
int answer;

void dfs(int u) {
    visited[u] = true;
    for (int i = 0; i < (int)graph[u].size(); ++i) {
        int v = graph[u][i].first;
        int type = graph[u][i].second;
        if (visited[v]) continue;
        dfs(v);
        if (type == 1) {
            if (num[v] < 0) {
                num[u] += num[v];
            } else {
                answer += abs(num[v]) + 1;
                num[u]--;
            }
        } else { // type == -1
            if (num[v] > 0) {
                num[u] += num[v];
            } else {
                num[u]++;
            }
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            graph[i].clear();
        }
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            // 正向边 u -> v，type = 1
            graph[u].push_back(make_pair(v, 1));
            // 反向边 v -> u，type = -1
            graph[v].push_back(make_pair(u, -1));
        }
        memset(num, 0, sizeof(num));
        memset(visited, false, sizeof(visited));
        answer = 0;
        dfs(0);
        if (num[0] > 0) {
            answer += num[0];
        }
        printf("Case %d: %d\n", ++caseNo, answer);
    }
    return 0;
}
