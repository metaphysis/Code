#include <bits/stdc++.h>
using namespace std;

int rotateRight(int value, int bitCount) {
    return (value >> 1) | ((value & 1) << (bitCount - 1));
}

vector<string> routeNetwork(int level, const vector<int> &mapping) {
    int size = 1 << level;
    if (level == 1)
        return vector<string>(1, string(1, mapping[0] == 0 ? '0' : '1'));
    int half = size >> 1;
    vector<int> inverseMapping(size), color(size, -1);
    vector<vector<int>> graph(size);
    for (int i = 0; i < size; i++)
        inverseMapping[mapping[i]] = i;
    for (int i = 0; i < size; i++) {
        int next = inverseMapping[mapping[i] ^ 1];
        graph[i].push_back(i ^ 1);
        graph[i ^ 1].push_back(i);
        graph[i].push_back(next);
        graph[next].push_back(i);
    }
    for (int start = 0; start < size; start += 2) {
        if (color[start] != -1)
            continue;
        color[start] = 0;
        queue<int> que;
        que.push(start);
        while (!que.empty()) {
            int current = que.front();
            que.pop();
            for (int next : graph[current]) {
                if (color[next] == -1) {
                    color[next] = color[current] ^ 1;
                    que.push(next);
                }
            }
        }
    }
    string firstRow(half, '0'), lastRow(half, '0');
    for (int i = 0; i < half; i++) {
        firstRow[i] = char('0' + color[i << 1]);
        lastRow[i] = char('0' + color[inverseMapping[i << 1]]);
    }
    vector<int> leftMapping(half), rightMapping(half);
    for (int i = 0; i < size; i++) {
        int inputPort = rotateRight(i, level);
        int outputPort = rotateRight(mapping[i], level);
        int side = color[i];
        int localInput = inputPort & (half - 1);
        int localOutput = outputPort & (half - 1);
        if (side == 0)
            leftMapping[localInput] = localOutput;
        else
            rightMapping[localInput] = localOutput;
    }
    vector<string> leftRows = routeNetwork(level - 1, leftMapping);
    vector<string> rightRows = routeNetwork(level - 1, rightMapping);
    vector<string> result;
    result.push_back(firstRow);
    for (int i = 0; i < (int)leftRows.size(); i++)
        result.push_back(leftRows[i] + rightRows[i]);
    result.push_back(lastRow);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int level;
    bool firstCase = true;
    while (cin >> level && level != 0) {
        int size = 1 << level;
        vector<int> permutation(size), inversePermutation(size);
        for (int i = 0; i < size; i++)
            cin >> permutation[i];
        for (int i = 0; i < size; i++)
            inversePermutation[permutation[i]] = i;
        vector<string> answer = routeNetwork(level, inversePermutation);
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        for (const string &row : answer)
            cout << row << '\n';
    }
    return 0;
}
