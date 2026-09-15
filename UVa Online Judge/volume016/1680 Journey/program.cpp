#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

struct Summary {
    bool inf, unbound;
    int rot;
    cpp_int dx, dy, mx[4];
};

struct Frame {
    int id;
    Summary pre;
};

struct Result {
    bool mark;
    int key;
    Summary sum;
};

vector<vector<string> > funcs;
vector<Summary> memo;
vector<bool> vis, active;
vector<Frame> callStack;

int signX[4] = {1, 1, -1, -1};
int signY[4] = {1, -1, 1, -1};
int dirX[4] = {1, 0, -1, 0};
int dirY[4] = {0, 1, 0, -1};

int normRot(int rot) {
    rot %= 4;
    if (rot < 0) rot += 4;
    return rot;
}

Summary emptySummary() {
    Summary res;
    res.inf = false;
    res.unbound = false;
    res.rot = 0;
    res.dx = 0;
    res.dy = 0;
    for (int i = 0; i < 4; i++) res.mx[i] = 0;
    return res;
}

int getProjectionIndex(int x, int y) {
    for (int i = 0; i < 4; i++)
        if (signX[i] == x && signY[i] == y) return i;
    return 0;
}

Summary appendSummary(const Summary &first, const Summary &second, int rot) {
    Summary res = first;
    rot = normRot(rot);
    cpp_int tx = second.dx, ty = second.dy;
    if (rot == 1) {
        tx = -second.dy;
        ty = second.dx;
    } else if (rot == 2) {
        tx = -second.dx;
        ty = -second.dy;
    } else if (rot == 3) {
        tx = second.dy;
        ty = -second.dx;
    }
    for (int i = 0; i < 4; i++) {
        int x = signX[i], y = signY[i], localX = x, localY = y;
        if (rot == 1) {
            localX = y;
            localY = -x;
        } else if (rot == 2) {
            localX = -x;
            localY = -y;
        } else if (rot == 3) {
            localX = -y;
            localY = x;
        }
        int index = getProjectionIndex(localX, localY);
        cpp_int value = x * first.dx + y * first.dy + second.mx[index];
        if (value > res.mx[i]) res.mx[i] = value;
    }
    res.dx = first.dx + tx;
    res.dy = first.dy + ty;
    res.rot = normRot(first.rot + second.rot);
    res.inf = first.inf || second.inf;
    res.unbound = first.unbound || second.unbound;
    return res;
}

void addGo(Summary &sum) {
    int rot = sum.rot;
    cpp_int nx = sum.dx + dirX[rot], ny = sum.dy + dirY[rot];
    for (int i = 0; i < 4; i++) {
        cpp_int value = signX[i] * nx + signY[i] * ny;
        if (value > sum.mx[i]) sum.mx[i] = value;
    }
    sum.dx = nx;
    sum.dy = ny;
}

Summary buildCycle(int id) {
    int start = 0;
    while (callStack[start].id != id) start++;
    Summary cycle = emptySummary();
    int rot = 0;
    for (int i = start; i < (int)callStack.size(); i++) {
        cycle = appendSummary(cycle, callStack[i].pre, rot);
        rot = normRot(rot + callStack[i].pre.rot);
    }
    return cycle;
}

Summary repeatCycle(const Summary &cycle) {
    int period = 1;
    while (normRot(cycle.rot * period) != 0) period++;
    Summary res = emptySummary();
    for (int i = 0; i < period; i++)
        res = appendSummary(res, cycle, normRot(cycle.rot * i));
    res.inf = true;
    res.unbound = res.dx != 0 || res.dy != 0;
    if (!res.unbound) {
        res.dx = 0;
        res.dy = 0;
        res.rot = 0;
    }
    return res;
}

Result evalFunc(int id) {
    if (vis[id]) return {false, -1, memo[id]};
    if (active[id]) return {true, id, buildCycle(id)};
    active[id] = true;
    callStack.push_back({id, emptySummary()});
    Summary pre = emptySummary();
    Result result;
    result.mark = false;
    result.key = -1;
    result.sum = emptySummary();
    for (const string &cmd : funcs[id]) {
        if (cmd == "GO") {
            addGo(pre);
            callStack.back().pre = pre;
        } else if (cmd == "LEFT") {
            pre.rot = normRot(pre.rot + 1);
            callStack.back().pre = pre;
        } else if (cmd == "RIGHT") {
            pre.rot = normRot(pre.rot + 3);
            callStack.back().pre = pre;
        } else {
            int nextId = stoi(cmd.substr(1));
            Result child = evalFunc(nextId);
            if (child.mark) {
                if (child.key == id) {
                    result.sum = repeatCycle(child.sum);
                    break;
                }
                callStack.pop_back();
                active[id] = false;
                return child;
            }
            pre = appendSummary(pre, child.sum, pre.rot);
            callStack.back().pre = pre;
            if (child.sum.inf) {
                result.sum = pre;
                break;
            }
        }
    }
    if (!result.sum.inf) result.sum = pre;
    memo[id] = result.sum;
    vis[id] = true;
    active[id] = false;
    callStack.pop_back();
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        funcs.assign(n + 1, vector<string>());
        memo.assign(n + 1, emptySummary());
        vis.assign(n + 1, false);
        active.assign(n + 1, false);
        callStack.clear();
        for (int i = 1; i <= n; i++) {
            int c;
            cin >> c;
            funcs[i].resize(c);
            for (int j = 0; j < c; j++) cin >> funcs[i][j];
        }
        Result ans = evalFunc(1);
        if (ans.sum.unbound) {
            cout << "Infinity\n";
        } else {
            cpp_int answer = 0;
            for (int i = 0; i < 4; i++)
                if (ans.sum.mx[i] > answer) answer = ans.sum.mx[i];
            cout << answer << '\n';
        }
    }
    return 0;
}
