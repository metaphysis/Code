#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

vector<int> mission[10];
int sumCnt[11][10][11];

LL getNext(int n, LL cur, int city) {
    for (int i = 0; i < n; i++) {
        LL bit = 1LL << (i * 3);
        int pos = (cur >> (i * 3)) & 7;
        if (pos < (int)mission[i].size() && mission[i][pos] == city)
            cur += bit;
    }
    return cur;
}

int getCost(int n, LL cur) {
    int total = 0;
    for (int city = 1; city <= 10; city++) {
        int maxValue = 0;
        for (int i = 0; i < n; i++) {
            int pos = (cur >> (i * 3)) & 7;
            maxValue = max(maxValue, sumCnt[city][i][pos]);
        }
        total += maxValue;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        memset(sumCnt, 0, sizeof(sumCnt));
        for (int i = 0; i < n; i++) {
            int size;
            cin >> size;
            mission[i].assign(size, 0);
            for (int j = 0; j < size; j++) {
                cin >> mission[i][j];
                sumCnt[mission[i][j]][i][j]++;
            }
        }
        for (int city = 1; city <= 10; city++)
            for (int i = 0; i < n; i++)
                for (int j = 9; j >= 0; j--)
                    sumCnt[city][i][j] += sumCnt[city][i][j + 1];
        int startCity;
        cin >> startCity;
        LL start = getNext(n, 0, startCity);
        vector<LL> states;
        vector<int> pre, moveCity, depth;
        unordered_map<LL, int> id;
        id.reserve(1 << 20);
        id.max_load_factor(0.7f);
        states.push_back(start);
        pre.push_back(-1);
        moveCity.push_back(startCity);
        depth.push_back(0);
        id[start] = 0;
        queue<int> que;
        que.push(0);
        int last = -1;
        while (!que.empty()) {
            int nowId = que.front();
            que.pop();
            LL now = states[nowId];
            int len = depth[nowId], cost = getCost(n, now);
            if (cost == 0) {
                last = nowId;
                break;
            }
            if (len + cost > 20) continue;
            for (int city = 1; city <= 10; city++) {
                LL next = getNext(n, now, city);
                if (id.count(next))
                    continue;
                int nextId = states.size();
                id[next] = nextId;
                states.push_back(next);
                pre.push_back(nowId);
                moveCity.push_back(city);
                depth.push_back(len + 1);
                que.push(nextId);
            }
        }
        vector<int> answer;
        while (last != 0) {
            answer.push_back(moveCity[last]);
            last = pre[last];
        }
        answer.push_back(startCity);
        reverse(answer.begin(), answer.end());
        for (int i = 0; i < (int)answer.size(); i++) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
    return 0;
}
