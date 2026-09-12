#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long start, len, maxLen;
    unsigned pri;
    Node *left, *right;
    Node(long long s, long long l, unsigned p) : start(s), len(l), maxLen(l), pri(p), left(nullptr), right(nullptr) {}
};

struct Req {
    long long m, p;
    int id;
};

struct Event {
    long long time, start, len;
    bool operator < (const Event &other) const {
        return time > other.time;
    }
};

mt19937 rng(712367821);

long long getMax(Node *root) {
    if (root == nullptr) return 0;
    return root->maxLen;
}

void pushUp(Node *root) {
    if (root == nullptr) return;
    root->maxLen = max(root->len, max(getMax(root->left), getMax(root->right)));
}

void split(Node *root, long long key, Node *&left, Node *&right) {
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    if (root->start < key) {
        left = root;
        split(root->right, key, left->right, right);
        pushUp(left);
    } else {
        right = root;
        split(root->left, key, left, right->left);
        pushUp(right);
    }
}

Node *mergeTree(Node *left, Node *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    if (left->pri > right->pri) {
        left->right = mergeTree(left->right, right);
        pushUp(left);
        return left;
    }
    right->left = mergeTree(left, right->left);
    pushUp(right);
    return right;
}

void insertNode(Node *&root, Node *node) {
    if (root == nullptr) {
        root = node;
        return;
    }
    if (node->pri > root->pri) {
        split(root, node->start, node->left, node->right);
        root = node;
        pushUp(root);
        return;
    }
    if (node->start < root->start) insertNode(root->left, node);
    else insertNode(root->right, node);
    pushUp(root);
}

void eraseNode(Node *&root, long long key) {
    if (root == nullptr) return;
    if (root->start == key) {
        Node *old = root;
        root = mergeTree(root->left, root->right);
        delete old;
        return;
    }
    if (key < root->start) eraseNode(root->left, key);
    else eraseNode(root->right, key);
    pushUp(root);
}

Node *findPrev(Node *root, long long key) {
    Node *ans = nullptr;
    while (root != nullptr) {
        if (root->start < key) {
            ans = root;
            root = root->right;
        } else root = root->left;
    }
    return ans;
}

Node *findNext(Node *root, long long key) {
    Node *ans = nullptr;
    while (root != nullptr) {
        if (root->start > key) {
            ans = root;
            root = root->left;
        } else root = root->right;
    }
    return ans;
}

Node *findFirst(Node *root, long long need) {
    if (root == nullptr || root->maxLen < need) return nullptr;
    if (getMax(root->left) >= need) return findFirst(root->left, need);
    if (root->len >= need) return root;
    return findFirst(root->right, need);
}

bool allocateBlock(Node *&root, long long need, long long &start) {
    Node *node = findFirst(root, need);
    if (node == nullptr) return false;
    start = node->start;
    long long len = node->len;
    eraseNode(root, start);
    if (len > need) insertNode(root, new Node(start + need, len - need, rng()));
    return true;
}

void freeBlock(Node *&root, long long start, long long len) {
    Node *prev = findPrev(root, start);
    if (prev != nullptr && prev->start + prev->len == start) {
        long long oldStart = prev->start, oldLen = prev->len;
        eraseNode(root, oldStart);
        start = oldStart;
        len += oldLen;
    }
    Node *next = findNext(root, start);
    if (next != nullptr && start + len == next->start) {
        long long oldStart = next->start, oldLen = next->len;
        eraseNode(root, oldStart);
        len += oldLen;
    }
    insertNode(root, new Node(start, len, rng()));
}

void allocateWait(Node *&root, deque<Req> &wait, priority_queue<Event> &events, long long time, int printEvent) {
    while (!wait.empty()) {
        long long start;
        if (!allocateBlock(root, wait.front().m, start)) break;
        Req req = wait.front();
        wait.pop_front();
        if (printEvent) cout << time << " " << req.id << " " << start << "\n";
        events.push({time + req.p, start, req.m});
    }
}

void processFinish(Node *&root, deque<Req> &wait, priority_queue<Event> &events, long long limit, int printEvent, long long &lastTime) {
    while (!events.empty() && events.top().time <= limit) {
        long long time = events.top().time;
        while (!events.empty() && events.top().time == time) {
            Event event = events.top();
            events.pop();
            freeBlock(root, event.start, event.len);
        }
        allocateWait(root, wait, events, time, printEvent);
        lastTime = time;
    }
}

void destroy(Node *root) {
    if (root == nullptr) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, t, m, p;
    int b;
    while (cin >> n >> b) {
        Node *root = new Node(0, n, rng());
        deque<Req> wait;
        priority_queue<Event> events;
        long long lastTime = 0;
        int id = 0, queued = 0;
        while (cin >> t >> m >> p) {
            if (t == 0 && m == 0 && p == 0) break;
            processFinish(root, wait, events, t, b, lastTime);
            ++id;
            long long start;
            if (allocateBlock(root, m, start)) {
                if (b) cout << t << " " << id << " " << start << "\n";
                events.push({t + p, start, m});
            } else {
                wait.push_back({m, p, id});
                ++queued;
            }
        }
        processFinish(root, wait, events, LLONG_MAX, b, lastTime);
        cout << lastTime << "\n" << queued << "\n\n";
        destroy(root);
    }
    return 0;
}
