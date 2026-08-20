#include <bits/stdc++.h>
using namespace std;

const int unuse = -2;
const int mix = -1;

struct Node {
    int state;
    Node *son[10];
    Node() {
        state = unuse;
        for (int i = 0; i < 10; i++) son[i] = nullptr;
    }
};

long long pw[12];
vector<string> plans;
int badId;

void update(Node *node, int dep, long long left, long long right, long long ql, long long qr, int id) {
    if (qr < left || right < ql || node->state >= 0) return;
    if (ql <= left && right <= qr && node->state == unuse) {
        node->state = id;
        return;
    }
    if (dep == 11) {
        node->state = id;
        return;
    }
    if (node->state == unuse) node->state = mix;
    long long size = pw[10 - dep];
    for (int i = 0; i < 10; i++) {
        long long nl = left + i * size, nr = nl + size - 1;
        if (qr < nl || nr < ql) continue;
        if (node->son[i] == nullptr) node->son[i] = new Node();
        update(node->son[i], dep + 1, nl, nr, ql, qr, id);
    }
    bool same = true;
    int value = unuse;
    for (int i = 0; i < 10; i++) {
        int cur = node->son[i] == nullptr ? unuse : node->son[i]->state;
        if (cur == mix) {
            same = false;
            break;
        }
        if (i == 0) value = cur;
        else if (value != cur) {
            same = false;
            break;
        }
    }
    if (same) node->state = value;
}

void collect(Node *node, const string &pre, vector<pair<string, string>> &ans) {
    if (node == nullptr || node->state == unuse || node->state == badId) return;
    if (node->state >= 0) {
        ans.push_back({pre, plans[node->state]});
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (node->son[i] == nullptr) continue;
        collect(node->son[i], pre + char('0' + i), ans);
    }
}

int getId(const string &name) {
    for (int i = 0; i < (int)plans.size(); i++)
        if (plans[i] == name) return i;
    plans.push_back(name);
    return (int)plans.size() - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pw[0] = 1;
    for (int i = 1; i <= 11; i++) pw[i] = pw[i - 1] * 10;
    int n, tc = 0;
    while (cin >> n) {
        if (tc++) cout << '\n';
        plans.clear();
        badId = getId("invalid");
        Node *root = new Node();
        for (int i = 0; i < n; i++) {
            string a, dash, b, name;
            cin >> a >> dash >> b >> name;
            int id = getId(name);
            string highPre = a.substr(0, a.size() - b.size()) + b;
            long long scale = pw[11 - a.size()];
            long long left = stoll(a) * scale;
            long long right = (stoll(highPre) + 1) * scale - 1;
            update(root, 0, 0, pw[11] - 1, left, right, id);
        }
        vector<pair<string, string>> ans;
        if (root->state >= 0 && root->state != badId) {
            for (int i = 0; i < 10; i++)
                ans.push_back({string(1, char('0' + i)), plans[root->state]});
        } else if (root->state == mix) {
            collect(root, "", ans);
        }
        cout << ans.size() << '\n';
        for (auto &item : ans)
            cout << item.first << ' ' << item.second << '\n';
    }
    return 0;
}
