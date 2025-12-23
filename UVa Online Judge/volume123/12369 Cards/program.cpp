// Cards
// UVa ID: 12369
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 1.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e30; // 表示无穷大，用于不可达状态
const int MAXN = 14;
double memo[MAXN][MAXN][MAXN][MAXN][3][3][3][3];
bool visited[MAXN][MAXN][MAXN][MAXN][3][3][3][3];
int needC, needD, needH, needS;

double dfs(int c, int d, int h, int s, int jc, int jd, int jh, int js) {
    // jc, jd, jh, js 分别表示Joker被指定为梅花、方块、红心、黑桃的数量
    // 总Joker使用数 = jc + jd + jh + js ≤ 2
    
    int totalC = c + jc;
    int totalD = d + jd;
    int totalH = h + jh;
    int totalS = s + js;
    
    if (totalC >= needC && totalD >= needD && totalH >= needH && totalS >= needS) {
        return 0.0; // 目标已达成，无需再抽牌
    }
    
    // 边界检查
    if (c > 13 || d > 13 || h > 13 || s > 13) return INF;
    if (jc + jd + jh + js > 2) return INF;
    if (c + d + h + s + jc + jd + jh + js > 54) return INF;
    
    int stateC = min(c, 13);
    int stateD = min(d, 13);
    int stateH = min(h, 13);
    int stateS = min(s, 13);
    
    if (visited[stateC][stateD][stateH][stateS][jc][jd][jh][js]) {
        return memo[stateC][stateD][stateH][stateS][jc][jd][jh][js];
    }
    
    int remainingClubs = 13 - c;
    int remainingDiamonds = 13 - d;
    int remainingHearts = 13 - h;
    int remainingSpades = 13 - s;
    int remainingJokers = 2 - (jc + jd + jh + js);
    int drawnCards = c + d + h + s + jc + jd + jh + js;
    int remainingCards = 54 - drawnCards;
    
    if (remainingCards == 0) {
        // 无牌可抽仍未达标
        visited[stateC][stateD][stateH][stateS][jc][jd][jh][js] = true;
        memo[stateC][stateD][stateH][stateS][jc][jd][jh][js] = INF;
        return INF;
    }
    
    double expected = 0.0;
    
    // 抽到梅花的期望
    if (remainingClubs > 0) {
        double prob = (double)remainingClubs / remainingCards;
        expected += prob * (1.0 + dfs(c + 1, d, h, s, jc, jd, jh, js));
    }
    
    // 抽到方块的期望
    if (remainingDiamonds > 0) {
        double prob = (double)remainingDiamonds / remainingCards;
        expected += prob * (1.0 + dfs(c, d + 1, h, s, jc, jd, jh, js));
    }
    
    // 抽到红心的期望
    if (remainingHearts > 0) {
        double prob = (double)remainingHearts / remainingCards;
        expected += prob * (1.0 + dfs(c, d, h + 1, s, jc, jd, jh, js));
    }
    
    // 抽到黑桃的期望
    if (remainingSpades > 0) {
        double prob = (double)remainingSpades / remainingCards;
        expected += prob * (1.0 + dfs(c, d, h, s + 1, jc, jd, jh, js));
    }
    
    // 抽到Joker的期望
    if (remainingJokers > 0) {
        double prob = (double)remainingJokers / remainingCards;
        double best = INF;
        
        // 尝试四种花色，选择期望最小的
        if (jc + jd + jh + js < 2) {
            best = min(best, 1.0 + dfs(c, d, h, s, jc + 1, jd, jh, js));
            best = min(best, 1.0 + dfs(c, d, h, s, jc, jd + 1, jh, js));
            best = min(best, 1.0 + dfs(c, d, h, s, jc, jd, jh + 1, js));
            best = min(best, 1.0 + dfs(c, d, h, s, jc, jd, jh, js + 1));
        }
        
        expected += prob * best;
    }
    
    visited[stateC][stateD][stateH][stateS][jc][jd][jh][js] = true;
    memo[stateC][stateD][stateH][stateS][jc][jd][jh][js] = expected;
    return expected;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> needC >> needD >> needH >> needS;
        
        // 检查是否可能
        int required = 0;
        if (needC > 13) required += needC - 13;
        if (needD > 13) required += needD - 13;
        if (needH > 13) required += needH - 13;
        if (needS > 13) required += needS - 13;
        
        if (required > 2) {
            printf("Case %d: -1.000\n", t);
            continue;
        }
        
        // 初始化记忆化数组
        memset(visited, 0, sizeof(visited));
        double result = dfs(0, 0, 0, 0, 0, 0, 0, 0);
        
        if (result > 1e20) {
            printf("Case %d: -1.000\n", t);
        } else {
            printf("Case %d: %.3lf\n", t, result);
        }
    }
    return 0;
}
