#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int cnt = 0;                 // 堆中元素个数
int heap[MAXN];              // 0-based 小根堆，有效下标 0 .. cnt-1

// 上浮：小根堆中，若当前结点小于父结点则交换
void swim(int n) {
    for (int i = n; i > 0 && heap[i] < heap[(i - 1) >> 1]; i = (i - 1) >> 1) {
        swap(heap[i], heap[(i - 1) >> 1]);
    }
}

// 返回结点 n 的较小子结点编号；若只有左儿子，则返回左儿子
int child(int n) {
    int left = (n << 1) + 1;
    int right = left + 1;
    if (right < cnt && heap[right] < heap[left]) return right;
    return left;
}

// 下沉：小根堆中，若当前结点大于较小子结点则交换
void sink(int n) {
    for (int i = n, c = child(i); c < cnt && heap[c] < heap[i]; i = c, c = child(i)) {
        swap(heap[i], heap[c]);
    }
}

// 插入元素：放到堆尾，然后上浮
void push(int x) {
    heap[cnt++] = x;
    swim(cnt - 1);
}

// 删除堆顶：用最后一个元素覆盖堆顶，缩小堆后下沉
void pop() {
    if (cnt == 0) return;
    heap[0] = heap[--cnt];
    if (cnt > 0) sink(0);
}

// 查询堆顶
int top() {
    return heap[0];
}

// 建堆：A 为 0-based 数组，长度为 n
void build(int A[], int n) {
    cnt = n;
    for (int i = 0; i < n; ++i) heap[i] = A[i];
    for (int i = n / 2 - 1; i >= 0; --i) sink(i);
}

// 返回堆的大小
int size() {
    return cnt;
}

// 返回堆是否为空
bool empty() {
    return cnt == 0;
}

// =============================================================
// 随机验证测试
// =============================================================

// 测试 1：动态 push/pop/top/size/empty 与 STL 小根堆对拍
bool testDynamic(int TEST_CASES) {
    mt19937 rng(20241106u);
    for (int tc = 1; tc <= TEST_CASES; ++tc) {
        cnt = 0;
        priority_queue<int, vector<int>, greater<int>> pq;
        int ops = (int)(rng() % 200) + 1;
        for (int k = 0; k < ops; ++k) {
            int op = (int)(rng() % 4);
            if (op == 0 || pq.empty()) {
                int x = (int)(rng() % 2001) - 1000;
                push(x);
                pq.push(x);
            } else if (op == 1) {
                pq.pop();
                pop();
            } else if (op == 2) {
                if (!pq.empty() && top() != pq.top()) {
                    cerr << "testDynamic failed: tc=" << tc
                         << " op=top, expected=" << pq.top()
                         << " got=" << top() << "\n";
                    return false;
                }
            } else {
                if (size() != (int)pq.size()) {
                    cerr << "testDynamic failed: tc=" << tc
                         << " op=size, expected=" << pq.size()
                         << " got=" << size() << "\n";
                    return false;
                }
                if (empty() != pq.empty()) {
                    cerr << "testDynamic failed: tc=" << tc
                         << " op=empty mismatch\n";
                    return false;
                }
            }
        }
    }
    return true;
}

// 测试 2：build 后连续 pop 得到非降序且与排序结果一致
bool testBuild(int TEST_CASES) {
    mt19937 rng(20241106u + 1);
    for (int tc = 1; tc <= TEST_CASES; ++tc) {
        int n = (int)(rng() % 100) + 1;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) a[i] = (int)(rng() % 2001) - 1000;
        build(a.data(), n);
        vector<int> popped;
        popped.reserve(n);
        while (!empty()) {
            popped.push_back(top());
            pop();
        }
        vector<int> sorted = a;
        sort(sorted.begin(), sorted.end());
        if (popped != sorted) {
            cerr << "testBuild failed: tc=" << tc << "\n";
            cerr << "original: ";
            for (int x : a) cerr << x << " ";
            cerr << "\npopped: ";
            for (int x : popped) cerr << x << " ";
            cerr << "\nsorted: ";
            for (int x : sorted) cerr << x << " ";
            cerr << "\n";
            return false;
        }
    }
    return true;
}

bool runTests() {
    const int T1 = 3000;
    const int T2 = 3000;
    if (!testDynamic(T1)) {
        cerr << "Dynamic tests failed.\n";
        return false;
    }
    cout << "All " << T1 << " dynamic tests passed.\n";
    if (!testBuild(T2)) {
        cerr << "Build tests failed.\n";
        return false;
    }
    cout << "All " << T2 << " build tests passed.\n";
    return true;
}

#define DEBUG

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef DEBUG
        return runTests() ? 0 : 1;
    #endif
    int a[] = {5, 3, 8};
    build(a, 3);
    cout << top() << "\n";  // 应输出 3
    push(1);
    cout << top() << "\n";  // 应输出 1
    pop();
    cout << top() << "\n";  // 应输出 3
    pop();
    cout << top() << "\n";  // 应输出 5
    return 0;
}