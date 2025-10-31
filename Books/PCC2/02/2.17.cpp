// union-find set

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100000;

int parent[MAXV], ranks[MAXV];

void makeSet1() {
    for (int i = 0; i < MAXV; i++) parent[i] = i, ranks[i] = 0;
}

void makeSet2(int n) {
    for (int i = 0; i < n; i++) parent[i] = i, ranks[i] = 0;
}

int findSet1(int x){
    return x == parent[x] ? x : parent[x] = findSet1(parent[x]);
}

int findSet2(int x) {
    int ancestor = x;
    while (ancestor != parent[ancestor]) ancestor = parent[ancestor];
    while (x != ancestor) {
        int temp = parent[x];
        parent[x] = ancestor;
        x = temp;
    }
    return x;
}

bool unionSet1(int x, int y) {
    x = findSet1(x), y = findSet1(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x, ranks[x] += ranks[y];
        else parent[x] = y, ranks[y] += ranks[x];
        return true;
    }
    return false;
}

bool unionSet2(int x, int y) {
    x = findSet1(x), y = findSet1(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    makeSet1();
    return 0;
}
