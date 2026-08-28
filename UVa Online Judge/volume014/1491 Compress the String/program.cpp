#include <bits/stdc++.h>
using namespace std;

const int maxN = 4;

int n, targetPos;
int limitLen[maxN], strLen[maxN], vis[maxN];
string targetStr;
char strRef[maxN][maxN], fillStr[maxN][maxN];

bool dfs2(int cur) {
    int sum = 0, i, index;
    for (i = strLen[cur] - 1; i >= 0; i--) {
        if (strRef[cur][i] == cur + '0') {
            if (targetPos < 0)
                return false;
            fillStr[cur][i] = targetStr[targetPos];
            targetPos--;
            sum++;
        } else {
            fillStr[cur][i] = strRef[cur][i];
            index = strRef[cur][i] - '0';
            if (vis[index] == 0) {
                if (!dfs2(index))
                    return false;
            } else {
                targetPos -= vis[index];
            }
            sum += vis[index];
            if (targetPos < -1)
                return false;
        }
    }
    vis[cur] = sum;
    return true;
}

bool checkResult() {
    string result;
    int i, j, index;
    memset(vis, 0, sizeof(vis));
    memset(fillStr, 0, sizeof(fillStr));
    targetPos = static_cast<int>(targetStr.size()) - 1;
    if (!dfs2(0))
        return false;
    if (targetPos != -1)
        return false;
    result = string(fillStr[0], fillStr[0] + strLen[0]);
    for (j = 0; j < n; j++) {
        for (i = static_cast<int>(result.size()) - 1; i >= 0; i--) {
            if (result[i] >= '0' && result[i] <= '9') {
                index = result[i] - '0';
                result.replace(i, 1, string(fillStr[index], fillStr[index] + strLen[index]));
            }
        }
    }
    return result == targetStr;
}

bool dfs(int cur, int len, int pos) {
    int i;
    if (cur == n)
        return checkResult();
    if (len != 0 && pos == len)
        return dfs(cur + 1, 0, 0);
    if (len == 0) {
        for (i = 1; i <= limitLen[cur]; i++) {
            strLen[cur] = i;
            if (dfs(cur, i, 0))
                return true;
        }
    } else {
        for (i = cur; i < n; i++) {
            strRef[cur][pos] = static_cast<char>(i + '0');
            if (dfs(cur, len, pos + 1))
                return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        int i;
        for (i = 0; i < n; i++)
            cin >> limitLen[i];
        cin >> targetStr;
        memset(strLen, 0, sizeof(strLen));
        memset(strRef, 0, sizeof(strRef));
        cout << (dfs(0, 0, 0) ? "Yes" : "No") << '\n';
    }
    return 0;
}
