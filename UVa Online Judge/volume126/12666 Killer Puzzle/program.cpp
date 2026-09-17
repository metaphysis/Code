#include <bits/stdc++.h>
using namespace std;

struct EvalError {};

struct Value {
    enum Type {
        Integer,
        String,
        Boolean,
        Function
    } type;
    long long intVal;
    string strVal;
    bool boolVal;
    shared_ptr<function<Value(const vector<Value>&)>> funcVal;
    static Value makeInteger(long long val) {
        Value res;
        res.type = Integer;
        res.intVal = val;
        return res;
    }

    static Value makeString(const string &val) {
        Value res;
        res.type = String;
        res.strVal = val;
        return res;
    }

    static Value makeBoolean(bool val) {
        Value res;
        res.type = Boolean;
        res.boolVal = val;
        return res;
    }

    static Value makeFunction(const function<Value(const vector<Value>&)> &func) {
        Value res;
        res.type = Function;
        res.funcVal = make_shared<function<Value(const vector<Value>&)>>(func);
        return res;
    }
};

struct Node {
    enum Type {
        Integer,
        String,
        Identifier,
        List
    } type;
    long long intVal;
    string strVal;
    vector<shared_ptr<Node>> children;
};

struct Parser {
    string text;
    int pos;
    Parser(const string &src) {
        text = src;
        pos = 0;
    }

    void skipSpaces() {
        while (pos < (int)text.size() && isspace((unsigned char)text[pos])) pos++;
    }

    shared_ptr<Node> parseExpression() {
        skipSpaces();
        if (pos >= (int)text.size()) throw EvalError();
        if (text[pos] == '(') return parseList();
        if (text[pos] == '"') return parseString();
        return parseAtom();
    }

    shared_ptr<Node> parseList() {
        shared_ptr<Node> node = make_shared<Node>();
        node->type = Node::List;
        pos++;
        skipSpaces();
        while (pos < (int)text.size() && text[pos] != ')') {
            node->children.push_back(parseExpression());
            skipSpaces();
        }
        if (pos >= (int)text.size() || text[pos] != ')') throw EvalError();
        pos++;
        return node;
    }

    shared_ptr<Node> parseString() {
        shared_ptr<Node> node = make_shared<Node>();
        string val;
        node->type = Node::String;
        pos++;
        while (pos < (int)text.size() && text[pos] != '"') {
            if (text[pos] == '\\' && pos + 1 < (int)text.size()) {
                pos++;
                val.push_back(text[pos]);
                pos++;
            } else {
                val.push_back(text[pos]);
                pos++;
            }
        }
        if (pos >= (int)text.size()) throw EvalError();
        pos++;
        node->strVal = val;
        return node;
    }

    shared_ptr<Node> parseAtom() {
        shared_ptr<Node> node = make_shared<Node>();
        string val;
        while (pos < (int)text.size() && !isspace((unsigned char)text[pos]) && text[pos] != '(' && text[pos] != ')') {
            val.push_back(text[pos]);
            pos++;
        }
        bool isNumber = !val.empty();
        for (char ch : val)
            if (!isdigit((unsigned char)ch)) isNumber = false;
        if (isNumber) {
            node->type = Node::Integer;
            node->intVal = stoll(val);
        } else {
            node->type = Node::Identifier;
            node->strVal = val;
        }
        return node;
    }
};

struct Solver {
    int n, m, curQuestion, curOption;
    vector<int> answers;
    vector<shared_ptr<Node>> questions;
    vector<vector<shared_ptr<Node>>> options;
    vector<vector<bool>> noneOption;
    vector<vector<int>> cacheState;
    vector<vector<Value>> cacheValue;
    unordered_map<string, Value> builtins;
    Solver(int questionCount, int optionCount) {
        n = questionCount;
        m = optionCount;
        curQuestion = curOption = -1;
        answers.assign(n, 0);
        questions.resize(n);
        options.assign(n, vector<shared_ptr<Node>>(m));
        noneOption.assign(n, vector<bool>(m, false));
        cacheState.assign(n, vector<int>(m, 0));
        cacheValue.assign(n, vector<Value>(m));
        initializeBuiltins();
    }

    bool sameValue(const Value &a, const Value &b) {
        if (a.type != b.type) return false;
        if (a.type == Value::Integer) return a.intVal == b.intVal;
        if (a.type == Value::String) return a.strVal == b.strVal;
        if (a.type == Value::Boolean) return a.boolVal == b.boolVal;
        return a.funcVal == b.funcVal;
    }

    bool isPrime(long long val) {
        if (val < 2) return false;
        for (long long i = 2; i <= val / i; i++)
            if (val % i == 0) return false;
        return true;
    }

    bool isFactorial(long long val) {
        if (val < 1) return false;
        long long product = 1;
        for (long long i = 1; product < val; i++) {
            if (product > val / (i + 1)) return false;
            product *= i + 1;
        }
        return product == val;
    }

    bool isSquare(long long val) {
        if (val < 0) return false;
        long long root = sqrt((long double)val);
        while (root < val / max(1LL, root)) root++;
        while (root > 0 && root > val / root) root--;
        return root * root == val;
    }

    bool isCubic(long long val) {
        if (val < 0) return false;
        long long root = cbrt((long double)val);
        while (root > 0 && root <= val / root && root * root <= val / max(1LL, root)) {
            if (root * root * root >= val) break;
            root++;
        }
        while (root > 0 && (root > val / root || root * root > val / root)) root--;
        return root * root * root == val;
    }

    bool isVowel(const string &val) {
        if (val.size() != 1 || !isalpha((unsigned char)val[0])) return false;
        char ch = tolower((unsigned char)val[0]);
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    bool isConsonant(const string &val) {
        if (val.size() != 1 || !isalpha((unsigned char)val[0])) return false;
        return !isVowel(val);
    }

    Value callFunction(const Value &func, const vector<Value> &args) {
        if (func.type != Value::Function) throw EvalError();
        return (*func.funcVal)(args);
    }

    bool callPredicate(const Value &pred, const Value &arg) {
        vector<Value> args(1, arg);
        Value res = callFunction(pred, args);
        if (res.type != Value::Boolean) throw EvalError();
        return res.boolVal;
    }

    Value evaluate(const shared_ptr<Node> &node) {
        if (node->type == Node::Integer) return Value::makeInteger(node->intVal);
        if (node->type == Node::String) return Value::makeString(node->strVal);
        if (node->type == Node::Identifier) {
            auto it = builtins.find(node->strVal);
            if (it == builtins.end()) throw EvalError();
            return it->second;
        }
        if (node->children.empty()) throw EvalError();
        Value func = evaluate(node->children[0]);
        vector<Value> args;
        for (int i = 1; i < (int)node->children.size(); i++) args.push_back(evaluate(node->children[i]));
        return callFunction(func, args);
    }

    Value evaluateOption(int question, int option) {
        if (question < 0 || question >= n || option < 0 || option >= m) throw EvalError();
        if (noneOption[question][option]) throw EvalError();
        if (cacheState[question][option] == 1 || cacheState[question][option] == 3) throw EvalError();
        if (cacheState[question][option] == 2) return cacheValue[question][option];
        cacheState[question][option] = 1;
        try {
            Value res = evaluate(options[question][option]);
            cacheValue[question][option] = res;
            cacheState[question][option] = 2;
            return res;
        } catch (...) {
            cacheState[question][option] = 3;
            throw;
        }
    }

    bool checkNormalOption(int question, int option) {
        curQuestion = question;
        curOption = option;
        try {
            Value res = evaluate(questions[question]);
            return res.type == Value::Boolean && res.boolVal;
        } catch (...) {
            return false;
        }
    }

    bool checkAssignment() {
        fillCache();
        for (int question = 0; question < n; question++) {
            int selected = answers[question];
            if (noneOption[question][selected]) {
                for (int option = 0; option < m; option++)
                    if (!noneOption[question][option] && checkNormalOption(question, option)) return false;
            } else {
                if (!checkNormalOption(question, selected)) return false;
                for (int option = 0; option < m; option++)
                    if (option != selected && !noneOption[question][option] && checkNormalOption(question, option)) return false;
            }
        }
        return true;
    }

    void fillCache() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) cacheState[i][j] = 0;
    }

    Value makePredicate(const function<bool(const Value&)> &pred) {
        return Value::makeFunction([pred](const vector<Value> &args) {
            if (args.size() != 1) throw EvalError();
            return Value::makeBoolean(pred(args[0]));
        });
    }

    void addBuiltin(const string &name, const function<Value(const vector<Value>&)> &func) {
        builtins[name] = Value::makeFunction(func);
    }

    void initializeBasicBuiltins() {
        addBuiltin("equal", [this](const vector<Value> &args) {
            if (args.size() != 2) throw EvalError();
            return Value::makeBoolean(sameValue(args[0], args[1]));
        });
        addBuiltin("option-value", [this](const vector<Value> &args) {
            if (!args.empty()) throw EvalError();
            return evaluateOption(curQuestion, curOption);
        });
        addBuiltin("answer", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Integer) throw EvalError();
            long long idx = args[0].intVal;
            if (idx < 1 || idx > n) throw EvalError();
            return Value::makeString(string(1, char('a' + answers[idx - 1])));
        });
        addBuiltin("answer-value", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Integer) throw EvalError();
            long long idx = args[0].intVal;
            if (idx < 1 || idx > n) throw EvalError();
            return evaluateOption(idx - 1, answers[idx - 1]);
        });
        addBuiltin("diff-answer", [this](const vector<Value> &args) {
            if (args.size() != 2 || args[0].type != Value::Integer || args[1].type != Value::Integer) throw EvalError();
            long long idx1 = args[0].intVal, idx2 = args[1].intVal;
            if (idx1 < 1 || idx1 > n || idx2 < 1 || idx2 > n) throw EvalError();
            return Value::makeInteger(abs(answers[idx1 - 1] - answers[idx2 - 1]));
        });
    }

    void initializePredicateBuiltins() {
        builtins["prime-p"] = makePredicate([this](const Value &val) {
            return val.type == Value::Integer && isPrime(val.intVal);
        });
        builtins["factorial-p"] = makePredicate([this](const Value &val) {
            return val.type == Value::Integer && isFactorial(val.intVal);
        });
        builtins["square-p"] = makePredicate([this](const Value &val) {
            return val.type == Value::Integer && isSquare(val.intVal);
        });
        builtins["cubic-p"] = makePredicate([this](const Value &val) {
            return val.type == Value::Integer && isCubic(val.intVal);
        });
        builtins["vowel-p"] = makePredicate([this](const Value &val) {
            return val.type == Value::String && isVowel(val.strVal);
        });
        builtins["consonant-p"] = makePredicate([this](const Value &val) {
            return val.type == Value::String && isConsonant(val.strVal);
        });
    }

    void initializeQueryBuiltins() {
        addBuiltin("first-question", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            for (int i = 1; i <= n; i++) {
                try {
                    if (callPredicate(args[0], Value::makeInteger(i))) return Value::makeInteger(i);
                } catch (...) {
                }
            }
            throw EvalError();
        });
        addBuiltin("last-question", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            for (int i = n; i >= 1; i--) {
                try {
                    if (callPredicate(args[0], Value::makeInteger(i))) return Value::makeInteger(i);
                } catch (...) {
                }
            }
            throw EvalError();
        });
        addBuiltin("only-question", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            int found = -1;
            for (int i = 1; i <= n; i++) {
                bool matched = false;
                try {
                    matched = callPredicate(args[0], Value::makeInteger(i));
                } catch (...) {
                    matched = false;
                }
                if (matched) {
                    if (found != -1) throw EvalError();
                    found = i;
                }
            }
            if (found == -1) throw EvalError();
            return Value::makeInteger(found);
        });
        addBuiltin("count-question", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            int count = 0;
            for (int i = 1; i <= n; i++) {
                try {
                    if (callPredicate(args[0], Value::makeInteger(i))) count++;
                } catch (...) {
                }
            }
            return Value::makeInteger(count);
        });
    }

    void initializeGeneratorBuiltins() {
        addBuiltin("make-answer-diff-next-equal", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Integer) throw EvalError();
            long long target = args[0].intVal;
            return makePredicate([this, target](const Value &val) {
                if (val.type != Value::Integer) throw EvalError();
                long long idx = val.intVal;
                if (idx < 1 || idx >= n) throw EvalError();
                return abs(answers[idx - 1] - answers[idx]) == target;
            });
        });
        addBuiltin("make-answer-equal", [this](const vector<Value> &args) {
            if (args.size() != 1) throw EvalError();
            Value target = args[0];
            return makePredicate([this, target](const Value &val) {
                if (val.type != Value::Integer) throw EvalError();
                long long idx = val.intVal;
                if (idx < 1 || idx > n) throw EvalError();
                return sameValue(Value::makeString(string(1, char('a' + answers[idx - 1]))), target);
            });
        });
        addBuiltin("make-answer-is", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            Value pred = args[0];
            return makePredicate([this, pred](const Value &val) {
                if (val.type != Value::Integer) throw EvalError();
                long long idx = val.intVal;
                if (idx < 1 || idx > n) throw EvalError();
                return callPredicate(pred, Value::makeString(string(1, char('a' + answers[idx - 1]))));
            });
        });
        addBuiltin("make-answer-value-equal", [this](const vector<Value> &args) {
            if (args.size() != 1) throw EvalError();
            Value target = args[0];
            return makePredicate([this, target](const Value &val) {
                if (val.type != Value::Integer) throw EvalError();
                long long idx = val.intVal;
                if (idx < 1 || idx > n) throw EvalError();
                return sameValue(evaluateOption(idx - 1, answers[idx - 1]), target);
            });
        });
        addBuiltin("make-answer-value-is", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            Value pred = args[0];
            return makePredicate([this, pred](const Value &val) {
                if (val.type != Value::Integer) throw EvalError();
                long long idx = val.intVal;
                if (idx < 1 || idx > n) throw EvalError();
                return callPredicate(pred, evaluateOption(idx - 1, answers[idx - 1]));
            });
        });
        addBuiltin("make-is-multiple", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Integer) throw EvalError();
            long long divisor = args[0].intVal;
            return makePredicate([divisor](const Value &val) {
                if (val.type != Value::Integer || divisor == 0) return false;
                return val.intVal % divisor == 0;
            });
        });
        addBuiltin("make-equal", [this](const vector<Value> &args) {
            if (args.size() != 1 || (args[0].type != Value::Integer && args[0].type != Value::String)) throw EvalError();
            Value target = args[0];
            return makePredicate([this, target](const Value &val) {
                return sameValue(val, target);
            });
        });
    }

    void initializeLogicBuiltins() {
        addBuiltin("make-not", [this](const vector<Value> &args) {
            if (args.size() != 1 || args[0].type != Value::Function) throw EvalError();
            Value pred = args[0];
            return makePredicate([this, pred](const Value &val) {
                return !callPredicate(pred, val);
            });
        });
        addBuiltin("make-and", [this](const vector<Value> &args) {
            if (args.size() != 2 || args[0].type != Value::Function || args[1].type != Value::Function) throw EvalError();
            Value pred1 = args[0], pred2 = args[1];
            return makePredicate([this, pred1, pred2](const Value &val) {
                bool first = callPredicate(pred1, val);
                bool second = callPredicate(pred2, val);
                return first && second;
            });
        });
        addBuiltin("make-or", [this](const vector<Value> &args) {
            if (args.size() != 2 || args[0].type != Value::Function || args[1].type != Value::Function) throw EvalError();
            Value pred1 = args[0], pred2 = args[1];
            return makePredicate([this, pred1, pred2](const Value &val) {
                bool first = callPredicate(pred1, val);
                bool second = callPredicate(pred2, val);
                return first || second;
            });
        });
    }

    void initializeBuiltins() {
        initializeBasicBuiltins();
        initializePredicateBuiltins();
        initializeQueryBuiltins();
        initializeGeneratorBuiltins();
        initializeLogicBuiltins();
    }

    bool nextAssignment() {
        for (int i = n - 1; i >= 0; i--) {
            answers[i]++;
            if (answers[i] < m) return true;
            answers[i] = 0;
        }
        return false;
    }

    vector<string> solve() {
        vector<string> result;
        do {
            if (checkAssignment()) {
                string answer;
                for (int val : answers) answer.push_back(char('a' + val));
                result.push_back(answer);
            }
        } while (nextAssignment());
        return result;
    }
};

string readNonEmptyLine() {
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        bool hasContent = false;
        for (char ch : line)
            if (!isspace((unsigned char)ch)) hasContent = true;
        if (hasContent) return line;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, caseNumber = 0;
    while (cin >> n >> m) {
        string line;
        getline(cin, line);
        Solver solver(n, m);
        for (int i = 0; i < n; i++) {
            line = readNonEmptyLine();
            solver.questions[i] = Parser(line).parseExpression();
            for (int j = 0; j < m; j++) {
                line = readNonEmptyLine();
                shared_ptr<Node> node = Parser(line).parseExpression();
                solver.options[i][j] = node;
                solver.noneOption[i][j] = node->type == Node::String && node->strVal == "none-of-above";
            }
        }
        vector<string> result = solver.solve();
        cout << "Case " << ++caseNumber << ":\n";
        for (const string &answer : result) cout << answer << '\n';
    }
    return 0;
}
