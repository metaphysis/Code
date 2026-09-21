#include <bits/stdc++.h>
using namespace std;

const double Inf = 1e100;
const double Eps = 1e-8;
const double Pi = acos(-1.0);

struct Point {
    double x, y;
};

struct Node {
    Point a, b;
};

struct Solver {
    int segmentCount;
    double rodLen;
    vector<double> segLen;
    vector<int> verticalSign;
    vector<Point> startPoint;
    vector<Point> direction;
    Point rightPoint;
    vector<Node> nodes;
    vector<vector<vector<int>>> cellNodes;
    vector<vector<pair<int, double>>> graph;
    vector<int> targetIds;
    int startId;

    Point addPoint(Point a, Point b) {
        return {a.x + b.x, a.y + b.y};
    }

    Point subPoint(Point a, Point b) {
        return {a.x - b.x, a.y - b.y};
    }

    Point mulPoint(Point a, double value) {
        return {a.x * value, a.y * value};
    }

    double dotProduct(Point a, Point b) {
        return a.x * b.x + a.y * b.y;
    }

    double normSquare(Point a) {
        return dotProduct(a, a);
    }

    bool samePoint(Point a, Point b) {
        return fabs(a.x - b.x) <= Eps && fabs(a.y - b.y) <= Eps;
    }

    Point getPoint(int segmentId, double value) {
        return addPoint(startPoint[segmentId], mulPoint(direction[segmentId], value));
    }

    double getParameter(int segmentId, Point point) {
        return dotProduct(subPoint(point, startPoint[segmentId]), direction[segmentId]);
    }

    void addCellNode(int cellA, int cellB, int nodeId) {
        for (int id : cellNodes[cellA][cellB])
            if (id == nodeId)
                return;
        cellNodes[cellA][cellB].push_back(nodeId);
    }

    int addNode(int segmentA, double parameterA, int segmentB, double parameterB) {
        Point pointA = getPoint(segmentA, parameterA);
        Point pointB = getPoint(segmentB, parameterB);
        for (int i = 0; i < (int)nodes.size(); i++) {
            if (samePoint(nodes[i].a, pointA) && samePoint(nodes[i].b, pointB)) {
                addCellNode(segmentA, segmentB, i);
                return i;
            }
        }
        int nodeId = nodes.size();
        nodes.push_back({pointA, pointB});
        addCellNode(segmentA, segmentB, nodeId);
        return nodeId;
    }

    void addFixedAIntersections(int segmentA, double parameterA, int segmentB) {
        Point pointA = getPoint(segmentA, parameterA);
        Point delta = subPoint(startPoint[segmentB], pointA);
        double linear = 2.0 * dotProduct(delta, direction[segmentB]);
        double constant = normSquare(delta) - rodLen * rodLen;
        double discriminant = linear * linear - 4.0 * constant;
        if (discriminant < -Eps)
            return;
        discriminant = max(0.0, discriminant);
        double root = sqrt(discriminant);
        double values[2] = {(-linear - root) / 2.0, (-linear + root) / 2.0};
        for (int i = 0; i < 2; i++)
            if (values[i] >= -Eps && values[i] <= segLen[segmentB] + Eps)
                addNode(segmentA, parameterA, segmentB, max(0.0, min(segLen[segmentB], values[i])));
    }

    void addFixedBIntersections(int segmentA, int segmentB, double parameterB) {
        Point pointB = getPoint(segmentB, parameterB);
        Point delta = subPoint(startPoint[segmentA], pointB);
        double linear = 2.0 * dotProduct(delta, direction[segmentA]);
        double constant = normSquare(delta) - rodLen * rodLen;
        double discriminant = linear * linear - 4.0 * constant;
        if (discriminant < -Eps)
            return;
        discriminant = max(0.0, discriminant);
        double root = sqrt(discriminant);
        double values[2] = {(-linear - root) / 2.0, (-linear + root) / 2.0};
        for (int i = 0; i < 2; i++)
            if (values[i] >= -Eps && values[i] <= segLen[segmentA] + Eps)
                addNode(segmentA, max(0.0, min(segLen[segmentA], values[i])), segmentB, parameterB);
    }

    void buildPath() {
        startPoint.assign(segmentCount, {});
        direction.assign(segmentCount, {});
        Point current = {0.0, 0.0};
        for (int i = 0; i < segmentCount; i++) {
            startPoint[i] = current;
            if (i % 2 == 0)
                direction[i] = {1.0, 0.0};
            else
                direction[i] = {0.0, (double)verticalSign[i]};
            current = addPoint(current, mulPoint(direction[i], segLen[i]));
        }
        rightPoint = current;
    }

    void buildNodes() {
        cellNodes.assign(segmentCount, vector<vector<int>>(segmentCount));
        for (int i = 0; i < segmentCount; i++) {
            for (int j = 0; j < segmentCount; j++) {
                addFixedAIntersections(i, 0.0, j);
                addFixedAIntersections(i, segLen[i], j);
                addFixedBIntersections(i, j, 0.0);
                addFixedBIntersections(i, j, segLen[j]);
            }
        }
        startId = addNode(0, rodLen, 0, 0.0);
        for (int i = 0; i < (int)nodes.size(); i++)
            if (samePoint(nodes[i].a, rightPoint))
                targetIds.push_back(i);
    }

    bool inRange(double value, double left, double right) {
        return value >= left - Eps && value <= right + Eps;
    }

    double getArcCost(double centerS, double radius, double angle1, double angle2) {
        vector<double> angles;
        angles.push_back(angle1);
        angles.push_back(angle2);
        double first = ceil((angle1 - Eps) / Pi) * Pi;
        for (double angle = first; angle < angle2 - Eps; angle += Pi)
            if (angle > angle1 + Eps)
                angles.push_back(angle);
        sort(angles.begin(), angles.end());
        double answer = 0.0;
        for (int i = 1; i < (int)angles.size(); i++) {
            double value1 = centerS + radius * cos(angles[i - 1]);
            double value2 = centerS + radius * cos(angles[i]);
            answer += fabs(value2 - value1);
        }
        return answer;
    }

    void addEdge(int u, int v, double weight) {
        if (weight < Eps)
            weight = 0.0;
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    void buildParallelCell(int segmentA, int segmentB) {
        vector<int> ids = cellNodes[segmentA][segmentB];
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());
        if ((int)ids.size() <= 1)
            return;
        double sameDirection = dotProduct(direction[segmentA], direction[segmentB]);
        vector<vector<int>> groups;
        for (int id : ids) {
            double parameterA = getParameter(segmentA, nodes[id].a);
            double parameterB = getParameter(segmentB, nodes[id].b);
            double key = parameterA - sameDirection * parameterB;
            int groupId = -1;
            for (int i = 0; i < (int)groups.size(); i++) {
                int otherId = groups[i][0];
                double otherA = getParameter(segmentA, nodes[otherId].a);
                double otherB = getParameter(segmentB, nodes[otherId].b);
                double otherKey = otherA - sameDirection * otherB;
                if (fabs(key - otherKey) <= 1e-7) {
                    groupId = i;
                    break;
                }
            }
            if (groupId == -1) {
                groups.push_back({});
                groupId = groups.size() - 1;
            }
            groups[groupId].push_back(id);
        }
        for (vector<int> &group : groups) {
            sort(group.begin(), group.end(), [&](int a, int b) {
                return getParameter(segmentA, nodes[a].a) < getParameter(segmentA, nodes[b].a);
            });
            for (int i = 1; i < (int)group.size(); i++) {
                double parameter1 = getParameter(segmentA, nodes[group[i - 1]].a);
                double parameter2 = getParameter(segmentA, nodes[group[i]].a);
                addEdge(group[i - 1], group[i], fabs(parameter2 - parameter1));
            }
        }
    }

    void buildPerpendicularCell(int segmentA, int segmentB) {
        vector<int> ids = cellNodes[segmentA][segmentB];
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());
        if ((int)ids.size() <= 1)
            return;
        Point delta = subPoint(startPoint[segmentA], startPoint[segmentB]);
        double centerS = -dotProduct(delta, direction[segmentA]);
        double centerT = dotProduct(delta, direction[segmentB]);
        double radiusSquare = rodLen * rodLen - normSquare(delta) + centerS * centerS + centerT * centerT;
        if (radiusSquare < -Eps)
            return;
        double radius = sqrt(max(0.0, radiusSquare));
        vector<pair<double, int>> order;
        for (int id : ids) {
            double parameterA = getParameter(segmentA, nodes[id].a);
            double parameterB = getParameter(segmentB, nodes[id].b);
            double angle = atan2(parameterB - centerT, parameterA - centerS);
            if (angle < 0.0)
                angle += 2.0 * Pi;
            order.push_back({angle, id});
        }
        sort(order.begin(), order.end());
        for (int i = 0; i < (int)order.size(); i++) {
            int next = (i + 1) % order.size();
            double angle1 = order[i].first;
            double angle2 = order[next].first;
            if (next == 0)
                angle2 += 2.0 * Pi;
            double middle = (angle1 + angle2) / 2.0;
            double parameterA = centerS + radius * cos(middle);
            double parameterB = centerT + radius * sin(middle);
            if (!inRange(parameterA, 0.0, segLen[segmentA]))
                continue;
            if (!inRange(parameterB, 0.0, segLen[segmentB]))
                continue;
            double weight = getArcCost(centerS, radius, angle1, angle2);
            addEdge(order[i].second, order[next].second, weight);
        }
    }

    void buildGraph() {
        graph.assign(nodes.size(), {});
        for (int i = 0; i < segmentCount; i++) {
            for (int j = 0; j < segmentCount; j++) {
                double cross = direction[i].x * direction[j].y - direction[i].y * direction[j].x;
                if (fabs(cross) <= Eps)
                    buildParallelCell(i, j);
                else
                    buildPerpendicularCell(i, j);
            }
        }
    }

    double shortestPath() {
        vector<double> distance(nodes.size(), Inf);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
        distance[startId] = 0.0;
        que.push({0.0, startId});
        while (!que.empty()) {
            pair<double, int> current = que.top();
            que.pop();
            double currentDistance = current.first;
            int currentId = current.second;
            if (currentDistance > distance[currentId] + Eps)
                continue;
            for (pair<int, double> edge : graph[currentId]) {
                int nextId = edge.first;
                double newDistance = currentDistance + edge.second;
                if (newDistance + Eps < distance[nextId]) {
                    distance[nextId] = newDistance;
                    que.push({newDistance, nextId});
                }
            }
        }
        double answer = Inf;
        for (int id : targetIds)
            answer = min(answer, distance[id]);
        return answer;
    }

    double solve() {
        buildPath();
        buildNodes();
        buildGraph();
        return shortestPath();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 1;
    while (true) {
        int n;
        cin >> n;
        if (!cin || n == 0)
            break;
        Solver solver;
        solver.segmentCount = n;
        cin >> solver.rodLen;
        solver.segLen.resize(n);
        solver.verticalSign.resize(n);
        for (int i = 0; i < n; i++) {
            int length;
            cin >> length;
            solver.segLen[i] = fabs((double)length);
            solver.verticalSign[i] = length >= 0 ? 1 : -1;
        }
        double answer = solver.solve();
        cout << "Case " << caseId++ << ": ";
        if (answer >= Inf / 2.0)
            cout << "-1\n";
        else
            cout << fixed << setprecision(2) << answer + 1e-9 << '\n';
    }
    return 0;
}
