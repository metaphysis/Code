#include <bits/stdc++.h>
using namespace std;

const int maxN = 1005;
const int maxM = 3005;

int regCnt, insCnt;
int leftReg[maxM], rightReg[maxM];
bool normalState[maxN], faultState[maxN];
bool nextNormal[maxN], nextFault[maxN];

int solve() {
    cin >> regCnt >> insCnt;
    for (int i = 1; i <= insCnt; i++)
        cin >> leftReg[i] >> rightReg[i];
    for (int i = 1; i <= regCnt; i++)
        normalState[i] = true, faultState[i] = false;
    for (int i = 1; i <= insCnt; i++) {
        memset(nextNormal, false, sizeof(nextNormal));
        memset(nextFault, false, sizeof(nextFault));
        for (int j = 1; j <= regCnt; j++) {
            if (normalState[j]) {
                if (j == rightReg[i])
                    nextNormal[leftReg[i]] = true;
                else
                    nextNormal[j] = true;
                nextFault[j] = true;
            }
            if (faultState[j]) {
                if (j == rightReg[i])
                    nextFault[leftReg[i]] = true;
                else
                    nextFault[j] = true;
            }
        }
        for (int j = 1; j <= regCnt; j++)
            normalState[j] = nextNormal[j], faultState[j] = nextFault[j];
    }
    int ans = 0;
    for (int i = 2; i <= regCnt; i++) {
        if (normalState[i])
            ans += 2;
        else if (faultState[i])
            ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCnt;
    cin >> caseCnt;
    for (int caseId = 1; caseId <= caseCnt; caseId++) {
        if (caseId > 1)
            cout << '\n';
        cout << solve() << '\n';
    }
    return 0;
}
