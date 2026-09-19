#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

string formatPercent(const cpp_int &value, const cpp_int &factor, int digits) {
    cpp_int scaled = value * factor;
    string result = scaled.convert_to<string>();
    if (digits > 0) {
        if (result.size() <= static_cast<size_t>(digits)) result.insert(0, digits + 1 - result.size(), '0');
        result.insert(result.size() - digits, 1, '.');
        while (result.back() == '0') result.pop_back();
        if (result.back() == '.') result.pop_back();
    }
    result += '%';
    return result;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> parentA(n + 1), parentB(n + 1), inDegree(n + 1), topoOrder;
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < k; ++i) {
        int child, firstParent, secondParent;
        cin >> child >> firstParent >> secondParent;
        parentA[child] = firstParent;
        parentB[child] = secondParent;
        inDegree[child] = 2;
        children[firstParent].push_back(child);
        children[secondParent].push_back(child);
    }
    queue<int> ready;
    for (int i = 1; i <= n; ++i) if (inDegree[i] == 0) ready.push(i);
    while (!ready.empty()) {
        int current = ready.front();
        ready.pop();
        topoOrder.push_back(current);
        for (int child : children[current]) {
            --inDegree[child];
            if (inDegree[child] == 0) ready.push(child);
        }
    }
    cpp_int scale = cpp_int(1) << k, factor = 100;
    for (int i = 0; i < k; ++i) factor *= 5;
    vector<vector<cpp_int>> relation(n + 1, vector<cpp_int>(n + 1));
    for (int i = 0; i < n; ++i) {
        int current = topoOrder[i];
        relation[current][current] = scale;
        if (parentA[current] == 0) continue;
        for (int j = 0; j < i; ++j) {
            int previous = topoOrder[j];
            relation[current][previous] = (relation[parentA[current]][previous] + relation[parentB[current]][previous]) / 2;
            relation[previous][current] = relation[current][previous];
        }
    }
    int queryCount;
    cin >> queryCount;
    while (queryCount--) {
        int first, second;
        cin >> first >> second;
        cout << formatPercent(relation[first][second], factor, k) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 0; caseId < testCount; ++caseId) {
        if (caseId > 0) cout << '\n';
        solve();
    }
    return 0;
}
