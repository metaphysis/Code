#include <bits/stdc++.h>
using namespace std;

struct RackState {
    int pos[3], outEight, outSolid, outStripe;
};

int encodeState(const RackState &state) {
    int code = state.pos[0];
    code = code * 4 + state.pos[1];
    code = code * 4 + state.pos[2];
    code = code * 2 + state.outEight;
    code = code * 8 + state.outSolid;
    code = code * 8 + state.outStripe;
    return code;
}

RackState decodeState(int code) {
    RackState state;
    state.outStripe = code % 8;
    code /= 8;
    state.outSolid = code % 8;
    code /= 8;
    state.outEight = code % 2;
    code /= 2;
    state.pos[2] = code % 4;
    code /= 4;
    state.pos[1] = code % 4;
    code /= 4;
    state.pos[0] = code % 4;
    return state;
}

int getType(int ball) {
    if (ball == 0)
        return 0;
    if (ball == 8)
        return 1;
    if (ball <= 7)
        return 2;
    return 3;
}

long long solveCase(int swapCost, int addCost, int removeCost, const vector<int> &balls) {
    const int stateCount = 4 * 4 * 4 * 2 * 8 * 8;
    const int totalCount[4] = {0, 1, 7, 7};
    const int specialIndex[3] = {10, 4, 14};
    RackState start;
    start.pos[0] = getType(balls[10]);
    start.pos[1] = getType(balls[4]);
    start.pos[2] = getType(balls[14]);
    start.outEight = 0;
    start.outSolid = 0;
    start.outStripe = 0;
    for (int i = 0; i < 15; i++) {
        if (i == 4 || i == 10 || i == 14)
            continue;
        int type = getType(balls[i]);
        if (type == 1)
            start.outEight++;
        else if (type == 2)
            start.outSolid++;
        else if (type == 3)
            start.outStripe++;
    }
    vector<long long> dist(stateCount, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > que;
    int startCode = encodeState(start);
    dist[startCode] = 0;
    que.push(make_pair(0, startCode));
    auto relax = [&](int nextCode, long long nextCost) {
        if (nextCost < dist[nextCode]) {
            dist[nextCode] = nextCost;
            que.push(make_pair(nextCost, nextCode));
        }
    };
    long long answer = LLONG_MAX;
    while (!que.empty()) {
        long long currentCost = que.top().first;
        int code = que.top().second;
        que.pop();
        if (currentCost != dist[code])
            continue;
        RackState state = decodeState(code);
        int specialUsed = (state.pos[0] != 0) + (state.pos[1] != 0) + (state.pos[2] != 0);
        int outsideUsed = state.outEight + state.outSolid + state.outStripe;
        if (state.pos[1] == 1 && ((state.pos[0] == 2 && state.pos[2] == 3) || (state.pos[0] == 3 && state.pos[2] == 2)) && specialUsed + outsideUsed == 15) {
            answer = currentCost;
            break;
        }
        int outside[4] = {0, state.outEight, state.outSolid, state.outStripe};
        int outsideCapacity = 12 - outsideUsed;
        for (int type = 1; type <= 3; type++) {
            int inSpecial = 0;
            for (int i = 0; i < 3; i++)
                if (state.pos[i] == type)
                    inSpecial++;
            if (inSpecial + outside[type] >= totalCount[type])
                continue;
            for (int i = 0; i < 3; i++) {
                if (state.pos[i] != 0)
                    continue;
                RackState next = state;
                next.pos[i] = type;
                relax(encodeState(next), currentCost + addCost);
            }
            if (outsideCapacity > 0) {
                RackState next = state;
                if (type == 1)
                    next.outEight++;
                else if (type == 2)
                    next.outSolid++;
                else
                    next.outStripe++;
                relax(encodeState(next), currentCost + addCost);
            }
        }
        for (int i = 0; i < 3; i++) {
            if (state.pos[i] == 0)
                continue;
            RackState next = state;
            next.pos[i] = 0;
            relax(encodeState(next), currentCost + removeCost);
        }
        if (state.outEight > 0) {
            RackState next = state;
            next.outEight--;
            relax(encodeState(next), currentCost + removeCost);
        }
        if (state.outSolid > 0) {
            RackState next = state;
            next.outSolid--;
            relax(encodeState(next), currentCost + removeCost);
        }
        if (state.outStripe > 0) {
            RackState next = state;
            next.outStripe--;
            relax(encodeState(next), currentCost + removeCost);
        }
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (state.pos[i] == 0 || state.pos[j] == 0)
                    continue;
                RackState next = state;
                swap(next.pos[i], next.pos[j]);
                relax(encodeState(next), currentCost + swapCost);
            }
        }
        for (int i = 0; i < 3; i++) {
            if (state.pos[i] == 0)
                continue;
            for (int type = 1; type <= 3; type++) {
                if (outside[type] == 0)
                    continue;
                RackState next = state;
                int oldType = next.pos[i];
                next.pos[i] = type;
                if (type == 1)
                    next.outEight--;
                else if (type == 2)
                    next.outSolid--;
                else
                    next.outStripe--;
                if (oldType == 1)
                    next.outEight++;
                else if (oldType == 2)
                    next.outSolid++;
                else
                    next.outStripe++;
                relax(encodeState(next), currentCost + swapCost);
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseIndex = 1; caseIndex <= testCount; caseIndex++) {
        int swapCost, addCost, removeCost;
        cin >> swapCost >> addCost >> removeCost;
        vector<int> balls(15);
        int index = 0;
        for (int row = 1; row <= 5; row++) {
            for (int column = 0; column < row; column++)
                cin >> balls[index++];
        }
        cout << "Case " << caseIndex << ": " << solveCase(swapCost, addCost, removeCost, balls) << '\n';
    }
    return 0;
}
