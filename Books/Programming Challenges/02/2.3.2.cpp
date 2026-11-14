int calculate(string postfix) {
    stack<int> result;
    for (auto c : postfix) {
        // 如果为数字，将其压入结果栈。
        if (isdigit(c)) result.push(c - '0');
        else {
            // 计算并将结果入栈。注意出栈时运算数的先后顺序。
            int second = result.top(); result.pop();
            int first = result.top(); result.pop();
            if (c == '+') result.push(first + second);
            if (c == '-') result.push(first - second);
            if (c == '*') result.push(first * second);
            if (c == '/') result.push(first / second);
        }
    }
    return result.top();
}

// 定义运算符在栈中的优先级顺序，值越高，优先级越高。注意，括号在栈中的优先级最小。
map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}
};
// 比较运算符在栈中的优先级顺序。
bool lessPriority(char previous, char next) {
    return priority[previous] <= priority[next];
}
// 将中缀表达式转换为后缀表达式。
string toPostfix(string infix) {
    // 操作数栈和运算符栈。
    stack<char> operands, operators;
    for (auto c : infix) {
        // 如果是数字，直接压入操作数栈中。
        if (isdigit(c)) {
            operands.push(c);
            continue;
        }
        // 如果是左括号，直接压入运算符栈中。
        if (c == '(') {
            operators.push(c);
            continue;
        }
        // 如果是右括号。
        if (c == ')') {
            // 弹出运算符栈顶元素，直到遇到左括号。
            while (!operators.empty() && operators.top() != '(') {
                operands.push(operators.top());
                operators.pop();
            }
            // 操作符栈不为空，继续弹出匹配的左括号。
            if (!operators.empty()) operators.pop();
            continue;
        }
        // 如果是非括号运算符，当运算符栈为空，或者运算符栈顶元素为
        // 左括号，或者比运算符栈顶运算符的优先级高，将当前运算符压入
        // 运算符栈。
        if (operators.empty() || operators.top() == '(' ||
            !lessPriority(c, operators.top())) {
            operators.push(c);
        }
        else {
            // 当运算符的优先级比运算符栈栈顶元素的优先级低或相等时，
            // 弹出运算符栈栈顶元素，直到运算符栈为空，或者遇到比
            // 当前运算符优先级低的运算符时结束。
            while (!operators.empty() && lessPriority(c, operators.top())) {
                operands.push(operators.top());
                operators.pop();
            }
            // 将当前运算符压入运算符栈。
            operators.push(c);
        }
    }
    // 当中缀表达式处理完毕，运算符栈不为空时，逐个弹出压入到操作数栈中。
    while (!operators.empty()) {
        operands.push(operators.top());
        operators.pop();
    }
    // 获取操作数栈中保存的后缀表达式。注意，栈中保存的表达式是从左至右的顺序，
    // 但从栈中弹出时是从右至左的顺序，需要适当调整。
    string postfix;
    while (!operands.empty()) {
        postfix = operands.top() + postfix;
        operands.pop();
    }
    // 返回结果。
    return postfix;
}
