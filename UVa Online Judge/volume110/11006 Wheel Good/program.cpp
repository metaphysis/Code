// Wheel Good
// UVa ID: 11006
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;

bool comparePair(const P &a, const P &b) {
    return a.first * (long long)b.second > a.second * (long long)b.first;
}

int main() {
    int N;
    while (scanf("%d", &N) == 1 && N != 0) {
        int sumX = 0, sumY = 0;
        vector<P> vec;
        for (int sLen = 1; sumX + sumY + sLen <= N; sLen++) {
            for (int aVal = 1; aVal < sLen; aVal++) {
                int bVal = sLen - aVal;
                if (__gcd(aVal, bVal) != 1) continue;
                vec.push_back(P(aVal, bVal));
                sumX += aVal;
                sumY += bVal;
                if (sumX + sumY + sLen > N) break;
            }
        }
        sort(vec.begin(), vec.end(), comparePair);
        if (sumX + sumY < N) {
            vec.insert(vec.begin(), P(N - sumX - sumY, 0));
            sumX += N - sumX - sumY;
        }
        int curX = sumY, curY = 0;
        printf("(%d,%d)\n", curX, curY);
        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < (int)vec.size(); i++) {
                int dx = vec[i].first, dy = vec[i].second;
                for (int j = 0; j < k; j++) {
                    swap(dx, dy);
                    dx = -dx;
                }
                curX += dx;
                curY += dy;
                if (k == 3 && i == (int)vec.size() - 1) continue;
                printf("(%d,%d)\n", curX, curY);
                assert(0 <= curX && curX <= N);
                assert(0 <= curY && curY <= N);
            }
        }
        printf("\n");
    }
    return 0;
}
