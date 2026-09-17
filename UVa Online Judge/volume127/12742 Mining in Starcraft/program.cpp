#include <bits/stdc++.h>
using namespace std;

struct State {
    int sm, sg, bs, br;
    array<int, 10> mq, gq;
    bool operator==(const State &other) const {
        return sm == other.sm && sg == other.sg && bs == other.bs && br == other.br && mq == other.mq && gq == other.gq;
    }
};

struct StateHash {
    size_t operator()(const State &s) const {
        size_t h = 1469598103934665603ULL;
        auto addValue = [&](int v) {
            h ^= static_cast<size_t>(v + 1009);
            h *= 1099511628211ULL;
        };
        addValue(s.sm);
        addValue(s.sg);
        addValue(s.bs);
        addValue(s.br);
        for (int i = 0; i < 10; i++) addValue(s.mq[i]);
        for (int i = 0; i < 10; i++) addValue(s.gq[i]);
        return h;
    }
};

struct Action {
    int time, mc, gc;
    bool build;
};

struct Node {
    State st;
    int parent;
    Action act;
};

int getActive(const array<int, 10> &q) {
    int sum = 0;
    for (int i = 0; i < 10; i++) sum += q[i];
    return sum;
}

int getCompletedMineral(const State &st) {
    return st.sm - getActive(st.mq);
}

int getBuiltScv(const State &st) {
    return st.bs - (st.br > 0 ? 1 : 0);
}

bool startBuild(State &st, int buildNeed) {
    if (st.bs >= buildNeed || st.br > 0) return false;
    int cm = getCompletedMineral(st);
    if (50 + 8 * cm - 50 * st.bs < 50) return false;
    st.bs++;
    return true;
}

bool isGoal(const State &st, int mineralNeed, int gasNeed, int buildNeed) {
    if (st.sm != mineralNeed || st.sg != gasNeed) return false;
    if (getActive(st.mq) > 0 || getActive(st.gq) > 0) return false;
    if (st.bs != buildNeed || st.br > 0) return false;
    return true;
}

bool canFinish(const State &st, int time, int maxTime, int t1, int t2, int t3, int mineralNeed, int gasNeed, int buildNeed) {
    int leftTime = maxTime - time;
    int built = getBuiltScv(st);
    int workers = 4 + built;
    int capacity = workers * leftTime;
    int remainBuild = buildNeed - built;
    int finishTime = 0;
    if (remainBuild > 0) {
        finishTime = st.br > 0 ? st.br : t3;
        for (int i = 0; i < remainBuild; i++) {
            if (i > 0) finishTime += t3;
            if (finishTime > leftTime) return false;
            capacity += leftTime - finishTime;
        }
    }
    int work = (mineralNeed - st.sm) * t1 + (gasNeed - st.sg) * t2;
    for (int i = 0; i < 10; i++) {
        work += st.mq[i] * (i + 1);
        work += st.gq[i] * (i + 1);
    }
    return work <= capacity;
}

void advanceState(State &st) {
    for (int i = 0; i < 9; i++) {
        st.mq[i] = st.mq[i + 1];
        st.gq[i] = st.gq[i + 1];
    }
    st.mq[9] = 0;
    st.gq[9] = 0;
    if (st.br > 0) st.br--;
}

void reconstructPlan(const vector<Node> &nodes, int endNode, int endTime, vector<Action> &plan) {
    plan.assign(endTime, Action{0, 0, 0, false});
    int cur = endNode;
    while (cur != -1) {
        const Action &act = nodes[cur].act;
        plan[act.time] = act;
        cur = nodes[cur].parent;
    }
}

bool searchPlan(int t1, int t2, int t3, int mineralNeed, int gasNeed, int buildNeed, int maxTime, int &endTime, vector<Action> &plan) {
    vector<Node> nodes;
    vector<int> layer, nextLayer;
    unordered_map<State, int, StateHash> stateMap;
    State init;
    init.sm = init.sg = init.bs = init.br = 0;
    init.mq.fill(0);
    init.gq.fill(0);
    bool initBuild = startBuild(init, buildNeed);
    if (initBuild) init.br = t3;
    if (isGoal(init, mineralNeed, gasNeed, buildNeed)) {
        endTime = 0;
        plan.clear();
        return true;
    }
    auto expandState = [&](const State &base, int parent, int time, bool build, unordered_map<State, int, StateHash> &mp, vector<int> &ids) {
        int built = getBuiltScv(base);
        int idle = 4 + built - getActive(base.mq) - getActive(base.gq);
        int remainM = mineralNeed - base.sm;
        int remainG = gasNeed - base.sg;
        int take = min(idle, remainM + remainG);
        int lowM = max(0, take - remainG);
        int highM = min(take, remainM);
        for (int mc = lowM; mc <= highM; mc++) {
            int gc = take - mc;
            State ns = base;
            ns.sm += mc;
            ns.sg += gc;
            ns.mq[t1 - 1] += mc;
            ns.gq[t2 - 1] += gc;
            if (!canFinish(ns, time, maxTime, t1, t2, t3, mineralNeed, gasNeed, buildNeed)) continue;
            if (mp.find(ns) != mp.end()) continue;
            int id = static_cast<int>(nodes.size());
            nodes.push_back(Node{ns, parent, Action{time, mc, gc, build}});
            mp[ns] = id;
            ids.push_back(id);
        }
    };
    if (!canFinish(init, 0, maxTime, t1, t2, t3, mineralNeed, gasNeed, buildNeed)) return false;
    expandState(init, -1, 0, initBuild, stateMap, layer);
    for (int time = 1; time <= maxTime; time++) {
        nextLayer.clear();
        unordered_map<State, int, StateHash> nextMap;
        nextMap.reserve(layer.size() * 2 + 1);
        for (int id : layer) {
            State st = nodes[id].st;
            advanceState(st);
            bool build = startBuild(st, buildNeed);
            if (build) st.br = t3;
            if (isGoal(st, mineralNeed, gasNeed, buildNeed)) {
                endTime = time;
                reconstructPlan(nodes, id, endTime, plan);
                return true;
            }
            if (time == maxTime) continue;
            expandState(st, id, time, build, nextMap, nextLayer);
        }
        layer.swap(nextLayer);
        if (layer.empty()) break;
    }
    return false;
}

void outputPlan(const vector<Action> &plan, int t1, int t2, int t3) {
    vector<int> ready(4, 0);
    int buildFinish = -1;
    for (const Action &act : plan) {
        int time = act.time;
        if (buildFinish == time) {
            ready.push_back(time);
            buildFinish = -1;
        }
        if (act.build) {
            cout << time << " 0\n";
            buildFinish = time + t3;
        }
        int needM = act.mc, needG = act.gc;
        for (int i = 0; i < static_cast<int>(ready.size()) && needM > 0; i++) {
            if (ready[i] > time) continue;
            cout << time << ' ' << i + 1 << " 1\n";
            ready[i] = time + t1;
            needM--;
        }
        for (int i = 0; i < static_cast<int>(ready.size()) && needG > 0; i++) {
            if (ready[i] > time) continue;
            cout << time << ' ' << i + 1 << " 2\n";
            ready[i] = time + t2;
            needG--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t1, t2, t3, p1, p2;
    int caseNo = 0;
    while (cin >> t1 >> t2 >> t3 >> p1 >> p2) {
        if (t1 == 0 && t2 == 0 && t3 == 0 && p1 == 0 && p2 == 0) break;
        int gasNeed = (p2 + 7) / 8;
        int mineralNeed = max(0, (p1 - 50 + 7) / 8);
        int bestTime = 50, currentTime;
        vector<Action> bestPlan, currentPlan;
        searchPlan(t1, t2, t3, mineralNeed, gasNeed, 0, 50, bestTime, bestPlan);
        for (int buildNeed = 1; buildNeed * t3 < bestTime; buildNeed++) {
            int need = p1 + 50 * buildNeed - 50;
            mineralNeed = max(0, (need + 7) / 8);
            int maxTime = bestTime - 1;
            if (!searchPlan(t1, t2, t3, mineralNeed, gasNeed, buildNeed, maxTime, currentTime, currentPlan)) continue;
            bestTime = currentTime;
            bestPlan = currentPlan;
        }
        cout << "Case " << ++caseNo << ": " << bestTime << '\n';
        outputPlan(bestPlan, t1, t2, t3);
        cout << '\n';
    }
    return 0;
}
