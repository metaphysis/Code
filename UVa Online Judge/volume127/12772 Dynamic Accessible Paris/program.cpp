#include <bits/stdc++.h>
using namespace std;

const int maxN = 100005, logN = 18;

struct Edge {
    int to, weight;
};

struct TreapNode {
    int key, left, right, size;
    unsigned int priority;
};

vector<Edge> graph[maxN];
deque<TreapNode> treap;
int up[maxN][logN], depth[maxN], rootDist[maxN], radius[maxN];
int allRoot[maxN], subRoot[maxN], cdParent[maxN], cdSize[maxN];
int firstChild[maxN], prevSibling[maxN], nextSibling[maxN];
int nodeMark[maxN], tempParent[maxN], tempSize[maxN], tempDist[maxN];
int freeHead, markId;
bool removed[maxN];
unsigned int rngState = 712367821u;

unsigned int nextRand() {
    rngState ^= rngState << 13;
    rngState ^= rngState >> 17;
    rngState ^= rngState << 5;
    return rngState;
}

void pull(int root) {
    treap[root].size = treap[treap[root].left].size + treap[treap[root].right].size + 1;
}

int newTreapNode(int key) {
    int root;
    if (freeHead) {
        root = freeHead;
        freeHead = treap[root].left;
    } else {
        root = treap.size();
        treap.push_back(TreapNode{0, 0, 0, 0, 0});
    }
    treap[root] = TreapNode{key, 0, 0, 1, nextRand()};
    return root;
}

void rotateLeft(int &root) {
    int child = treap[root].right;
    treap[root].right = treap[child].left;
    treap[child].left = root;
    pull(root);
    pull(child);
    root = child;
}

void rotateRight(int &root) {
    int child = treap[root].left;
    treap[root].left = treap[child].right;
    treap[child].right = root;
    pull(root);
    pull(child);
    root = child;
}

void insertKey(int &root, int key) {
    if (!root) {
        root = newTreapNode(key);
        return;
    }
    if (key <= treap[root].key) {
        insertKey(treap[root].left, key);
        if (treap[treap[root].left].priority > treap[root].priority) rotateRight(root);
    } else {
        insertKey(treap[root].right, key);
        if (treap[treap[root].right].priority > treap[root].priority) rotateLeft(root);
    }
    pull(root);
}

int countLe(int root, int key) {
    int result = 0;
    while (root) {
        if (treap[root].key <= key) {
            result += treap[treap[root].left].size + 1;
            root = treap[root].right;
        } else {
            root = treap[root].left;
        }
    }
    return result;
}

void recycleTree(int root) {
    if (!root) return;
    recycleTree(treap[root].left);
    recycleTree(treap[root].right);
    treap[root].left = freeHead;
    freeHead = root;
}

int getLca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int bit = 0; bit < logN; ++bit) if ((diff >> bit) & 1) u = up[u][bit];
    if (u == v) return u;
    for (int bit = logN - 1; bit >= 0; --bit) {
        if (up[u][bit] != up[v][bit]) {
            u = up[u][bit];
            v = up[v][bit];
        }
    }
    return up[u][0];
}

int getDist(int u, int v) {
    int ancestor = getLca(u, v);
    return rootDist[u] + rootDist[v] - 2 * rootDist[ancestor];
}

void attachChild(int child, int parent) {
    cdParent[child] = parent;
    prevSibling[child] = 0;
    nextSibling[child] = 0;
    if (!parent) return;
    nextSibling[child] = firstChild[parent];
    if (firstChild[parent]) prevSibling[firstChild[parent]] = child;
    firstChild[parent] = child;
}

void detachChild(int child) {
    int parent = cdParent[child], prev = prevSibling[child], next = nextSibling[child];
    if (prev) nextSibling[prev] = next;
    else if (parent) firstChild[parent] = next;
    if (next) prevSibling[next] = prev;
    prevSibling[child] = nextSibling[child] = 0;
}

bool isActive(int node) {
    return nodeMark[node] == markId && !removed[node];
}

int findCentroid(int start, int &total) {
    vector<int> nodes;
    nodes.push_back(start);
    tempParent[start] = 0;
    for (int pos = 0; pos < (int)nodes.size(); ++pos) {
        int u = nodes[pos];
        tempSize[u] = 1;
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            if (v == tempParent[u] || !isActive(v)) continue;
            tempParent[v] = u;
            nodes.push_back(v);
        }
    }
    total = nodes.size();
    for (int pos = total - 1; pos > 0; --pos) tempSize[tempParent[nodes[pos]]] += tempSize[nodes[pos]];
    int centroid = start, best = total;
    for (int u : nodes) {
        int largest = total - tempSize[u];
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            if (isActive(v) && tempParent[v] == u) largest = max(largest, tempSize[v]);
        }
        if (largest < best) {
            best = largest;
            centroid = u;
        }
    }
    return centroid;
}

int buildBranch(int start, int parent, int weight, int centroid) {
    vector<int> nodes;
    int branchRoot = 0;
    nodes.push_back(start);
    tempParent[start] = parent;
    tempDist[start] = weight;
    for (int pos = 0; pos < (int)nodes.size(); ++pos) {
        int u = nodes[pos], key = tempDist[u] - radius[u];
        insertKey(allRoot[centroid], key);
        insertKey(branchRoot, key);
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            if (v == tempParent[u] || !isActive(v)) continue;
            tempParent[v] = u;
            tempDist[v] = tempDist[u] + edge.weight;
            nodes.push_back(v);
        }
    }
    return branchRoot;
}

void buildDecomposition(int start, int parent, int branchRoot) {
    int total = 0, centroid = findCentroid(start, total);
    removed[centroid] = true;
    cdSize[centroid] = total;
    subRoot[centroid] = branchRoot;
    attachChild(centroid, parent);
    insertKey(allRoot[centroid], -radius[centroid]);
    for (const Edge &edge : graph[centroid]) {
        int v = edge.to;
        if (!isActive(v)) continue;
        int childRoot = buildBranch(v, centroid, edge.weight, centroid);
        buildDecomposition(v, centroid, childRoot);
    }
}

void rebuild(int root) {
    vector<int> nodes;
    int parent = cdParent[root], branchRoot = 0;
    nodes.push_back(root);
    for (int pos = 0; pos < (int)nodes.size(); ++pos) {
        int u = nodes[pos];
        for (int child = firstChild[u]; child; child = nextSibling[child]) nodes.push_back(child);
    }
    detachChild(root);
    ++markId;
    for (int u : nodes) {
        recycleTree(allRoot[u]);
        recycleTree(subRoot[u]);
        allRoot[u] = subRoot[u] = 0;
        firstChild[u] = prevSibling[u] = nextSibling[u] = 0;
        cdParent[u] = 0;
        nodeMark[u] = markId;
        removed[u] = false;
    }
    if (parent) {
        for (int u : nodes) insertKey(branchRoot, getDist(parent, u) - radius[u]);
    }
    buildDecomposition(root, parent, branchRoot);
}

long long queryNode(int node) {
    long long result = 0;
    int child = 0;
    for (int current = node; current; current = cdParent[current]) {
        int limit = radius[node] - getDist(node, current);
        result += countLe(allRoot[current], limit);
        if (child) result -= countLe(subRoot[child], limit);
        child = current;
    }
    return result;
}

void updateNode(int node) {
    for (int current = node; current; current = cdParent[current]) {
        int parent = cdParent[current];
        ++cdSize[current];
        insertKey(allRoot[current], getDist(node, current) - radius[node]);
        if (parent) insertKey(subRoot[current], getDist(node, parent) - radius[node]);
    }
    int badRoot = 0;
    for (int current = node; cdParent[current]; current = cdParent[current]) {
        int parent = cdParent[current];
        if (cdSize[current] * 4 > cdSize[parent] * 3) badRoot = parent;
    }
    if (badRoot) rebuild(badRoot);
}

void initCase(int n) {
    treap.clear();
    treap.push_back(TreapNode{0, 0, 0, 0, 0});
    freeHead = markId = 0;
    for (int i = 1; i <= n; ++i) {
        graph[i].clear();
        allRoot[i] = subRoot[i] = cdParent[i] = cdSize[i] = 0;
        firstChild[i] = prevSibling[i] = nextSibling[i] = nodeMark[i] = 0;
        removed[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseId = 0;
    while (cin >> n && n) {
        initCase(n);
        long long answer = 0;
        cout << "Case " << ++caseId << ":\n";
        for (int i = 1; i <= n; ++i) {
            int encodedParent, weight, range;
            cin >> encodedParent >> weight >> range;
            int parent = encodedParent ^ (int)(answer % 1000000000LL);
            radius[i] = range;
            up[i][0] = parent;
            depth[i] = depth[parent] + 1;
            rootDist[i] = rootDist[parent] + weight;
            for (int bit = 1; bit < logN; ++bit) up[i][bit] = up[up[i][bit - 1]][bit - 1];
            if (parent) {
                graph[parent].push_back(Edge{i, weight});
                graph[i].push_back(Edge{parent, weight});
            }
            attachChild(i, parent);
            answer += queryNode(i);
            updateNode(i);
            cout << answer << '\n';
        }
        cout << '\n';
    }
    return 0;
}
