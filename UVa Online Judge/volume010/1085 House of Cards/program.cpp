// House of Cards
// UVa ID: 1085
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 0.330s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int UP = 0, DOWN = 1, FLAT = 2;
const int MAXN = 100;

int N;
int deck[MAXN]; // 正数为红色，负数为黑色

// 计算三张牌的得分：点数和，多数颜色为正，少数为负
int getScore(int c1, int c2, int c3) {
    int sum = abs(c1) + abs(c2) + abs(c3);
    int red = 0, black = 0;
    if (c1 > 0) red++; else black++;
    if (c2 > 0) red++; else black++;
    if (c3 > 0) red++; else black++;
    return (red > black) ? sum : -sum;
}

struct State {
    int val[8];          // 8个位置的值
    int dir[8];          // 方向：UP, DOWN, FLAT
    int hold[2];         // 两位玩家手中的牌，0表示无
    int nextPos;         // 下一个要抽取的牌在deck中的下标
    int score;           // 当前累计得分（红方减黑方）

    // 初始化，前8张牌构成底层四个峰
    State() {
        for (int i = 0; i < 8; ++i) {
            val[i] = deck[i];
            dir[i] = (i % 2 == 0) ? UP : DOWN;
        }
        hold[0] = hold[1] = 0;
        nextPos = 8;
        score = 0;
    }
    
    // 判断是否终局（牌已抽完），此时结算手牌
    bool isFinal() {
        if (nextPos == 2 * N) {
            score += hold[0] + hold[1]; // 红为正，黑为负
            hold[0] = hold[1] = 0;
            return true;
        }
        return false;
    }
    
    // 生成下一状态（仅推进牌堆指针）
    State child() const {
        State s = *this;
        s.nextPos++;
        return s;
    }
    
    // 扩展所有合法子状态
    void expand(int player, vector<State>& children) const {
        int cur = deck[nextPos];
        // 1. 若当前玩家无手牌，可选择持牌
        if (hold[player] == 0) {
            State s = child();
            s.hold[player] = cur;
            children.push_back(s);
        }
        // 2. 放置地板：寻找相邻的 DOWN 和 UP（即一个谷）
        for (int i = 0; i < 7; ++i) {
            if (dir[i] == DOWN && dir[i + 1] == UP) {
                // 2a. 使用刚抽到的牌 cur 作为地板
                State s = child();
                s.score += getScore(val[i], val[i + 1], cur);
                s.dir[i] = s.dir[i + 1] = FLAT;
                s.val[i] = s.val[i + 1] = cur;
                children.push_back(s);
                // 2b. 若手中有牌，用手牌作地板，cur 成为新手牌
                if (hold[player] != 0) {
                    State t = child();
                    t.score += getScore(val[i], val[i + 1], hold[player]);
                    t.dir[i] = t.dir[i + 1] = FLAT;
                    t.val[i] = t.val[i + 1] = hold[player];
                    t.hold[player] = cur;
                    children.push_back(t);
                }
            }
        }
        // 3. 建造峰：需要手牌，且存在相邻两个 FLAT 且值相同（同一地板）
        if (hold[player] != 0) {
            for (int i = 0; i < 7; ++i) {
                if (dir[i] == FLAT && dir[i + 1] == FLAT && val[i] == val[i + 1]) {
                    int top1 = cur, top2 = hold[player];
                    // 顺序1：cur 在左，hold 在右
                    State s = child();
                    s.score += getScore(val[i], top1, top2);
                    s.dir[i] = UP;
                    s.dir[i + 1] = DOWN;
                    s.val[i] = top1;
                    s.val[i + 1] = top2;
                    s.hold[player] = 0;
                    children.push_back(s);
                    // 顺序2：hold 在左，cur 在右
                    State t = child();
                    t.score += getScore(val[i], top2, top1);
                    t.dir[i] = UP;
                    t.dir[i + 1] = DOWN;
                    t.val[i] = top2;
                    t.val[i + 1] = top1;
                    t.hold[player] = 0;
                    children.push_back(t);
                }
            }
        }
    }
};

// alpha-beta 剪枝搜索，player=0 为 Axel（最大化），player=1 为 Birgit（最小化）
int alphaBeta(int player, State& s, int alpha, int beta) {
    if (s.isFinal()) return s.score;
    vector<State> children;
    s.expand(player, children);
    for (const State& child : children) {
        int val = alphaBeta(1 - player, const_cast<State&>(child), alpha, beta);
        if (player == 0) alpha = max(alpha, val);
        else beta = min(beta, val);
        if (beta <= alpha) break;
    }
    return (player == 0) ? alpha : beta;
}

int main() {
    int caseNo = 0;
    char name[10];
    while (scanf("%s", name) == 1 && name[0] != 'E') {
        scanf("%d", &N);
        for (int i = 0; i < 2 * N; ++i) {
            char ch;
            scanf("%d%c", &deck[i], &ch);
            if (ch == 'B') deck[i] = -deck[i]; // 黑色为负
        }
        State init;
        int firstPlayer = (deck[0] > 0) ? 0 : 1; // 红先为Axel，黑先为Birgit
        int ans = alphaBeta(firstPlayer, init, -INF, INF);
        if (name[0] == 'B') ans = -ans; // 若目标为Birgit，取反
        printf("Case %d: ", ++caseNo);
        if (ans == 0) printf("Axel and Birgit tie\n");
        else if (ans > 0) printf("%s wins %d\n", name, ans);
        else printf("%s loses %d\n", name, -ans);
    }
    return 0;
}
