// Throwing Cards Away I
// UVa ID: 10935
// Verdict: Accepted
// Submission Date: 2018-01-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int CAPACITY = 1010;
int memory[CAPACITY], head = 0, rear = 0;

bool empty() { return head == rear; }
int size() { return rear >= head ? (rear - head) : (rear + CAPACITY - head); }
int front() { return memory[head]; }
int back() { return memory[(rear - 1 + CAPACITY) % CAPACITY]; }

void push(int x) {
    memory[rear] = x;
    rear = (rear + 1) % CAPACITY;
}

void pop() { head = (head + 1) % CAPACITY; }
void reset() { head = rear = 0; }

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        reset();
        for (int i = 1; i <= n; i++) push(i);
        
        cout << "Discarded cards:";
        int cnt = 0;
        while (size() > 1)
        {
            if (cnt++) cout << ',';
            cout << ' ' << front();
            pop();
            push(front());
            pop();
        }
        cout << '\n';
        cout << "Remaining card: " << front() << '\n';
    }

    return 0;
}
