#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, digit, doorId;
};

int n, m, bestCount;
vector<Edge> graph[10];
vector<int> legalGroups[10];
bool canReach[10][10];
unordered_set<unsigned long long> visited;
set<int> answerMasks;

int digitRoot(int value) {
    while (value >= 10)
        value = value / 10 + value % 10;
    return value;
}

unsigned long long encodeState(int usedMask, const array<int, 9> &pos) {
    unsigned long long code = usedMask;
    for (int i = 0; i < 9; i++)
        code = code * n + pos[i];
    return code;
}

void updateAnswer(const array<int, 9> &pos) {
    int escapeMask = 0;
    for (int i = 0; i < 9; i++)
        if (pos[i] == n - 1)
            escapeMask |= 1 << i;
    int count = __builtin_popcount(static_cast<unsigned int>(escapeMask));
    if (count > bestCount) {
        bestCount = count;
        answerMasks.clear();
        if (count > 0)
            answerMasks.insert(escapeMask);
    } else if (count == bestCount && count > 0) {
        answerMasks.insert(escapeMask);
    }
}

int getPossibleCount(const array<int, 9> &pos) {
    int count = 0;
    for (int i = 0; i < 9; i++)
        if (canReach[pos[i]][n - 1])
            count++;
    return count;
}

void dfs(int usedMask, const array<int, 9> &pos) {
    int possibleCount = getPossibleCount(pos);
    if (possibleCount < bestCount)
        return;
    unsigned long long code = encodeState(usedMask, pos);
    if (visited.count(code))
        return;
    visited.insert(code);
    updateAnswer(pos);
    if (bestCount == 9)
        return;
    for (int from = 0; from < n; from++) {
        if (!canReach[from][n - 1])
            continue;
        for (const Edge &edge : graph[from]) {
            if (edge.digit != 0 && (usedMask & (1 << edge.doorId)))
                continue;
            int atMask = 0;
            for (int i = 0; i < 9; i++)
                if (pos[i] == from)
                    atMask |= 1 << i;
            if (atMask == 0)
                continue;
            if (edge.digit == 0) {
                for (int i = 0; i < 9; i++) {
                    if (!(atMask & (1 << i)))
                        continue;
                    array<int, 9> nextPos = pos;
                    nextPos[i] = edge.to;
                    dfs(usedMask, nextPos);
                }
            } else {
                for (int groupMask : legalGroups[edge.digit]) {
                    if ((atMask & groupMask) != groupMask)
                        continue;
                    array<int, 9> nextPos = pos;
                    for (int i = 0; i < 9; i++)
                        if (groupMask & (1 << i))
                            nextPos[i] = edge.to;
                    dfs(usedMask | (1 << edge.doorId), nextPos);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int mask = 0; mask < (1 << 9); mask++) {
        int count = __builtin_popcount(static_cast<unsigned int>(mask));
        if (count < 3 || count > 5)
            continue;
        int sum = 0;
        for (int i = 0; i < 9; i++)
            if (mask & (1 << i))
                sum += i + 1;
        legalGroups[digitRoot(sum)].push_back(mask);
    }
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++)
            graph[i].clear();
        memset(canReach, false, sizeof(canReach));
        for (int i = 0; i < n; i++)
            canReach[i][i] = true;
        for (int i = 0; i < m; i++) {
            int u, v, d;
            cin >> u >> v >> d;
            --u;
            --v;
            graph[u].push_back({v, d, d == 0 ? -1 : i});
            canReach[u][v] = true;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (canReach[i][k] && canReach[k][j])
                        canReach[i][j] = true;
        bestCount = 0;
        answerMasks.clear();
        visited.clear();
        visited.reserve(1 << 20);
        array<int, 9> startPos;
        startPos.fill(0);
        dfs(0, startPos);
        vector<string> answers;
        for (int mask : answerMasks) {
            string answer;
            for (int i = 0; i < 9; i++)
                if (mask & (1 << i))
                    answer += char('1' + i);
            answers.push_back(answer);
        }
        sort(answers.begin(), answers.end());
        cout << bestCount;
        for (const string &answer : answers)
            cout << ' ' << answer;
        cout << '\n';
    }
    return 0;
}
