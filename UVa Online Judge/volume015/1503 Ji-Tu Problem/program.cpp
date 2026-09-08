#include <bits/stdc++.h>
using namespace std;

int countTwo(int q, int sum, int &leg1, int &num1, int &leg2, int &num2) {
    int ways = 0;
    for (int low = 0; low * q <= sum && ways < 2; low++) {
        int rest = sum - low * q;
        if (rest == 0)
            continue;
        for (int d = 1; d * d <= rest && ways < 2; d++) {
            if (rest % d != 0)
                continue;
            int divs[2] = {d, rest / d};
            for (int j = 0; j < 2 && ways < 2; j++) {
                if (j == 1 && divs[0] == divs[1])
                    continue;
                int gap = divs[j], highNum = rest / gap;
                if (highNum <= 0 || highNum >= q)
                    continue;
                ways++;
                if (ways == 1) {
                    leg1 = low;
                    num1 = q - highNum;
                    leg2 = low + gap;
                    num2 = highNum;
                }
            }
        }
    }
    return ways;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    for (int caseId = 1; caseId <= testCase; caseId++) {
        int n, k;
        cin >> n >> k;
        int a[1005], d[1005], cnt[1005], ansLeg[1005], ansNum[1005];
        for (int i = 0; i <= k; i++)
            cin >> a[i];
        bool valid = true;
        for (int i = 1; i <= k; i++) {
            d[i] = a[i - 1] - a[i];
            if (d[i] < 0)
                valid = false;
        }
        for (int i = 1; i < k; i++) {
            cnt[i] = d[i] - d[i + 1];
            if (cnt[i] < 0)
                valid = false;
        }
        int knownKinds = 0;
        for (int i = 1; i < k; i++)
            if (cnt[i] > 0)
                knownKinds++;
        int q = d[k], r = n - knownKinds, status = 0;
        int tailLeg[1005], tailNum[1005], tailCnt = 0;
        if (valid && r >= 0) {
            if (r == 0) {
                if (q == 0 && a[k] == 0)
                    status = 1;
            } else if (q >= r) {
                if (r == 1) {
                    if (a[k] % q == 0) {
                        status = 1;
                        tailLeg[tailCnt] = k + a[k] / q;
                        tailNum[tailCnt++] = q;
                    }
                } else if (r == 2) {
                    int leg1, num1, leg2, num2;
                    int ways = countTwo(q, a[k], leg1, num1, leg2, num2);
                    if (ways == 1) {
                        status = 1;
                        tailLeg[tailCnt] = k + leg1;
                        tailNum[tailCnt++] = num1;
                        tailLeg[tailCnt] = k + leg2;
                        tailNum[tailCnt++] = num2;
                    } else if (ways > 1) {
                        status = 2;
                    }
                } else {
                    long long minSum = 1LL * r * (r - 1) / 2;
                    if (a[k] < minSum) {
                        status = 0;
                    } else if (q == r) {
                        if (a[k] == minSum || a[k] == minSum + 1) {
                            status = 1;
                            if (a[k] == minSum) {
                                for (int i = 0; i < r; i++) {
                                    tailLeg[tailCnt] = k + i;
                                    tailNum[tailCnt++] = 1;
                                }
                            } else {
                                for (int i = 0; i < r - 1; i++) {
                                    tailLeg[tailCnt] = k + i;
                                    tailNum[tailCnt++] = 1;
                                }
                                tailLeg[tailCnt] = k + r;
                                tailNum[tailCnt++] = 1;
                            }
                        } else {
                            status = 2;
                        }
                    } else {
                        if (a[k] == minSum) {
                            status = 1;
                            for (int i = 0; i < r; i++) {
                                tailLeg[tailCnt] = k + i;
                                tailNum[tailCnt++] = i == 0 ? q - r + 1 : 1;
                            }
                        } else {
                            status = 2;
                        }
                    }
                }
            }
        }
        cout << "Case #" << caseId << ":\n";
        if (status == 0) {
            cout << "No Solution\n";
        } else if (status == 2) {
            cout << "Multiple Solutions\n";
        } else {
            cout << "Unique Solution\n";
            int ansCnt = 0;
            for (int i = 1; i < k; i++) {
                if (cnt[i] > 0) {
                    ansLeg[ansCnt] = i;
                    ansNum[ansCnt++] = cnt[i];
                }
            }
            for (int i = 0; i < tailCnt; i++) {
                ansLeg[ansCnt] = tailLeg[i];
                ansNum[ansCnt++] = tailNum[i];
            }
            for (int i = 0; i < ansCnt; i++)
                cout << ansLeg[i] << ' ' << ansNum[i] << '\n';
        }
    }
    return 0;
}
