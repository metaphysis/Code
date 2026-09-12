// A Problemsetter Blind with Emotion
// UVa ID: 11801
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.130s


#include <bits/stdc++.h>
using namespace std;

struct Topic {
    long long x, a, b, c, d;
};

long long calcTopic(long long need, const Topic &topic) {
    long long ans = LLONG_MAX;
    if (topic.b <= topic.d) {
        long long limit = need / topic.b;
        for (long long r = 0; r < topic.d; r++) {
            if (r > limit) continue;
            long long rest = max(0LL, need - r * topic.b);
            long long article = (rest + topic.d - 1) / topic.d;
            ans = min(ans, r * topic.a + article * topic.c);
            long long book = limit - (limit - r) % topic.d;
            rest = max(0LL, need - book * topic.b);
            article = (rest + topic.d - 1) / topic.d;
            ans = min(ans, book * topic.a + article * topic.c);
        }
        long long book = (need + topic.b - 1) / topic.b;
        ans = min(ans, book * topic.a);
    } else {
        long long limit = need / topic.d;
        for (long long r = 0; r < topic.b; r++) {
            if (r > limit) continue;
            long long rest = max(0LL, need - r * topic.d);
            long long book = (rest + topic.b - 1) / topic.b;
            ans = min(ans, r * topic.c + book * topic.a);
            long long article = limit - (limit - r) % topic.b;
            rest = max(0LL, need - article * topic.d);
            book = (rest + topic.b - 1) / topic.b;
            ans = min(ans, article * topic.c + book * topic.a);
        }
        long long article = (need + topic.d - 1) / topic.d;
        ans = min(ans, article * topic.c);
    }
    return ans;
}

bool check(long long people, long long maxTime, const vector<Topic> &topics) {
    long long total = 0;
    for (const Topic &topic : topics) {
        long long need = topic.x * people;
        total += calcTopic(need, topic);
        if (total > maxTime) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase, n;
    long long m;
    cin >> testCase;
    for (int caseId = 1; caseId <= testCase; caseId++) {
        cin >> n >> m;
        vector<Topic> topics(n);
        long long sumX = 0;
        for (Topic &topic : topics) {
            cin >> topic.x >> topic.a >> topic.b >> topic.c >> topic.d;
            sumX += topic.x;
        }
        long long low = 0, high = m / sumX;
        while (low < high) {
            long long mid = (low + high + 1) / 2;
            if (check(mid, m, topics)) low = mid;
            else high = mid - 1;
        }
        cout << "Case " << caseId << ": " << low << '\n';
    }
    return 0;
}
