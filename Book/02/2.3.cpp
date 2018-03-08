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
#include <vector>

using namespace std;

const int ERROR = -0x3fffffff, CAPACITY = 1010;
int memory[CAPACITY], rear = 0;

bool empty() { return rear == 0; }
int size() { return rear; }

bool push(int x) {
    if (rear < CAPACITY) { memory[rear++] = x; return true; }
    return false;
}

void pop() { if (rear > 0) rear--; }
void reset() { rear = 0; }

int top() {
    if (rear > 0) return memory[rear - 1];
    return ERROR;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 100; i++)
    {
        push(i);
        cout << top() << '\n';
        pop();
    }
}

