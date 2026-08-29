#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    long long cap;
};

class Dinic {
private:
    vector<vector<Edge>> graph;
    vector<int> level, work;

    bool bfs(int source, int sink) {
        queue<int> que;
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int node = que.front();
            que.pop();
            for (const Edge &edge : graph[node])
                if (edge.cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[node] + 1;
                    que.push(edge.to);
                }
        }
        return level[sink] != -1;
    }

    long long dfs(int node, int sink, long long flow) {
        if (node == sink || flow == 0)
            return flow;
        for (int &i = work[node]; i < static_cast<int>(graph[node].size()); ++i) {
            Edge &edge = graph[node][i];
            if (edge.cap > 0 && level[edge.to] == level[node] + 1) {
                long long pushed = dfs(edge.to, sink, min(flow, edge.cap));
                if (pushed > 0) {
                    edge.cap -= pushed;
                    graph[edge.to][edge.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int n) {
        graph.resize(n);
        level.resize(n);
        work.resize(n);
    }

    void addEdge(int from, int to, long long cap) {
        Edge forward = {to, static_cast<int>(graph[to].size()), cap};
        Edge backward = {from, static_cast<int>(graph[from].size()), 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    long long maxFlow(int source, int sink) {
        long long result = 0, pushed;
        while (bfs(source, sink)) {
            fill(work.begin(), work.end(), 0);
            while ((pushed = dfs(source, sink, numeric_limits<long long>::max())) > 0)
                result += pushed;
        }
        return result;
    }

    vector<bool> getReachable(int source) {
        vector<bool> visited(graph.size(), false);
        queue<int> que;
        visited[source] = true;
        que.push(source);
        while (!que.empty()) {
            int node = que.front();
            que.pop();
            for (const Edge &edge : graph[node])
                if (edge.cap > 0 && !visited[edge.to]) {
                    visited[edge.to] = true;
                    que.push(edge.to);
                }
        }
        return visited;
    }
};

void printTeamList(const vector<string> &names, const vector<int> &group) {
    int size = group.size();
    for (int i = 0; i < size; ++i) {
        if (i > 0 && i == size - 1)
            cout << " and ";
        else if (i > 0)
            cout << ", ";
        cout << names[group[i]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNo = 1;
    while (cin >> n && n != -1) {
        vector<string> names(n);
        vector<int> wins(n), losses(n), leftGames(n);
        vector<vector<long long>> remain(n, vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            cin >> names[i] >> wins[i] >> losses[i] >> leftGames[i];
            for (int j = 0; j < n; ++j)
                cin >> remain[i][j];
        }
        cout << "Case " << caseNo++ << ":\n";
        for (int candidate = 0; candidate < n; ++candidate) {
            int maxWins = wins[candidate] + leftGames[candidate];
            int directTeam = -1;
            for (int i = 0; i < n; ++i)
                if (i != candidate && wins[i] > maxWins) {
                    directTeam = i;
                    break;
                }
            if (directTeam != -1) {
                cout << "Team " << names[candidate] << " is eliminated.\n";
                cout << "They can win at most " << wins[candidate] << " + " << leftGames[candidate] << " = " << maxWins << " games.\n";
                cout << names[directTeam] << " have won a total of " << wins[directTeam] << " games.\n";
                cout << "They play each other 0 times.\n";
                cout << fixed << setprecision(6);
                cout << "So, on average, each of the teams wins (" << wins[directTeam] << "+0)/1 = " << static_cast<double>(wins[directTeam]) << " games which is greater than " << maxWins << ".\n";
                cout << '\n';
                continue;
            }
            vector<int> teamNode(n, -1);
            int nodeCount = 1, gameCount = 0;
            for (int i = 0; i < n; ++i)
                if (i != candidate)
                    teamNode[i] = nodeCount++;
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    if (i != candidate && j != candidate)
                        ++gameCount;
            int source = 0, firstGame = nodeCount, sink = firstGame + gameCount;
            Dinic dinic(sink + 1);
            long long totalGames = 0;
            int gameNode = firstGame;
            for (int i = 0; i < n; ++i) {
                if (i == candidate)
                    continue;
                dinic.addEdge(teamNode[i], sink, maxWins - wins[i]);
            }
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (i == candidate || j == candidate)
                        continue;
                    long long games = remain[i][j];
                    dinic.addEdge(source, gameNode, games);
                    dinic.addEdge(gameNode, teamNode[i], numeric_limits<long long>::max() / 4);
                    dinic.addEdge(gameNode, teamNode[j], numeric_limits<long long>::max() / 4);
                    totalGames += games;
                    ++gameNode;
                }
            }
            long long flow = dinic.maxFlow(source, sink);
            if (flow == totalGames)
                continue;
            vector<bool> reachable = dinic.getReachable(source);
            vector<int> group;
            long long totalWins = 0, insideGames = 0;
            for (int i = 0; i < n; ++i)
                if (i != candidate && reachable[teamNode[i]]) {
                    group.push_back(i);
                    totalWins += wins[i];
                }
            for (int i = 0; i < static_cast<int>(group.size()); ++i)
                for (int j = i + 1; j < static_cast<int>(group.size()); ++j)
                    insideGames += remain[group[i]][group[j]];
            cout << "Team " << names[candidate] << " is eliminated.\n";
            cout << "They can win at most " << wins[candidate] << " + " << leftGames[candidate] << " = " << maxWins << " games.\n";
            printTeamList(names, group);
            cout << " have won a total of " << totalWins << " games.\n";
            cout << "They play each other " << insideGames << " times.\n";
            cout << fixed << setprecision(6);
            double average = static_cast<double>(totalWins + insideGames) / group.size();
            cout << "So, on average, each of the teams wins (" << totalWins << "+" << insideGames << ")/" << group.size() << " = " << average << " games which is greater than " << maxWins << ".\n";
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
