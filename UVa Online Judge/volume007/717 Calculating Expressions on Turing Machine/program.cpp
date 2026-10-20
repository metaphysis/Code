// Calculating Expressions on Turing Machine
// UVa ID: 717
// Verdict: Accepted
// Submission Date: 2026-10-21
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Node {
    char op;
    int variable, left, right;
    Node(char o, int v, int l = -1, int r = -1) : op(o), variable(v), left(l), right(r) {}
};

struct Parser {
    string text;
    size_t pos;
    vector<Node> nodes;

    explicit Parser(const string& s) : text(s), pos(0) {}

    int parse(int level = 0) {
        if (level == 2) {
            if (text[pos] == '(') {
                ++pos;
                int root = parse();
                assert(pos < text.size() && text[pos] == ')');
                ++pos;
                return root;
            }
            assert(text[pos] >= '1' && text[pos] <= '9');
            nodes.push_back(Node('v', text[pos++] - '0'));
            return static_cast<int>(nodes.size()) - 1;
        }
        int root = parse(level + 1);
        char operation = level == 0 ? '+' : '*';
        while (pos < text.size() && text[pos] == operation) {
            ++pos;
            int right = parse(level + 1);
            nodes.push_back(Node(operation, 0, root, right));
            root = static_cast<int>(nodes.size()) - 1;
        }
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
    State(int next = -1, char direction = 'R') : fallbackNext(next), fallbackDirection(direction) {}
};

class Generator {
    const vector<Node>& nodes;
    vector<State> states;
    vector<int> boundary, entry, suffixSymbols, carry;
    map<int, int> returnMarkers;
    array<int, 10> inputBoundary, marked;
    int nextSymbol = 10;
    int homeSymbol, endSymbol, outputEndSymbol;
    int appendReturn, outputEntry, haltState;

    int newState(int next = -1, char direction = 'R') {
        states.push_back(State(next, direction));
        return static_cast<int>(states.size()) - 1;
    }

    int newSymbol() {
        return nextSymbol++;
    }

    void edge(int state, int read, int write, int next, char direction) {
        assert(states[state].edges.find(read) == states[state].edges.end());
        states[state].edges.emplace(read, Edge(write, next, direction));
    }

    int seek(int symbol, char direction, int next) {
        int state = newState();
        states[state].fallbackNext = state;
        states[state].fallbackDirection = direction;
        edge(state, symbol, symbol, next, 'S');
        return state;
    }

    int home(int next) {
        return seek(homeSymbol, 'L', next);
    }

    void connect(int state, int next) {
        edge(state, homeSymbol, homeSymbol, next, 'S');
    }

    int append(int reg, int digit, int continuation) {
        if (!returnMarkers.count(continuation)) {
            int symbol = newSymbol();
            returnMarkers[continuation] = symbol;
            edge(appendReturn, symbol, homeSymbol, continuation, 'S');
        }
        int insert = newState();
        edge(insert, boundary[reg], digit, carry[boundary[reg]], 'R');
        int find = seek(boundary[reg], 'R', insert);
        int start = newState();
        edge(start, homeSymbol, returnMarkers[continuation], find, 'R');
        return start;
    }

    void allocateSymbols() {
        homeSymbol = newSymbol();
        inputBoundary[1] = homeSymbol;
        for (int i = 2; i <= 9; ++i) inputBoundary[i] = newSymbol();
        boundary.resize(nodes.size() + 1);
        for (int& symbol : boundary) symbol = newSymbol();
        endSymbol = newSymbol();
        outputEndSymbol = newSymbol();
        for (int& symbol : marked) symbol = newSymbol();
        for (int digit = 0; digit < 10; ++digit) suffixSymbols.push_back(digit);
        for (int symbol : marked) suffixSymbols.push_back(symbol);
        for (size_t i = 1; i < boundary.size(); ++i) suffixSymbols.push_back(boundary[i]);
        suffixSymbols.push_back(endSymbol);
        carry.resize(nextSymbol);
        for (int symbol : suffixSymbols) carry[symbol] = newState();
        appendReturn = newState();
        states[appendReturn].fallbackNext = appendReturn;
        states[appendReturn].fallbackDirection = 'L';
    }

    void buildCarry() {
        for (int symbol : suffixSymbols) {
            for (int current : suffixSymbols) edge(carry[symbol], current, symbol, carry[current], 'R');
            edge(carry[symbol], -1, symbol, appendReturn, 'L');
        }
    }

    void buildInitialization() {
        array<int, 10> scan, look;
        for (int i = 1; i <= 9; ++i) scan[i] = newState();
        for (int i = 1; i <= 9; ++i) look[i] = newState();
        int writeHome = newState();
        for (int digit = 0; digit < 10; ++digit) edge(0, digit, digit, writeHome, 'L');
        edge(writeHome, -1, homeSymbol, scan[1], 'R');
        int firstWriter = newState();
        edge(firstWriter, -1, endSymbol, home(entry[1]), 'L');
        for (int i = static_cast<int>(nodes.size()); i >= 0; --i) {
            int state = newState();
            edge(state, -1, boundary[i], firstWriter, 'R');
            firstWriter = state;
        }
        for (int i = 1; i <= 9; ++i) {
            for (int digit = 0; digit < 10; ++digit) edge(scan[i], digit, digit, scan[i], 'R');
            edge(scan[i], -1, -1, look[i], 'R');
            edge(look[i], -1, -1, firstWriter, 'L');
            if (i < 9) {
                int separator = newState();
                edge(separator, -1, inputBoundary[i + 1], scan[i + 1], 'R');
                for (int digit = 0; digit < 10; ++digit) edge(look[i], digit, digit, separator, 'L');
            }
        }
    }

    void buildVariable(int reg, int variable, int start, int next) {
        int take = newState();
        int scanEnd = newState();
        int restore = newState();
        int finish = home(next);
        for (int digit = 0; digit < 10; ++digit) {
            int push = append(reg, digit, start);
            edge(scanEnd, digit, digit, scanEnd, 'R');
            edge(scanEnd, marked[digit], marked[digit], scanEnd, 'R');
            edge(take, marked[digit], marked[digit], take, 'L');
            edge(take, digit, marked[digit], home(push), 'L');
            edge(restore, digit, digit, restore, 'R');
            edge(restore, marked[digit], digit, restore, 'R');
        }
        for (int i = 2; i <= 9; ++i) {
            edge(scanEnd, inputBoundary[i], inputBoundary[i], take, 'L');
            edge(restore, inputBoundary[i], inputBoundary[i], finish, 'S');
        }
        edge(scanEnd, boundary[0], boundary[0], take, 'L');
        edge(restore, boundary[0], boundary[0], finish, 'S');
        edge(take, inputBoundary[variable], inputBoundary[variable], restore, 'R');
        connect(start, seek(inputBoundary[variable], 'R', newState(scanEnd, 'R')));
    }

    int readRegister(int reg, const array<int, 11>& callbacks, bool consume) {
        int scan = newState();
        for (int digit = 0; digit < 10; ++digit) {
            edge(scan, digit, consume ? marked[digit] : digit, home(callbacks[digit]), 'L');
            if (consume) edge(scan, marked[digit], marked[digit], scan, 'R');
        }
        if (consume) edge(scan, boundary[reg], boundary[reg], home(callbacks[10]), 'L');
        return seek(boundary[reg - 1], 'R', newState(scan, 'R'));
    }

    void buildAddition(int reg, int left, int right, int start, int next) {
        array<int, 2> loop = {{start, newState()}};
        array<array<int, 10>, 2> push;
        for (int carryBit = 0; carryBit < 2; ++carryBit) {
            for (int digit = 0; digit < 10; ++digit) push[carryBit][digit] = append(reg, digit, loop[carryBit]);
        }
        int finalCarry = append(reg, 1, next);
        for (int carryBit = 0; carryBit < 2; ++carryBit) {
            array<int, 11> leftCallbacks;
            for (int x = 0; x <= 10; ++x) {
                array<int, 11> rightCallbacks;
                for (int y = 0; y <= 10; ++y) {
                    int sum = (x == 10 ? 0 : x) + (y == 10 ? 0 : y) + carryBit;
                    rightCallbacks[y] = x == 10 && y == 10 ? (carryBit ? finalCarry : next) : push[sum / 10][sum % 10];
                }
                leftCallbacks[x] = readRegister(right, rightCallbacks, true);
            }
            connect(loop[carryBit], readRegister(left, leftCallbacks, true));
        }
    }

    void buildMultiplication(int reg, int left, int right, int start, int next) {
        array<int, 10> push;
        array<int, 11> leftCallbacks = {};
        for (int digit = 0; digit < 10; ++digit) push[digit] = append(reg, digit, next);
        for (int x = 0; x < 10; ++x) {
            array<int, 11> rightCallbacks = {};
            for (int y = 0; y < 10; ++y) rightCallbacks[y] = push[x * y % 10];
            leftCallbacks[x] = readRegister(right, rightCallbacks, false);
        }
        connect(start, readRegister(left, leftCallbacks, false));
    }

    void buildNodes() {
        int count = static_cast<int>(nodes.size());
        for (int i = 0; i < count; ++i) {
            int reg = i + 1;
            int next = reg == count ? outputEntry : entry[reg + 1];
            const Node& node = nodes[i];
            if (node.op == 'v') buildVariable(reg, node.variable, entry[reg], next);
            else if (node.op == '+') buildAddition(reg, node.left + 1, node.right + 1, entry[reg], next);
            else buildMultiplication(reg, node.left + 1, node.right + 1, entry[reg], next);
        }
    }

    void buildOutput() {
        int root = static_cast<int>(nodes.size());
        int loop = newState();
        int take = newState();
        int finalMove = newState();
        edge(finalMove, endSymbol, endSymbol, haltState, 'R');
        int erase = newState();
        edge(erase, outputEndSymbol, -1, home(seek(endSymbol, 'R', finalMove)), 'L');
        edge(take, boundary[root - 1], boundary[root - 1], home(seek(outputEndSymbol, 'R', erase)), 'S');
        int writeMarker = newState();
        edge(writeMarker, -1, outputEndSymbol, home(loop), 'L');
        for (int digit = 0; digit < 10; ++digit) {
            int writeDigit = newState();
            edge(writeDigit, outputEndSymbol, digit, writeMarker, 'R');
            edge(take, digit, marked[digit], home(seek(outputEndSymbol, 'R', writeDigit)), 'L');
            edge(take, marked[digit], marked[digit], take, 'L');
        }
        connect(loop, seek(boundary[root], 'R', newState(take, 'L')));
        int afterEnd = newState();
        edge(afterEnd, endSymbol, endSymbol, writeMarker, 'R');
        connect(outputEntry, seek(endSymbol, 'R', afterEnd));
    }

    void lowerStationaryTransitions() {
        int originalCount = static_cast<int>(states.size());
        map<int, int> bridge;
        for (int state = 0; state < originalCount; ++state) {
            for (const auto& item : states[state].edges) {
                if (item.second.direction == 'S') bridge.emplace(item.second.next, -1);
            }
        }
        for (auto& item : bridge) item.second = newState(item.first, 'L');
        for (int state = 0; state < originalCount; ++state) {
            for (auto& item : states[state].edges) {
                Edge& transition = item.second;
                if (transition.direction == 'S') {
                    transition.next = bridge.at(transition.next);
                    transition.direction = 'R';
                }
            }
        }
    }

public:
    explicit Generator(const vector<Node>& tree) : nodes(tree) {
        newState();
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
    }

    void print() const {
        cout << nextSymbol - 1 << ' ' << max(1, static_cast<int>(states.size()) - 1) << '\n';
        for (int state = 0; state < static_cast<int>(states.size()); ++state) {
            const State& current = states[state];
            if (current.edges.empty() && current.fallbackNext == -1) continue;
            for (int symbol = -1; symbol < nextSymbol; ++symbol) {
                auto found = current.edges.find(symbol);
                if (found != current.edges.end()) {
                    const Edge& transition = found->second;
                    cout << state << ' ' << symbol << ' ' << transition.write << ' ' << transition.next << ' ' << transition.direction << '\n';
                } else if (current.fallbackNext != -1) {
                    cout << state << ' ' << symbol << ' ' << symbol << ' ' << current.fallbackNext << ' ' << current.fallbackDirection << '\n';
                }
            }
        }
        cout << "-\n";
    }
};

void printVariableOnly(int variable) {
    cout << "9 " << max(1, variable - 1) << '\n';
    for (int state = 0; state < variable - 1; ++state) {
        for (int digit = 0; digit < 10; ++digit) cout << state << ' ' << digit << ' ' << digit << ' ' << state << " R\n";
        cout << state << " -1 -1 " << state + 1 << " R\n";
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
        assert(parser.pos == expression.size());
        if (parser.nodes[root].op == 'v') printVariableOnly(parser.nodes[root].variable);
        else {
            Generator generator(parser.nodes);
            generator.print();
        }
    }
    return 0;
}
