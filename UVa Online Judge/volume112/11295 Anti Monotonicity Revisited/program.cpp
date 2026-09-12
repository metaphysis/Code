#include <bits/stdc++.h>
using namespace std;

const int mod = 10000007;

struct Node {
    int len, cnt;
};

Node mergeNode(Node a, Node b) {
    if (a.len > b.len)
        return a;
    if (a.len < b.len)
        return b;
    if (a.len == 0)
        return {0, 0};
    return {a.len, (a.cnt + b.cnt) % mod};
}

struct FenwickTree {
    int size;
    vector<Node> tree;

    FenwickTree(int n) : size(n), tree(n + 1, {0, 0}) {
    }

    void update(int pos, Node value) {
        while (pos <= size) {
            tree[pos] = mergeNode(tree[pos], value);
            pos += pos & -pos;
        }
    }

    Node query(int pos) {
        Node result = {0, 0};
        while (pos > 0) {
            result = mergeNode(result, tree[pos]);
            pos -= pos & -pos;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> arr[i];
        if (n == 0) {
            cout << "0 1 0\n";
            continue;
        }
        FenwickTree lowTree(n), highTree(n);
        int ansLen = 0, ansCnt = 0;
        for (int i = 1; i <= n; i++) {
            int value = arr[i], revValue = n - value + 1;
            Node high = {1, 1}, low = {0, 0};
            Node lowPrev = lowTree.query(value - 1);
            if (lowPrev.len > 0)
                high = mergeNode(high, {lowPrev.len + 1, lowPrev.cnt});
            Node highPrev = highTree.query(n - value);
            if (highPrev.len > 0)
                low = {highPrev.len + 1, highPrev.cnt};
            highTree.update(revValue, high);
            if (low.len > 0)
                lowTree.update(value, low);
            Node current = mergeNode(high, low);
            if (current.len > ansLen) {
                ansLen = current.len;
                ansCnt = current.cnt;
            } else if (current.len == ansLen) {
                ansCnt = (ansCnt + current.cnt) % mod;
            }
        }
        int meanLen = (4 * n + 4) / 6;
        cout << ansLen << ' ' << ansCnt % mod << ' ' << meanLen << '\n';
    }
    return 0;
}
