#include <bits/stdc++.h>
using namespace std;

const long long infValue = 4000000000000000000LL;

struct FenwickTree {
    int size;
    vector<long long> tree;

    void init(const vector<long long> &value) {
        size = (int)value.size() - 1;
        tree.assign(size + 1, 0);
        for (int i = 1; i <= size; ++i) {
            tree[i] += value[i];
            int parent = i + (i & -i);
            if (parent <= size) tree[parent] += tree[i];
        }
    }

    void add(int pos, long long value) {
        while (pos <= size) {
            tree[pos] += value;
            pos += pos & -pos;
        }
    }

    long long sum(int pos) const {
        long long result = 0;
        while (pos > 0) {
            result += tree[pos];
            pos -= pos & -pos;
        }
        return result;
    }

    long long query(int left, int right) const {
        if (left > right) return 0;
        return sum(right) - sum(left - 1);
    }
};

struct SegmentTree {
    int size;
    vector<long long> leftTree, rightTree;

    void init(const vector<long long> &value) {
        int n = (int)value.size() - 1;
        size = 1;
        while (size < n) size <<= 1;
        leftTree.assign(size << 1, infValue);
        rightTree.assign(size << 1, infValue);
        for (int i = 1; i <= n; ++i) {
            leftTree[size + i - 1] = value[i] - i;
            rightTree[size + i - 1] = value[i] + i;
        }
        for (int i = size - 1; i > 0; --i) {
            leftTree[i] = min(leftTree[i << 1], leftTree[i << 1 | 1]);
            rightTree[i] = min(rightTree[i << 1], rightTree[i << 1 | 1]);
        }
    }

    void update(int pos, long long value) {
        int index = size + pos - 1;
        leftTree[index] = value - pos;
        rightTree[index] = value + pos;
        index >>= 1;
        while (index > 0) {
            leftTree[index] = min(leftTree[index << 1], leftTree[index << 1 | 1]);
            rightTree[index] = min(rightTree[index << 1], rightTree[index << 1 | 1]);
            index >>= 1;
        }
    }

    long long query(const vector<long long> &tree, int left, int right) const {
        if (left > right) return infValue;
        int l = size + left - 1, r = size + right - 1;
        long long result = infValue;
        while (l <= r) {
            if (l & 1) result = min(result, tree[l++]);
            if (!(r & 1)) result = min(result, tree[r--]);
            l >>= 1;
            r >>= 1;
        }
        return result;
    }

    long long queryLeft(int left, int right) const {
        return query(leftTree, left, right);
    }

    long long queryRight(int left, int right) const {
        return query(rightTree, left, right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> value(n + 1);
        for (int i = 1; i <= n; ++i) cin >> value[i];
        FenwickTree sumTree;
        SegmentTree minTree;
        sumTree.init(value);
        minTree.init(value);
        int q;
        cin >> q;
        while (q--) {
            int queryType, pos, virusType;
            long long newValue;
            cin >> queryType >> pos >> newValue;
            if (queryType == 1) {
                sumTree.add(pos, newValue - value[pos]);
                value[pos] = newValue;
                minTree.update(pos, newValue);
            } else {
                virusType = (int)newValue;
                long long height = value[pos];
                height = min(height, minTree.queryLeft(1, pos - 1) + pos);
                height = min(height, minTree.queryRight(pos + 1, n) - pos);
                long long left, right, infected, total;
                if (virusType == 1) {
                    height = min(height, (long long)pos);
                    height = min(height, (long long)(n - pos + 1));
                    left = pos - height + 1;
                    right = pos + height - 1;
                    infected = height * height;
                } else {
                    left = max(1LL, pos - height + 1);
                    right = min((long long)n, pos + height - 1);
                    long long leftCount = pos - left, rightCount = right - pos;
                    long long infectedLeft = leftCount * height - leftCount * (leftCount + 1) / 2;
                    long long infectedRight = rightCount * height - rightCount * (rightCount + 1) / 2;
                    infected = height + infectedLeft + infectedRight;
                }
                total = sumTree.query((int)left, (int)right);
                cout << height << ' ' << total - infected << '\n';
            }
        }
    }
    return 0;
}
