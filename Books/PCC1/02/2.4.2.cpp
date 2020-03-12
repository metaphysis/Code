#include <bits/stdc++.h>

using namespace std;

// 默认最大值优先。
priority_queue<int> greaterDefault;

// 使用结构模板 greater<T>得到最小值优先队列。
priority_queue<int, vector<int>, greater<int>> lessInt;

// 使用结构模板 less<T> 得到最大值优先队列。
priority_queue<int, vector<int>, less<int>> greaterInt;

struct A {
    bool operator() (int x, int y) const { return x > y; }
};
// 通过重载括号运算符得到最小值优先队列。
priority_queue<int, vector<int>, A> lessA;

struct B {
    bool operator() (int x, int y) const { return x < y; }
};
// 通过重载括号运算符得到最大值优先队列。
priority_queue<int, vector<int>, B> greaterB;

struct C {
    int index;
    bool operator<(C x) const { return index > x.index; }
};
// 通过重载小于运算符得到最小值优先队列。
priority_queue<C> lessC;

struct D {
    int index;
    bool operator<(D x) const { return index < x.index; }
};
// 通过重载小于运算符得到最大值优先队列。
priority_queue<D> greaterD;

class E {
public:
    int index;
    bool operator<(E x) const { return index > x.index; }
};
// 通过重载小于运算符得到最小值优先队列。
priority_queue<E> lessE;

int main(int argc, char* argv[])
{
    for (int i = 0; i < 20; i++) greaterB.push(i);
    while (greaterB.empty() == false)
    {
        cout << greaterB.top() << '\n';
        greaterB.pop();
    }
    return 0;
}
