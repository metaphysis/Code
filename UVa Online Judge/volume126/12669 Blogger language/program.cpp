// Blogger language
// UVa ID: 12669
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 9.170s

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    string T;
    while (cin >> N >> T) {
        string P;
        cin >> P;
        int lenT = T.size();
        int M = P.size();
        P = " " + P; // 1-indexed
        // 记录初始大小写，1表示大写，0表示小写
        vector<int> isUpperP(M + 1);
        for (int i = 1; i <= M; ++i) isUpperP[i] = isupper(P[i]) ? 1 : 0;
        vector<int> isUpperT(lenT);
        for (int k = 0; k < lenT; ++k) isUpperT[k] = isupper(T[k]) ? 1 : 0;
        // 找出所有忽略大小写匹配的起始位置
        vector<bool> validStart(M + 1, false);
        for (int i = 1; i <= M - lenT + 1; ++i) {
            bool ok = true;
            for (int k = 0; k < lenT; ++k)
                if (tolower(P[i + k]) != tolower(T[k])) { ok = false; break; }
            validStart[i] = ok;
        }
        // 分块大小
        int B = max(1, (int)sqrt(M));
        while (B < lenT) B = lenT; // 保证块大小不小于模式串长，简化跨块处理
        int blockCnt = (M + B - 1) / B;
        vector<int> blockId(M + 1);
        for (int i = 1; i <= M; ++i) blockId[i] = (i - 1) / B;
        // 块信息
        struct Block {
            vector<int> innerStarts;    // 纯内部窗口起始位置
            vector<int> boundStarts;    // 跨块边界窗口起始位置
            int maxBase, minBase;       // 忽略整块懒标记时的最大值/最小值
            bool dirty;                 // 是否需要重算 maxBase/minBase
        };
        vector<Block> blocks(blockCnt);
        vector<int> baseV(M + 1); // 纯内部窗口的 base 值
        // 将有效窗口划分到各块
        for (int i = 1; i <= M - lenT + 1; ++i) {
            if (!validStart[i]) continue;
            int bs = blockId[i], be = blockId[i + lenT - 1];
            if (bs == be) {
                blocks[bs].innerStarts.push_back(i);
                int sum = 0;
                for (int k = 0; k < lenT; ++k) sum += isUpperP[i + k] ^ isUpperT[k];
                baseV[i] = sum;
            } else blocks[bs].boundStarts.push_back(i); // 因为B>=lenT，最多跨相邻两块
        }
        // 初始化各块的统计值
        for (int b = 0; b < blockCnt; ++b) {
            blocks[b].maxBase = -1;
            blocks[b].minBase = INF;
            for (int i : blocks[b].innerStarts) {
                int v = baseV[i];
                if (v > blocks[b].maxBase) blocks[b].maxBase = v;
                if (v < blocks[b].minBase) blocks[b].minBase = v;
            }
            if (blocks[b].minBase == INF) blocks[b].minBase = -1;
            blocks[b].dirty = false;
        }
        vector<int> lazy(blockCnt, 0); // 整块翻转懒标记
        vector<int> flip(M + 1, 0);    // 单点翻转标记（不包含懒标记）
        // 计算某个匹配起始位置的实际 mismatch
        auto calcMismatch = [&](int i) -> int {
            int sum = 0;
            for (int k = 0; k < lenT; ++k) {
                int j = i + k;
                int actualFlip = flip[j] ^ lazy[blockId[j]];
                sum += isUpperP[j] ^ actualFlip ^ isUpperT[k];
            }
            return sum;
        };
        // 重新计算某块的 maxBase/minBase
        auto recalcBlock = [&](int b) {
            blocks[b].maxBase = -1;
            blocks[b].minBase = INF;
            for (int i : blocks[b].innerStarts) {
                int v = baseV[i];
                if (v > blocks[b].maxBase) blocks[b].maxBase = v;
                if (v < blocks[b].minBase) blocks[b].minBase = v;
            }
            if (blocks[b].minBase == INF) blocks[b].minBase = -1;
            blocks[b].dirty = false;
        };
        // 翻转单个字符，并更新受影响的纯内部窗口
        auto flipChar = [&](int j) {
            int oldFlip = flip[j];
            flip[j] ^= 1;
            for (int k = 0; k < lenT; ++k) {
                int i = j - k;
                if (i >= 1 && i <= M - lenT + 1 && validStart[i]) {
                    int bs = blockId[i], be = blockId[i + lenT - 1];
                    if (bs == be) { // 纯内部窗口
                        int oldBit = isUpperP[j] ^ oldFlip ^ isUpperT[k];
                        int delta = 1 - 2 * oldBit;
                        baseV[i] += delta;
                        blocks[bs].dirty = true;
                    }
                }
            }
        };
        // 区间翻转
        auto applyFlip = [&](int L, int R) {
            int bl = blockId[L], br = blockId[R];
            if (bl == br) {
                for (int j = L; j <= R; ++j) flipChar(j);
                return;
            }
            int blkRight = min(M, (bl + 1) * B);
            for (int j = L; j <= blkRight; ++j) flipChar(j);
            int brkLeft = br * B + 1;
            for (int j = brkLeft; j <= R; ++j) flipChar(j);
            for (int b = bl + 1; b <= br - 1; ++b) lazy[b] ^= 1;
        };
        // 处理每个查询
        for (int q = 0; q < N; ++q) {
            int L, R;
            cin >> L >> R;
            int startL = L, startR = R - lenT + 1;
            int ans = -1;
            if (startL <= startR) {
                int bl = blockId[startL], br = blockId[startR];
                if (bl == br) {
                    for (int i = startL; i <= startR; ++i)
                        if (validStart[i]) ans = max(ans, calcMismatch(i));
                } else {
                    // 左边缘块
                    int blkRight = min(M, (bl + 1) * B);
                    for (int i = startL; i <= blkRight && i <= startR; ++i)
                        if (validStart[i]) ans = max(ans, calcMismatch(i));
                    // 中间整块
                    for (int b = bl + 1; b <= br - 1; ++b) {
                        if (blocks[b].dirty) recalcBlock(b);
                        if (blocks[b].maxBase != -1) {
                            int actualMax = lazy[b] ? lenT - blocks[b].minBase : blocks[b].maxBase;
                            ans = max(ans, actualMax);
                        }
                        // 跨块边界窗口
                        for (int i : blocks[b].boundStarts)
                            if (i <= startR) ans = max(ans, calcMismatch(i));
                    }
                    // 右边缘块
                    int brkLeft = br * B + 1;
                    for (int i = brkLeft; i <= startR; ++i)
                        if (validStart[i]) ans = max(ans, calcMismatch(i));
                }
            }
            cout << ans << '\n';
            applyFlip(L, R); // 查询后应用翻转
        }
    }
    return 0;
}
