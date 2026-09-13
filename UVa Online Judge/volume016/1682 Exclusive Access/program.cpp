#include <bits/stdc++.h>
using namespace std;

struct Instruction {
    int type, var, value, next0, next1;
};

const int N = 700;

int m[2], nState, ncsPos[2], csPos[2], valueId[256];
int nxt[N][2], dfn[N], low[N], belong[N], stk[N], compSize[N], compLabel[N];
int topIndex, timeStamp, componentCount;
bool reach[N], valid[N], inStack[N], selfLoop[N];
Instruction code[2][10];

int encodeState(int p0, int p1, int mask) {
    return (((p0 - 1) * m[1] + (p1 - 1)) * 8 + mask);
}

void decodeState(int state, int &p0, int &p1, int &mask) {
    mask = state % 8;
    state /= 8;
    p1 = state % m[1] + 1;
    p0 = state / m[1] + 1;
}

int getNextState(int state, int who) {
    int p0, p1, mask, pos, nextPos;
    decodeState(state, p0, p1, mask);
    pos = who == 0 ? p0 : p1;
    Instruction &ins = code[who][pos];
    if (ins.type == 0 || ins.type == 3) {
        nextPos = ins.next0;
    } else if (ins.type == 1) {
        if (ins.value == 0) mask &= ~(1 << ins.var);
        else mask |= (1 << ins.var);
        nextPos = ins.next0;
    } else {
        if ((mask & (1 << ins.var)) == 0) nextPos = ins.next0;
        else nextPos = ins.next1;
    }
    if (who == 0) p0 = nextPos;
    else p1 = nextPos;
    return encodeState(p0, p1, mask);
}

void tarjan(int u, int edgeMask) {
    dfn[u] = low[u] = ++timeStamp;
    stk[++topIndex] = u;
    inStack[u] = true;
    for (int who = 0; who < 2; who++) {
        if ((edgeMask & (1 << who)) == 0) continue;
        int v = nxt[u][who];
        if (!valid[v]) continue;
        if (!dfn[v]) {
            tarjan(v, edgeMask);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        while (true) {
            int v = stk[topIndex--];
            inStack[v] = false;
            belong[v] = componentCount;
            if (v == u) break;
        }
        componentCount++;
    }
}

bool hasCycle(int edgeMask, int needMask) {
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(belong, -1, sizeof(belong));
    memset(inStack, false, sizeof(inStack));
    memset(compSize, 0, sizeof(compSize));
    memset(compLabel, 0, sizeof(compLabel));
    memset(selfLoop, false, sizeof(selfLoop));
    topIndex = timeStamp = componentCount = 0;
    for (int i = 0; i < nState; i++)
        if (valid[i] && !dfn[i]) tarjan(i, edgeMask);
    for (int i = 0; i < nState; i++) {
        if (!valid[i]) continue;
        compSize[belong[i]]++;
        for (int who = 0; who < 2; who++) {
            if ((edgeMask & (1 << who)) == 0) continue;
            int j = nxt[i][who];
            if (!valid[j] || belong[i] != belong[j]) continue;
            compLabel[belong[i]] |= (1 << who);
            if (i == j) selfLoop[belong[i]] = true;
        }
    }
    for (int i = 0; i < componentCount; i++)
        if ((compSize[i] > 1 || selfLoop[i]) && (compLabel[i] & needMask) == needMask) return true;
    return false;
}

bool checkDeadlockBad() {
    for (int state = 0; state < nState; state++) {
        int p0, p1, mask;
        decodeState(state, p0, p1, mask);
        valid[state] = reach[state] && p0 != csPos[0] && p1 != csPos[1];
    }
    if (hasCycle(3, 3)) return true;
    for (int stopped = 0; stopped < 2; stopped++) {
        for (int state = 0; state < nState; state++) {
            int p0, p1, mask, pos;
            decodeState(state, p0, p1, mask);
            pos = stopped == 0 ? p0 : p1;
            valid[state] = reach[state] && p0 != csPos[0] && p1 != csPos[1] && pos == ncsPos[stopped];
        }
        if (hasCycle(1 << (1 - stopped), 1 << (1 - stopped))) return true;
    }
    return false;
}

bool checkStarvationBad(int hungry) {
    int stopped = 1 - hungry;
    for (int state = 0; state < nState; state++) {
        int p0, p1, mask, pos;
        decodeState(state, p0, p1, mask);
        pos = hungry == 0 ? p0 : p1;
        valid[state] = reach[state] && pos != csPos[hungry];
    }
    if (hasCycle(3, 3)) return true;
    for (int state = 0; state < nState; state++) {
        int p0, p1, mask, posHungry, posStopped;
        decodeState(state, p0, p1, mask);
        posHungry = hungry == 0 ? p0 : p1;
        posStopped = stopped == 0 ? p0 : p1;
        valid[state] = reach[state] && posHungry != csPos[hungry] && posStopped == ncsPos[stopped];
    }
    return hasCycle(1 << hungry, 1 << hungry);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    valueId['A'] = 0;
    valueId['B'] = 1;
    valueId['C'] = 2;
    while (cin >> m[0] >> m[1]) {
        for (int who = 0; who < 2; who++) {
            for (int i = 1; i <= m[who]; i++) {
                int line;
                char var;
                string op;
                cin >> line >> op;
                if (op == "NCS") {
                    code[who][line] = {0, 0, 0, 0, 0};
                    cin >> code[who][line].next0;
                    ncsPos[who] = line;
                } else if (op == "CS") {
                    code[who][line] = {3, 0, 0, 0, 0};
                    cin >> code[who][line].next0;
                    csPos[who] = line;
                } else if (op == "SET") {
                    code[who][line] = {1, 0, 0, 0, 0};
                    cin >> var >> code[who][line].value >> code[who][line].next0;
                    code[who][line].var = valueId[(int)var];
                } else {
                    code[who][line] = {2, 0, 0, 0, 0};
                    cin >> var >> code[who][line].next0 >> code[who][line].next1;
                    code[who][line].var = valueId[(int)var];
                }
            }
        }
        nState = m[0] * m[1] * 8;
        for (int state = 0; state < nState; state++) {
            nxt[state][0] = getNextState(state, 0);
            nxt[state][1] = getNextState(state, 1);
        }
        memset(reach, false, sizeof(reach));
        queue<int> que;
        int start = encodeState(1, 1, 0);
        reach[start] = true;
        que.push(start);
        while (!que.empty()) {
            int state = que.front();
            que.pop();
            for (int who = 0; who < 2; who++) {
                int nextState = nxt[state][who];
                if (!reach[nextState]) {
                    reach[nextState] = true;
                    que.push(nextState);
                }
            }
        }
        bool mutual = true;
        for (int state = 0; state < nState; state++) {
            int p0, p1, mask;
            decodeState(state, p0, p1, mask);
            if (reach[state] && p0 == csPos[0] && p1 == csPos[1]) mutual = false;
        }
        bool deadlock = !checkDeadlockBad();
        bool starvation = !checkStarvationBad(0) && !checkStarvationBad(1);
        cout << (mutual ? 'Y' : 'N') << (deadlock ? 'Y' : 'N') << (starvation ? 'Y' : 'N') << '\n';
    }
    return 0;
}
