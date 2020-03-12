// Self-Describing Queue
// UVa ID: 10049
// Verdict: Accepted
// Submission Date: 2020-03-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 表示输入的结构体。
struct data { int idx, n, fn; };

bool cmp1(data d1, data d2) { return d1.n < d2.n; }
bool cmp2(data d1, data d2) { return d1.idx < d2.idx; }

// 表示输入的向量。
vector<data> Xs;

void getFn()
{
    int idx = 0;
    // 输入中尚未确定函数值的元素个数。
    int unsetted = Xs.size();

    // 处理n=1和n=2时的特殊情形。
    while (Xs[idx].n <= 2) {
        Xs[idx].fn = Xs[idx].n;
        idx++;
        unsetted--;
    }
    if (!unsetted) return;

    queue<int> Q;
    // hendn为队列首端所对应的函数自变量值，totaln为队列能够产生的元素的数量。
    int headn = 3, totaln = 2;
    // 压入初始元素，即f(3)=2。
    Q.push(2);

    // 当队列能够生成的元素总数小于输入中最大值时，继续添加元素。
    while (totaln < Xs.back().n) {
        int fn = Q.front(); Q.pop();
        // 根据自描诉序列的定义，将fn个headn压入队列。
        for (int i = 1; i <= fn; i++) Q.push(headn);
        // 比较输入和当前自变量是否匹配。
        if (Xs[idx].n == headn) {
            Xs[idx++].fn = fn;
            unsetted--;
        }
        if (!unsetted) return;
        // 计数队列总共能够产生的元素总数。
        totaln += fn * headn, headn++;
    }

    // 确定当前队列末尾元素所对应的自变量值。
    int endn = headn + Q.size();
    while (Q.size()) {
        int fn = Q.front(); Q.pop();
        // 比较输入和队列首端的自变量是否匹配。
        if (Xs[idx].n == headn) {
            Xs[idx++].fn = fn;
            unsetted--;
        }
        // 确定是否有输入在区间[endn, endn+fn)，根据自描述序列的定义，
        // 在此区间内的整数的函数值均为headn。
        for (int i = idx; i < Xs.size(); i++)
            if (endn <= Xs[i].n && Xs[i].n <= (endn + fn - 1)) {
                Xs[i].fn = headn;
                unsetted--;
            }
        // 所有输入的函数值均已确定，退出。
        if (!unsetted) return;
        // 更改队列首端和尾端所对应的自变量值。注意，并不需要在队列末端实际添加元素。
        // 这是非递推方法的关键，否则会造成超出内存。
        endn += fn, headn++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int idx = 0, n;
    while (cin >> n, n) Xs.push_back(data{idx++, n, 0});
    // 排序，从小到大确定输入的函数值。
    sort(Xs.begin(), Xs.end(), cmp1);
    getFn();
    // 恢复输入顺序。
    sort(Xs.begin(), Xs.end(), cmp2);
    for (int i = 0; i < Xs.size(); i++) cout << Xs[i].fn << '\n';
    return 0;
}
