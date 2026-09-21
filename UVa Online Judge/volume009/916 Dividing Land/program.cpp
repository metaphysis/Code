#include <bits/stdc++.h>
using namespace std;

using Mask = bitset<100>;

struct Transform {
    array<int, 100> to, from;
};

struct Candidate {
    int transId;
    Mask image, domain;
    array<int, 27> counts;
};

struct Solver {
    int rows, cols, sonCount, cellCount, pieceSize, cellId[10][10];
    vector<int> rowPos, colPos, resource;
    vector<vector<int>> adj;
    vector<Transform> transforms;
    array<int, 27> quota, picked;
    Mask allCells;
    Mask flood(const Mask &allowed, int start) {
        Mask reached;
        int que[100], head = 0, tail = 0;
        que[tail++] = start;
        reached.set(start);
        while (head < tail) {
            int cur = que[head++];
            for (int next : adj[cur]) {
                if (!allowed[next] || reached[next]) continue;
                reached.set(next);
                que[tail++] = next;
            }
        }
        return reached;
    }

    bool checkRemain(Mask left) {
        while (left.any()) {
            int start = 0, size;
            while (!left[start]) ++start;
            Mask component = flood(left, start);
            array<int, 27> counts{};
            size = (int)component.count();
            if (size % pieceSize != 0) return false;
            for (int i = 0; i < cellCount; ++i) if (component[i]) ++counts[resource[i]];
            for (int i = 0; i < 27; ++i) if (counts[i] != quota[i] * (size / pieceSize)) return false;
            left &= ~component;
        }
        return true;
    }

    bool cover(Mask left, int parts, const vector<Mask> &tiles) {
        if (left.none()) return parts == 0;
        if (parts == 0 || !checkRemain(left)) return false;
        if (parts == 1) {
            for (const Mask &tile : tiles) if (tile == left) return true;
            return false;
        }
        vector<int> valid, best;
        for (int i = 0; i < (int)tiles.size(); ++i) if ((tiles[i] & left) == tiles[i]) valid.push_back(i);
        if ((int)valid.size() < parts) return false;
        int bestSize = (int)valid.size() + 1;
        for (int cell = 0; cell < cellCount; ++cell) {
            if (!left[cell]) continue;
            vector<int> options;
            for (int id : valid) if (tiles[id][cell]) options.push_back(id);
            if (options.empty()) return false;
            if ((int)options.size() < bestSize) {
                bestSize = (int)options.size();
                best.swap(options);
            }
            if (bestSize == 1) break;
        }
        for (int id : best) if (cover(left & ~tiles[id], parts - 1, tiles)) return true;
        return false;
    }

    bool finish(const Mask &shape, const vector<Candidate> &candidates) {
        vector<Mask> tiles;
        set<pair<unsigned long long, unsigned long long>> seen;
        for (const Candidate &candidate : candidates) {
            unsigned long long high = (candidate.image >> 50).to_ullong(), low = ((candidate.image << 50) >> 50).to_ullong();
            if (seen.insert(make_pair(high, low)).second) tiles.push_back(candidate.image);
        }
        if ((int)tiles.size() < sonCount - 1) return false;
        return cover(allCells & ~shape, sonCount - 1, tiles);
    }

    bool searchShape(Mask shape, Mask frontier, Mask excluded, int size, vector<Candidate> candidates) {
        if ((int)candidates.size() < sonCount - 1) return false;
        if (size == pieceSize) return finish(shape, candidates);
        if (frontier.none()) return false;
        Mask reachable = flood(allCells & ~excluded, 0);
        array<int, 27> available{};
        if ((int)reachable.count() < pieceSize) return false;
        for (int i = 0; i < cellCount; ++i) if (reachable[i]) ++available[resource[i]];
        for (int i = 0; i < 27; ++i) if (available[i] < quota[i]) return false;
        int kept = 0;
        for (int i = 0; i < (int)candidates.size(); ++i) {
            if ((int)(candidates[i].domain & reachable).count() < pieceSize) continue;
            if (kept != i) candidates[kept] = move(candidates[i]);
            ++kept;
        }
        candidates.resize(kept);
        if (kept < sonCount - 1) return false;
        int cell = 0, kind;
        while (!frontier[cell]) ++cell;
        kind = resource[cell];
        frontier.reset(cell);
        if (picked[kind] < quota[kind]) {
            Mask nextShape = shape, nextFrontier = frontier;
            vector<Candidate> nextCandidates;
            nextShape.set(cell);
            for (int next : adj[cell]) if (!nextShape[next] && !excluded[next]) nextFrontier.set(next);
            nextCandidates.reserve(candidates.size());
            for (const Candidate &candidate : candidates) {
                if (!candidate.domain[cell]) continue;
                const Transform &trans = transforms[candidate.transId];
                int mapped = trans.to[cell], mappedKind = resource[mapped], preimage = trans.from[cell];
                if (candidate.counts[mappedKind] >= quota[mappedKind]) continue;
                Candidate nextCandidate = candidate;
                nextCandidate.image.set(mapped);
                nextCandidate.domain.reset(mapped);
                if (preimage != -1) nextCandidate.domain.reset(preimage);
                ++nextCandidate.counts[mappedKind];
                if ((nextCandidate.image & nextShape).any()) continue;
                if ((int)(nextCandidate.domain & reachable).count() < pieceSize) continue;
                nextCandidates.push_back(move(nextCandidate));
            }
            ++picked[kind];
            bool found = searchShape(nextShape, nextFrontier, excluded, size + 1, move(nextCandidates));
            --picked[kind];
            if (found) return true;
        }
        excluded.set(cell);
        return searchShape(shape, frontier, excluded, size, move(candidates));
    }

    bool solve(const vector<string> &grid, int sons) {
        rows = (int)grid.size();
        cols = (int)grid[0].size();
        sonCount = sons;
        cellCount = 0;
        quota.fill(0);
        picked.fill(0);
        allCells.reset();
        rowPos.clear();
        colPos.clear();
        resource.clear();
        transforms.clear();
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                cellId[row][col] = -1;
                if (grid[row][col] == '#') continue;
                int kind = grid[row][col] == '.' ? 26 : grid[row][col] - 'A';
                cellId[row][col] = cellCount++;
                rowPos.push_back(row);
                colPos.push_back(col);
                resource.push_back(kind);
                ++quota[kind];
            }
        }
        if (cellCount == 0 || cellCount % sonCount != 0) return false;
        pieceSize = cellCount / sonCount;
        for (int i = 0; i < 27; ++i) {
            if (quota[i] % sonCount != 0) return false;
            quota[i] /= sonCount;
        }
        adj.assign(cellCount, vector<int>());
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        for (int i = 0; i < cellCount; ++i) {
            allCells.set(i);
            for (int dir = 0; dir < 4; ++dir) {
                int nextRow = rowPos[i] + dr[dir], nextCol = colPos[i] + dc[dir];
                if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) continue;
                if (cellId[nextRow][nextCol] != -1) adj[i].push_back(cellId[nextRow][nextCol]);
            }
        }
        if (sonCount == 1) return (int)flood(allCells, 0).count() == cellCount;
        if (!checkRemain(allCells)) return false;
        if (quota[resource[0]] == 0) return false;
        vector<Candidate> candidates;
        for (int dir = 0; dir < 8; ++dir) {
            for (int target = 1; target < cellCount; ++target) {
                if (quota[resource[target]] == 0) continue;
                Transform trans;
                Candidate candidate;
                trans.to.fill(-1);
                trans.from.fill(-1);
                candidate.counts.fill(0);
                for (int cell = 0; cell < cellCount; ++cell) {
                    int dx = rowPos[cell] - rowPos[0], dy = colPos[cell] - colPos[0];
                    if (dir >= 4) dy = -dy;
                    for (int turn = 0; turn < dir % 4; ++turn) {
                        int temp = dx;
                        dx = -dy;
                        dy = temp;
                    }
                    int nextRow = rowPos[target] + dx, nextCol = colPos[target] + dy;
                    if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) continue;
                    int mapped = cellId[nextRow][nextCol];
                    if (mapped == -1) continue;
                    trans.to[cell] = mapped;
                    trans.from[mapped] = cell;
                    if (mapped != cell) candidate.domain.set(cell);
                }
                candidate.image.set(target);
                candidate.domain.reset(target);
                if (trans.from[0] != -1) candidate.domain.reset(trans.from[0]);
                if (!candidate.domain[0]) continue;
                candidate.domain = flood(candidate.domain, 0);
                if ((int)candidate.domain.count() < pieceSize) continue;
                candidate.transId = (int)transforms.size();
                ++candidate.counts[resource[target]];
                transforms.push_back(trans);
                candidates.push_back(move(candidate));
            }
        }
        Mask shape, frontier, excluded;
        shape.set(0);
        for (int next : adj[0]) frontier.set(next);
        ++picked[resource[0]];
        return searchShape(shape, frontier, excluded, 1, move(candidates));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int rows, cols, sons;
        cin >> rows >> cols >> sons;
        vector<string> grid(rows);
        for (string &row : grid) cin >> row;
        Solver solver;
        cout << (solver.solve(grid, sons) ? "Yes" : "No") << '\n';
    }
    return 0;
}
