// Legendary Pokemon
// UVa ID: 10121
// Verdict: Accepted
// Submission Date: 2026-08-
// UVa Run Time: s

#include <bits/stdc++.h>
using namespace std;

int L, G, MAX_HP;
int run[6];
int p1, p2;
int bInit[5];
int k;
struct Move {
    int type;
    int dmg, acc, conf, poison;
};
vector<Move> moves;

struct State {
    int round;
    int hpMe, hpOpp;
    int potionsMe, potionsOpp;
    array<int, 5> balls;
    int statusType;         // 0无 1睡眠 2混乱
    int statusRem;
    int confuseVal;
    int poisonRem;
    int poisonVal;
    bool operator<(const State& o) const {
        if (round != o.round) return round < o.round;
        if (hpMe != o.hpMe) return hpMe < o.hpMe;
        if (hpOpp != o.hpOpp) return hpOpp < o.hpOpp;
        if (potionsMe != o.potionsMe) return potionsMe < o.potionsMe;
        if (potionsOpp != o.potionsOpp) return potionsOpp < o.potionsOpp;
        for (int i = 0; i < 5; ++i)
            if (balls[i] != o.balls[i]) return balls[i] < o.balls[i];
        if (statusType != o.statusType) return statusType < o.statusType;
        if (statusRem != o.statusRem) return statusRem < o.statusRem;
        if (confuseVal != o.confuseVal) return confuseVal < o.confuseVal;
        if (poisonRem != o.poisonRem) return poisonRem < o.poisonRem;
        return poisonVal < o.poisonVal;
    }
};

map<State, double> memo;

double catchProb(int ballIdx, const State& s) {
    double base;
    if (ballIdx == 0) base = 0.05;
    else if (ballIdx == 1) base = 0.10;
    else if (ballIdx == 2) base = 0.15;
    else if (ballIdx == 3) {
        if (L > 50) base = 0.18;
        else base = 0.10;
    } else {
        if (G == 1) base = 0.20;
        else base = 0.0;
    }
    double crit = 0.0;
    if (s.hpOpp > 0) {
        if (s.hpOpp <= 50) crit = 0.10;
        else if (s.hpOpp <= 100) crit = 0.05;
    }
    double poisonBonus = (s.poisonRem > 0) ? 0.10 : 0.0;
    double statusBonus = (s.statusRem > 0) ? 0.05 : 0.0;
    double p = base + crit + poisonBonus + statusBonus;
    if (p > 1.0) p = 1.0;
    return p;
}

double opponentAction(State s);
double dfs(const State& s) {
    if (s.round > 5) return 0.0;
    auto it = memo.find(s);
    if (it != memo.end()) return it->second;

    double best = 0.0;

    // 使用药
    if (s.potionsMe > 0) {
        State ns = s;
        ns.hpMe = min(MAX_HP, ns.hpMe + 200);
        ns.potionsMe--;
        best = max(best, opponentAction(ns));
    }

    // 使用球
    for (int i = 0; i < 5; ++i) {
        if (s.balls[i] == 0) continue;
        double p = catchProb(i, s);
        State ns = s;
        ns.balls[i]--;
        double val = p * 1.0 + (1 - p) * opponentAction(ns);
        best = max(best, val);
    }

    // 使用招式
    for (const Move& mv : moves) {
        double acc = mv.acc / 100.0;
        if (mv.type == 1) {
            State ns = s;
            ns.hpOpp -= mv.dmg;
            if (ns.hpOpp <= 0) {
                double missVal = opponentAction(s);
                best = max(best, (1 - acc) * missVal);
                continue;
            }
            double hitVal = opponentAction(ns);
            double missVal = opponentAction(s);
            best = max(best, acc * hitVal + (1 - acc) * missVal);
        } else if (mv.type == 2) {
            if (s.statusRem > 0) {
                best = max(best, opponentAction(s));
            } else {
                State ns = s;
                if (mv.conf == 0) ns.statusType = 1;
                else {
                    ns.statusType = 2;
                    ns.confuseVal = mv.conf;
                }
                ns.statusRem = 3;
                double hitVal = opponentAction(ns);
                double missVal = opponentAction(s);
                best = max(best, acc * hitVal + (1 - acc) * missVal);
            }
        } else {
            State ns = s;
            ns.hpOpp -= mv.dmg;
            if (ns.hpOpp <= 0) {
                double missVal = opponentAction(s);
                best = max(best, (1 - acc) * missVal);
                continue;
            }
            if (s.poisonRem == 0) {
                ns.poisonRem = 3;
                ns.poisonVal = mv.poison;
            }
            double hitVal = opponentAction(ns);
            double missVal = opponentAction(s);
            best = max(best, acc * hitVal + (1 - acc) * missVal);
        }
    }

    // 跳过（什么都不做）
    best = max(best, opponentAction(s));

    memo[s] = best;
    return best;
}

double opponentAction(State s) {
    // 1. 毒伤害（在敌方行动前）
    if (s.poisonRem > 0) {
        s.hpOpp -= s.poisonVal;
        s.poisonRem--;
        if (s.hpOpp <= 0) return 0.0;
    }

    // 2. 逃跑判定
    double escapeProb = run[s.round] / 100.0;
    if (escapeProb == 1.0) return 0.0;
    double nonEscape = 1.0 - escapeProb;

    // 3. 未逃跑，执行行动
    if (s.statusType == 1) { // 睡眠
        // 睡眠状态下仍可用药（根据策略特殊说明）
        if (s.hpOpp <= 150 && s.potionsOpp > 0) {
            State ns = s;
            ns.hpOpp = min(999, ns.hpOpp + 200);
            ns.potionsOpp--;
            ns.statusRem--;
            if (ns.statusRem == 0) ns.statusType = 0;
            ns.round++;
            return nonEscape * dfs(ns);
        } else {
            // 睡眠不能攻击，只能跳过（但也没药可用了）
            State ns = s;
            ns.statusRem--;
            if (ns.statusRem == 0) ns.statusType = 0;
            ns.round++;
            return nonEscape * dfs(ns);
        }
    } else if (s.statusType == 2) { // 混乱
        double selfProb = s.confuseVal / 100.0;
        // 自残分支（攻击自己，伤害300，必中）
        State nsSelf = s;
        nsSelf.hpOpp -= 300;
        if (nsSelf.hpOpp <= 0) return nonEscape * 0.0; // 自己打死自己，失败
        nsSelf.statusRem--;
        if (nsSelf.statusRem == 0) nsSelf.statusType = 0;
        nsSelf.round++;
        double expSelf = dfs(nsSelf);

        // 非自残分支（正常行动）
        State nsNormal = s;
        nsNormal.statusRem--;
        if (nsNormal.statusRem == 0) nsNormal.statusType = 0;
        double expNormal;
        if (nsNormal.hpOpp <= 150 && nsNormal.potionsOpp > 0) {
            // 用药
            State ns = nsNormal;
            ns.hpOpp = min(999, ns.hpOpp + 200);
            ns.potionsOpp--;
            ns.round++;
            expNormal = dfs(ns);
        } else {
            // 攻击我方 Cross Chop（命中率30%）
            double hitProb = 0.30;
            State nsHit = nsNormal;
            nsHit.hpMe -= 300;
            double expHit = 0.0;
            if (nsHit.hpMe > 0) {
                nsHit.round++;
                expHit = dfs(nsHit);
            }
            State nsMiss = nsNormal;
            nsMiss.round++;
            double expMiss = dfs(nsMiss);
            expNormal = hitProb * expHit + (1 - hitProb) * expMiss;
        }
        double expIfNotEscape = selfProb * expSelf + (1 - selfProb) * expNormal;
        return nonEscape * expIfNotEscape;
    } else { // 无状态
        if (s.hpOpp <= 150 && s.potionsOpp > 0) {
            State ns = s;
            ns.hpOpp = min(999, ns.hpOpp + 200);
            ns.potionsOpp--;
            ns.round++;
            return nonEscape * dfs(ns);
        } else {
            double hitProb = 0.30;
            State nsHit = s;
            nsHit.hpMe -= 300;
            double expHit = 0.0;
            if (nsHit.hpMe > 0) {
                nsHit.round++;
                expHit = dfs(nsHit);
            }
            State nsMiss = s;
            nsMiss.round++;
            double expMiss = dfs(nsMiss);
            double expIfNotEscape = hitProb * expHit + (1 - hitProb) * expMiss;
            return nonEscape * expIfNotEscape;
        }
    }
}

int main() {
    while (true) {
        scanf("%d%d%d", &L, &G, &MAX_HP);
        if (L == 0 && G == 0 && MAX_HP == 0) break;
        for (int i = 1; i <= 5; ++i) scanf("%d", &run[i]);
        scanf("%d%d", &p1, &p2);
        for (int i = 0; i < 5; ++i) scanf("%d", &bInit[i]);
        scanf("%d", &k);
        moves.clear();
        for (int i = 0; i < k; ++i) {
            int t; scanf("%d", &t);
            Move mv; mv.type = t;
            if (t == 1) {
                scanf("%d%d", &mv.dmg, &mv.acc);
            } else if (t == 2) {
                scanf("%d%d", &mv.conf, &mv.acc);
                mv.dmg = mv.poison = 0;
            } else {
                scanf("%d%d%d", &mv.dmg, &mv.poison, &mv.acc);
            }
            moves.push_back(mv);
        }
        memo.clear();
        State start;
        start.round = 1;
        start.hpMe = MAX_HP;
        start.hpOpp = 999;
        start.potionsMe = p1;
        start.potionsOpp = p2;
        for (int i = 0; i < 5; ++i) start.balls[i] = bInit[i];
        start.statusType = 0;
        start.statusRem = 0;
        start.confuseVal = 0;
        start.poisonRem = 0;
        start.poisonVal = 0;
        double ans = dfs(start);
        printf("%.4f\n", ans);
    }
    return 0;
}
