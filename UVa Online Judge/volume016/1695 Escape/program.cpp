#include <bits/stdc++.h>
using namespace std;

using TaskMap = map<long long, long long>;
using TaskHeap = priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>>;

void addTask(TaskMap &tasks, long long need, long long gain) {
    if (gain <= 0) return;
    auto current = tasks.lower_bound(need);
    if (current != tasks.end() && current->first == need) {
        current->second += gain;
    } else {
        current = tasks.emplace_hint(current, need, gain);
    }
    if (current != tasks.begin()) {
        auto previous = prev(current);
        if (current->first <= previous->first + previous->second) {
            previous->second += current->second;
            tasks.erase(current);
            current = previous;
        }
    }
    auto nextTask = next(current);
    while (nextTask != tasks.end() && nextTask->first <= current->first + current->second) {
        current->second += nextTask->second;
        nextTask = tasks.erase(nextTask);
    }
}

void mergeTasks(TaskMap &destination, TaskMap &source) {
    for (const auto &task : source) addTask(destination, task.first, task.second);
}

void applyNode(TaskMap &tasks, long long value) {
    if (value > 0) {
        addTask(tasks, 0, value);
        return;
    }
    if (value == 0) return;
    long long cost = -value, sumGain = 0, requiredHealth = cost;
    while (sumGain <= cost && !tasks.empty()) {
        auto current = tasks.begin();
        long long need = current->first, gain = current->second;
        requiredHealth = max(requiredHealth, cost + need - sumGain);
        sumGain += gain;
        tasks.erase(current);
    }
    if (sumGain <= cost) return;
    addTask(tasks, requiredHealth, sumGain - cost);
}

void collectTasks(TaskHeap &available, long long &health) {
    while (!available.empty() && available.top().first <= health) {
        health += available.top().second;
        available.pop();
    }
}

void solve() {
    int n, target;
    cin >> n >> target;
    vector<long long> value(n + 1);
    for (int i = 1; i <= n; i++) cin >> value[i];
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> parent(n + 1, -1), order(1, 1);
    parent[1] = 0;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int v : graph[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            order.push_back(v);
        }
    }
    vector<int> path;
    for (int u = target; u != 0; u = parent[u]) path.push_back(u);
    reverse(path.begin(), path.end());
    vector<bool> onPath(n + 1, false);
    for (int u : path) onPath[u] = true;
    vector<TaskMap *> taskMaps(n + 1, nullptr);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (onPath[u]) continue;
        TaskMap *current = new TaskMap();
        for (int v : graph[u]) {
            if (parent[v] != u || onPath[v]) continue;
            TaskMap *childMap = taskMaps[v];
            if (current->size() < childMap->size()) swap(current, childMap);
            mergeTasks(*current, *childMap);
            delete childMap;
            taskMaps[v] = nullptr;
        }
        applyNode(*current, value[u]);
        taskMaps[u] = current;
    }
    TaskHeap available;
    long long health = 0;
    bool escaped = true;
    for (int u : path) {
        health += value[u];
        if (health < 0) {
            escaped = false;
            break;
        }
        if (u == target) break;
        for (int v : graph[u]) {
            if (parent[v] != u || onPath[v]) continue;
            for (const auto &task : *taskMaps[v]) available.push(task);
            delete taskMaps[v];
            taskMaps[v] = nullptr;
        }
        collectTasks(available, health);
    }
    for (int i = 1; i <= n; i++) {
        if (taskMaps[i] != nullptr) delete taskMaps[i];
    }
    cout << (escaped ? "escaped" : "trapped") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    while (testCases--) solve();
    return 0;
}
