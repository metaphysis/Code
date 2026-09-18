#include <bits/stdc++.h>
using namespace std;

const int maxT = 6, maxV = 25, maxMoves = 1050, tableSize = 1 << 18;

struct Move {
    long long damage;
    int id, nearDist;
};

struct Entry {
    long long hp[maxT], value;
    uint64_t code;
    int bestMove, depth, flag;
};

int n, m, maxDepth, soldierCount, pace[3], owner[maxT], kind[maxT], pos[maxT];
long long hp[maxT];
uint32_t boardMask, landMask, plainMask, leftMask, rightMask, attackMask[3][maxV];
vector<Entry> table;

uint64_t mixBits(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

uint32_t expandMask(uint32_t mask) {
    return (((mask & ~leftMask) >> 1) | ((mask & ~rightMask) << 1) | (mask >> m) | (mask << m)) & boardMask;
}

uint32_t getReach(int id, uint32_t ownMask, uint32_t enemyMask) {
    uint32_t startMask = 1U << pos[id], seen = startMask, front = startMask;
    uint32_t allowed = (kind[id] == 1 ? plainMask : landMask) & ~enemyMask;
    for (int step = 0; step < pace[kind[id]] && front; ++step) {
        front = expandMask(front) & allowed & ~seen;
        seen |= front;
    }
    return seen & ~(ownMask ^ startMask);
}

void buildAttack() {
    memset(attackMask, 0, sizeof(attackMask));
    for (int from = 0; from < n * m; ++from) {
        for (int to = 0; to < n * m; ++to) {
            int dx = abs(from / m - to / m), dy = abs(from % m - to % m);
            if (dx + dy == 0) continue;
            if (max(dx, dy) <= 1) attackMask[0][from] |= 1U << to;
            if (dx + dy == 1) attackMask[1][from] |= 1U << to;
            if (max(dx, dy) <= 1 || dx + dy == 2) attackMask[2][from] |= 1U << to;
        }
    }
}

long long getDamage(int from, int to) {
    long long damage = hp[from];
    if ((kind[from] + 2) % 3 == kind[to]) damage *= 2;
    else if (kind[from] != kind[to]) damage /= 2;
    return min(damage, hp[to]);
}

uint64_t getCode(int side) {
    uint64_t code = static_cast<uint64_t>(side) << 30;
    for (int i = 0; i < soldierCount; ++i) code |= static_cast<uint64_t>(hp[i] > 0 ? pos[i] : 31) << (i * 5);
    return code;
}

int getIndex(uint64_t code) {
    uint64_t hashValue = mixBits(code);
    for (int i = 0; i < soldierCount; ++i) hashValue ^= mixBits(static_cast<uint64_t>(hp[i]) + 0x9e3779b97f4a7c15ULL * (i + 1));
    return static_cast<int>(hashValue & (tableSize - 1));
}

bool sameState(const Entry &entry, uint64_t code) {
    if (entry.flag == 0 || entry.code != code) return false;
    for (int i = 0; i < soldierCount; ++i) if (entry.hp[i] != hp[i]) return false;
    return true;
}

void saveEntry(int index, uint64_t code, int depth, long long value, int flag, int bestMove) {
    Entry &entry = table[index];
    entry.code = code;
    entry.depth = depth;
    entry.value = value;
    entry.flag = flag;
    entry.bestMove = bestMove;
    for (int i = 0; i < soldierCount; ++i) entry.hp[i] = hp[i];
}

long long search(int depth, int side, long long alpha, long long beta) {
    long long ownSum = 0, enemySum = 0;
    uint32_t ownMask = 0, enemyMask = 0;
    for (int i = 0; i < soldierCount; ++i) {
        if (hp[i] == 0) continue;
        if (owner[i] == side) {
            ownSum += hp[i];
            ownMask |= 1U << pos[i];
        } else {
            enemySum += hp[i];
            enemyMask |= 1U << pos[i];
        }
    }
    if (depth == 0 || ownSum == 0 || enemySum == 0) return ownSum - enemySum;
    if (ownSum <= alpha) return ownSum;
    if (-enemySum >= beta) return -enemySum;
    long long oldAlpha = alpha, oldBeta = beta;
    uint64_t code = getCode(side);
    int index = getIndex(code), hashMove = -1;
    if (sameState(table[index], code)) {
        const Entry &entry = table[index];
        hashMove = entry.bestMove;
        if (entry.depth == depth) {
            if (entry.flag == 1) return entry.value;
            if (entry.flag == 2) alpha = max(alpha, entry.value);
            else beta = min(beta, entry.value);
            if (alpha >= beta) return entry.value;
        }
    }
    Move moves[maxMoves];
    int moveCount = 0, bestMove = -1;
    long long bestDamage = 0;
    bool hasWait = false;
    for (int i = 0; i < soldierCount; ++i) {
        if (hp[i] == 0 || owner[i] != side) continue;
        uint32_t reach = getReach(i, ownMask, enemyMask);
        while (reach) {
            int dest = __builtin_ctz(reach), nearDist = maxV;
            reach &= reach - 1;
            uint32_t targets = attackMask[kind[i]][dest] & enemyMask;
            for (int j = 0; j < soldierCount; ++j) {
                if (hp[j] == 0 || owner[j] == side) continue;
                if (depth > 1) nearDist = min(nearDist, abs(dest / m - pos[j] / m) + abs(dest % m - pos[j] % m));
                if ((targets & (1U << pos[j])) == 0) continue;
                long long damage = getDamage(i, j);
                if (damage == 0) continue;
                int moveId = i | (dest << 3) | (j << 8);
                if (damage > bestDamage) {
                    bestDamage = damage;
                    bestMove = moveId;
                }
                if (depth > 1) moves[moveCount++] = Move{damage, moveId, 0};
            }
            if (depth == 1) continue;
            if (dest == pos[i]) {
                if (hasWait) continue;
                hasWait = true;
            }
            int moveId = i | (dest << 3) | (maxT << 8);
            moves[moveCount++] = Move{0, moveId, nearDist};
        }
    }
    if (depth == 1) {
        long long value = ownSum - enemySum + bestDamage;
        saveEntry(index, code, depth, value, 1, bestMove);
        return value;
    }
    sort(moves, moves + moveCount, [hashMove](const Move &a, const Move &b) {
        bool aFirst = a.id == hashMove, bFirst = b.id == hashMove;
        if (aFirst != bFirst) return aFirst;
        if (a.damage != b.damage) return a.damage > b.damage;
        if (a.nearDist != b.nearDist) return a.nearDist < b.nearDist;
        return a.id < b.id;
    });
    long long bestValue = numeric_limits<long long>::lowest();
    for (int i = 0; i < moveCount; ++i) {
        int moveId = moves[i].id, id = moveId & 7, dest = (moveId >> 3) & 31, target = (moveId >> 8) & 7, oldPos = pos[id];
        pos[id] = dest;
        if (target < soldierCount) hp[target] -= moves[i].damage;
        long long value = -search(depth - 1, side ^ 1, -beta, -alpha);
        if (target < soldierCount) hp[target] += moves[i].damage;
        pos[id] = oldPos;
        if (value > bestValue) {
            bestValue = value;
            bestMove = moveId;
        }
        alpha = max(alpha, bestValue);
        if (alpha >= beta) break;
    }
    int flag = 1;
    if (bestValue <= oldAlpha) flag = 3;
    else if (bestValue >= oldBeta) flag = 2;
    saveEntry(index, code, depth, bestValue, flag, bestMove);
    return bestValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> maxDepth) {
        if (n == 0 && m == 0 && maxDepth == 0) break;
        boardMask = (1U << (n * m)) - 1;
        landMask = plainMask = leftMask = rightMask = 0;
        for (int row = 0; row < n; ++row) {
            leftMask |= 1U << (row * m);
            rightMask |= 1U << (row * m + m - 1);
            for (int col = 0; col < m; ++col) {
                int terrain, cell = row * m + col;
                cin >> terrain;
                if (terrain != 2) landMask |= 1U << cell;
                if (terrain == 0) plainMask |= 1U << cell;
            }
        }
        cin >> soldierCount >> pace[0] >> pace[1] >> pace[2];
        for (int i = 0; i < 3; ++i) pace[i] = min(pace[i], n * m - 1);
        long long total = 0, answer = 0;
        for (int i = 0; i < soldierCount; ++i) {
            int row, col;
            cin >> row >> col >> owner[i] >> hp[i] >> kind[i];
            pos[i] = (row - 1) * m + col - 1;
            total += hp[i];
        }
        buildAttack();
        table.assign(tableSize, Entry{});
        for (int depth = 1; depth <= maxDepth; ++depth) answer = search(depth, 0, -total - 1, total + 1);
        cout << answer << '\n';
    }
    return 0;
}
