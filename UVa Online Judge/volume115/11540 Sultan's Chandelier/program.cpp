// Sultan's Chandelier
// UVa ID: 11540
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.050s

#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;

map<vector<int>, int> idMap;
vector<long long> ways;
string tree;
int indexPos;
int colorCount;

long long modPow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

vector<int> getCanonical(const vector<int> &child) {
    int size = child.size();
    vector<int> best = child;
    for (int shift = 1; shift < size; shift++) {
        vector<int> current;
        for (int i = 0; i < size; i++)
            current.push_back(child[(i + shift) % size]);
        if (current < best) best = current;
    }
    return best;
}

int getId(const vector<int> &child) {
    vector<int> canonical = getCanonical(child);
    auto iter = idMap.find(canonical);
    if (iter != idMap.end()) return iter->second;
    int id = ways.size();
    idMap[canonical] = id;
    ways.push_back(0);
    return id;
}

int parseTree() {
    indexPos++;
    vector<int> child;
    while (tree[indexPos] != ']') {
        if (tree[indexPos] == ',') {
            indexPos++;
        } else {
            child.push_back(parseTree());
        }
    }
    indexPos++;
    int id = getId(child);
    int size = child.size();
    long long fixedSum = 0;
    int symmetry = 0;
    for (int shift = 0; shift < max(1, size); shift++) {
        bool same = true;
        for (int i = 0; i < size; i++) {
            if (child[i] != child[(i + shift) % size]) {
                same = false;
                break;
            }
        }
        if (!same) continue;
        symmetry++;
        vector<char> visited(size, 0);
        long long fixed = 1;
        for (int i = 0; i < size; i++) {
            if (visited[i]) continue;
            int current = i;
            long long count = 1;
            while (!visited[current]) {
                visited[current] = 1;
                current = (current + shift) % size;
            }
            count = ways[child[i]];
            fixed = fixed * count % mod;
        }
        fixedSum = (fixedSum + fixed) % mod;
    }
    ways[id] = colorCount * fixedSum % mod * modPow(symmetry, mod - 2) % mod;
    return id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> tree >> colorCount;
        indexPos = 0;
        idMap.clear();
        ways.clear();
        int root = parseTree();
        cout << "Case #" << cs << ": " << ways[root] << '\n';
    }
    return 0;
}
