#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    for (int i = 1; i <= 100; i++)
    {
        push(i);
        cout << "size() = " << size() << " front() = " << front() << '\n';
        if (i % 20 == 0 && size()) pop();
    }    
    
    return 0;
}
