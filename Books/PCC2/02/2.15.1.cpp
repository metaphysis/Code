#include <bits/stdc++.h>

using namespace std;

const int BLOCK_SIZE = 1024;

typedef struct _BLOCK {
    int size, next;
    char s[BLOCK_SIZE << 1];
} block;

block blk[BLOCK_SIZE << 2];

int cache[BLOCK_SIZE << 2], cp = 0;

int locate(int &idx) {
    int now = 0;
    while (idx > blk[now].size && blk[now].next != -1) {
        idx -= blk[now].size;
        now = blk[now].next;
    }
    return now;
}

int allocate() { return cache[cp++]; }

void recycle(int x) { cache[--cp] = x; }

void initialize() {
    for (int i = 0; i < (BLOCK_SIZE << 2); i++) cache[i] = i;
    cp++;
    blk[0].size = 0, blk[0].next = -1;
}

void append(int x, int y, char s[], int n) {
    if (y != -1) {
        blk[y].next = blk[x].next, blk[y].size = n;
        memcpy(blk[y].s, s, n);
    }
    blk[x].next = y;
}

void merge(int x, int y) {
    if (x == -1 || y == -1) return;
    if (blk[x].size + blk[y].size >= BLOCK_SIZE) return;
    memcpy(blk[x].s + blk[x].size, blk[y].s, blk[y].size);
    blk[x].size += blk[y].size, blk[x].next = blk[y].next;
    recycle(y);
}

void split(int x, int idx) {
    if (x == -1 || idx == blk[x].size) return;
    append(x, allocate(), blk[x].s + idx, blk[x].size - idx);
    blk[x].size = idx;
}

void insert(int idx, char s[], int n) {
    int now = locate(idx);
    if (idx > blk[now].size && blk[now].next == -1) return;
    split(now, idx);
    int inserted = 0, start = now;
    while (inserted + BLOCK_SIZE < n) {
        append(now, allocate(), s + inserted, BLOCK_SIZE);
        inserted += BLOCK_SIZE;
        now = blk[now].next;
    }
    if (inserted < n) append(now, allocate(), s + inserted, n - inserted);
    merge(now, blk[now].next);
    merge(start, blk[start].next);
}

bool erase(int idx, int n) {
    int now = locate(idx);
    if (idx > blk[now].size && blk[now].next == -1) return;
    split(now, idx);
    int end = blk[now].next;
    while (end != -1 && n > blk[end].size) {
        n -= blk[end].size;
        end = blk[end].next;
    }
    split(end, n);
    end = blk[end].next;
    for (int i = blk[now].next; i != end; i = blk[now].next) {
        blk[now].next = blk[i].next;
        recycle(i);
    }
    merge(now, end);
}

void get(int idx, char s[], int n) {
    int now = locate(idx);
    if (idx > blk[now].size && blk[now].next == -1) {
        s[0] = '\0';
        return;
    }
    int copied = min(n, blk[now].size - idx);
    memcpy(s, blk[now].s + idx, copied);
    now = blk[now].next;
    while (now != -1 && n > copied + blk[now].size) {
        memcpy(s + copied, blk[now].s, blk[now].size);
        copied += blk[now].size;
        now = blk[now].next;
    }
    if (copied < n && now != -1) memcpy(s + copied, blk[now].s, n - copied);
    s[n] = '\0';
}

int main(int argc, char *argv[])
{
    return 0;
}
