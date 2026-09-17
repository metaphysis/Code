#include <bits/stdc++.h>
using namespace std;

enum ValueType {
    NilType,
    BoolType,
    NumType,
    StrType,
    TableType,
    FuncType,
    IterType
};

struct Value;
struct Table;
struct Function;
struct Env;
struct Expr;
struct Stmt;

typedef shared_ptr<Expr> ExprPtr;
typedef shared_ptr<Stmt> StmtPtr;
typedef shared_ptr<Env> EnvPtr;

struct Value {
    ValueType type;
    bool boolean, iterPairs;
    double number;
    string str;
    shared_ptr<Table> table, iterTable;
    shared_ptr<Function> func;
    Value() : type(NilType), boolean(false), iterPairs(false), number(0) {}
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
    static Value makeTable();
    static Value makeFunc(const shared_ptr<Function> &value) {
        Value result;
        result.type = FuncType;
        result.func = value;
        return result;
    }
    static Value makeIter(const shared_ptr<Table> &value, bool pairs) {
        Value result;
        result.type = IterType;
        result.iterTable = value;
        result.iterPairs = pairs;
        return result;
    }
};

struct Table {
    map<string, pair<Value, Value> > data;
};

Value Value::makeTable() {
    Value result;
    result.type = TableType;
    result.table = make_shared<Table>();
    return result;
}

struct Env {
    map<string, Value> values;
    EnvPtr parent;
    Env(const EnvPtr &value = nullptr) : parent(value) {}
};

enum ExprType {
    NumberExpr,
    StringExpr,
    NilExpr,
    BoolExpr,
    TableExpr,
    VarExpr,
    UnaryExpr,
    BinaryExpr,
    CallExpr
};

struct Expr {
    ExprType type;
    bool boolean;
    double number;
    string text, op;
    ExprPtr left, right, callee;
    vector<ExprPtr> keys, args;
    Expr() : boolean(false), number(0) {}
};

enum StmtType {
    ExprStmt,
    AssignStmt,
    LocalStmt,
    BlockStmt,
    IfStmt,
    WhileStmt,
    RepeatStmt,
    NumForStmt,
    IterForStmt,
    FuncStmt,
    ReturnStmt,
    BreakStmt
};

struct IfPart {
    ExprPtr condition;
    vector<StmtPtr> body;
};

struct Stmt {
    StmtType type;
    string name;
    ExprPtr expr, expr2, expr3, variable;
    vector<string> params;
    vector<StmtPtr> body, elseBody;
    vector<IfPart> ifParts;
};

struct Function {
    bool native;
    function<Value(const vector<Value> &)> nativeFunc;
    vector<string> params;
    vector<StmtPtr> body;
    EnvPtr closure;
    Function() : native(false) {}
};

enum TokenType {
    EndToken,
    EolToken,
    NumberToken,
    StringToken,
    NameToken,
    SymbolToken
};

struct Token {
    TokenType type;
    string text;
    double number;
};

class Lexer {
private:
    string source;
    int position;
    vector<Token> tokens;
    bool isDigit(char ch) {
        return ch >= '0' && ch <= '9';
    }
    bool isAlpha(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
    }
    bool isHex(char ch) {
        return isDigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
    }
    void scanNumber() {
        int start = position;
        if (source[position] == '0' && position + 1 < (int)source.size() && (source[position + 1] == 'x' || source[position + 1] == 'X')) {
            position += 2;
            while (position < (int)source.size() && isHex(source[position])) position++;
            string text = source.substr(start, position - start);
            unsigned long long value = 0;
            for (int i = 2; i < (int)text.size(); i++) {
                value *= 16;
                if (text[i] >= '0' && text[i] <= '9') value += text[i] - '0';
                else if (text[i] >= 'a' && text[i] <= 'f') value += text[i] - 'a' + 10;
                else value += text[i] - 'A' + 10;
            }
            tokens.push_back({NumberToken, text, (double)value});
            return;
        }
        while (position < (int)source.size() && isDigit(source[position])) position++;
        if (position < (int)source.size() && source[position] == '.' && (position + 1 >= (int)source.size() || source[position + 1] != '.')) {
            position++;
            while (position < (int)source.size() && isDigit(source[position])) position++;
        }
        if (position < (int)source.size() && (source[position] == 'e' || source[position] == 'E')) {
            position++;
            if (position < (int)source.size() && (source[position] == '+' || source[position] == '-')) position++;
            while (position < (int)source.size() && isDigit(source[position])) position++;
        }
        string text = source.substr(start, position - start);
        tokens.push_back({NumberToken, text, stod(text)});
    }
    void scanString() {
        char quote = source[position++];
        string value;
        while (position < (int)source.size() && source[position] != quote) {
            if (source[position] == '\\') {
                position++;
                char ch = source[position++];
                if (ch == 'n') value.push_back('\n');
                else value.push_back(ch);
            } else {
                value.push_back(source[position++]);
            }
        }
        if (position < (int)source.size()) position++;
        tokens.push_back({StringToken, value, 0});
    }
    void scanName() {
        int start = position;
        while (position < (int)source.size() && (isAlpha(source[position]) || isDigit(source[position]))) position++;
        tokens.push_back({NameToken, source.substr(start, position - start), 0});
    }
    void scanSymbol() {
        string text(1, source[position++]);
        if (position < (int)source.size()) {
            string two = text + source[position];
            if (two == "==" || two == "~=" || two == "<=" || two == ">=" || two == "..") {
                text = two;
                position++;
            }
        }
        if (text == ".." && position < (int)source.size() && source[position] == '.') {
            text.push_back('.');
            position++;
        }
        tokens.push_back({SymbolToken, text, 0});
    }
    void scan() {
        while (position < (int)source.size()) {
            char ch = source[position];
            if (ch == ' ' || ch == '\t' || ch == '\r') position++;
            else if (ch == '\n') {
                tokens.push_back({EolToken, "", 0});
                position++;
            } else if (ch == '-' && position + 1 < (int)source.size() && source[position + 1] == '-') {
                while (position < (int)source.size() && source[position] != '\n') position++;
            } else if (isDigit(ch) || (ch == '.' && position + 1 < (int)source.size() && isDigit(source[position + 1]))) scanNumber();
            else if (ch == '\'' || ch == '"') scanString();
            else if (isAlpha(ch)) scanName();
            else scanSymbol();
        }
        tokens.push_back({EndToken, "", 0});
    }
public:
    Lexer(const string &value) : source(value), position(0) {
        scan();
    }
    const vector<Token> &getTokens() const {
        return tokens;
    }
};

class Parser {
private:
    vector<Token> tokens;
    int position;
    Token current() {
        return tokens[position];
    }
    void next() {
        if (position + 1 < (int)tokens.size()) position++;
    }
    bool match(const string &text) {
        if (current().text != text) return false;
        next();
        return true;
    }
    void skipEol() {
        while (current().type == EolToken) next();
    }
    int priority(const string &op) {
        if (op == "or") return 1;
        if (op == "and") return 2;
        if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "~=" || op == "==") return 3;
        if (op == "..") return 4;
        if (op == "+" || op == "-") return 5;
        if (op == "*" || op == "/" || op == "%") return 6;
        if (op == "^") return 8;
        return -1;
    }
    ExprPtr makeExpression(ExprType type) {
        ExprPtr result = make_shared<Expr>();
        result->type = type;
        return result;
    }
    ExprPtr parsePrimary() {
        Token token = current();
        if (token.type == NumberToken) {
            next();
            ExprPtr result = makeExpression(NumberExpr);
            result->number = token.number;
            return result;
        }
        if (token.type == StringToken) {
            next();
            ExprPtr result = makeExpression(StringExpr);
            result->text = token.text;
            return result;
        }
        if (token.text == "nil") {
            next();
            return makeExpression(NilExpr);
        }
        if (token.text == "true" || token.text == "false") {
            next();
            ExprPtr result = makeExpression(BoolExpr);
            result->boolean = token.text == "true";
            return result;
        }
        if (match("{")) {
            match("}");
            return makeExpression(TableExpr);
        }
        if (match("(")) {
            ExprPtr result = parseExpression(1);
            match(")");
            return result;
        }
        if (token.type == NameToken) {
            next();
            ExprPtr result = makeExpression(VarExpr);
            result->text = token.text;
            while (true) {
                if (match(".")) {
                    ExprPtr key = makeExpression(StringExpr);
                    key->text = current().text;
                    next();
                    result->keys.push_back(key);
                } else if (match("[")) {
                    result->keys.push_back(parseExpression(1));
                    match("]");
                } else if (match("(")) {
                    ExprPtr call = makeExpression(CallExpr);
                    call->callee = result;
                    if (!match(")")) {
                        while (true) {
                            call->args.push_back(parseExpression(1));
                            if (match(")")) break;
                            match(",");
                        }
                    }
                    result = call;
                } else break;
            }
            return result;
        }
        next();
        return makeExpression(NilExpr);
    }
    ExprPtr parseUnary() {
        if (current().text != "not" && current().text != "#" && current().text != "-") return parsePrimary();
        ExprPtr result = makeExpression(UnaryExpr);
        result->op = current().text;
        next();
        result->left = parseExpression(7);
        return result;
    }
    ExprPtr parseExpression(int minimum) {
        ExprPtr left = parseUnary();
        while (true) {
            string op = current().text;
            int value = priority(op);
            if (value < minimum) break;
            next();
            ExprPtr right = parseExpression(value + (op == "^" || op == ".." ? 0 : 1));
            ExprPtr result = makeExpression(BinaryExpr);
            result->op = op;
            result->left = left;
            result->right = right;
            left = result;
        }
        return left;
    }
    vector<StmtPtr> parseBlock(const set<string> &ends) {
        vector<StmtPtr> result;
        skipEol();
        while (current().type != EndToken && !ends.count(current().text)) {
            result.push_back(parseStatement());
            skipEol();
        }
        return result;
    }
    StmtPtr parseIf() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->type = IfStmt;
        IfPart part;
        part.condition = parseExpression(1);
        match("then");
        skipEol();
        part.body = parseBlock({"elseif", "else", "end"});
        result->ifParts.push_back(part);
        while (match("elseif")) {
            IfPart nextPart;
            nextPart.condition = parseExpression(1);
            match("then");
            skipEol();
            nextPart.body = parseBlock({"elseif", "else", "end"});
            result->ifParts.push_back(nextPart);
        }
        if (match("else")) {
            skipEol();
            result->elseBody = parseBlock({"end"});
        }
        match("end");
        return result;
    }
    StmtPtr parseWhile() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->type = WhileStmt;
        result->expr = parseExpression(1);
        match("do");
        skipEol();
        result->body = parseBlock({"end"});
        match("end");
        return result;
    }
    StmtPtr parseRepeat() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->type = RepeatStmt;
        skipEol();
        result->body = parseBlock({"until"});
        match("until");
        result->expr = parseExpression(1);
        return result;
    }
    StmtPtr parseFor() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->name = current().text;
        next();
        if (match("=")) {
            result->type = NumForStmt;
            result->expr = parseExpression(1);
            match(",");
            result->expr2 = parseExpression(1);
            if (match(",")) result->expr3 = parseExpression(1);
            else {
                result->expr3 = makeExpression(NumberExpr);
                result->expr3->number = 1;
            }
        } else {
            result->type = IterForStmt;
            match("in");
            result->expr = parseExpression(1);
        }
        match("do");
        skipEol();
        result->body = parseBlock({"end"});
        match("end");
        return result;
    }
    StmtPtr parseFunction() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->type = FuncStmt;
        result->name = current().text;
        next();
        match("(");
        if (!match(")")) {
            while (true) {
                result->params.push_back(current().text);
                next();
                if (match(")")) break;
                match(",");
            }
        }
        skipEol();
        result->body = parseBlock({"end"});
        match("end");
        return result;
    }
    StmtPtr parseLocal() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->type = LocalStmt;
        result->name = current().text;
        next();
        if (match("=")) result->expr = parseExpression(1);
        return result;
    }
    StmtPtr parseDo() {
        next();
        StmtPtr result = make_shared<Stmt>();
        result->type = BlockStmt;
        skipEol();
        result->body = parseBlock({"end"});
        match("end");
        return result;
    }
    StmtPtr parseStatement() {
        if (current().text == "if") return parseIf();
        if (current().text == "while") return parseWhile();
        if (current().text == "repeat") return parseRepeat();
        if (current().text == "for") return parseFor();
        if (current().text == "function") return parseFunction();
        if (current().text == "local") return parseLocal();
        if (current().text == "do") return parseDo();
        if (current().text == "return") {
            next();
            StmtPtr result = make_shared<Stmt>();
            result->type = ReturnStmt;
            if (current().type != EolToken && current().type != EndToken) result->expr = parseExpression(1);
            return result;
        }
        if (current().text == "break") {
            next();
            StmtPtr result = make_shared<Stmt>();
            result->type = BreakStmt;
            return result;
        }
        ExprPtr left = parseExpression(1);
        if (match("=")) {
            StmtPtr result = make_shared<Stmt>();
            result->type = AssignStmt;
            result->variable = left;
            result->expr = parseExpression(1);
            return result;
        }
        StmtPtr result = make_shared<Stmt>();
        result->type = ExprStmt;
        result->expr = left;
        return result;
    }
public:
    Parser(const string &source) : position(0) {
        Lexer lexer(source);
        tokens = lexer.getTokens();
    }
    vector<StmtPtr> parse() {
        return parseBlock({});
    }
};

enum FlowType {
    NormalFlow,
    ReturnFlow,
    BreakFlow
};

struct ExecResult {
    FlowType type;
    Value value;
    EnvPtr env;
    ExecResult(FlowType valueType, const EnvPtr &valueEnv) : type(valueType), env(valueEnv) {}
};

class Interpreter {
private:
    EnvPtr global;
    string keyOf(const Value &value) {
        if (value.type == NumType) {
            double number = value.number == 0 ? 0 : value.number;
            ostringstream output;
            output << setprecision(17) << number;
            return "n:" + output.str();
        }
        if (value.type == StrType) return "s:" + value.str;
        if (value.type == BoolType) return value.boolean ? "b:1" : "b:0";
        if (value.type == TableType) {
            ostringstream output;
            output << value.table.get();
            return "t:" + output.str();
        }
        if (value.type == FuncType) {
            ostringstream output;
            output << value.func.get();
            return "f:" + output.str();
        }
        return "nil";
    }
    bool truth(const Value &value) {
        if (value.type == NilType) return false;
        if (value.type == BoolType) return value.boolean;
        return true;
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
        if (value.type == FuncType) return "function";
        return "iterator";
    }
    int tableLength(const Value &value) {
        int length = 0;
        while (true) {
            string key = keyOf(Value::makeNum(length + 1));
            if (!value.table->data.count(key)) break;
            length++;
        }
        return length;
    }
    Value getVariable(const EnvPtr &env, const string &name) {
        EnvPtr current = env;
        while (current) {
            if (current->values.count(name)) return current->values[name];
            current = current->parent;
        }
        return Value::makeNil();
    }
    void setVariable(const EnvPtr &env, const string &name, const Value &value) {
        EnvPtr current = env;
        while (current) {
            if (current->values.count(name)) {
                current->values[name] = value;
                return;
            }
            current = current->parent;
        }
        if (value.type == NilType) global->values.erase(name);
        else global->values[name] = value;
    }
    bool equalValue(const Value &left, const Value &right) {
        if (left.type != right.type) return false;
        if (left.type == NilType) return true;
        if (left.type == BoolType) return left.boolean == right.boolean;
        if (left.type == NumType) return left.number == right.number;
        if (left.type == StrType) return left.str == right.str;
        if (left.type == TableType) return left.table == right.table;
        if (left.type == FuncType) return left.func == right.func;
        return left.iterTable == right.iterTable && left.iterPairs == right.iterPairs;
    }
    bool lessValue(const Value &left, const Value &right) {
        if (left.type == NumType) return left.number < right.number;
        return left.str < right.str;
    }
    Value evalVariable(const ExprPtr &expr, const EnvPtr &env) {
        Value result = getVariable(env, expr->text);
        for (const ExprPtr &keyExpr : expr->keys) {
            Value key = eval(keyExpr, env);
            if (result.type != TableType || key.type == NilType) return Value::makeNil();
            string keyText = keyOf(key);
            if (!result.table->data.count(keyText)) return Value::makeNil();
            result = result.table->data[keyText].second;
        }
        return result;
    }
    Value calculate(const Value &left, const string &op, const Value &right) {
        if (op == "+") return Value::makeNum(left.number + right.number);
        if (op == "-") return Value::makeNum(left.number - right.number);
        if (op == "*") return Value::makeNum(left.number * right.number);
        if (op == "/") return Value::makeNum(left.number / right.number);
        if (op == "%") return Value::makeNum(left.number - floor(left.number / right.number) * right.number);
        if (op == "^") return Value::makeNum(pow(left.number, right.number));
        if (op == "..") return Value::makeStr(toString(left) + toString(right));
        if (op == "==") return Value::makeBool(equalValue(left, right));
        if (op == "~=") return Value::makeBool(!equalValue(left, right));
        if (op == "<") return Value::makeBool(lessValue(left, right));
        if (op == ">") return Value::makeBool(lessValue(right, left));
        if (op == "<=") return Value::makeBool(!lessValue(right, left));
        if (op == ">=") return Value::makeBool(!lessValue(left, right));
        return Value::makeNil();
    }
    Value eval(const ExprPtr &expr, const EnvPtr &env) {
        if (!expr) return Value::makeNil();
        if (expr->type == NumberExpr) return Value::makeNum(expr->number);
        if (expr->type == StringExpr) return Value::makeStr(expr->text);
        if (expr->type == NilExpr) return Value::makeNil();
        if (expr->type == BoolExpr) return Value::makeBool(expr->boolean);
        if (expr->type == TableExpr) return Value::makeTable();
        if (expr->type == VarExpr) return evalVariable(expr, env);
        if (expr->type == CallExpr) {
            Value function = eval(expr->callee, env);
            vector<Value> args;
            for (const ExprPtr &arg : expr->args) args.push_back(eval(arg, env));
            return call(function, args);
        }
        if (expr->type == UnaryExpr) {
            Value value = eval(expr->left, env);
            if (expr->op == "not") return Value::makeBool(!truth(value));
            if (expr->op == "-") return Value::makeNum(-value.number);
            if (value.type == StrType) return Value::makeNum(value.str.size());
            if (value.type == TableType) return Value::makeNum(tableLength(value));
            return Value::makeNum(0);
        }
        if (expr->op == "and") {
            Value left = eval(expr->left, env);
            if (!truth(left)) return Value::makeBool(false);
            return Value::makeBool(truth(eval(expr->right, env)));
        }
        if (expr->op == "or") {
            Value left = eval(expr->left, env);
            if (truth(left)) return Value::makeBool(true);
            return Value::makeBool(truth(eval(expr->right, env)));
        }
        return calculate(eval(expr->left, env), expr->op, eval(expr->right, env));
    }
    void assign(const ExprPtr &variable, const Value &value, const EnvPtr &env) {
        if (variable->keys.empty()) {
            setVariable(env, variable->text, value);
            return;
        }
        Value current = getVariable(env, variable->text);
        for (int i = 0; i + 1 < (int)variable->keys.size(); i++) {
            Value key = eval(variable->keys[i], env);
            string keyText = keyOf(key);
            if (!current.table->data.count(keyText)) current.table->data[keyText] = make_pair(key, Value::makeTable());
            current = current.table->data[keyText].second;
        }
        Value key = eval(variable->keys.back(), env);
        string keyText = keyOf(key);
        if (value.type == NilType) current.table->data.erase(keyText);
        else current.table->data[keyText] = make_pair(key, value);
    }
    Value call(const Value &value, const vector<Value> &args) {
        if (value.type != FuncType) return Value::makeNil();
        if (value.func->native) return value.func->nativeFunc(args);
        EnvPtr callEnv = make_shared<Env>(value.func->closure);
        for (int i = 0; i < (int)value.func->params.size(); i++) {
            Value argument = i < (int)args.size() ? args[i] : Value::makeNil();
            callEnv->values[value.func->params[i]] = argument;
        }
        ExecResult result = executeBlock(value.func->body, callEnv);
        if (result.type == ReturnFlow) return result.value;
        return Value::makeNil();
    }
    ExecResult executeStatement(const StmtPtr &stmt, const EnvPtr &env) {
        if (stmt->type == ExprStmt) {
            eval(stmt->expr, env);
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == AssignStmt) {
            Value value = eval(stmt->expr, env);
            assign(stmt->variable, value, env);
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == BlockStmt) return executeBlock(stmt->body, make_shared<Env>(env));
        if (stmt->type == IfStmt) {
            for (const IfPart &part : stmt->ifParts)
                if (truth(eval(part.condition, env))) return executeBlock(part.body, make_shared<Env>(env));
            if (!stmt->elseBody.empty()) return executeBlock(stmt->elseBody, make_shared<Env>(env));
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == WhileStmt) {
            while (truth(eval(stmt->expr, env))) {
                ExecResult result = executeBlock(stmt->body, make_shared<Env>(env));
                if (result.type == ReturnFlow) return result;
                if (result.type == BreakFlow) break;
            }
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == RepeatStmt) {
            while (true) {
                EnvPtr repeatEnv = make_shared<Env>(env);
                ExecResult result = executeBlock(stmt->body, repeatEnv);
                if (result.type == ReturnFlow) return result;
                if (result.type == BreakFlow) break;
                if (truth(eval(stmt->expr, result.env))) break;
            }
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == NumForStmt) {
            double begin = eval(stmt->expr, env).number;
            double limit = eval(stmt->expr2, env).number;
            double step = eval(stmt->expr3, env).number;
            EnvPtr loopEnv = make_shared<Env>(env);
            loopEnv->values[stmt->name] = Value::makeNum(begin);
            for (double value = begin; step > 0 ? value <= limit : value >= limit; value += step) {
                loopEnv->values[stmt->name] = Value::makeNum(value);
                ExecResult result = executeBlock(stmt->body, make_shared<Env>(loopEnv));
                if (result.type == ReturnFlow) return result;
                if (result.type == BreakFlow) break;
            }
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == IterForStmt) {
            Value iterator = eval(stmt->expr, env);
            vector<Value> keys;
            if (iterator.type == IterType && iterator.iterPairs) {
                for (const auto &item : iterator.iterTable->data) keys.push_back(item.second.first);
            } else if (iterator.type == IterType) {
                Value table = Value::makeNil();
                table.type = TableType;
                table.table = iterator.iterTable;
                int length = tableLength(table);
                for (int i = 1; i <= length; i++) keys.push_back(Value::makeNum(i));
            }
            EnvPtr loopEnv = make_shared<Env>(env);
            loopEnv->values[stmt->name] = Value::makeNil();
            for (const Value &key : keys) {
                loopEnv->values[stmt->name] = key;
                ExecResult result = executeBlock(stmt->body, make_shared<Env>(loopEnv));
                if (result.type == ReturnFlow) return result;
                if (result.type == BreakFlow) break;
            }
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == FuncStmt) {
            shared_ptr<Function> functionValue = make_shared<Function>();
            functionValue->params = stmt->params;
            functionValue->body = stmt->body;
            functionValue->closure = env;
            global->values[stmt->name] = Value::makeFunc(functionValue);
            return ExecResult(NormalFlow, env);
        }
        if (stmt->type == ReturnStmt) {
            ExecResult result(ReturnFlow, env);
            result.value = eval(stmt->expr, env);
            return result;
        }
        return ExecResult(BreakFlow, env);
    }
    ExecResult executeBlock(const vector<StmtPtr> &body, const EnvPtr &startEnv) {
        EnvPtr env = startEnv;
        for (const StmtPtr &stmt : body) {
            if (stmt->type == LocalStmt) {
                Value value = eval(stmt->expr, env);
                EnvPtr nextEnv = make_shared<Env>(env);
                nextEnv->values[stmt->name] = value;
                env = nextEnv;
            } else {
                ExecResult result = executeStatement(stmt, env);
                if (result.type != NormalFlow) return result;
            }
        }
        return ExecResult(NormalFlow, env);
    }
    Value makeNative(const function<Value(const vector<Value> &)> &nativeFunc) {
        shared_ptr<Function> functionValue = make_shared<Function>();
        functionValue->native = true;
        functionValue->nativeFunc = nativeFunc;
        return Value::makeFunc(functionValue);
    }
    void setTable(const Value &table, const string &name, const Value &value) {
        Value key = Value::makeStr(name);
        table.table->data[keyOf(key)] = make_pair(key, value);
    }
    void initBuiltins() {
        global->values["print"] = makeNative([this](const vector<Value> &args) {
            cout << toString(args[0]) << '\n';
            return Value::makeNil();
        });
        global->values["tonumber"] = makeNative([](const vector<Value> &args) {
            if (args[0].type == NumType) return args[0];
            if (args[0].type != StrType) return Value::makeNil();
            char *end;
            double value = strtod(args[0].str.c_str(), &end);
            if (*end == '\0') return Value::makeNum(value);
            return Value::makeNil();
        });
        global->values["tostring"] = makeNative([this](const vector<Value> &args) {
            return Value::makeStr(toString(args[0]));
        });
        global->values["pairs"] = makeNative([](const vector<Value> &args) {
            return Value::makeIter(args[0].table, true);
        });
        global->values["ipairs"] = makeNative([](const vector<Value> &args) {
            return Value::makeIter(args[0].table, false);
        });
        Value math = Value::makeTable();
        setTable(math, "pi", Value::makeNum(acos(-1)));
        setTable(math, "abs", makeNative([](const vector<Value> &args) { return Value::makeNum(fabs(args[0].number)); }));
        setTable(math, "floor", makeNative([](const vector<Value> &args) { return Value::makeNum(floor(args[0].number)); }));
        setTable(math, "ceil", makeNative([](const vector<Value> &args) { return Value::makeNum(ceil(args[0].number)); }));
        setTable(math, "sqrt", makeNative([](const vector<Value> &args) { return Value::makeNum(sqrt(args[0].number)); }));
        setTable(math, "exp", makeNative([](const vector<Value> &args) { return Value::makeNum(exp(args[0].number)); }));
        setTable(math, "log", makeNative([](const vector<Value> &args) { return Value::makeNum(log(args[0].number)); }));
        setTable(math, "log10", makeNative([](const vector<Value> &args) { return Value::makeNum(log10(args[0].number)); }));
        setTable(math, "rad", makeNative([](const vector<Value> &args) { return Value::makeNum(args[0].number * acos(-1) / 180); }));
        setTable(math, "deg", makeNative([](const vector<Value> &args) { return Value::makeNum(args[0].number * 180 / acos(-1)); }));
        setTable(math, "acos", makeNative([](const vector<Value> &args) { return Value::makeNum(acos(args[0].number)); }));
        setTable(math, "asin", makeNative([](const vector<Value> &args) { return Value::makeNum(asin(args[0].number)); }));
        setTable(math, "atan", makeNative([](const vector<Value> &args) { return Value::makeNum(atan(args[0].number)); }));
        setTable(math, "atan2", makeNative([](const vector<Value> &args) { return Value::makeNum(atan2(args[0].number, args[1].number)); }));
        setTable(math, "cos", makeNative([](const vector<Value> &args) { return Value::makeNum(cos(args[0].number)); }));
        setTable(math, "sin", makeNative([](const vector<Value> &args) { return Value::makeNum(sin(args[0].number)); }));
        setTable(math, "tan", makeNative([](const vector<Value> &args) { return Value::makeNum(tan(args[0].number)); }));
        setTable(math, "min", makeNative([](const vector<Value> &args) { return Value::makeNum(min(args[0].number, args[1].number)); }));
        setTable(math, "max", makeNative([](const vector<Value> &args) { return Value::makeNum(max(args[0].number, args[1].number)); }));
        global->values["math"] = math;
        Value stringLib = Value::makeTable();
        setTable(stringLib, "rep", makeNative([](const vector<Value> &args) {
            string result;
            for (int i = 0; i < (int)args[1].number; i++) result += args[0].str;
            return Value::makeStr(result);
        }));
        setTable(stringLib, "sub", makeNative([](const vector<Value> &args) {
            int length = args[0].str.size(), left = (int)args[1].number;
            int right = args.size() >= 3 ? (int)args[2].number : -1;
            if (left < 0) left = length + left + 1;
            if (right < 0) right = length + right + 1;
            left = max(left, 1);
            right = min(right, length);
            if (left > right) return Value::makeStr("");
            return Value::makeStr(args[0].str.substr(left - 1, right - left + 1));
        }));
        global->values["string"] = stringLib;
        Value tableLib = Value::makeTable();
        setTable(tableLib, "concat", makeNative([this](const vector<Value> &args) {
            string result, separator = args.size() >= 2 ? args[1].str : "";
            int length = tableLength(args[0]);
            for (int i = 1; i <= length; i++) {
                if (i > 1) result += separator;
                result += args[0].table->data[keyOf(Value::makeNum(i))].second.str;
            }
            return Value::makeStr(result);
        }));
        setTable(tableLib, "sort", makeNative([this](const vector<Value> &args) {
            int length = tableLength(args[0]);
            vector<Value> values;
            for (int i = 1; i <= length; i++) values.push_back(args[0].table->data[keyOf(Value::makeNum(i))].second);
            Value comparator = args.size() >= 2 ? args[1] : Value::makeNil();
            sort(values.begin(), values.end(), [this, comparator](const Value &left, const Value &right) {
                if (comparator.type == FuncType) return truth(call(comparator, {left, right}));
                return lessValue(left, right);
            });
            for (int i = 1; i <= length; i++) {
                Value key = Value::makeNum(i);
                args[0].table->data[keyOf(key)] = make_pair(key, values[i - 1]);
            }
            return Value::makeNil();
        }));
        global->values["table"] = tableLib;
    }
public:
    Interpreter() {
        global = make_shared<Env>();
        initBuiltins();
    }
    void execute(const vector<StmtPtr> &program) {
        executeBlock(program, global);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> programs;
    string line, source;
    while (getline(cin, line)) {
        if (line.rfind("--", 0) == 0 && line.find("PROGRAM") != string::npos) {
            if (!source.empty()) {
                programs.push_back(source);
                source.clear();
            }
        } else {
            source += line;
            source.push_back('\n');
        }
    }
    if (!source.empty()) programs.push_back(source);
    for (int i = 0; i < (int)programs.size(); i++) {
        cout << "Program " << i + 1 << ":\n";
        Parser parser(programs[i]);
        Interpreter interpreter;
        interpreter.execute(parser.parse());
        cout << '\n';
    }
    return 0;
}
