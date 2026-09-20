#include <bits/stdc++.h>
using namespace std;

struct Requirement {
    int index, amount;
};

struct Block {
    long long benefit, cost;
    __int128 value;
    int left, right, dist;
};

vector<long long> benefits, costs;
vector<vector<Requirement>> requirements;
vector<Block> blocks;

int compareDensity(int a, int b) {
    __int128 leftValue = (__int128)blocks[a].benefit * blocks[b].cost;
    __int128 rightValue = (__int128)blocks[b].benefit * blocks[a].cost;
    if (leftValue < rightValue) return -1;
    if (leftValue > rightValue) return 1;
    return 0;
}

bool heapLess(int a, int b) {
    int result = compareDensity(a, b);
    if (result != 0) return result < 0;
    return a > b;
}

int mergeHeap(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (heapLess(b, a)) swap(a, b);
    blocks[a].right = mergeHeap(blocks[a].right, b);
    if (blocks[blocks[a].left].dist < blocks[blocks[a].right].dist) swap(blocks[a].left, blocks[a].right);
    blocks[a].dist = blocks[blocks[a].right].dist + 1;
    return a;
}

int createBlock(int type) {
    Block block;
    block.benefit = benefits[type];
    block.cost = costs[type];
    block.value = (__int128)benefits[type] * costs[type];
    block.left = block.right = 0;
    block.dist = 1;
    blocks.push_back(block);
    return (int)blocks.size() - 1;
}

void combineBlocks(int first, int second) {
    blocks[second].value = blocks[first].value + blocks[second].value + (__int128)blocks[first].cost * blocks[second].benefit;
    blocks[second].benefit += blocks[first].benefit;
    blocks[second].cost += blocks[first].cost;
}

int buildTree(int type) {
    int heapRoot = 0;
    for (const Requirement &requirement : requirements[type]) {
        for (int i = 0; i < requirement.amount; i++) {
            int childHeap = buildTree(requirement.index);
            heapRoot = mergeHeap(heapRoot, childHeap);
        }
    }
    int current = createBlock(type);
    while (heapRoot != 0 && compareDensity(heapRoot, current) < 0) {
        int previous = heapRoot;
        heapRoot = mergeHeap(blocks[previous].left, blocks[previous].right);
        combineBlocks(previous, current);
    }
    return mergeHeap(heapRoot, current);
}

void printInt128(__int128 value) {
    if (value == 0) {
        cout << '0';
        return;
    }
    if (value < 0) {
        cout << '-';
        value = -value;
    }
    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    cout << result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int typeCount;
        cin >> typeCount;
        benefits.assign(typeCount + 1, 0);
        costs.assign(typeCount + 1, 0);
        requirements.assign(typeCount + 1, vector<Requirement>());
        for (int i = 1; i <= typeCount; i++) {
            int requirementCount;
            cin >> benefits[i] >> costs[i];
            cin >> requirementCount;
            requirements[i].resize(requirementCount);
            for (int j = 0; j < requirementCount; j++) cin >> requirements[i][j].index >> requirements[i][j].amount;
        }
        blocks.clear();
        blocks.reserve(1000001);
        blocks.push_back({0, 0, 0, 0, 0, 0});
        int heapRoot = buildTree(1), suffix = 0;
        while (heapRoot != 0) {
            int current = heapRoot;
            heapRoot = mergeHeap(blocks[current].left, blocks[current].right);
            if (suffix == 0) {
                suffix = current;
            } else {
                combineBlocks(current, suffix);
            }
        }
        __int128 totalProduct = (__int128)blocks[suffix].cost * blocks[suffix].benefit;
        __int128 answer = totalProduct - blocks[suffix].value;
        cout << "Case #" << testCase << ": ";
        printInt128(answer);
        cout << '\n';
    }
    return 0;
}
