#include <bits/stdc++.h>
using namespace std;

const int maxK = 20005;
int n, parentPos[maxK], parentKey[maxK];
long long target, keyVal[55], answer[55];

long long getGcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void solveCase() {
    long long allGcd = 0;
    for (int i = 0; i < n; i++)
        allGcd = getGcd(allGcd, keyVal[i]);
    if (target % allGcd != 0) {
        cout << "Stupid keypad!\n";
        return;
    }
    for (int i = 0; i < n; i++)
        answer[i] = 0;
    int base = static_cast<int>(keyVal[0]);
    long long startSum = 0;
    for (int i = 1; i < n; i++) {
        answer[i] = 1;
        startSum += keyVal[i];
    }
    int startPos = static_cast<int>((startSum % base + base) % base);
    for (int i = 0; i < base; i++) {
        parentPos[i] = -1;
        parentKey[i] = -1;
    }
    queue<int> que;
    parentPos[startPos] = startPos;
    que.push(startPos);
    while (!que.empty()) {
        int pos = que.front();
        que.pop();
        for (int i = 1; i < n; i++) {
            int nextPos = (pos + static_cast<int>(keyVal[i] % base)) % base;
            if (parentPos[nextPos] != -1)
                continue;
            parentPos[nextPos] = pos;
            parentKey[nextPos] = i;
            que.push(nextPos);
        }
    }
    long long targetPos = target % base;
    if (targetPos < 0)
        targetPos += base;
    if (parentPos[targetPos] == -1) {
        cout << "Stupid keypad!\n";
        return;
    }
    int cur = static_cast<int>(targetPos);
    while (cur != startPos) {
        int index = parentKey[cur];
        answer[index]++;
        cur = parentPos[cur];
    }
    long long sum = 0;
    for (int i = 1; i < n; i++)
        sum += answer[i] * keyVal[i];
    answer[0] = (target - sum) / keyVal[0];
    for (int i = 0; i < n; i++) {
        if (i != 0)
            cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 1;
    while (cin >> n >> target && (n != 0 || target != 0)) {
        for (int i = 0; i < n; i++)
            cin >> keyVal[i];
        cout << "Case #" << caseId++ << ": ";
        solveCase();
    }
    return 0;
}
