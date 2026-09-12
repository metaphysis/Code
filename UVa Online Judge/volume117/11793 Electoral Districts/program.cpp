#include <bits/stdc++.h>
using namespace std;

struct District {
    int mask, value;
};

int n, cellCount, fullMask;
vector<int> diffValue;
vector<vector<District>> options;
vector<signed char> memo;

bool isConnected(int mask) {
    int start = __builtin_ctz(mask), seen = 0, count = 0;
    queue<int> que;
    que.push(start);
    seen |= 1 << start;
    while (!que.empty()) {
        int pos = que.front();
        que.pop();
        count++;
        int row = pos / n, col = pos % n;
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        for (int dir = 0; dir < 4; dir++) {
            int nextRow = row + dr[dir], nextCol = col + dc[dir];
            if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n) continue;
            int nextPos = nextRow * n + nextCol, bit = 1 << nextPos;
            if ((mask & bit) == 0 || (seen & bit) != 0) continue;
            seen |= bit;
            que.push(nextPos);
        }
    }
    return count == n;
}

void generateDistricts(int start, int chosen, int mask, int sum) {
    if (chosen == n) {
        if (!isConnected(mask)) return;
        int value = sum > 0 ? 1 : (sum < 0 ? -1 : 0);
        for (int pos = 0; pos < cellCount; pos++)
            if (mask & (1 << pos))
                options[pos].push_back({mask, value});
        return;
    }
    if (cellCount - start < n - chosen) return;
    for (int pos = start; pos <= cellCount - (n - chosen); pos++)
        generateDistricts(pos + 1, chosen + 1, mask | (1 << pos), sum + diffValue[pos]);
}

int searchAnswer(int usedMask) {
    if (usedMask == fullMask) return 0;
    signed char &cached = memo[usedMask];
    if (cached != -2) return cached;
    int first = __builtin_ctz(fullMask ^ usedMask), best = -100;
    for (const District &district : options[first]) {
        if ((usedMask & district.mask) != 0) continue;
        int current = district.value + searchAnswer(usedMask | district.mask);
        best = max(best, current);
    }
    cached = static_cast<signed char>(best);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> n;
        cellCount = n * n;
        fullMask = (1 << cellCount) - 1;
        diffValue.assign(cellCount, 0);
        options.assign(cellCount, vector<District>());
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++)
                cin >> diffValue[row * n + col];
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++) {
                int votes;
                cin >> votes;
                diffValue[row * n + col] -= votes;
            }
        generateDistricts(0, 0, 0, 0);
        memo.assign(1 << cellCount, static_cast<signed char>(-2));
        cout << searchAnswer(0) << '\n';
    }
    return 0;
}
