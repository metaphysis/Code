#include <bits/stdc++.h>
using namespace std;

bool check(long long time, long long need, long long floorCnt, const vector<long long>& first) {
    long long cnt = 0, period = 2 * floorCnt;
    for (long long x : first) {
        if (time >= x) cnt += (time - x) / period + 1;
        if (cnt >= need) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    while (testCnt--) {
        long long personCnt, floorCnt, boxCnt;
        cin >> personCnt >> floorCnt >> boxCnt;
        vector<long long> first(personCnt);
        for (int i = 0; i < personCnt; i++) {
            long long floor, hasBox;
            cin >> floor >> hasBox;
            if (hasBox == 0) first[i] = floor;
            else first[i] = 2 * floorCnt - floor;
        }
        long long left = 0, right = 2 * floorCnt * boxCnt;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (check(mid, boxCnt, floorCnt, first)) right = mid;
            else left = mid + 1;
        }
        cout << left + floorCnt << '\n';
    }
    return 0;
}
