#include <bits/stdc++.h>
using namespace std;

struct Instruction {
    int label, destLabel, dest;
    string type;
};

struct Program {
    int arity;
    vector<Instruction> code;
    vector<int> memo;
};

struct NodeKey {
    int var, low, high;
    bool operator == (const NodeKey &other) const {
        return var == other.var && low == other.low && high == other.high;
    }
};

struct NodeHash {
    size_t operator () (const NodeKey &key) const {
        size_t result = key.var + 1000003;
        result = result * 1000003 + key.low;
        result = result * 1000003 + key.high;
        return result;
    }
};

class BddManager {
private:
    unordered_map<NodeKey, int, NodeHash> uniqueTable;
public:
    BddManager() {
        uniqueTable.reserve(2000000);
    }
    int makeNode(int var, int low, int high) {
        if (low == high) return low;
        NodeKey key = {var, low, high};
        unordered_map<NodeKey, int, NodeHash>::iterator it = uniqueTable.find(key);
        if (it != uniqueTable.end()) return it->second;
        int id = static_cast<int>(uniqueTable.size()) + 2;
        uniqueTable[key] = id;
        return id;
    }
};

BddManager manager;

int buildBdd(Program &program, int pc, int pos) {
    int width = program.arity + 1;
    int key = pc * width + pos;
    if (program.memo[key] != -1) return program.memo[key];
    Instruction &instruction = program.code[pc];
    int result;
    if (instruction.type == "RET0") result = 0;
    else if (instruction.type == "RET1") result = 1;
    else if (instruction.type == "JMP") result = buildBdd(program, instruction.dest, pos);
    else {
        int low = buildBdd(program, pc + 1, pos + 1);
        int high = buildBdd(program, instruction.dest, pos + 1);
        result = manager.makeNode(pos, low, high);
    }
    program.memo[key] = result;
    return result;
}

Program readProgram(int arity) {
    Program program;
    program.arity = arity;
    string token;
    while (cin >> token) {
        if (token == "END") break;
        Instruction instruction;
        instruction.label = stoi(token);
        cin >> instruction.type;
        instruction.destLabel = -1;
        instruction.dest = -1;
        if (instruction.type == "BRTRUE" || instruction.type == "JMP") cin >> instruction.destLabel;
        program.code.push_back(instruction);
    }
    unordered_map<int, int> labelIndex;
    for (int i = 0; i < static_cast<int>(program.code.size()); i++) labelIndex[program.code[i].label] = i;
    for (int i = 0; i < static_cast<int>(program.code.size()); i++)
        if (program.code[i].destLabel != -1) program.code[i].dest = labelIndex[program.code[i].destLabel];
    program.memo.assign(program.code.size() * (arity + 1), -1);
    return program;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int testCount;
    cin >> testCount;
    for (int testId = 0; testId < testCount; testId++) {
        int pairCount;
        cin >> pairCount;
        if (testId > 0) cout << '\n';
        for (int pairId = 0; pairId < pairCount; pairId++) {
            int arity;
            cin >> arity;
            Program first = readProgram(arity);
            Program second = readProgram(arity);
            int firstRoot = buildBdd(first, 0, 0);
            int secondRoot = buildBdd(second, 0, 0);
            cout << (firstRoot == secondRoot ? 1 : 0) << '\n';
        }
    }
    return 0;
}
