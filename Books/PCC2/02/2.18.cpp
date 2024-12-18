// binary heap

#include <bits/stdc++.h>

const int MAXN = 1000010;

int cnt, heap[MAXN];

void swim(int n) {
    for (int i = n; i > 1 && heap[i] > heap[i >> 1]; i >>= 1)
        swap(heap[i], heap[i >> 1]);
}

int child(int n) {
    return (n << 1) + ((n << 1) + 1 <= cnt && heap[(n << 1) + 1] > heap[(n << 1)]);
}

void sink(int n) {
    for (int i = n, c = child(i); c <= cnt && heap[c] > heap[i]; i = c, c = child(i))
        swap(heap[i], heap[c]);
}

void push(int x) {
    heap[cnt] = x;
    swim(cnt);
    cnt++;
}

void pop() {
    swap(heap[0], heap[--cnt]);
    sink(0);
}

int top() { return heap[0]; }

void build(int A[], int n) {
    memcpy(heap, a, sizeof(int) * n);
    for (int i = (n >> 1); i >= 0; i--)
        sink(i);
}

int size() { return cnt; }

bool empty() { return !cnt; }

int main(int argc, char* argv[]) {
    return 0;
}
