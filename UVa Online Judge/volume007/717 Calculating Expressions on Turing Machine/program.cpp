// Calculating Expressions on Turing Machine
// UVa ID: 717
// Verdict: Accepted
// Submission Date: 2026-10-21
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <string>
#include <cassert>
#include <algorithm>
#include <utility>

using namespace std;

struct Node {
    char op;
    int variable, left, right;
    Node(char o, int v, int l, int r) : op(o), variable(v), left(l), right(r) {}
};

struct Parser {
    string text;
    size_t pos;
    vector<Node> nodes;

    explicit Parser(const string& s) : text(s), pos(0) {}

    int atom() {
        if (text[pos] == '(') {
            ++pos;
            int u = expression();
            assert(pos < text.size() && text[pos] == ')');
            ++pos;
            return u;
        }
        assert(text[pos] >= '1' && text[pos] <= '9');
        int v = text[pos++] - '0';
        nodes.push_back(Node('v', v, -1, -1));
        return static_cast<int>(nodes.size()) - 1;
    }

    int term() {
        int u = atom();
        while (pos < text.size() && text[pos] == '*') {
            ++pos;
            int v = atom();
            nodes.push_back(Node('*', 0, u, v));
            u = static_cast<int>(nodes.size()) - 1;
        }
        return u;
    }

    int expression() {
        int u = term();
        while (pos < text.size() && text[pos] == '+') {
            ++pos;
            int v = term();
            nodes.push_back(Node('+', 0, u, v));
            u = static_cast<int>(nodes.size()) - 1;
        }
        return u;
    }

    int parse() {
        int root = expression();
        assert(pos == text.size());
        return root;
    }
};

struct Edge {
    int write, next;
    char direction;
    Edge(int w, int n, char d) : write(w), next(n), direction(d) {}
};

struct State {
    map<int, Edge> edges;
    int fallbackNext;
    char fallbackDirection;
    State() : fallbackNext(-1), fallbackDirection('R') {}
};

class Generator {
    const vector<Node>& nodes;
    vector<State> states;
    vector<int> boundary, entry, suffixSymbols;
    map<int, int> carry, returnMarkers;
    array<int, 10> inputBoundary, marked;
    int nextSymbol, homeSymbol, endSymbol, outputEndSymbol;
    int appendReturn, outputEntry, haltState;

    int newState() {
        states.push_back(State());
        return static_cast<int>(states.size()) - 1;
    }

    int newSymbol() {
        return nextSymbol++;
    }

    void edge(int q, int read, int write, int next, char direction) {
        assert(q >= 0 && q < static_cast<int>(states.size()));
        assert(states[q].edges.find(read) == states[q].edges.end());
        states[q].edges.emplace(read, Edge(write, next, direction));
    }

    void fallback(int q, int next, char direction) {
        assert(states[q].fallbackNext == -1);
        assert(direction == 'L' || direction == 'R');
        states[q].fallbackNext = next;
        states[q].fallbackDirection = direction;
    }

    int seek(int symbol, char direction, int next) {
        int q = newState();
        fallback(q, q, direction);
        edge(q, symbol, symbol, next, 'S');
        return q;
    }

    int home(int next) {
        return seek(homeSymbol, 'L', next);
    }

    int move(char direction, int next) {
        int q = newState();
        fallback(q, next, direction);
        return q;
    }

    void connect(int q, int next) {
        edge(q, homeSymbol, homeSymbol, next, 'S');
    }

    int returnMarker(int continuation) {
        auto it = returnMarkers.find(continuation);
        if (it != returnMarkers.end()) return it->second;
        int symbol = newSymbol();
        returnMarkers[continuation] = symbol;
        edge(appendReturn, symbol, homeSymbol, continuation, 'S');
        return symbol;
    }

    int append(int reg, int digit, int continuation) {
        int marker = returnMarker(continuation);
        int insert = newState();
        edge(insert, boundary[reg], digit, carry.at(boundary[reg]), 'R');
        int find = seek(boundary[reg], 'R', insert);
        int start = newState();
        edge(start, homeSymbol, marker, find, 'R');
        return start;
    }

    void allocateSymbols() {
        homeSymbol = newSymbol();
        inputBoundary.fill(-1);
        inputBoundary[1] = homeSymbol;
        for (int i = 2; i <= 9; ++i) inputBoundary[i] = newSymbol();
        boundary.resize(nodes.size() + 1);
        for (size_t i = 0; i < boundary.size(); ++i) boundary[i] = newSymbol();
        endSymbol = newSymbol();
        outputEndSymbol = newSymbol();
        for (int d = 0; d < 10; ++d) marked[d] = newSymbol();
        for (int d = 0; d < 10; ++d) suffixSymbols.push_back(d);
        for (int d = 0; d < 10; ++d) suffixSymbols.push_back(marked[d]);
        for (size_t i = 1; i < boundary.size(); ++i) suffixSymbols.push_back(boundary[i]);
        suffixSymbols.push_back(endSymbol);
        for (int symbol : suffixSymbols) carry[symbol] = newState();
        appendReturn = newState();
        fallback(appendReturn, appendReturn, 'L');
    }

    void buildCarry() {
        for (int symbol : suffixSymbols) {
            int q = carry.at(symbol);
            for (int current : suffixSymbols) edge(q, current, symbol, carry.at(current), 'R');
            edge(q, -1, symbol, appendReturn, 'L');
        }
    }

    void buildInitialization() {
        array<int, 10> scan, look;
        for (int i = 1; i <= 9; ++i) scan[i] = newState();
        for (int i = 1; i <= 9; ++i) look[i] = newState();
        int writeHome = newState();
        for (int d = 0; d < 10; ++d) edge(0, d, d, writeHome, 'L');
        edge(writeHome, -1, homeSymbol, scan[1], 'R');
        int writeEnd = newState();
        edge(writeEnd, -1, endSymbol, home(entry[1]), 'L');
        int firstWriter = writeEnd;
        for (int j = static_cast<int>(nodes.size()); j >= 0; --j) {
            int q = newState();
            edge(q, -1, boundary[j], firstWriter, 'R');
            firstWriter = q;
        }
        for (int i = 1; i <= 9; ++i) {
            for (int d = 0; d < 10; ++d) edge(scan[i], d, d, scan[i], 'R');
            edge(scan[i], -1, -1, look[i], 'R');
            edge(look[i], -1, -1, firstWriter, 'L');
            if (i < 9) {
                int separator = newState();
                edge(separator, -1, inputBoundary[i + 1], scan[i + 1], 'R');
                for (int d = 0; d < 10; ++d) edge(look[i], d, d, separator, 'L');
            }
        }
    }

    void buildVariable(int reg, int variable, int start, int next) {
        int take = newState();
        int scanEnd = newState();
        int restore = newState();
        int leftBoundary = inputBoundary[variable];
        int finish = home(next);
        array<int, 10> push;
        for (int d = 0; d < 10; ++d) push[d] = append(reg, d, start);
        for (int d = 0; d < 10; ++d) {
            edge(scanEnd, d, d, scanEnd, 'R');
            edge(scanEnd, marked[d], marked[d], scanEnd, 'R');
            edge(take, marked[d], marked[d], take, 'L');
            edge(take, d, marked[d], home(push[d]), 'L');
            edge(restore, d, d, restore, 'R');
            edge(restore, marked[d], d, restore, 'R');
        }
        for (int i = 2; i <= 9; ++i) {
            edge(scanEnd, inputBoundary[i], inputBoundary[i], take, 'L');
            edge(restore, inputBoundary[i], inputBoundary[i], finish, 'S');
        }
        edge(scanEnd, boundary[0], boundary[0], take, 'L');
        edge(restore, boundary[0], boundary[0], finish, 'S');
        edge(take, leftBoundary, leftBoundary, restore, 'R');
        connect(start, seek(leftBoundary, 'R', move('R', scanEnd)));
    }

    int readNext(int reg, const array<int, 11>& callbacks) {
        int scan = newState();
        for (int d = 0; d < 10; ++d) {
            edge(scan, marked[d], marked[d], scan, 'R');
            edge(scan, d, marked[d], home(callbacks[d]), 'L');
        }
        edge(scan, boundary[reg], boundary[reg], home(callbacks[10]), 'L');
        return seek(boundary[reg - 1], 'R', move('R', scan));
    }

    int readFirst(int reg, const array<int, 10>& callbacks) {
        int read = newState();
        for (int d = 0; d < 10; ++d) edge(read, d, d, home(callbacks[d]), 'L');
        return seek(boundary[reg - 1], 'R', move('R', read));
    }

    void buildAddition(int reg, int left, int right, int start, int next) {
        array<int, 2> loop = {{start, newState()}};
        array<array<int, 10>, 2> push;
        for (int c = 0; c < 2; ++c) {
            for (int d = 0; d < 10; ++d) push[c][d] = append(reg, d, loop[c]);
        }
        int finalCarry = append(reg, 1, next);
        for (int c = 0; c < 2; ++c) {
            array<int, 11> leftCallbacks;
            for (int x = 0; x <= 10; ++x) {
                array<int, 11> rightCallbacks;
                for (int y = 0; y <= 10; ++y) {
                    if (x == 10 && y == 10) {
                        rightCallbacks[y] = c ? finalCarry : next;
                    } else {
                        int sum = (x == 10 ? 0 : x) + (y == 10 ? 0 : y) + c;
                        rightCallbacks[y] = push[sum / 10][sum % 10];
                    }
                }
                leftCallbacks[x] = readNext(right, rightCallbacks);
            }
            connect(loop[c], readNext(left, leftCallbacks));
        }
    }

    void buildMultiplication(int reg, int left, int right, int start, int next) {
        array<int, 10> push, leftCallbacks;
        for (int d = 0; d < 10; ++d) push[d] = append(reg, d, next);
        for (int x = 0; x < 10; ++x) {
            array<int, 10> rightCallbacks;
            for (int y = 0; y < 10; ++y) rightCallbacks[y] = push[(x * y) % 10];
            leftCallbacks[x] = readFirst(right, rightCallbacks);
        }
        connect(start, readFirst(left, leftCallbacks));
    }

    void buildNodes() {
        int count = static_cast<int>(nodes.size());
        for (int i = 0; i < count; ++i) {
            int reg = i + 1;
            int next = reg == count ? outputEntry : entry[reg + 1];
            const Node& u = nodes[i];
            if (u.op == 'v') buildVariable(reg, u.variable, entry[reg], next);
            else if (u.op == '+') buildAddition(reg, u.left + 1, u.right + 1, entry[reg], next);
            else buildMultiplication(reg, u.left + 1, u.right + 1, entry[reg], next);
        }
    }

    void buildOutput() {
        int root = static_cast<int>(nodes.size());
        int loop = newState();
        int take = newState();
        int finalMove = newState();
        edge(finalMove, endSymbol, endSymbol, haltState, 'R');
        int finalFind = seek(endSymbol, 'R', finalMove);
        int erase = newState();
        edge(erase, outputEndSymbol, -1, home(finalFind), 'L');
        int clean = seek(outputEndSymbol, 'R', erase);
        edge(take, boundary[root - 1], boundary[root - 1], home(clean), 'S');
        for (int d = 0; d < 10; ++d) {
            int writeMarker = newState();
            edge(writeMarker, -1, outputEndSymbol, home(loop), 'L');
            int writeDigit = newState();
            edge(writeDigit, outputEndSymbol, d, writeMarker, 'R');
            int findMarker = seek(outputEndSymbol, 'R', writeDigit);
            edge(take, d, marked[d], home(findMarker), 'L');
            edge(take, marked[d], marked[d], take, 'L');
        }
        connect(loop, seek(boundary[root], 'R', move('L', take)));
        int initializeMarker = newState();
        edge(initializeMarker, -1, outputEndSymbol, home(loop), 'L');
        int afterEnd = newState();
        edge(afterEnd, endSymbol, endSymbol, initializeMarker, 'R');
        connect(outputEntry, seek(endSymbol, 'R', afterEnd));
    }

    void lowerStationaryTransitions() {
        int originalCount = static_cast<int>(states.size());
        set<int> targets;
        for (int q = 0; q < originalCount; ++q) {
            for (const auto& item : states[q].edges) {
                if (item.second.direction == 'S') targets.insert(item.second.next);
            }
        }
        map<int, int> bridge;
        for (int target : targets) {
            int q = newState();
            fallback(q, target, 'L');
            bridge[target] = q;
        }
        for (int q = 0; q < originalCount; ++q) {
            for (auto& item : states[q].edges) {
                Edge& e = item.second;
                if (e.direction == 'S') {
                    e.next = bridge.at(e.next);
                    e.direction = 'R';
                }
            }
        }
    }

    void validate() const {
        int count = static_cast<int>(states.size());
        int maximumSymbol = nextSymbol - 1;
        assert(states[haltState].edges.empty());
        assert(states[haltState].fallbackNext == -1);
        for (int q = 0; q < count; ++q) {
            const State& s = states[q];
            if (s.fallbackNext != -1) {
                assert(s.fallbackNext >= 0 && s.fallbackNext < count);
                assert(s.fallbackDirection == 'L' || s.fallbackDirection == 'R');
            }
            for (const auto& item : s.edges) {
                const Edge& e = item.second;
                assert(item.first >= -1 && item.first <= maximumSymbol);
                assert(e.write >= -1 && e.write <= maximumSymbol);
                assert(e.next >= 0 && e.next < count);
                assert(e.direction == 'L' || e.direction == 'R');
            }
        }
    }

public:
    explicit Generator(const vector<Node>& tree) : nodes(tree), nextSymbol(10) {
        assert(newState() == 0);
        allocateSymbols();
        entry.resize(nodes.size() + 1);
        for (size_t i = 1; i < entry.size(); ++i) entry[i] = newState();
        outputEntry = newState();
        haltState = newState();
        buildInitialization();
        buildNodes();
        buildOutput();
        buildCarry();
        lowerStationaryTransitions();
        validate();
    }

    void print() const {
        int maximumSymbol = nextSymbol - 1;
        cout << maximumSymbol << ' ' << max(1, static_cast<int>(states.size()) - 1) << '\n';
        for (int q = 0; q < static_cast<int>(states.size()); ++q) {
            const State& s = states[q];
            if (s.fallbackNext == -1) {
                for (const auto& item : s.edges) {
                    const Edge& e = item.second;
                    cout << q << ' ' << item.first << ' ' << e.write << ' ' << e.next << ' ' << e.direction << '\n';
                }
            } else {
                for (int symbol = -1; symbol <= maximumSymbol; ++symbol) {
                    auto it = s.edges.find(symbol);
                    if (it == s.edges.end()) cout << q << ' ' << symbol << ' ' << symbol << ' ' << s.fallbackNext << ' ' << s.fallbackDirection << '\n';
                    else cout << q << ' ' << symbol << ' ' << it->second.write << ' ' << it->second.next << ' ' << it->second.direction << '\n';
                }
            }
        }
        cout << "-\n";
    }
};

void printVariableOnly(int variable) {
    cout << 9 << ' ' << max(1, variable - 1) << '\n';
    for (int q = 0; q < variable - 1; ++q) {
        for (int d = 0; d < 10; ++d) cout << q << ' ' << d << ' ' << d << ' ' << q << " R\n";
        cout << q << " -1 -1 " << q + 1 << " R\n";
    }
    cout << "-\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    while (cases--) {
        string expression;
        cin >> expression;
        Parser parser(expression);
        int root = parser.parse();
        if (parser.nodes[root].op == 'v') printVariableOnly(parser.nodes[root].variable);
        else {
            Generator generator(parser.nodes);
            generator.print();
        }
    }
    return 0;
}
