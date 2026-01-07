// Traffic
// UVa ID: 10704
// Verdict: Accepted
// Submission Date: 2026-01-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 方块类型常量定义
const int WHITE = 0, HORIZONTAL = 1, VERTICAL = 2;

// 方块结构体：记录位置、长度和类型
struct Block { int r, c, length, type; };

// 状态结构体：包含所有方块、棋盘状态和步数
struct State { vector<Block> blks; long long room; int step; };

// 位操作辅助函数
void clearBit(long long& bit, int p) { bit &= (~(1LL << p)); }
void setBit(long long& bit, int p) { bit |= (1LL << p); }
int getBit(long long& bit, int p) { return bit & (1LL << p) ? 1 : 0; }

// 从棋盘状态中移除一个方块
void removeBlock(const Block& blk, long long& bit) {
    for (int i = 0; i < blk.length; i++) {
        int x = blk.r, y = blk.c;
        if (blk.type <= HORIZONTAL) y += i;  // 水平方块：列增加
        else x += i;                         // 竖直方块：行增加
        clearBit(bit, x * 6 + y);
    }
}

// 向棋盘状态中添加一个方块
void placeBlock(const Block& blk, long long& bit) {
    for (int i = 0; i < blk.length; i++) {
        int x = blk.r, y = blk.c;
        if (blk.type <= HORIZONTAL) y += i;
        else x += i;
        setBit(bit, x * 6 + y);
    }
}

// 移动方向偏移量：WHITE/HORIZONTAL:左(-1,0)、右(1,0); VERTICAL:上(0,-1)、下(0,1)
int offset[3][2][2] = {{{0, -1}, {0, 1}}, {{0, -1}, {0, 1}}, {{-1, 0}, {1, 0}}};

// BFS搜索最少步数
int bfs(vector<Block> blks) {
    queue<State> q;
    long long bit = 0;
    // 初始化棋盘状态
    for (auto blk : blks) placeBlock(blk, bit);
    q.push({blks, bit, 0});
    
    // 已访问状态集合（使用棋盘状态的long long表示）
    unordered_set<long long> visited;
    visited.insert(bit);
    
    while (!q.empty()) {
        State u = q.front(); q.pop();
        
        // 尝试移动每个方块
        for (int i = 0; i < u.blks.size(); i++) {
            // 两个方向：左/右 或 上/下
            for (int j = 0; j < 2; j++) {
                // 尝试移动1,2,3,...格
                for (int k = 1; ; k++) {
                    State v = u;
                    Block blk = v.blks[i];
                    removeBlock(blk, v.room);  // 临时移除该方块
                    
                    // 计算新位置
                    int nr = blk.r + k * offset[blk.type][j][0];
                    int nc = blk.c + k * offset[blk.type][j][1];
                    
                    // 边界检查
                    if (nr < 0 || nr >= 6 || nc < 0 || nc  >= 6) break;
                    if (blk.type <= HORIZONTAL && nc + blk.length > 6) break;
                    if (blk.type == VERTICAL && nr + blk.length > 6) break;
                    
                    // 碰撞检测：检查目标位置是否被其他方块占据
                    int valid = true;
                    for (int z = 0; z < blk.length; z++) {
                        int idx = nr * 6 + nc + z;
                        if (blk.type == VERTICAL) idx = (nr + z) * 6 + nc;
                        if (getBit(v.room, idx)) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) break;
                    
                    // 检查白色方块是否到达出口
                    if (blk.type == WHITE && nc + blk.length == 6) return u.step + 1;
                    
                    // 更新方块位置并重新放置到棋盘
                    blk.r = nr, blk.c = nc;
                    placeBlock(blk, v.room);
                    
                    // 状态判重
                    if (visited.count(v.room)) continue;
                    visited.insert(v.room);
                    
                    v.blks[i] = blk;
                    v.step += 1;
                    q.push(v);
                }
            }
        }
    }
    return -1;  // 理论上不会执行（题目保证有解）
}

int main() {
    int N;
    cin >> N;
    for (int p = 1; p <= N; ++p) {
        vector<Block> blocks;
        int n, r, c;
        
        // 白色方块
        cin >> r >> c;
        blocks.push_back({r, c, 2, WHITE});
        
        // 读取其他方块：按顺序为v2, v3, h2, h3
        for (int i = 0; i < 4; i++) {
            cin >> n;
            for (int j = 0; j < n; j++) {
                cin >> r >> c;
                // i<2: 竖直方块；i>=2: 水平方块
                // i%2==0: 长度2；i%2==1: 长度3
                blocks.push_back({r, c, 2 + (i % 2), i < 2 ? VERTICAL : HORIZONTAL});
            }
        }
        
        int result = bfs(blocks);
        cout << "The minimal number of moves to solve puzzle " << p << " is ";
        cout << result << ".\n";
    }
    return 0;
}
