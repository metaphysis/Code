// Christmas Lights
// UVa ID: 13123
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.080s

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> segTree, lazyTag;
    const string *hexStr;
    int lightCount;

    int getBit(int pos) {
        int bitIndex = lightCount - pos;
        int charIndex = (int)hexStr->size() - 1 - bitIndex / 4;
        if (charIndex < 0) return 0;
        int value;
        char ch = (*hexStr)[charIndex];
        if (ch >= '0' && ch <= '9') value = ch - '0';
        else value = ch - 'A' + 10;
        return (value >> (bitIndex % 4)) & 1;
    }

    void buildTree(int node, int left, int right) {
        if (left == right) segTree[node] = getBit(left);
        else {
            int mid = (left + right) >> 1;
            int leftChild = node << 1, rightChild = leftChild | 1;
            buildTree(leftChild, left, mid);
            buildTree(rightChild, mid + 1, right);
            segTree[node] = segTree[leftChild] + segTree[rightChild];
        }
    }

    void pushDown(int node, int left, int right) {
        if (!lazyTag[node]) return;
        int mid = (left + right) >> 1;
        int leftChild = node << 1, rightChild = leftChild | 1;
        segTree[leftChild] = (mid - left + 1) - segTree[leftChild];
        segTree[rightChild] = (right - mid) - segTree[rightChild];
        lazyTag[leftChild] ^= 1;
        lazyTag[rightChild] ^= 1;
        lazyTag[node] = 0;
    }

    void reverseRange(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryLeft <= left && right <= queryRight) {
            segTree[node] = right - left + 1 - segTree[node];
            lazyTag[node] ^= 1;
            return;
        }
        pushDown(node, left, right);
        int mid = (left + right) >> 1;
        int leftChild = node << 1, rightChild = leftChild | 1;
        if (queryLeft <= mid) reverseRange(leftChild, left, mid, queryLeft, queryRight);
        if (queryRight > mid) reverseRange(rightChild, mid + 1, right, queryLeft, queryRight);
        segTree[node] = segTree[leftChild] + segTree[rightChild];
    }

    int findLastLight(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryRight < left || right < queryLeft || segTree[node] == 0) return 0;
        if (left == right) return left;
        pushDown(node, left, right);
        int mid = (left + right) >> 1;
        int leftChild = node << 1, rightChild = leftChild | 1;
        if (queryRight > mid) {
            int result = findLastLight(rightChild, mid + 1, right, queryLeft, queryRight);
            if (result) return result;
        }
        if (queryLeft <= mid) return findLastLight(leftChild, left, mid, queryLeft, queryRight);
        return 0;
    }

    int findFirstLight(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryRight < left || right < queryLeft || segTree[node] == 0) return 0;
        if (left == right) return left;
        pushDown(node, left, right);
        int mid = (left + right) >> 1;
        int leftChild = node << 1, rightChild = leftChild | 1;
        if (queryLeft <= mid) {
            int result = findFirstLight(leftChild, left, mid, queryLeft, queryRight);
            if (result) return result;
        }
        if (queryRight > mid) return findFirstLight(rightChild, mid + 1, right, queryLeft, queryRight);
        return 0;
    }

    void collectBits(int node, int left, int right, vector<int> &bits) {
        if (left == right) bits[left] = segTree[node];
        else {
            pushDown(node, left, right);
            int mid = (left + right) >> 1;
            int leftChild = node << 1, rightChild = leftChild | 1;
            collectBits(leftChild, left, mid, bits);
            collectBits(rightChild, mid + 1, right, bits);
        }
    }

public:
    SegmentTree(int count, const string &value) {
        lightCount = count;
        hexStr = &value;
        segTree.assign(count * 4 + 5, 0);
        lazyTag.assign(count * 4 + 5, 0);
        buildTree(1, 1, count);
    }

    void reverseRange(int left, int right) {
        reverseRange(1, 1, lightCount, left, right);
    }

    int findLastLight(int left, int right) {
        if (left > right) return 0;
        return findLastLight(1, 1, lightCount, left, right);
    }

    int findFirstLight(int left, int right) {
        if (left > right) return 0;
        return findFirstLight(1, 1, lightCount, left, right);
    }

    vector<int> getBits() {
        vector<int> bits(lightCount + 1);
        collectBits(1, 1, lightCount, bits);
        return bits;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int k, m;
        string hexStr;
        cin >> k >> m >> hexStr;
        SegmentTree tree(k, hexStr);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            int left = tree.findLastLight(1, a);
            int right = tree.findFirstLight(b, k);
            if (left == 0) left = a;
            if (right == 0) right = b;
            tree.reverseRange(left, right);
        }
        vector<int> bits = tree.getBits();
        string hexDigits = "0123456789ABCDEF";
        string answer;
        int digitCount = (k + 3) / 4, padding = digitCount * 4 - k;
        for (int i = 0; i < digitCount; i++) {
            int value = 0;
            for (int j = 0; j < 4; j++) {
                int pos = i * 4 + j - padding + 1;
                value <<= 1;
                if (pos >= 1) value |= bits[pos];
            }
            answer.push_back(hexDigits[value]);
        }
        size_t first = answer.find_first_not_of('0');
        if (first == string::npos) cout << "0\n";
        else cout << answer.substr(first) << '\n';
    }
    return 0;
}
