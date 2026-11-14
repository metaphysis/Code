#include <bits/stdc++.h>

using namespace std;

const int BLOCK_SIZE = 2000;

struct block {
    string s;
    block *next;
};

block *head = new block;

int idx;
int cursor = 0;

block* locate() {
    idx = cursor;
    block *now = head;
    while (idx > now->s.size() && now->next != nullptr) {
        idx -= now->s.size();
        now = now->next;
    }
    return now;
}

pair<block*, block*> build(string s) {
    int cnt = 0, n = s.size();
    block *first = nullptr, *last = nullptr;
    while (cnt < n) {
        block *tmp = new block;
        tmp->next = nullptr;
        tmp->s.insert(tmp->s.end(), s.begin() + cnt, s.begin() + min(n, cnt + BLOCK_SIZE));
        if (first == nullptr) first = tmp;
        else last->next = tmp;
        last = tmp;
        cnt += BLOCK_SIZE;
    }
    return make_pair(first, last);
}

bool merge(block *b1, block *b2) {
    if (b1 == b2) return false;
    if (b1 == nullptr || b2 == nullptr) return false;
    if (b1->s.size() + b2->s.size() >= 2 * BLOCK_SIZE) return false;
    b1->s.insert(b1->s.end(), b2->s.begin(), b2->s.end());
    b1->next = b2->next;
    delete b2;
    return true;
}

pair<block*, block*> split(block *now, int idx) {
    block *tmp = new block;
    tmp->next = nullptr;
    tmp->s.insert(tmp->s.end(), now->s.begin() + idx, now->s.end());
    now->s.erase(now->s.begin() + idx, now->s.end());
    tmp->next = now->next;
    now->next = tmp;
    return make_pair(now, tmp);
}

void insert() {
    int n;
    cin >> n;

    string s, line;
    cin.ignore(256, '\n');
    while (n > 0) {
        getline(cin, line);
        while (line.back() < 32 || line.back() > 126) line.pop_back();
        s += line;
        n -= line.length();
    }

    block *now = locate();
    if (now->s.size() + s.size() < 2 * BLOCK_SIZE)
        now->s.insert(now->s.begin() + idx, s.begin(), s.end());
    else {
        pair<block*, block*> p1 = split(now, idx);
        pair<block*, block*> p2 = build(s);
        p1.first->next = p2.first;
        p2.second->next = p1.second;
        if (p2.first == p2.second) {
            if (!merge(p1.first, p2.first))
                merge(p2.first, p1.second);
        } else {
            merge(p1.first, p2.first);
            merge(p2.second, p1.second);
        }
    }
}

void erase() {
    int n;
    cin >> n;
    block *now = locate();
    split(now, idx);
    block *end = now->next;
    while (end != nullptr && n > end->s.size()) {
        n -= end->s.size();
        end = end->next;
    }
    split(end, n);
    end = end->next;
    for (block *i = now->next; i != end; i = now->next) {
        now->next = i->next;
        delete i;
    }
    merge(now, end);
}

void get() {
    int n;
    cin >> n;
    block *now = locate();
    while (n) {
        if (idx + n < now->s.size()) {
            cout << now->s.substr(idx, n);
            n = 0;
        } else {
            if (idx) {
                cout << now->s.substr(idx);
                n -= now->s.size() - idx;
                idx = 0;
            } else {
                cout << now->s;
                n -= now->s.size();
            }
        }
        now = now->next;
    }
    cout << '\n';
}

void destroy(block *now) {
    if (now != nullptr) {
        if (now->next != nullptr) destroy(now->next);
        delete now;
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int t;
    cin >> t;
    string cmd;
    for (int i = 1; i <= t; i++) {
        cin >> cmd;
        if (cmd == "Insert")        insert();
        else if (cmd == "Delete")   erase();
        else if (cmd == "Get")      get();
        else if (cmd == "Move")     cin >> cursor;
        else if (cmd == "Prev")     cursor--;
        else if (cmd == "Next")     cursor++;
    }
    destroy(head);

    return 0;
}
