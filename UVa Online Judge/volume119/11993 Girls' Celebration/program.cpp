#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    static const int base = 1000000000;
    vector<int> num;
    BigInt(int val = 0) {
        if (val == 0) num.push_back(0);
        while (val > 0) {
            num.push_back(val % base);
            val /= base;
        }
    }
    void multiply(int val) {
        long long carry = 0;
        for (int &x : num) {
            long long cur = 1LL * x * val + carry;
            x = cur % base;
            carry = cur / base;
        }
        while (carry > 0) {
            num.push_back(carry % base);
            carry /= base;
        }
    }
    bool lessEqual(int val) const {
        if (num.size() > 1) return false;
        return num[0] <= val;
    }
    string toString() const {
        string res = to_string(num.back());
        for (int i = (int)num.size() - 2; i >= 0; i--) {
            string cur = to_string(num[i]);
            res += string(9 - cur.size(), '0') + cur;
        }
        return res;
    }
};

struct Node {
    int type, val;
    vector<int> ch;
    Node(int nodeType = 0, int nodeVal = 0) {
        type = nodeType;
        val = nodeVal;
    }
};

class PqTree {
private:
    vector<Node> nodes;
    int root, n;
    vector<vector<vector<int>>> wayMemo;
    vector<char> wayReady;
    pair<int, int> getStat(int id, const vector<char> &selected) {
        if (nodes[id].type == 0) return {selected[nodes[id].val], 1};
        int selectedCount = 0, totalCount = 0;
        for (int child : nodes[id].ch) {
            pair<int, int> stat = getStat(child, selected);
            selectedCount += stat.first;
            totalCount += stat.second;
        }
        return {selectedCount, totalCount};
    }
    int makeNode(int type, const vector<int> &children) {
        if (children.size() == 1) return children[0];
        Node node(type, 0);
        node.ch = children;
        nodes.push_back(node);
        return nodes.size() - 1;
    }
    int makeGroup(const vector<int> &children) {
        if (children.empty()) return -1;
        return makeNode(1, children);
    }
    vector<int> getUnits(int id) {
        if (nodes[id].type == 2) return nodes[id].ch;
        return {id};
    }
    int reduceP(const vector<int> &emptyCh, const vector<int> &fullCh, const vector<int> &partialCh, bool rootMode, bool &ok) {
        if (!rootMode) {
            if (partialCh.size() > 1) {
                ok = false;
                return -1;
            }
            vector<int> seq;
            int emptyGroup = makeGroup(emptyCh);
            int fullGroup = makeGroup(fullCh);
            if (emptyGroup != -1) seq.push_back(emptyGroup);
            if (!partialCh.empty()) {
                vector<int> units = getUnits(partialCh[0]);
                seq.insert(seq.end(), units.begin(), units.end());
            }
            if (fullGroup != -1) seq.push_back(fullGroup);
            return makeNode(2, seq);
        }
        if (partialCh.size() > 2) {
            ok = false;
            return -1;
        }
        if (partialCh.empty()) {
            vector<int> children = emptyCh;
            int fullGroup = makeGroup(fullCh);
            if (fullGroup != -1) children.push_back(fullGroup);
            return makeNode(1, children);
        }
        if (partialCh.size() == 1) {
            vector<int> seq = getUnits(partialCh[0]);
            int fullGroup = makeGroup(fullCh);
            if (fullGroup != -1) seq.push_back(fullGroup);
            int core = makeNode(2, seq);
            vector<int> children = emptyCh;
            children.push_back(core);
            return makeNode(1, children);
        }
        vector<int> seq = getUnits(partialCh[0]);
        int fullGroup = makeGroup(fullCh);
        if (fullGroup != -1) seq.push_back(fullGroup);
        vector<int> rightUnits = getUnits(partialCh[1]);
        reverse(rightUnits.begin(), rightUnits.end());
        seq.insert(seq.end(), rightUnits.begin(), rightUnits.end());
        int core = makeNode(2, seq);
        vector<int> children = emptyCh;
        children.push_back(core);
        return makeNode(1, children);
    }
    int reduceQ(const vector<int> &children, const vector<int> &state, bool rootMode, bool &ok) {
        int childCount = children.size();
        int left = childCount, right = -1, partialCount = 0, fullCount = 0;
        for (int i = 0; i < childCount; i++) {
            if (state[i] != 0) {
                left = min(left, i);
                right = max(right, i);
            }
            if (state[i] == 1) fullCount++;
            if (state[i] == 2) partialCount++;
        }
        for (int i = left; i <= right; i++) {
            if (state[i] == 0) {
                ok = false;
                return -1;
            }
        }
        if (partialCount > 2) {
            ok = false;
            return -1;
        }
        for (int i = left + 1; i < right; i++) {
            if (state[i] == 2) {
                ok = false;
                return -1;
            }
        }
        if (left < right && state[left] == 2 && state[right] == 2 && partialCount != 2) {
            ok = false;
            return -1;
        }
        if (left < right) {
            for (int i = left + 1; i < right; i++) {
                if (state[i] != 1) {
                    ok = false;
                    return -1;
                }
            }
        }
        if (!rootMode) {
            if (left == right && state[left] == 2) {
                if (left != 0 && left != childCount - 1) {
                    ok = false;
                    return -1;
                }
                vector<int> seq;
                for (int i = 0; i < childCount; i++) {
                    if (i != left) seq.push_back(children[i]);
                    else {
                        vector<int> units = getUnits(children[i]);
                        if (left == 0) reverse(units.begin(), units.end());
                        seq.insert(seq.end(), units.begin(), units.end());
                    }
                }
                if (left == 0) reverse(seq.begin(), seq.end());
                return makeNode(2, seq);
            }
            bool noLeftEmpty = left == 0 && state[left] == 1;
            bool noRightEmpty = right == childCount - 1 && state[right] == 1;
            if (!noLeftEmpty && !noRightEmpty) {
                ok = false;
                return -1;
            }
        }
        vector<int> seq;
        for (int i = 0; i < childCount; i++) {
            if (state[i] != 2) {
                seq.push_back(children[i]);
            } else {
                vector<int> units = getUnits(children[i]);
                if (i == right) reverse(units.begin(), units.end());
                seq.insert(seq.end(), units.begin(), units.end());
            }
        }
        if (!rootMode && left == 0 && state[left] == 1) reverse(seq.begin(), seq.end());
        return makeNode(2, seq);
    }
    int reduceNode(int id, const vector<char> &selected, bool rootMode, bool &ok) {
        if (!ok || nodes[id].type == 0) return id;
        vector<int> children = nodes[id].ch;
        vector<int> state(children.size()), emptyCh, fullCh, partialCh;
        int fullCount = 0, partialCount = 0, onlyPartial = -1;
        for (int i = 0; i < (int)children.size(); i++) {
            pair<int, int> stat = getStat(children[i], selected);
            if (stat.first == 0) state[i] = 0;
            else if (stat.first == stat.second) {
                state[i] = 1;
                fullCount++;
            } else {
                state[i] = 2;
                partialCount++;
                onlyPartial = i;
            }
        }
        if (rootMode && partialCount == 1 && fullCount == 0) {
            children[onlyPartial] = reduceNode(children[onlyPartial], selected, true, ok);
            if (ok) nodes[id].ch = children;
            return id;
        }
        for (int i = 0; i < (int)children.size(); i++) {
            if (state[i] == 2) children[i] = reduceNode(children[i], selected, false, ok);
            if (!ok) return -1;
        }
        for (int i = 0; i < (int)children.size(); i++) {
            if (state[i] == 0) emptyCh.push_back(children[i]);
            else if (state[i] == 1) fullCh.push_back(children[i]);
            else partialCh.push_back(children[i]);
        }
        if (nodes[id].type == 1) return reduceP(emptyCh, fullCh, partialCh, rootMode, ok);
        return reduceQ(children, state, rootMode, ok);
    }
    void collectFactors(int id, BigInt &answer) {
        if (nodes[id].type == 0) return;
        int childCount = nodes[id].ch.size();
        if (nodes[id].type == 1) {
            for (int i = 2; i <= childCount; i++) answer.multiply(i);
        } else if (childCount > 1) answer.multiply(2);
        for (int child : nodes[id].ch) collectFactors(child, answer);
    }
    vector<vector<int>> combineWays(const vector<vector<int>> &leftWays, const vector<vector<int>> &rightWays) {
        vector<vector<int>> result;
        for (const vector<int> &left : leftWays) {
            for (const vector<int> &right : rightWays) {
                vector<int> cur = left;
                cur.insert(cur.end(), right.begin(), right.end());
                result.push_back(cur);
            }
        }
        return result;
    }
    vector<vector<int>> getWays(int id) {
        if (wayReady[id]) return wayMemo[id];
        wayReady[id] = 1;
        if (nodes[id].type == 0) {
            wayMemo[id] = {{nodes[id].val}};
            return wayMemo[id];
        }
        vector<vector<int>> result;
        vector<int> order(nodes[id].ch.size());
        iota(order.begin(), order.end(), 0);
        if (nodes[id].type == 1) {
            do {
                vector<vector<int>> cur(1);
                for (int pos : order) cur = combineWays(cur, getWays(nodes[id].ch[pos]));
                result.insert(result.end(), cur.begin(), cur.end());
            } while (next_permutation(order.begin(), order.end()));
        } else {
            vector<vector<int>> cur(1);
            for (int pos : order) cur = combineWays(cur, getWays(nodes[id].ch[pos]));
            result.insert(result.end(), cur.begin(), cur.end());
            if (order.size() > 1) {
                reverse(order.begin(), order.end());
                cur.assign(1, {});
                for (int pos : order) cur = combineWays(cur, getWays(nodes[id].ch[pos]));
                result.insert(result.end(), cur.begin(), cur.end());
            }
        }
        wayMemo[id] = result;
        return wayMemo[id];
    }
public:
    PqTree(int girlCount = 0) {
        n = girlCount;
        vector<int> leaves;
        for (int i = 1; i <= n; i++) {
            nodes.push_back(Node(0, i));
            leaves.push_back(nodes.size() - 1);
        }
        root = makeNode(1, leaves);
    }
    bool addConstraint(const vector<char> &selected) {
        pair<int, int> stat = getStat(root, selected);
        if (stat.first == 0 || stat.first == stat.second) return true;
        vector<Node> backupNodes = nodes;
        int backupRoot = root;
        bool ok = true;
        root = reduceNode(root, selected, true, ok);
        if (!ok) {
            nodes = backupNodes;
            root = backupRoot;
            return false;
        }
        return true;
    }
    BigInt countWays() {
        BigInt answer(1);
        collectFactors(root, answer);
        return answer;
    }
    vector<vector<int>> enumerateWays() {
        wayMemo.assign(nodes.size(), {});
        wayReady.assign(nodes.size(), 0);
        vector<vector<int>> result = getWays(root);
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    while (cin >> n >> m >> k) {
        PqTree tree(n);
        for (int i = 0; i < m; i++) {
            vector<char> selected(n + 1, 0);
            int girl;
            while (cin >> girl && girl != 0) selected[girl] = 1;
            if (!tree.addConstraint(selected)) {
                cout << "0\n";
                continue;
            }
            BigInt answer = tree.countWays();
            cout << answer.toString() << '\n';
            if (answer.lessEqual(k)) {
                vector<vector<int>> ways = tree.enumerateWays();
                for (const vector<int> &way : ways) {
                    for (int j = 0; j < n; j++) {
                        if (j > 0) cout << ' ';
                        cout << way[j];
                    }
                    cout << '\n';
                }
            }
        }
    }
    return 0;
}
