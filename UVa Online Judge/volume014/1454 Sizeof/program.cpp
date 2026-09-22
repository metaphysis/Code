#include <bits/stdc++.h>
using namespace std;

struct TypeNode;

struct Field {
    TypeNode *type;
    int primitiveSize;
};

struct Scope {
    Scope *parent;
    unordered_map<string, TypeNode *> types;
};

struct TypeNode {
    vector<Field> fields;
    int state;
    long long size;
};

class Parser {
private:
    vector<string> tokens;
    vector<TypeNode *> nodes;
    vector<Scope *> scopes;
    int pos, wordSize;
    bool hasError;

    bool isIdentifier(const string &text) {
        if (text.empty())
            return false;
        if (!isalpha(text[0]) && text[0] != '_')
            return false;
        for (int i = 1, n = text.size(); i < n; i++)
            if (!isalnum(text[i]) && text[i] != '_')
                return false;
        return true;
    }

    bool isPrimitive(const string &text) {
        return text.size() == 2 && text[0] == 'T' && text[1] >= '1' && text[1] <= '9';
    }

    bool check(const string &text) {
        return pos < tokens.size() && tokens[pos] == text;
    }

    string getToken() {
        if (pos >= tokens.size()) {
            hasError = true;
            return "";
        }
        return tokens[pos++];
    }

    Scope *createScope(Scope *parent) {
        Scope *scope = new Scope();
        scope->parent = parent;
        scopes.push_back(scope);
        return scope;
    }

    TypeNode *createType() {
        TypeNode *type = new TypeNode();
        type->state = 0;
        type->size = 0;
        nodes.push_back(type);
        return type;
    }

    TypeNode *findType(Scope *scope, const string &name) {
        while (scope != nullptr) {
            auto it = scope->types.find(name);
            if (it != scope->types.end())
                return it->second;
            scope = scope->parent;
        }
        return nullptr;
    }

    void addType(Scope *scope, const string &name, TypeNode *type) {
        if (findType(scope, name) != nullptr) {
            hasError = true;
            return;
        }
        scope->types[name] = type;
    }

    void addField(TypeNode *owner, TypeNode *type, int primitiveSize, const string &name, unordered_set<string> &fieldNames) {
        if (fieldNames.count(name)) {
            hasError = true;
            return;
        }
        fieldNames.insert(name);
        owner->fields.push_back({type, primitiveSize});
    }

    TypeNode *parseStruct(Scope *scope) {
        getToken();
        string name;
        bool hasName = false;
        if (!check("{")) {
            name = getToken();
            hasName = true;
            if (!isIdentifier(name))
                hasError = true;
        }
        TypeNode *type = createType();
        if (hasName)
            addType(scope, name, type);
        if (!check("{")) {
            hasError = true;
            return type;
        }
        getToken();
        parseBody(type, scope);
        return type;
    }

    void parseFieldList(TypeNode *owner, TypeNode *type, int primitiveSize, unordered_set<string> &fieldNames) {
        while (true) {
            string name = getToken();
            if (!isIdentifier(name)) {
                hasError = true;
                return;
            }
            addField(owner, type, primitiveSize, name, fieldNames);
            if (!check(","))
                break;
            getToken();
        }
        if (!check(";")) {
            hasError = true;
            return;
        }
        getToken();
    }

    void parseMember(TypeNode *owner, Scope *scope, unordered_set<string> &fieldNames) {
        TypeNode *type = nullptr;
        int primitiveSize = 0;
        bool isDefinition = false;
        if (check("struct")) {
            type = parseStruct(scope);
            isDefinition = true;
        } else {
            string name = getToken();
            if (isPrimitive(name))
                primitiveSize = name[1] - '0';
            else {
                type = findType(scope, name);
                if (type == nullptr)
                    hasError = true;
            }
        }
        if (isDefinition && check(";")) {
            getToken();
            return;
        }
        parseFieldList(owner, type, primitiveSize, fieldNames);
    }

    void parseBody(TypeNode *owner, Scope *parentScope) {
        Scope *scope = createScope(parentScope);
        unordered_set<string> fieldNames;
        while (pos < tokens.size() && !check("}"))
            parseMember(owner, scope, fieldNames);
        if (!check("}")) {
            hasError = true;
            return;
        }
        getToken();
    }

    long long alignSize(long long value) {
        return (value + wordSize - 1) / wordSize * wordSize;
    }

    bool calculateSize(TypeNode *type) {
        if (type->state == 1)
            return false;
        if (type->state == 2)
            return true;
        type->state = 1;
        long long totalSize = 0;
        for (const Field &field : type->fields) {
            long long fieldSize;
            if (field.type != nullptr) {
                if (!calculateSize(field.type))
                    return false;
                fieldSize = field.type->size;
            } else {
                fieldSize = field.primitiveSize;
            }
            totalSize = alignSize(totalSize);
            totalSize += alignSize(fieldSize);
        }
        type->size = alignSize(totalSize);
        type->state = 2;
        return true;
    }

public:
    Parser(const vector<string> &inputTokens, int inputWordSize) {
        tokens = inputTokens;
        pos = 0;
        wordSize = inputWordSize;
        hasError = false;
    }

    ~Parser() {
        for (TypeNode *type : nodes)
            delete type;
        for (Scope *scope : scopes)
            delete scope;
    }

    long long solve() {
        Scope *globalScope = createScope(nullptr);
        TypeNode *root = nullptr;
        if (!check("struct")) {
            hasError = true;
        } else {
            root = parseStruct(globalScope);
            if (!check(";"))
                hasError = true;
            else
                getToken();
        }
        if (pos != tokens.size())
            hasError = true;
        for (TypeNode *type : nodes)
            if (!calculateSize(type))
                hasError = true;
        if (hasError || root == nullptr)
            return -1;
        return root->size;
    }
};

vector<string> tokenize(const string &text) {
    vector<string> tokens;
    int i = 0, n = text.size();
    while (i < n) {
        if (isspace(text[i])) {
            i++;
        } else if (isalnum(text[i]) || text[i] == '_') {
            int start = i;
            while (i < n && (isalnum(text[i]) || text[i] == '_'))
                i++;
            tokens.push_back(text.substr(start, i - start));
        } else {
            tokens.push_back(string(1, text[i]));
            i++;
        }
    }
    return tokens;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    string line;
    getline(cin, line);
    for (int testId = 0; testId < testCount; testId++) {
        string content;
        while (getline(cin, line)) {
            int index = 0, length = line.size();
            while (index < length && isspace(line[index]))
                index++;
            if (index < length && line[index] == '$')
                break;
            content += line;
            content += '\n';
        }
        vector<string> allTokens = tokenize(content);
        if (allTokens.empty()) {
            cout << "error\n";
            continue;
        }
        int wordSize = stoi(allTokens[0]);
        vector<string> declarationTokens(allTokens.begin() + 1, allTokens.end());
        Parser parser(declarationTokens, wordSize);
        long long answer = parser.solve();
        if (answer < 0)
            cout << "error\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
