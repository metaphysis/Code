#include <bits/stdc++.h>
using namespace std;

struct CodeLine {
    int n;
    vector<string> data;
};

struct Module {
    int base;
    vector<pair<string, int>> defs;
    vector<string> refs;
    vector<CodeLine> codes;
};

struct Symbol {
    bool defined;
    bool duplicate;
    int value;
};

int hexVal(const string &s) {
    int val = 0;
    for (char c : s) {
        val <<= 4;
        if (c >= '0' && c <= '9') val += c - '0';
        else val += c - 'A' + 10;
    }
    return val;
}

int nextCheck(int check, int byte) {
    check = ((check << 1) | (check >> 15)) & 0xffff;
    check = (check + byte) & 0xffff;
    return check;
}

void linkCase(vector<Module> &mods, int caseNo) {
    map<string, Symbol> table;
    int nextAddr = 0x100;
    for (auto &mod : mods) {
        mod.base = nextAddr;
        for (const auto &def : mod.defs) {
            Symbol &sym = table[def.first];
            if (!sym.defined) {
                sym.defined = true;
                sym.value = mod.base + def.second;
            } else sym.duplicate = true;
        }
        for (const string &name : mod.refs) table[name].defined = table[name].defined;
        for (const CodeLine &code : mod.codes) nextAddr += code.n;
    }
    int check = 0;
    for (const Module &mod : mods) {
        for (const CodeLine &code : mod.codes) {
            for (int i = 0; i < (int)code.data.size();) {
                if (code.data[i] == "$") {
                    int idx = hexVal(code.data[i + 1]);
                    int val = 0;
                    if (idx < (int)mod.refs.size()) {
                        const string &name = mod.refs[idx];
                        if (table[name].defined) val = table[name].value;
                    }
                    check = nextCheck(check, (val >> 8) & 0xff);
                    check = nextCheck(check, val & 0xff);
                    i += 2;
                } else {
                    check = nextCheck(check, hexVal(code.data[i]));
                    i++;
                }
            }
        }
    }
    if (caseNo > 1) cout << "\n";
    cout << "Case " << caseNo << ": checksum = ";
    cout << uppercase << hex << setw(4) << setfill('0') << check;
    cout << setfill(' ') << dec << "\n";
    cout << " SYMBOL   ADDR\n";
    cout << "--------  ----\n";
    for (const auto &item : table) {
        cout << left << setw(10) << item.first;
        if (!item.second.defined) cout << "????";
        else {
            cout << right << uppercase << hex << setw(4) << setfill('0') << item.second.value;
            cout << setfill(' ') << dec;
            if (item.second.duplicate) cout << " M";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line, op, symbol, offset, token;
    vector<Module> mods;
    Module cur;
    bool inCase = false;
    int caseNo = 1;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> op;
        if (op.empty()) continue;
        if (op == "$") {
            if (!inCase) break;
            linkCase(mods, caseNo++);
            mods.clear();
            cur = Module();
            inCase = false;
        } else if (op == "D") {
            ss >> symbol >> offset;
            cur.defs.push_back({symbol, hexVal(offset)});
            inCase = true;
        } else if (op == "E") {
            ss >> symbol;
            cur.refs.push_back(symbol);
            inCase = true;
        } else if (op == "C") {
            CodeLine code;
            string count;
            ss >> count;
            code.n = hexVal(count);
            while (ss >> token) code.data.push_back(token);
            cur.codes.push_back(code);
            inCase = true;
        } else if (op == "Z") {
            mods.push_back(cur);
            cur = Module();
            inCase = true;
        }
    }
    return 0;
}
