#include <bits/stdc++.h>
using namespace std;

int spf[201], fac[2][201], val[30][50], pos[30][50];
int valCnt, directCnt;
unordered_map<unsigned long long, int> memo;

unsigned long long nextSet(unsigned long long mask) {
    unsigned long long low = mask & -mask;
    unsigned long long rise = mask + low;
    unsigned long long newLow = rise & -rise;
    unsigned long long ones = ((newLow / low) >> 1) - 1;
    return rise | ones;
}

int calc(int dep, unsigned long long used, int minSize) {
    if (memo.count(used))
        return memo[used];
    int size = 0;
    for (int i = 0; i < valCnt; i++) {
        if ((used >> i) & 1)
            continue;
        val[dep + 1][size] = val[0][i];
        pos[dep + 1][size++] = i;
    }
    int res = max(0, size - 1);
    for (int take = minSize; take <= size / 2; take++) {
        int usedCnt = valCnt - size;
        int lowerRemain = 2 * (usedCnt / 3) + usedCnt % 3;
        int lowerCur = (take - 1) * (size / take) + size % take;
        if (lowerCur + lowerRemain + directCnt >= 20)
            break;
        if (res <= lowerCur)
            break;
        unsigned long long limit = 1ULL << size;
        for (unsigned long long mask = (1ULL << take) - 1; mask < limit; mask = nextSet(mask)) {
            unsigned long long cur = mask, nextUsed = used;
            int sum = 0;
            while (cur) {
                int id = __builtin_ctzll(cur);
                sum += val[dep + 1][id];
                nextUsed |= 1ULL << pos[dep + 1][id];
                cur -= cur & -cur;
            }
            if (sum == 0) {
                res = min(res, calc(dep + 1, nextUsed, take) + take - 1);
                if (res <= lowerCur)
                    break;
            }
        }
    }
    return memo[used] = res;
}

void initSpf() {
    memset(spf, 0, sizeof(spf));
    for (int i = 2; i <= 200; i++) {
        if (spf[i] != 0)
            continue;
        for (int j = i; j <= 200; j += i)
            spf[j] = i;
    }
}

void addFactor(int side, int num) {
    while (num > 1) {
        int p = spf[num];
        fac[side][p]++;
        num /= p;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initSpf();
    int testCnt;
    cin >> testCnt;
    for (int caseId = 1; caseId <= testCnt; caseId++) {
        memset(fac, 0, sizeof(fac));
        for (int side = 0; side < 2; side++) {
            int cnt;
            cin >> cnt;
            for (int i = 0; i < cnt; i++) {
                int num;
                cin >> num;
                addFactor(side, num);
            }
        }
        for (int p = 2; p <= 200; p++) {
            int same = min(fac[0][p], fac[1][p]);
            fac[0][p] -= same;
            fac[1][p] -= same;
        }
        directCnt = 0;
        for (int i = 2; i <= 200; i++) {
            if (fac[0][i] == 0)
                continue;
            for (int j = 2; j <= 200; j++) {
                if (fac[1][j] == 0)
                    continue;
                if (fac[0][i] == fac[1][j]) {
                    fac[0][i] = 0;
                    fac[1][j] = 0;
                    directCnt++;
                    break;
                }
            }
        }
        vector<int> left, right;
        int leftSum = 0, rightSum = 0;
        for (int p = 2; p <= 200; p++) {
            if (fac[0][p] > 0) {
                left.push_back(fac[0][p]);
                leftSum += fac[0][p];
            }
            if (fac[1][p] > 0) {
                right.push_back(fac[1][p]);
                rightSum += fac[1][p];
            }
        }
        sort(left.rbegin(), left.rend());
        sort(right.rbegin(), right.rend());
        valCnt = 0;
        for (int x : left)
            val[0][valCnt++] = x;
        for (int x : right)
            val[0][valCnt++] = -x;
        int ans = 20;
        memo.clear();
        if (leftSum == rightSum && valCnt < 40 - 2 * directCnt)
            ans = calc(0, 0, 3) + directCnt;
        if (ans >= 20)
            ans = -1;
        cout << "Case " << caseId << ": " << ans << '\n';
    }
    return 0;
}
