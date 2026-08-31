#include <bits/stdc++.h>
using namespace std;

const int maxDim = 14;

struct RawCommand {
    string left, first, second;
    char oper;
};

struct Operand {
    int kind, value;
};

struct Instruction {
    int type, target, source, oper;
};

using State = array<double, maxDim>;

string trimString(const string &s) {
    int left = 0, right = (int)s.size() - 1;
    while (left <= right && isspace((unsigned char)s[left]) != 0)
        ++left;
    while (right >= left && isspace((unsigned char)s[right]) != 0)
        --right;
    if (left > right)
        return "";
    return s.substr(left, right - left + 1);
}

string normalizeName(string s) {
    for (char &ch : s)
        ch = (char)toupper((unsigned char)ch);
    return s;
}

RawCommand parseCommand(string s) {
    string compact;
    for (char ch : s)
        if (isspace((unsigned char)ch) == 0)
            compact += ch;
    int assignPos = (int)compact.find(":=");
    int operPos = (int)compact.find_first_of("+-", assignPos + 2);
    RawCommand command;
    command.left = normalizeName(compact.substr(0, assignPos));
    command.first = normalizeName(compact.substr(assignPos + 2, operPos - assignPos - 2));
    command.second = normalizeName(compact.substr(operPos + 1));
    command.oper = compact[operPos];
    return command;
}

vector<RawCommand> readProgram(set<string> &nameSet) {
    vector<RawCommand> program;
    string line;
    while (getline(cin, line)) {
        line = trimString(line);
        if (line.empty())
            continue;
        if (line == "END")
            break;
        RawCommand command = parseCommand(line);
        program.push_back(command);
        nameSet.insert(command.left);
        if (isdigit((unsigned char)command.first[0]) == 0)
            nameSet.insert(command.first);
        if (isdigit((unsigned char)command.second[0]) == 0)
            nameSet.insert(command.second);
    }
    return program;
}

Operand makeOperand(const string &text, const map<string, int> &idMap) {
    Operand operand;
    if (isdigit((unsigned char)text[0]) != 0) {
        operand.kind = 1;
        operand.value = stoi(text);
    } else {
        operand.kind = 0;
        operand.value = idMap.at(text);
    }
    return operand;
}

vector<Instruction> compileProgram(const vector<RawCommand> &rawProgram, const map<string, int> &idMap) {
    vector<Instruction> program;
    for (const RawCommand &command : rawProgram) {
        Operand first = makeOperand(command.first, idMap);
        Operand second = makeOperand(command.second, idMap);
        program.push_back({0, 0, first.kind, first.value});
        program.push_back({1, 0, second.kind, second.value});
        program.push_back({2, 0, 0, command.oper == '+' ? 1 : -1});
        program.push_back({3, idMap.at(command.left), 0, 0});
    }
    return program;
}

double getValue(const State &state, const Operand &operand, double stateProb) {
    if (operand.kind == 1)
        return operand.value * stateProb;
    return state[operand.value];
}

void execute(State &state, const Instruction &instruction, int varCount, int programId, double stateProb) {
    int regBase = varCount + programId * 2;
    if (instruction.type == 0) {
        Operand operand = {instruction.source, instruction.oper};
        state[regBase] = getValue(state, operand, stateProb);
    } else if (instruction.type == 1) {
        Operand operand = {instruction.source, instruction.oper};
        state[regBase + 1] = getValue(state, operand, stateProb);
    } else if (instruction.type == 2) {
        state[regBase] += instruction.oper * state[regBase + 1];
    } else {
        state[instruction.target] = state[regBase];
    }
}

void addTransition(vector<vector<State>> &dp, vector<vector<double>> &stateProb, int fromI, int fromJ, int toI, int toJ, const vector<Instruction> &program, int programId, double transitionProb, int varCount) {
    State next = dp[fromI][fromJ];
    double currentProb = stateProb[fromI][fromJ];
    execute(next, program[programId == 0 ? fromI : fromJ], varCount, programId, currentProb);
    for (int k = 0; k < maxDim; ++k)
        dp[toI][toJ][k] += next[k] * transitionProb;
    stateProb[toI][toJ] += currentProb * transitionProb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    string line;
    getline(cin, line);
    for (int testCase = 0; testCase < testCount; ++testCase) {
        set<string> nameSet;
        vector<RawCommand> rawProgram1 = readProgram(nameSet);
        vector<RawCommand> rawProgram2 = readProgram(nameSet);
        map<string, int> idMap;
        int varCount = 0;
        for (const string &name : nameSet)
            idMap[name] = varCount++;
        vector<Instruction> program1 = compileProgram(rawProgram1, idMap);
        vector<Instruction> program2 = compileProgram(rawProgram2, idMap);
        int len1 = (int)program1.size(), len2 = (int)program2.size();
        vector<vector<State>> dp(len1 + 1, vector<State>(len2 + 1));
        vector<vector<double>> stateProb(len1 + 1, vector<double>(len2 + 1, 0.0));
        for (int i = 0; i <= len1; ++i)
            for (int j = 0; j <= len2; ++j)
                dp[i][j].fill(0.0);
        stateProb[0][0] = 1.0;
        for (int i = 0; i <= len1; ++i) {
            for (int j = 0; j <= len2; ++j) {
                if (i == len1 && j == len2)
                    continue;
                if (i < len1 && j < len2) {
                    addTransition(dp, stateProb, i, j, i + 1, j, program1, 0, 0.5, varCount);
                    addTransition(dp, stateProb, i, j, i, j + 1, program2, 1, 0.5, varCount);
                } else if (i < len1) {
                    addTransition(dp, stateProb, i, j, i + 1, j, program1, 0, 1.0, varCount);
                } else {
                    addTransition(dp, stateProb, i, j, i, j + 1, program2, 1, 1.0, varCount);
                }
            }
        }
        if (testCase > 0)
            cout << '\n';
        cout << fixed << setprecision(4);
        for (int i = 0; i < varCount; ++i) {
            double answer = dp[len1][len2][i];
            if (fabs(answer) < 0.00005)
                answer = 0.0;
            cout << answer << '\n';
        }
    }
    return 0;
}
