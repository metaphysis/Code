#include <bits/stdc++.h>
using namespace std;

struct VectorHash {
    size_t operator()(const vector<int>& values) const {
        size_t hashValue = values.size();
        for (int value : values) hashValue ^= hash<int>{}(value) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        return hashValue;
    }
};

unordered_set<vector<int>, VectorHash> visited;

bool sameSign(int first, int second) {
    return (first > 0) == (second > 0);
}

pair<int, int> makeEdge(int first, int second) {
    first = abs(first);
    second = abs(second);
    if (first > second) swap(first, second);
    return {first, second};
}

bool canMoveTwo(const vector<int>& code, int firstPos, int secondPos) {
    pair<int, int> firstEdge = makeEdge(code[firstPos], code[firstPos + 1]);
    pair<int, int> secondEdge = makeEdge(code[secondPos], code[secondPos + 1]);
    if (firstEdge.first == firstEdge.second) return false;
    if (firstEdge != secondEdge) return false;
    if (!sameSign(code[firstPos], code[firstPos + 1])) return false;
    if (!sameSign(code[secondPos], code[secondPos + 1])) return false;
    return true;
}

bool canMoveThree(const vector<int>& code, int firstPos, int secondPos, int thirdPos) {
    array<pair<int, int>, 3> edges = {
        makeEdge(code[firstPos], code[firstPos + 1]),
        makeEdge(code[secondPos], code[secondPos + 1]),
        makeEdge(code[thirdPos], code[thirdPos + 1])
    };
    for (const pair<int, int>& edge : edges)
        if (edge.first == edge.second) return false;
    sort(edges.begin(), edges.end());
    if (edges[0] == edges[1] || edges[1] == edges[2]) return false;
    array<int, 6> ids = {
        edges[0].first, edges[0].second,
        edges[1].first, edges[1].second,
        edges[2].first, edges[2].second
    };
    sort(ids.begin(), ids.end());
    int distinctCount = 1;
    for (int i = 1; i < 6; i++)
        if (ids[i] != ids[i - 1]) distinctCount++;
    if (distinctCount != 3) return false;
    int sameCount = 0;
    if (sameSign(code[firstPos], code[firstPos + 1])) sameCount++;
    if (sameSign(code[secondPos], code[secondPos + 1])) sameCount++;
    if (sameSign(code[thirdPos], code[thirdPos + 1])) sameCount++;
    return sameCount == 2;
}

bool canUntie(const vector<int>& code) {
    if (code.empty()) return true;
    if (!visited.insert(code).second) return false;
    int size = code.size();
    for (int i = 0; i + 1 < size; i++) {
        if (abs(code[i]) == abs(code[i + 1])) {
            vector<int> nextCode = code;
            nextCode.erase(nextCode.begin() + i, nextCode.begin() + i + 2);
            if (canUntie(nextCode)) return true;
        }
    }
    for (int i = 0; i + 1 < size; i++) {
        for (int j = i + 2; j + 1 < size; j++) {
            if (!canMoveTwo(code, i, j)) continue;
            vector<int> nextCode = code;
            nextCode.erase(nextCode.begin() + j, nextCode.begin() + j + 2);
            nextCode.erase(nextCode.begin() + i, nextCode.begin() + i + 2);
            if (canUntie(nextCode)) return true;
        }
    }
    for (int i = 0; i + 1 < size; i++) {
        for (int j = i + 2; j + 1 < size; j++) {
            for (int k = j + 2; k + 1 < size; k++) {
                if (!canMoveThree(code, i, j, k)) continue;
                vector<int> nextCode = code;
                swap(nextCode[i], nextCode[i + 1]);
                swap(nextCode[j], nextCode[j + 1]);
                swap(nextCode[k], nextCode[k + 1]);
                if (canUntie(nextCode)) return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        vector<int> code;
        int value;
        while (cin >> value && value != 0) code.push_back(value);
        visited.clear();
        bool untied = canUntie(code);
        cout << "Case " << caseNumber << ": " << (untied ? "No" : "Yes") << '\n';
    }
    return 0;
}
