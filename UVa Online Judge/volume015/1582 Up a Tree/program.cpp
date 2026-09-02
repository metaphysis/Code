#include <bits/stdc++.h>
using namespace std;

struct Key {
    int start[3], len, lab[3];
    bool operator < (const Key &other) const {
        for (int i = 0; i < 3; i++)
            if (start[i] != other.start[i])
                return start[i] < other.start[i];
        if (len != other.len)
            return len < other.len;
        for (int i = 0; i < 3; i++)
            if (lab[i] != other.lab[i])
                return lab[i] < other.lab[i];
        return false;
    }
};

struct Result {
    bool ok;
    string pre, in, post;
};

class Solver {
private:
    string obs[3];
    int calls[3][2];
    map<Key, Result> memo;

    int getRootOffset(int type, int leftSize, int len) {
        if (type == 0)
            return 0;
        if (type == 1)
            return leftSize;
        return len - 1;
    }

    int getChildOffset(int type, int side, int leftSize, int len) {
        if (type == 0)
            return side == 0 ? 1 : leftSize + 1;
        if (type == 1)
            return side == 0 ? 0 : leftSize + 1;
        return side == 0 ? 0 : leftSize;
    }

    int getMask(int start, int len, int index) {
        int mask = 0;
        for (int i = 0; i < len; i++)
            mask |= 1 << (obs[index][start + i] - 'A');
        return mask;
    }

    Result search(const Key &state) {
        map<Key, Result>::iterator it = memo.find(state);
        if (it != memo.end())
            return it->second;
        Result answer;
        answer.ok = false;
        answer.pre = answer.in = answer.post = "";
        if (state.len == 0) {
            answer.ok = true;
            memo[state] = answer;
            return answer;
        }
        for (int leftSize = 0; leftSize < state.len; leftSize++) {
            char root = 0;
            bool valid = true;
            for (int i = 0; i < 3; i++) {
                int offset = getRootOffset(state.lab[i], leftSize, state.len);
                char value = obs[i][state.start[i] + offset];
                if (root == 0)
                    root = value;
                else if (root != value)
                    valid = false;
            }
            if (!valid)
                continue;
            int firstMask = getMask(state.start[0], state.len, 0);
            if (firstMask != getMask(state.start[1], state.len, 1) || firstMask != getMask(state.start[2], state.len, 2))
                continue;
            Key left, right;
            left.len = leftSize;
            right.len = state.len - 1 - leftSize;
            for (int i = 0; i < 3; i++) {
                int type = state.lab[i];
                left.start[i] = state.start[i] + getChildOffset(type, 0, leftSize, state.len);
                right.start[i] = state.start[i] + getChildOffset(type, 1, leftSize, state.len);
                left.lab[i] = calls[type][0];
                right.lab[i] = calls[type][1];
            }
            Result leftResult = search(left);
            if (!leftResult.ok)
                continue;
            Result rightResult = search(right);
            if (!rightResult.ok)
                continue;
            Result current;
            current.ok = true;
            current.pre = root + leftResult.pre + rightResult.pre;
            current.in = leftResult.in + root + rightResult.in;
            current.post = leftResult.post + rightResult.post + root;
            if (!answer.ok || current.pre < answer.pre || current.pre == answer.pre && current.in < answer.in)
                answer = current;
        }
        memo[state] = answer;
        return answer;
    }

    void enumerate(int pos, int count[3], int order[6], vector<Result> &results, vector<string> &plans) {
        if (pos == 6) {
            Key root;
            root.len = obs[0].size();
            for (int i = 0; i < 3; i++) {
                root.start[i] = 0;
                root.lab[i] = i;
            }
            memo.clear();
            Result result = search(root);
            if (result.ok) {
                string plan;
                for (int i = 0; i < 6; i++) {
                    if (i > 0)
                        plan += " ";
                    plan += order[i] == 0 ? "Pre" : order[i] == 1 ? "In" : "Post";
                }
                plans.push_back(plan);
                results.push_back(result);
            }
            return;
        }
        for (int value = 0; value < 3; value++) {
            if (count[value] == 2)
                continue;
            count[value]++;
            order[pos] = value;
            if (pos < 2)
                calls[0][pos] = value;
            else if (pos < 4)
                calls[1][pos - 2] = value;
            else
                calls[2][pos - 4] = value;
            enumerate(pos + 1, count, order, results, plans);
            count[value]--;
        }
    }

public:
    void run() {
        while (cin >> obs[0] >> obs[1] >> obs[2]) {
            vector<Result> results;
            vector<string> plans;
            int count[3] = {0, 0, 0}, order[6];
            enumerate(0, count, order, results, plans);
            for (int i = 0; i < (int)plans.size(); i++) {
                cout << plans[i] << '\n';
                cout << results[i].pre << '\n';
                cout << results[i].in << '\n';
                cout << results[i].post << '\n';
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solver solver;
    solver.run();
    return 0;
}
