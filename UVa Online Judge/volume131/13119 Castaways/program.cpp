#include <bits/stdc++.h>
using namespace std;

unsigned short triArea[257][257][257];
int cnt[257];
vector<int> pairVals, squareVals;

int getArea(int a, int b, int c) {
    long long val = 1LL * (a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c);
    long long root = sqrtl(val);
    while ((root + 1) * (root + 1) <= val) root++;
    while (root * root > val) root--;
    return root / 4;
}

void initArea() {
    int a, b, c;
    for (a = 1; a <= 256; a++) {
        for (b = a; b <= 256; b++) {
            for (c = b; c < a + b && c <= 256; c++)
                triArea[a][b][c] = getArea(a, b, c);
        }
    }
}

long long getRect(int a, int b, int c) {
    int x = 0, y = 0, left;
    long long ans = 0;
    for (int val : pairVals) {
        left = cnt[val] - (val == a) - (val == b) - (val == c);
        if (left >= 2) {
            if (!x) x = val;
            else {
                y = val;
                break;
            }
        }
    }
    if (x && y) ans = 1LL * x * y;
    for (int val : squareVals) {
        left = cnt[val] - (val == a) - (val == b) - (val == c);
        if (left >= 4) ans = max(ans, 1LL * val * val);
    }
    return ans;
}

void buildVals() {
    int val;
    pairVals.clear();
    squareVals.clear();
    for (val = 256; val >= 1; val--) {
        if (cnt[val] >= 2 && pairVals.size() < 5) pairVals.push_back(val);
        if (cnt[val] >= 4 && squareVals.size() < 5) squareVals.push_back(val);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initArea();
    int n, val, a, b, c, maxVal, needA, needB, needC;
    while (cin >> n) {
        memset(cnt, 0, sizeof(cnt));
        maxVal = 0;
        for (int i = 0; i < n; i++) {
            cin >> val;
            cnt[val]++;
            maxVal = max(maxVal, val);
        }
        buildVals();
        long long ans = getRect(0, 0, 0);
        for (a = 1; a <= maxVal; a++) {
            if (!cnt[a]) continue;
            for (b = a; b <= maxVal; b++) {
                needA = 1;
                needB = 1;
                if (a == b) needA++;
                if (cnt[a] < needA || cnt[b] < needB) continue;
                for (c = b; c < a + b && c <= maxVal; c++) {
                    needA = 1;
                    needB = 1;
                    needC = 1;
                    if (a == b) needA++;
                    if (a == c) needA++;
                    if (b == c) needB++;
                    if (cnt[a] < needA || cnt[b] < needB || cnt[c] < needC) continue;
                    ans = max(ans, 1LL * triArea[a][b][c] + getRect(a, b, c));
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
