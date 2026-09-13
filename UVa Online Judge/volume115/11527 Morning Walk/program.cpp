#include <bits/stdc++.h>
using namespace std;

unordered_map<int, vector<array<int, 3>>> ansCache;

bool isSquare(long long value) {
    long long root = sqrtl((long double)value);
    while (root * root < value) ++root;
    while (root * root > value) --root;
    return root * root == value;
}

vector<array<int, 3>> getAnswer(int sum) {
    vector<array<int, 3>> answer;
    int minB, maxB, a, b, c;
    long long value;
    for (a = 1; a * 3 <= sum; ++a) {
        minB = max(a, (sum - 2 * a) / 2 + 1);
        maxB = (sum - a) / 2;
        for (b = minB; b <= maxB; ++b) {
            c = sum - a - b;
            value = 1LL * sum * (sum - 2LL * a) * (sum - 2LL * b) * (2LL * a + 2LL * b - sum);
            if (!isSquare(value)) continue;
            answer.push_back({a, b, c});
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> query;
    int sum, caseId = 1;
    while (cin >> sum && sum != 0)
        query.push_back(sum);
    for (int value : query)
        if (ansCache.find(value) == ansCache.end())
            ansCache[value] = getAnswer(value);
    for (int value : query) {
        cout << "Case " << caseId++ << ":\n";
        const vector<array<int, 3>> &answer = ansCache[value];
        if (answer.empty()) {
            cout << "Peter has Forgotten Everything\n";
            continue;
        }
        for (const array<int, 3> &item : answer)
            cout << item[0] << ' ' << item[1] << ' ' << item[2] << '\n';
    }
    return 0;
}
