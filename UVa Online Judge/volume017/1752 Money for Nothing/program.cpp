// Money for Nothing
// UVa ID: 1752
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.220s

#include <bits/stdc++.h>
using namespace std;

struct Producer {
    long long price, day;
};

struct Consumer {
    long long price, endDay;
};

vector<Producer> producers;
vector<Consumer> consumers;
long long answer;

int getLow(long long price) {
    int left = 0, right = (int)consumers.size();
    while (left < right) {
        int mid = (left + right) >> 1;
        if (consumers[mid].price <= price) left = mid + 1;
        else right = mid;
    }
    return left;
}

int getHigh(long long day) {
    int left = 0, right = (int)consumers.size();
    while (left < right) {
        int mid = (left + right) >> 1;
        if (consumers[mid].endDay > day) left = mid + 1;
        else right = mid;
    }
    return left - 1;
}

void calc(int left, int right, int optLeft, int optRight) {
    if (left > right) return;
    int mid = (left + right) >> 1;
    int low = getLow(producers[mid].price), high = getHigh(producers[mid].day);
    int begin = max(optLeft, low), end = min(optRight, high), best = -1;
    long long bestValue = 0;
    for (int i = begin; i <= end; i++) {
        long long value = (consumers[i].price - producers[mid].price) * (consumers[i].endDay - producers[mid].day);
        if (best == -1 || value > bestValue) {
            best = i;
            bestValue = value;
        }
    }
    if (best == -1) {
        calc(left, mid - 1, optLeft, optRight);
        calc(mid + 1, right, optLeft, optRight);
        return;
    }
    answer = max(answer, bestValue);
    calc(left, mid - 1, optLeft, best);
    calc(mid + 1, right, best, optRight);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    while (cin >> m >> n) {
        vector<Producer> rawProducers(m);
        vector<Consumer> rawConsumers(n);
        for (int i = 0; i < m; i++) cin >> rawProducers[i].price >> rawProducers[i].day;
        for (int i = 0; i < n; i++) cin >> rawConsumers[i].price >> rawConsumers[i].endDay;
        sort(rawProducers.begin(), rawProducers.end(), [](const Producer &a, const Producer &b) {
            if (a.price != b.price) return a.price < b.price;
            return a.day < b.day;
        });
        sort(rawConsumers.begin(), rawConsumers.end(), [](const Consumer &a, const Consumer &b) {
            if (a.price != b.price) return a.price < b.price;
            return a.endDay > b.endDay;
        });
        producers.clear();
        consumers.clear();
        for (int i = 0; i < m; i++) {
            if (!producers.empty() && producers.back().price == rawProducers[i].price) continue;
            producers.push_back(rawProducers[i]);
        }
        vector<Producer> goodProducers;
        long long minDay = LLONG_MAX;
        for (int i = 0; i < (int)producers.size(); i++) {
            if (producers[i].day < minDay) {
                goodProducers.push_back(producers[i]);
                minDay = producers[i].day;
            }
        }
        producers.swap(goodProducers);
        vector<Consumer> uniqueConsumers;
        for (int i = 0; i < n; i++) {
            if (!uniqueConsumers.empty() && uniqueConsumers.back().price == rawConsumers[i].price) continue;
            uniqueConsumers.push_back(rawConsumers[i]);
        }
        long long maxDay = -1;
        vector<Consumer> goodConsumers;
        for (int i = (int)uniqueConsumers.size() - 1; i >= 0; i--) {
            if (uniqueConsumers[i].endDay > maxDay) {
                goodConsumers.push_back(uniqueConsumers[i]);
                maxDay = uniqueConsumers[i].endDay;
            }
        }
        reverse(goodConsumers.begin(), goodConsumers.end());
        consumers.swap(goodConsumers);
        answer = 0;
        if (!producers.empty() && !consumers.empty()) calc(0, (int)producers.size() - 1, 0, (int)consumers.size() - 1);
        cout << answer << '\n';
    }
    return 0;
}
