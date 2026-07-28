// File Retrieval
// UVa ID: 12361
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.320s
// https://blog.csdn.net/metaphysis/article/details/163259554

#include <bits/stdc++.h>
using namespace std;

vector<array<int, 26>> nextState;
vector<int> linkArr, lenArr;
vector<unsigned long long> fileMask;
int stateCount;

int insertState(int last, int c) {
    if (nextState[last][c]) {
        int p = last, q = nextState[p][c];
        if (lenArr[p] + 1 == lenArr[q]) return q;
        int clone = ++stateCount;
        lenArr.push_back(lenArr[p] + 1);
        nextState.push_back(nextState[q]);
        linkArr.push_back(linkArr[q]);
        fileMask.push_back(0);
        while (p != -1 && nextState[p][c] == q) {
            nextState[p][c] = clone;
            p = linkArr[p];
        }
        linkArr[q] = clone;
        return clone;
    }
    int cur = ++stateCount;
    lenArr.push_back(lenArr[last] + 1);
    nextState.push_back({});
    linkArr.push_back(0);
    fileMask.push_back(0);
    int p = last;
    while (p != -1 && !nextState[p][c]) {
        nextState[p][c] = cur;
        p = linkArr[p];
    }
    if (p == -1) linkArr[cur] = 0;
    else {
        int q = nextState[p][c];
        if (lenArr[p] + 1 == lenArr[q]) linkArr[cur] = q;
        else {
            int clone = ++stateCount;
            lenArr.push_back(lenArr[p] + 1);
            nextState.push_back(nextState[q]);
            linkArr.push_back(linkArr[q]);
            fileMask.push_back(0);
            while (p != -1 && nextState[p][c] == q) {
                nextState[p][c] = clone;
                p = linkArr[p];
            }
            linkArr[q] = linkArr[cur] = clone;
        }
    }
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int F;
    while (cin >> F && F) {
        stateCount = 0;
        nextState.clear();
        linkArr.clear();
        lenArr.clear();
        fileMask.clear();
        nextState.push_back({});
        linkArr.push_back(-1);
        lenArr.push_back(0);
        fileMask.push_back(0);
        for (int i = 0; i < F; ++i) {
            string s;
            cin >> s;
            int last = 0;
            for (char ch : s) {
                last = insertState(last, ch - 'a');
                fileMask[last] |= (1ULL << i);
            }
        }
        vector<int> order(stateCount + 1);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return lenArr[a] > lenArr[b];
        });
        for (int v : order) {
            if (v == 0) continue;
            int p = linkArr[v];
            if (p != -1) fileMask[p] |= fileMask[v];
        }
        vector<unsigned long long> masks;
        for (int v = 1; v <= stateCount; ++v) {
            if (fileMask[v] != 0) masks.push_back(fileMask[v]);
        }
        sort(masks.begin(), masks.end());
        masks.erase(unique(masks.begin(), masks.end()), masks.end());
        cout << masks.size() << '\n';
    }
    return 0;
}
