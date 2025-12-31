// Envelopes
// UVa ID: 10053
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Card {
    int l, w;
};

struct Envelope {
    int L, W, cost, id;
};

int m, n, minCost;
vector<Card> cards;
vector<Envelope> envelopes;
vector<int> bestAssign, currentAssign;
vector<bool> used;
bool found;

const double PI = acos(-1.0);
const double EPS = 1e-8;

// 判断贺卡能否放入信封（考虑斜放）
bool canFit(const Card& card, const Envelope& env) {
    double a = max(card.l, card.w);
    double b = min(card.l, card.w);
    double A = max(env.L, env.W);
    double B = min(env.L, env.W);

    // 检查是否可以直接对齐放（不旋转或旋转90度）
    if (a <= A + EPS && b <= B + EPS) return true;
    if (a <= B + EPS && b <= A + EPS) return true; // 旋转90度
    
    // 如果短边b > B，且长边a > A，不可能放（因为旋转只会让投影更大）
    if (b > B + EPS) return false;
    
    // 现在 b <= B，但 a > A，需要斜着放
    // 数值搜索 θ 在 [0, π/2] 之间
    for (double theta = 0.0; theta <= PI/2.0; theta += 0.001) {
        double proj1 = a * cos(theta) + b * sin(theta);
        double proj2 = a * sin(theta) + b * cos(theta);
        if (proj1 <= A + EPS && proj2 <= B + EPS) return true;
        if (proj1 <= B + EPS && proj2 <= A + EPS) return true; // 信封可旋转
    }
    return false;
}

// 回溯搜索
void backtrack(int idx, int currentCost) {
    if (currentCost >= minCost) return; // 剪枝
    if (idx == m) {
        minCost = currentCost;
        bestAssign = currentAssign;
        found = true;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i] && canFit(cards[idx], envelopes[i])) {
            used[i] = true;
            currentAssign[idx] = i;
            backtrack(idx + 1, currentCost + envelopes[i].cost);
            used[i] = false;
        }
    }
}

int main() {
    int caseNum = 1;
    while (cin >> m >> n && (m || n)) {
        cards.resize(m);
        for (int i = 0; i < m; ++i) cin >> cards[i].l >> cards[i].w;
        envelopes.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> envelopes[i].L >> envelopes[i].W >> envelopes[i].cost;
            envelopes[i].id = i + 1;
        }
        
        found = false;
        minCost = INT_MAX;
        currentAssign.resize(m);
        bestAssign.resize(m);
        used.assign(n, false);
        backtrack(0, 0);
        
        if (caseNum > 1) cout << endl;
        cout << "Case #" << caseNum++ << endl;
        if (found) {
            for (int i = 0; i < m; ++i) cout << envelopes[bestAssign[i]].id << endl;
        } else {
            cout << "cannot buy" << endl;
        }
    }
    return 0;
}
