#include <bits/stdc++.h>
using namespace std;

const int maxN = 28;
const int maxType = 14;
const long long inf = 1000000000000000000LL;

int primeVal[6] = {2, 3, 5, 7, 11, 13};
int typeOf[maxN + 1], repVal[maxType + 1];
int baseVal[maxType + 1], typeCount;
int initCount[maxType + 1], curCount[maxType + 1];
bool okAdj[maxType + 1][maxType + 1];
vector<long long> dp;

int gcdVal(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int getMask(int x) {
    int mask = 0;
    for (int i = 0; i < 6; i++)
        if (x % primeVal[i] == 0)
            mask |= 1 << i;
    return mask;
}

int getStateId(const int *count) {
    int id = 0;
    for (int i = 1; i <= typeCount; i++)
        id = id * baseVal[i] + count[i];
    return id;
}

long long countPerm(int remaining, int last) {
    if (remaining == 0) return 1;
    int id = getStateId(curCount);
    long long &res = dp[id * (maxType + 1) + last];
    if (res != -1) return res;
    res = 0;
    for (int i = 1; i <= typeCount; i++) {
        if (curCount[i] == 0 || !okAdj[last][i]) continue;
        int cnt = curCount[i];
        curCount[i]--;
        long long ways = countPerm(remaining - 1, i);
        curCount[i]++;
        if (ways > inf / cnt) {
            res = inf;
            break;
        }
        long long add = ways * cnt;
        if (res > inf - add) {
            res = inf;
            break;
        }
        res += add;
    }
    return res;
}

void buildType() {
    int maskType[64];
    for (int i = 0; i < 64; i++) maskType[i] = 0;
    typeCount = 0;
    for (int x = 1; x <= maxN; x++) {
        int mask = getMask(x);
        if (maskType[mask] == 0) {
            typeCount++;
            maskType[mask] = typeCount;
            repVal[typeCount] = x;
        }
        typeOf[x] = maskType[mask];
        initCount[typeOf[x]]++;
    }
}

void buildGraph() {
    for (int i = 0; i <= typeCount; i++)
        for (int j = 0; j <= typeCount; j++)
            okAdj[i][j] = false;
    for (int i = 0; i <= typeCount; i++) {
        okAdj[0][i] = true;
        okAdj[i][0] = true;
    }
    for (int i = 1; i <= typeCount; i++)
        for (int j = 1; j <= typeCount; j++) {
            if (i == j)
                okAdj[i][j] = (i == typeOf[1]);
            else
                okAdj[i][j] = (gcdVal(repVal[i], repVal[j]) == 1);
        }
}

void buildDp() {
    long long stateCount = 1;
    for (int i = 1; i <= typeCount; i++) {
        baseVal[i] = initCount[i] + 1;
        stateCount *= baseVal[i];
    }
    dp.assign(stateCount * (maxType + 1), -1);
}

void solveCase(int caseId, int n, long long k) {
    memset(curCount, 0, sizeof(curCount));
    for (int x = 1; x <= n; x++)
        curCount[typeOf[x]]++;
    long long total = countPerm(n, 0);
    cout << "Case " << caseId << ":";
    if (total < k) {
        cout << " -1\n";
        return;
    }
    bool used[maxN + 1] = {false};
    int last = 0;
    for (int pos = 1; pos <= n; pos++) {
        bool placed = false;
        for (int x = 1; x <= n; x++) {
            if (used[x] || (last != 0 && !okAdj[typeOf[last]][typeOf[x]])) continue;
            int type = typeOf[x];
            curCount[type]--;
            long long ways = countPerm(n - pos, type);
            if (k <= ways) {
                cout << " " << x;
                used[x] = true;
                last = x;
                placed = true;
                break;
            }
            k -= ways;
            curCount[type]++;
        }
        if (!placed) {
            cout << " -1\n";
            return;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    buildType();
    buildGraph();
    buildDp();
    int t;
    cin >> t;
    for (int caseId = 1; caseId <= t; caseId++) {
        int n;
        long long k;
        cin >> n >> k;
        solveCase(caseId, n, k);
    }
    return 0;
}
