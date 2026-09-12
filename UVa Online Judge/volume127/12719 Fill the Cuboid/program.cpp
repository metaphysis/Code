#include <bits/stdc++.h>
using namespace std;

struct Mask {
    uint64_t low, high;
};

struct Bits {
    uint64_t low, high;
};

struct State {
    uint64_t low, high;
    bool operator == (const State &other) const {
        return low == other.low && high == other.high;
    }
};

struct StateHash {
    size_t operator () (const State &state) const {
        uint64_t value = state.low + 0x9e3779b97f4a7c15ULL;
        value ^= state.high + 0x9e3779b97f4a7c15ULL + (value << 6) + (value >> 2);
        value ^= value >> 30;
        value *= 0xbf58476d1ce4e5b9ULL;
        value ^= value >> 27;
        value *= 0x94d049bb133111ebULL;
        value ^= value >> 31;
        return (size_t)value;
    }
};

int a, b, c, total;
vector<Mask> cubes;
vector<int> places[125];
unordered_map<State, Bits, StateHash> memo;

int getId(int x, int y, int z) {
    return x * b * c + y * c + z;
}

void setBit(Mask &mask, int id) {
    if (id < 64) mask.low |= 1ULL << id;
    else mask.high |= 1ULL << (id - 64);
}

void setBit(State &state, int id) {
    if (id < 64) state.low |= 1ULL << id;
    else state.high |= 1ULL << (id - 64);
}

bool isUsed(const State &state, int id) {
    if (id < 64) return (state.low >> id) & 1ULL;
    return (state.high >> (id - 64)) & 1ULL;
}

bool canPlace(const State &state, const Mask &mask) {
    if ((state.low & mask.low) != 0) return false;
    if ((state.high & mask.high) != 0) return false;
    return true;
}

State putCube(const State &state, const Mask &mask) {
    State next = state;
    next.low |= mask.low;
    next.high |= mask.high;
    return next;
}

Bits shiftBits(const Bits &bits) {
    Bits result;
    result.low = bits.low << 1;
    result.high = (bits.high << 1) | (bits.low >> 63);
    return result;
}

void buildCubes() {
    cubes.clear();
    for (int i = 0; i < 125; i++) places[i].clear();
    for (int x = 0; x < a; x++)
        for (int y = 0; y < b; y++)
            for (int z = 0; z < c; z++) {
                int maxSize = min(a - x, min(b - y, c - z));
                for (int size = 1; size <= maxSize; size++) {
                    Mask mask = {0, 0};
                    for (int dx = 0; dx < size; dx++)
                        for (int dy = 0; dy < size; dy++)
                            for (int dz = 0; dz < size; dz++)
                                setBit(mask, getId(x + dx, y + dy, z + dz));
                    int cubeId = (int)cubes.size();
                    cubes.push_back(mask);
                    for (int dx = 0; dx < size; dx++)
                        for (int dy = 0; dy < size; dy++)
                            for (int dz = 0; dz < size; dz++)
                                places[getId(x + dx, y + dy, z + dz)].push_back(cubeId);
                }
            }
}

Bits search(const State &state, int freeCount) {
    auto it = memo.find(state);
    if (it != memo.end()) return it->second;
    if (freeCount == 0) {
        Bits result = {1, 0};
        memo[state] = result;
        return result;
    }
    int selected = -1, best = INT_MAX;
    for (int cell = 0; cell < total; cell++) {
        if (isUsed(state, cell)) continue;
        int count = 0;
        for (int cubeId : places[cell])
            if (canPlace(state, cubes[cubeId])) count++;
        if (count == 0) {
            Bits result = {0, 0};
            memo[state] = result;
            return result;
        }
        if (count < best) {
            best = count;
            selected = cell;
            if (best == 1) break;
        }
    }
    Bits answer = {0, 0};
    for (int cubeId : places[selected]) {
        const Mask &mask = cubes[cubeId];
        if (!canPlace(state, mask)) continue;
        State next = putCube(state, mask);
        int cubeVolume = __builtin_popcountll(mask.low) + __builtin_popcountll(mask.high);
        Bits child = search(next, freeCount - cubeVolume);
        Bits shifted = shiftBits(child);
        answer.low |= shifted.low;
        answer.high |= shifted.high;
    }
    memo[state] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, caseId = 1;
    while (cin >> a >> b >> c >> m) {
        if (a == 0 && b == 0 && c == 0 && m == 0) break;
        total = a * b * c;
        State initial = {0, 0};
        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            setBit(initial, getId(x - 1, y - 1, z - 1));
        }
        buildCubes();
        memo.clear();
        memo.reserve(1 << 18);
        Bits answer = search(initial, total - m);
        cout << "Case " << caseId++ << ":";
        for (int i = 1; i <= total; i++) {
            bool possible;
            if (i < 64) possible = (answer.low >> i) & 1ULL;
            else possible = (answer.high >> (i - 64)) & 1ULL;
            if (possible) cout << " " << i;
        }
        cout << "\n";
    }
    return 0;
}
