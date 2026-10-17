#include <bits/stdc++.h>
using namespace std;

vector<int> getBfsOrder(const vector<vector<int> >& graph, int root) {
    vector<int> order, parent(graph.size(), 0);
    queue<int> que;
    parent[root] = -1;
    que.push(root);
    while (!que.empty()) {
        int node = que.front();
        que.pop();
        order.push_back(node);
        for (int next : graph[node])
            if (next != parent[node]) {
                parent[next] = node;
                que.push(next);
            }
    }
    return order;
}

vector<int> getDfsOrder(const vector<vector<int> >& graph, int root) {
    vector<int> order;
    vector<pair<int, int> > stack;
    stack.push_back(make_pair(root, 0));
    while (!stack.empty()) {
        int node = stack.back().first, parent = stack.back().second;
        stack.pop_back();
        order.push_back(node);
        int degree = graph[node].size();
        for (int i = degree - 1; i >= 0; i--)
            if (graph[node][i] != parent)
                stack.push_back(make_pair(graph[node][i], node));
    }
    return order;
}

void printOrder(const vector<int>& order) {
    int size = order.size();
    for (int i = 0; i < size; i++) {
        if (i > 0) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int m = argc >= 2 ? atoi(argv[1]) : 100, caseCount = argc >= 3 ? atoi(argv[2]) : 100;
    if (m < 1 || m > 1000 || caseCount < 1) return 1;
    unsigned int seed = argc >= 4 ? atoi(argv[3]) : chrono::steady_clock::now().time_since_epoch().count() ^ clock();
    mt19937 randomEngine(seed);
    for (int testCase = 1; testCase <= caseCount; testCase++) {
        int n = rand() % m + 1;
        vector<int> entered, notEntered, parent(n + 1, 0);
        vector<vector<int> > graph(n + 1);
        for (int i = 1; i <= n; i++)
            notEntered.push_back(i);
        uniform_int_distribution<int> rootDistribution(0, n - 1);
        int rootIndex = rootDistribution(randomEngine), root = notEntered[rootIndex];
        swap(notEntered[rootIndex], notEntered.back());
        notEntered.pop_back();
        entered.push_back(root);
        while (!notEntered.empty()) {
            uniform_int_distribution<int> nodeDistribution(0, notEntered.size() - 1);
            uniform_int_distribution<int> parentDistribution(0, entered.size() - 1);
            int nodeIndex = nodeDistribution(randomEngine), parentIndex = parentDistribution(randomEngine);
            int node = notEntered[nodeIndex], father = entered[parentIndex];
            swap(notEntered[nodeIndex], notEntered.back());
            notEntered.pop_back();
            entered.push_back(node);
            parent[node] = father;
            graph[node].push_back(father);
            graph[father].push_back(node);
        }
        for (int i = 1; i <= n; i++)
            sort(graph[i].begin(), graph[i].end());
        vector<int> bfsOrder = getBfsOrder(graph, root), dfsOrder = getDfsOrder(graph, root);
        cout << n << '\n';
        printOrder(bfsOrder);
        printOrder(dfsOrder);
        cout.flush();
    }
    cout << "0\n";
    return 0;
}
