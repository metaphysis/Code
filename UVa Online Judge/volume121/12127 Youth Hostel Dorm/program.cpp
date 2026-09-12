#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cost, rowMask;
    unsigned long long pre;
};

int h, w;

int bitCount(int x) {
    return __builtin_popcount((unsigned)x);
}

int findRoot(int parent[20], int x) {
    return parent[x] == x ? x : parent[x] = findRoot(parent, parent[x]);
}

void unite(int parent[20], int a, int b) {
    a = findRoot(parent, a);
    b = findRoot(parent, b);
    if (a != b)
        parent[b] = a;
}

void normalize(int lab[8]) {
    int trans[20] = {}, nextLabel = 0;
    for (int c = 0; c < w; c++)
        if (lab[c]) {
            if (!trans[lab[c]])
                trans[lab[c]] = ++nextLabel;
            lab[c] = trans[lab[c]];
        }
}

unsigned long long encodeState(int mask, int dom, const int lab[8], int closed, int boundary) {
    unsigned long long code = mask | ((unsigned long long)dom << 8);
    for (int c = 0; c < w; c++)
        code |= (unsigned long long)lab[c] << (16 + 4 * c);
    code |= (unsigned long long)closed << 48;
    code |= (unsigned long long)boundary << 49;
    return code;
}

void decodeState(unsigned long long code, int &mask, int &dom, int lab[8], int &closed, int &boundary) {
    mask = code & 255;
    dom = (code >> 8) & 255;
    for (int c = 0; c < w; c++)
        lab[c] = (code >> (16 + 4 * c)) & 15;
    closed = (code >> 48) & 1;
    boundary = (code >> 49) & 1;
}

void updateState(unordered_map<unsigned long long, Node> &mp, unsigned long long code, int cost, int rowMask, unsigned long long pre) {
    auto it = mp.find(code);
    if (it == mp.end() || cost < it->second.cost)
        mp[code] = {cost, rowMask, pre};
}

vector<string> solveGrid(int height, int width) {
    h = height;
    w = width;
    vector<unordered_map<unsigned long long, Node> > history(h);
    for (int mask = 0; mask < (1 << w); mask++) {
        int lab[8] = {}, dom = mask, nextLabel = 0;
        for (int c = 0; c < w; c++)
            if (mask & (1 << c)) {
                if (c == 0 || !(mask & (1 << (c - 1))))
                    nextLabel++;
                lab[c] = nextLabel;
                if (c > 0)
                    dom |= 1 << (c - 1);
                if (c + 1 < w)
                    dom |= 1 << (c + 1);
            }
        int boundary = (mask & 1) || (mask & (1 << (w - 1))) || mask;
        unsigned long long code = encodeState(mask, dom, lab, 0, boundary);
        updateState(history[0], code, bitCount(mask), mask, 0);
    }
    for (int r = 0; r + 1 < h; r++) {
        for (auto &item : history[r]) {
            int oldMask, oldDom, oldLab[8], closed, boundary;
            decodeState(item.first, oldMask, oldDom, oldLab, closed, boundary);
            for (int nextMask = 0; nextMask < (1 << w); nextMask++) {
                if (closed && nextMask)
                    continue;
                if ((oldDom | nextMask) != (1 << w) - 1)
                    continue;
                int oldCount = 0;
                for (int c = 0; c < w; c++)
                    oldCount = max(oldCount, oldLab[c]);
                bool attached[20] = {};
                for (int c = 0; c < w; c++)
                    if ((oldMask & (1 << c)) && (nextMask & (1 << c)))
                        attached[oldLab[c]] = true;
                bool disappeared = false;
                for (int id = 1; id <= oldCount; id++)
                    if (!attached[id])
                        disappeared = true;
                if (disappeared && (oldCount != 1 || nextMask || closed))
                    continue;
                int nextLab[8] = {}, nextCount = 0;
                for (int c = 0; c < w; c++)
                    if (nextMask & (1 << c)) {
                        if (c == 0 || !(nextMask & (1 << (c - 1))))
                            nextCount++;
                        nextLab[c] = nextCount;
                    }
                int parent[20];
                for (int i = 0; i < 20; i++)
                    parent[i] = i;
                for (int c = 0; c < w; c++)
                    if ((oldMask & (1 << c)) && (nextMask & (1 << c)))
                        unite(parent, oldLab[c], oldCount + nextLab[c]);
                int lab[8] = {};
                for (int c = 0; c < w; c++)
                    if (nextMask & (1 << c))
                        lab[c] = findRoot(parent, oldCount + nextLab[c]);
                normalize(lab);
                int nextDom = nextMask | oldMask;
                nextDom |= (nextMask << 1) | (nextMask >> 1);
                nextDom &= (1 << w) - 1;
                int nextClosed = closed || disappeared;
                int nextBoundary = boundary || (r + 1 == h - 1 && nextMask) || (nextMask & 1) || (nextMask & (1 << (w - 1)));
                unsigned long long code = encodeState(nextMask, nextDom, lab, nextClosed, nextBoundary);
                updateState(history[r + 1], code, item.second.cost + bitCount(nextMask), nextMask, item.first);
            }
        }
    }
    int bestCost = INT_MAX;
    unsigned long long bestCode = 0;
    for (auto &item : history[h - 1]) {
        int mask, dom, lab[8], closed, boundary;
        decodeState(item.first, mask, dom, lab, closed, boundary);
        if (dom != (1 << w) - 1 || !boundary)
            continue;
        int count = 0;
        for (int c = 0; c < w; c++)
            count = max(count, lab[c]);
        if (closed ? mask != 0 : count != 1)
            continue;
        if (item.second.cost < bestCost) {
            bestCost = item.second.cost;
            bestCode = item.first;
        }
    }
    vector<int> rowMasks(h, 0);
    for (int r = h - 1; r >= 0; r--) {
        Node node = history[r][bestCode];
        rowMasks[r] = node.rowMask;
        bestCode = node.pre;
    }
    vector<string> ans(h, string(w, 'B'));
    int entranceR = -1, entranceC = -1;
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++)
            if (rowMasks[r] & (1 << c)) {
                ans[r][c] = '.';
                if (entranceR == -1 && (r == 0 || r == h - 1 || c == 0 || c == w - 1)) {
                    entranceR = r;
                    entranceC = c;
                }
            }
    ans[entranceR][entranceC] = 'E';
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    map<pair<int, int>, vector<string> > cache;
    int t;
    cin >> t;
    while (t--) {
        int l, width;
        cin >> l >> width;
        bool transposed = l < width;
        int height = max(l, width), smallWidth = min(l, width);
        pair<int, int> key = {height, smallWidth};
        if (!cache.count(key))
            cache[key] = solveGrid(height, smallWidth);
        vector<string> result(l, string(width, 'B'));
        for (int r = 0; r < l; r++)
            for (int c = 0; c < width; c++)
                result[r][c] = transposed ? cache[key][c][r] : cache[key][r][c];
        for (int r = 0; r < l; r++)
            cout << result[r] << '\n';
    }
    return 0;
}
