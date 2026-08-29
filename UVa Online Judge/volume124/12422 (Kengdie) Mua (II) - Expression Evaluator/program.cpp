#include <bits/stdc++.h>
using namespace std;

enum ValueType {
    NilType,
    BoolType,
    NumType,
    StrType,
    TableType,
    FuncType
};

struct Value {
    ValueType type;
    bool boolean;
    double number;
    string str;
    shared_ptr<map<string, Value> > table;
    string func;
    Value() : type(NilType), boolean(false), number(0) {}
    static Value makeNil() {
        return Value();
    }
    static Value makeBool(bool value) {
        Value result;
        result.type = BoolType;
        result.boolean = value;
        return result;
    }
    static Value makeNum(double value) {
        Value result;
        result.type = NumType;
        result.number = value;
        return result;
    }
    static Value makeStr(const string &value) {
        Value result;
        result.type = StrType;
        result.str = value;
        return result;
    }
    static Value makeTable() {
        Value result;
        result.type = TableType;
        result.table = make_shared<map<string, Value> >();
        return result;
    }
    static Value makeFunc(const string &value) {
        Value result;
        result.type = FuncType;
        result.func = value;
        return result;
    }
};

struct Token {
    int type;
    string text;
    double number;
};

enum TokenType {
    EndToken,
    NumberToken,
    StringToken,
    NameToken,
    SymbolToken
};

class Lexer {
private:
    string source;
    int position;
    vector<Token> tokens;
public:
    Lexer(const string &value) : source(value), position(0) {
        scan();
    }
    const vector<Token> &getTokens() const {
        return tokens;
    }
private:
    void scan() {
        while (position < (int)source.size()) {
            char current = source[position];
            if (isspace((unsigned char)current)) {
                position++;
            } else if (isdigit((unsigned char)current) || (current == '.' && position + 1 < (int)source.size() && isdigit((unsigned char)source[position + 1]))) {
                scanNumber();
            } else if (isalpha((unsigned char)current) || current == '_') {
                scanName();
            } else if (current == '\'' || current == '"') {
                scanString();
            } else {
                scanSymbol();
            }
        }
        tokens.push_back({EndToken, "", 0});
    }
    void scanNumber() {
        int start = position;
        bool hasExp = false;
        while (position < (int)source.size()) {
            char current = source[position];
            if (isdigit((unsigned char)current) || current == '.') {
                position++;
            } else if ((current == 'e' || current == 'E') && !hasExp) {
                hasExp = true;
                position++;
                if (position < (int)source.size() && (source[position] == '+' || source[position] == '-')) position++;
            } else {
                break;
            }
        }
        string text = source.substr(start, position - start);
        tokens.push_back({NumberToken, text, stod(text)});
    }
    void scanName() {
        int start = position;
        while (position < (int)source.size() && (isalnum((unsigned char)source[position]) || source[position] == '_')) position++;
        tokens.push_back({NameToken, source.substr(start, position - start), 0});
    }
    void scanString() {
        char quote = source[position++];
        string value;
        while (position < (int)source.size()) {
            char current = source[position++];
            if (current == quote) break;
            if (current == '\\' && position < (int)source.size()) {
                char escaped = source[position++];
                if (escaped == 'n') value.push_back('\n');
                else if (escaped == 'r') value.push_back('\r');
                else if (escaped == 't') value.push_back('\t');
                else value.push_back(escaped);
            } else {
                value.push_back(current);
            }
        }
        tokens.push_back({StringToken, value, 0});
    }
    void scanSymbol() {
        string op;
        op.push_back(source[position++]);
        if (position < (int)source.size()) {
            string two = op + source[position];
            if (two == "==" || two == "~=" || two == "<=" || two == ">=" || two == "..") {
                op = two;
                position++;
            }
        }
        tokens.push_back({SymbolToken, op, 0});
    }
};

class Parser {
private:
    vector<Token> tokens;
    int position;
    map<string, Value> &variables;
public:
    Parser(const string &source, map<string, Value> &env) : position(0), variables(env) {
        Lexer lexer(source);
        tokens = lexer.getTokens();
    }
    Value parse() {
        return parseExpression(1);
    }
    Value parseLValue(vector<string> &keys, string &base) {
        base = current().text;
        next();
        while (true) {
            if (match(".")) {
                keys.push_back(current().text);
                next();
            } else if (match("[")) {
                Value key = parseExpression(1);
                keys.push_back(keyString(key));
                expect("]");
            } else {
                break;
            }
        }
        return variables[base];
    }
private:
    Token current() {
        return tokens[position];
    }
    void next() {
        if (position < (int)tokens.size() - 1) position++;
    }
    bool match(const string &text) {
        if (current().text == text) {
            next();
            return true;
        }
        return false;
    }
    void expect(const string &text) {
        if (current().text == text) next();
    }
    Value parseExpression(int minimum) {
        Value left = parseUnary();
        while (true) {
            string op = current().text;
            int priority = getPriority(op);
            if (priority < minimum) break;
            next();
            int nextPriority = priority + (op == "^" ? 0 : 1);
            Value right = parseExpression(nextPriority);
            left = calculate(left, op, right);
        }
        return left;
    }
    Value parseUnary() {
        string op = current().text;
        if (op == "not" || op == "#" || op == "-") {
            next();
            Value value = parseExpression(7);
            if (op == "not") return Value::makeBool(!truth(value));
            if (op == "-") return Value::makeNum(-value.number);
            if (value.type == StrType) return Value::makeNum((double)value.str.size());
            if (value.type == TableType) return Value::makeNum((double)tableLength(value));
            return Value::makeNum(0);
        }
        return parsePrimary();
    }
    Value parsePrimary() {
        Token token = current();
        if (token.type == NumberToken) {
            next();
            return Value::makeNum(token.number);
        }
        if (token.type == StringToken) {
            next();
            return Value::makeStr(token.text);
        }
        if (token.text == "nil") {
            next();
            return Value::makeNil();
        }
        if (token.text == "true") {
            next();
            return Value::makeBool(true);
        }
        if (token.text == "false") {
            next();
            return Value::makeBool(false);
        }
        if (match("{")) {
            expect("}");
            return Value::makeTable();
        }
        if (match("(")) {
            Value value = parseExpression(1);
            expect(")");
            return parsePostfix(value);
        }
        if (token.type == NameToken) {
            string name = token.text;
            next();
            Value value = getVariable(name);
            value = parsePostfix(value);
            return value;
        }
        next();
        return Value::makeNil();
    }
    Value parsePostfix(Value value) {
        while (true) {
            if (match(".")) {
                string name = current().text;
                next();
                value = getElement(value, Value::makeStr(name));
            } else if (match("[")) {
                Value key = parseExpression(1);
                expect("]");
                value = getElement(value, key);
            } else if (match("(")) {
                vector<Value> args;
                if (!match(")")) {
                    while (true) {
                        args.push_back(parseExpression(1));
                        if (match(")")) break;
                        expect(",");
                    }
                }
                value = callFunction(value, args);
            } else {
                break;
            }
        }
        return value;
    }
    int getPriority(const string &op) {
        if (op == "or") return 1;
        if (op == "and") return 2;
        if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "~=" || op == "==") return 3;
        if (op == "..") return 4;
        if (op == "+" || op == "-") return 5;
        if (op == "*" || op == "/" || op == "%") return 6;
        if (op == "^") return 8;
        return -1;
    }
    Value getVariable(const string &name) {
        if (variables.count(name)) return variables[name];
        return Value::makeNil();
    }
    Value getElement(const Value &value, const Value &key) {
        if (value.type != TableType || key.type == NilType) return Value::makeNil();
        string id = keyString(key);
        if (!value.table->count(id)) return Value::makeNil();
        return (*value.table)[id];
    }
    string keyString(const Value &value) {
        if (value.type == NumType) {
            ostringstream output;
            output << setprecision(17) << value.number;
            return "n:" + output.str();
        }
        if (value.type == StrType) return "s:" + value.str;
        if (value.type == BoolType) return value.boolean ? "b:1" : "b:0";
        if (value.type == FuncType) return "f:" + value.func;
        if (value.type == TableType) {
            ostringstream output;
            output << "t:" << value.table.get();
            return output.str();
        }
        return "nil";
    }
    bool truth(const Value &value) {
        if (value.type == NilType) return false;
        if (value.type == BoolType) return value.boolean;
        return true;
    }
    int tableLength(const Value &value) {
        int length = 0;
        while (true) {
            string key = keyString(Value::makeNum(length + 1));
            if (!value.table->count(key) || (*value.table)[key].type == NilType) break;
            length++;
        }
        return length;
    }
    Value calculate(const Value &left, const string &op, const Value &right) {
        if (op == "and") return Value::makeBool(truth(left) && truth(right));
        if (op == "or") return Value::makeBool(truth(left) || truth(right));
        if (op == "+") return Value::makeNum(left.number + right.number);
        if (op == "-") return Value::makeNum(left.number - right.number);
        if (op == "*") return Value::makeNum(left.number * right.number);
        if (op == "/") return Value::makeNum(left.number / right.number);
        if (op == "%") return Value::makeNum(left.number - floor(left.number / right.number) * right.number);
        if (op == "^") return Value::makeNum(pow(left.number, right.number));
        if (op == "..") return Value::makeStr(toString(left) + toString(right));
        if (op == "==") return Value::makeBool(equal(left, right));
        if (op == "~=") return Value::makeBool(!equal(left, right));
        if (op == "<") return Value::makeBool(less(left, right));
        if (op == ">") return Value::makeBool(less(right, left));
        if (op == "<=") return Value::makeBool(!less(right, left));
        if (op == ">=") return Value::makeBool(!less(left, right));
        return Value::makeNil();
    }
    bool equal(const Value &left, const Value &right) {
        if (left.type != right.type) return false;
        if (left.type == NilType) return true;
        if (left.type == BoolType) return left.boolean == right.boolean;
        if (left.type == NumType) return left.number == right.number;
        if (left.type == StrType) return left.str == right.str;
        if (left.type == FuncType) return left.func == right.func;
        return left.table == right.table;
    }
    bool less(const Value &left, const Value &right) {
        if (left.type == NumType) return left.number < right.number;
        return left.str < right.str;
    }
    string toString(const Value &value) {
        if (value.type == NilType) return "nil";
        if (value.type == BoolType) return value.boolean ? "true" : "false";
        if (value.type == NumType) {
            char buffer[100];
            sprintf(buffer, "%.14g", value.number);
            return buffer;
        }
        if (value.type == StrType) return value.str;
        if (value.type == TableType) return "table";
        return "function";
    }
    Value callFunction(const Value &function, const vector<Value> &args) {
        string name = function.func;
        if (function.type != FuncType) return Value::makeNil();
        if (name == "print") {
            cout << toString(args[0]) << '\n';
            return Value::makeNil();
        }
        if (name == "tonumber") {
            if (args[0].type == NumType) return args[0];
            if (args[0].type == StrType) {
                char *end;
                double value = strtod(args[0].str.c_str(), &end);
                if (*end == '\0') return Value::makeNum(value);
            }
            return Value::makeNil();
        }
        if (name == "tostring") return Value::makeStr(toString(args[0]));
        if (name == "math.abs") return Value::makeNum(fabs(args[0].number));
        if (name == "math.floor") return Value::makeNum(floor(args[0].number));
        if (name == "math.ceil") return Value::makeNum(ceil(args[0].number));
        if (name == "math.sqrt") return Value::makeNum(sqrt(args[0].number));
        if (name == "math.exp") return Value::makeNum(exp(args[0].number));
        if (name == "math.log") return Value::makeNum(log(args[0].number));
        if (name == "math.log10") return Value::makeNum(log10(args[0].number));
        if (name == "math.rad") return Value::makeNum(args[0].number * acos(-1) / 180.0);
        if (name == "math.deg") return Value::makeNum(args[0].number * 180.0 / acos(-1));
        if (name == "math.acos") return Value::makeNum(acos(args[0].number));
        if (name == "math.asin") return Value::makeNum(asin(args[0].number));
        if (name == "math.atan") return Value::makeNum(atan(args[0].number));
        if (name == "math.atan2") return Value::makeNum(atan2(args[0].number, args[1].number));
        if (name == "math.cos") return Value::makeNum(cos(args[0].number));
        if (name == "math.sin") return Value::makeNum(sin(args[0].number));
        if (name == "math.tan") return Value::makeNum(tan(args[0].number));
        if (name == "math.min") return Value::makeNum(min(args[0].number, args[1].number));
        if (name == "math.max") return Value::makeNum(max(args[0].number, args[1].number));
        if (name == "string.rep") {
            string result;
            for (int i = 0; i < (int)args[1].number; i++) result += args[0].str;
            return Value::makeStr(result);
        }
        if (name == "string.sub") {
            int length = args[0].str.size();
            int left = (int)args[1].number;
            int right = args.size() == 3 ? (int)args[2].number : -1;
            if (left < 0) left = length + left + 1;
            if (right < 0) right = length + right + 1;
            left = max(left, 1);
            right = min(right, length);
            if (left > right) return Value::makeStr("");
            return Value::makeStr(args[0].str.substr(left - 1, right - left + 1));
        }
        if (name == "table.concat") {
            string separator = args.size() == 2 ? args[1].str : "";
            string result;
            int length = tableLength(args[0]);
            for (int i = 1; i <= length; i++) {
                if (i > 1) result += separator;
                result += getElement(args[0], Value::makeNum(i)).str;
            }
            return Value::makeStr(result);
        }
        return Value::makeNil();
    }
};

void initBuiltins(map<string, Value> &variables) {
    variables["print"] = Value::makeFunc("print");
    variables["tonumber"] = Value::makeFunc("tonumber");
    variables["tostring"] = Value::makeFunc("tostring");
    variables["math"] = Value::makeTable();
    variables["string"] = Value::makeTable();
    variables["table"] = Value::makeTable();
    (*variables["math"].table)["s:pi"] = Value::makeNum(acos(-1));
    vector<string> mathNames = {"abs", "floor", "ceil", "sqrt", "exp", "log", "log10", "rad", "deg", "acos", "asin", "atan", "atan2", "cos", "sin", "tan", "min", "max"};
    for (const string &name : mathNames) (*variables["math"].table)["s:" + name] = Value::makeFunc("math." + name);
    (*variables["string"].table)["s:rep"] = Value::makeFunc("string.rep");
    (*variables["string"].table)["s:sub"] = Value::makeFunc("string.sub");
    (*variables["table"].table)["s:concat"] = Value::makeFunc("table.concat");
}

bool findAssignment(const string &line, int &position) {
    int round = 0, square = 0;
    bool quoted = false;
    char quote = 0;
    for (int i = 0; i < (int)line.size(); i++) {
        char current = line[i];
        if (quoted) {
            if (current == '\\') i++;
            else if (current == quote) quoted = false;
        } else if (current == '\'' || current == '"') {
            quoted = true;
            quote = current;
        } else if (current == '(') {
            round++;
        } else if (current == ')') {
            round--;
        } else if (current == '[') {
            square++;
        } else if (current == ']') {
            square--;
        } else if (current == '=' && round == 0 && square == 0 && (i + 1 == (int)line.size() || line[i + 1] != '=')) {
            position = i;
            return true;
        }
    }
    return false;
}

void assignValue(const string &left, const Value &value, map<string, Value> &variables) {
    Parser parser(left, variables);
    vector<string> keys;
    string base;
    Value root = parser.parseLValue(keys, base);
    if (keys.empty()) {
        if (value.type == NilType) variables.erase(base);
        else variables[base] = value;
        return;
    }
    Value *current = &variables[base];
    for (int i = 0; i + 1 < (int)keys.size(); i++) {
        if (current->type != TableType) *current = Value::makeTable();
        if (!current->table->count(keys[i]) || (*current->table)[keys[i]].type == NilType) (*current->table)[keys[i]] = Value::makeTable();
        current = &(*current->table)[keys[i]];
    }
    if (current->type != TableType) *current = Value::makeTable();
    if (value.type == NilType) current->table->erase(keys.back());
    else (*current->table)[keys.back()] = value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    map<string, Value> variables;
    initBuiltins(variables);
    while (getline(cin, line)) {
        if (line.empty()) {
            variables.clear();
            initBuiltins(variables);
            continue;
        }
        int assignment;
        if (findAssignment(line, assignment)) {
            string left = line.substr(0, assignment);
            string right = line.substr(assignment + 1);
            Parser parser(right, variables);
            assignValue(left, parser.parse(), variables);
        } else {
            Parser parser(line, variables);
            parser.parse();
        }
    }
    return 0;
}
