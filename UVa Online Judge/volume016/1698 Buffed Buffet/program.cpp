#include <bits/stdc++.h>
using namespace std;

const long long negInf = LLONG_MIN / 4;

struct Dish {
    int taste, decay;
};

long long lineValue(int idx, int x, int decay, const vector<long long> &intercept) {
    return intercept[idx] + 1LL * decay * idx * x;
}

bool isRedundant(int first, int second, int third, const vector<long long> &intercept) {
    return (intercept[first] - intercept[second]) * (third - second) >= (intercept[second] - intercept[third]) * (second - first);
}

void addDiscrete(vector<long long> &dp, int itemW, int taste, int decay) {
    int maxW = static_cast<int>(dp.size()) - 1;
    if (itemW > maxW) return;
    if (decay == 0) {
        for (int curW = itemW; curW <= maxW; ++curW) if (dp[curW - itemW] != negInf) dp[curW] = max(dp[curW], dp[curW - itemW] + taste);
        return;
    }
    vector<long long> nextDp(maxW + 1, negInf), intercept(maxW + 1);
    vector<int> hull(maxW + 1);
    for (int rem = 0; rem < itemW; ++rem) {
        int head = 0, tail = 0;
        for (int k = 0, curW = rem; curW <= maxW; ++k, curW += itemW) {
            if (dp[curW] != negInf) {
                intercept[k] = dp[curW] - 1LL * k * taste - 1LL * decay * k * (k + 1) / 2;
                while (tail - head >= 2 && isRedundant(hull[tail - 2], hull[tail - 1], k, intercept)) --tail;
                hull[tail++] = k;
            }
            if (head == tail) continue;
            while (tail - head >= 2 && lineValue(hull[head], k, decay, intercept) <= lineValue(hull[head + 1], k, decay, intercept)) ++head;
            nextDp[curW] = 1LL * k * taste - 1LL * decay * k * (k - 1) / 2 + lineValue(hull[head], k, decay, intercept);
        }
    }
    dp.swap(nextDp);
}

vector<long double> buildContinuous(const vector<Dish> &cont, int maxW) {
    int flatTaste = -1, pos = 0;
    vector<Dish> falling;
    vector<long double> best(maxW + 1, 0.0L);
    long double sumInv = 0.0L, sumTaste = 0.0L, sumSquare = 0.0L;
    for (const Dish &dish : cont) {
        if (dish.decay == 0) flatTaste = max(flatTaste, dish.taste);
        else falling.push_back(dish);
    }
    sort(falling.begin(), falling.end(), [](const Dish &left, const Dish &right) {
        return left.taste > right.taste;
    });
    for (int weight = 1; weight <= maxW; ++weight) {
        while (pos < static_cast<int>(falling.size()) && falling[pos].taste > flatTaste && (sumInv == 0.0L || sumTaste - sumInv * falling[pos].taste < weight)) {
            long double inv = 1.0L / falling[pos].decay, taste = falling[pos].taste;
            sumInv += inv;
            sumTaste += taste * inv;
            sumSquare += taste * taste * inv;
            ++pos;
        }
        if (sumInv == 0.0L) {
            best[weight] = 1.0L * weight * flatTaste;
            continue;
        }
        long double level = (sumTaste - weight) / sumInv;
        if (flatTaste >= 0 && level < flatTaste) {
            level = flatTaste;
            best[weight] = (sumSquare - sumInv * level * level) / 2.0L + level * (weight - (sumTaste - sumInv * level));
        } else {
            best[weight] = (sumSquare - sumInv * level * level) / 2.0L;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int dishCount, maxW;
    cout << fixed << setprecision(9);
    while (cin >> dishCount >> maxW) {
        vector<long long> dp(maxW + 1, negInf);
        vector<Dish> cont;
        dp[0] = 0;
        for (int i = 0; i < dishCount; ++i) {
            char type;
            int itemW, taste, decay;
            cin >> type;
            if (type == 'D') {
                cin >> itemW >> taste >> decay;
                addDiscrete(dp, itemW, taste, decay);
            } else {
                cin >> taste >> decay;
                cont.push_back({taste, decay});
            }
        }
        if (cont.empty()) {
            if (dp[maxW] == negInf) cout << "impossible\n";
            else cout << static_cast<long double>(dp[maxW]) << '\n';
            continue;
        }
        vector<long double> best = buildContinuous(cont, maxW);
        long double answer = best[maxW];
        for (int weight = 0; weight <= maxW; ++weight) if (dp[weight] != negInf) answer = max(answer, static_cast<long double>(dp[weight]) + best[maxW - weight]);
        cout << answer << '\n';
    }
    return 0;
}
