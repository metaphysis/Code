#include <bits/stdc++.h>
using namespace std;

const long double Eps = 1e-18L;
const long double Limit = 1e12L;

long double checkRatio(int g, long double ratio, const vector<array<long double, 3>> &prob) {
    int offset = g + 1;
    vector<long double> cur(2 * g + 3), nxt(2 * g + 3);
    for (int diff = -g; diff <= g; diff++) {
        if (diff > 0)
            cur[diff + offset] = 1.0L;
        else if (diff == 0)
            cur[diff + offset] = 0.0L;
        else
            cur[diff + offset] = -ratio;
    }
    for (int game = g - 1; game >= 0; game--) {
        for (int diff = -game; diff <= game; diff++) {
            long double rockWin = prob[game][2], rockLose = prob[game][1], rockDraw = prob[game][0];
            long double paperWin = prob[game][0], paperLose = prob[game][2], paperDraw = prob[game][1];
            long double scissorsWin = prob[game][1], scissorsLose = prob[game][0], scissorsDraw = prob[game][2];
            long double rockValue = rockWin * cur[diff + 1 + offset] + rockDraw * cur[diff + offset] + rockLose * cur[diff - 1 + offset];
            long double paperValue = paperWin * cur[diff + 1 + offset] + paperDraw * cur[diff + offset] + paperLose * cur[diff - 1 + offset];
            long double scissorsValue = scissorsWin * cur[diff + 1 + offset] + scissorsDraw * cur[diff + offset] + scissorsLose * cur[diff - 1 + offset];
            nxt[diff + offset] = max(rockValue, max(paperValue, scissorsValue));
        }
        cur.swap(nxt);
    }
    return cur[offset];
}

long double calcAnswer(long double ratio, int w, int l) {
    if (ratio < Eps)
        return 0.0L;
    if (fabsl(ratio - 1.0L) < Eps)
        return (long double)l / (w + l);
    if (ratio > 1.0L) {
        long double inv = 1.0L / ratio;
        return (1.0L - powl(inv, l)) / (1.0L - powl(inv, w + l));
    }
    return powl(ratio, w) * (1.0L - powl(ratio, l)) / (1.0L - powl(ratio, w + l));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int g, w, l;
    while (cin >> g >> w >> l) {
        if (g == 0 && w == 0 && l == 0)
            break;
        vector<array<long double, 3>> prob(g);
        for (int game = 0; game < g; game++) {
            int rock, paper, scissors;
            cin >> rock >> paper >> scissors;
            prob[game][0] = rock / 100.0L;
            prob[game][1] = paper / 100.0L;
            prob[game][2] = scissors / 100.0L;
        }
        long double low = 0.0L, high = 1.0L;
        while (checkRatio(g, high, prob) > 0.0L) {
            low = high;
            if (high >= Limit)
                break;
            high *= 2.0L;
        }
        long double answer;
        if (high >= Limit && checkRatio(g, high, prob) > 0.0L)
            answer = 1.0L;
        else {
            for (int step = 0; step < 55; step++) {
                long double mid = (low + high) / 2.0L;
                if (checkRatio(g, mid, prob) > 0.0L)
                    low = mid;
                else
                    high = mid;
            }
            answer = calcAnswer(low, w, l);
        }
        if (answer < 0.0L)
            answer = 0.0L;
        if (answer > 1.0L)
            answer = 1.0L;
        cout << fixed << setprecision(3) << answer * 100.0L << "%\n";
    }
    return 0;
}
