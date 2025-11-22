// Calculator
// UVa ID: 10932
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

map<char, double> vars;
string expr;
int pos;

void skipSpaces() {
  while (pos < expr.size() && expr[pos] == ' ') pos++;
}

double parseExpression();

double parseFactor() {
  skipSpaces();
  if (expr[pos] == '(') {
    pos++;
    double result = parseExpression();
    skipSpaces();
    pos++; // skip ')'
    return result;
  }
  if (isdigit(expr[pos])) {
    double num = 0;
    while (pos < expr.size() && isdigit(expr[pos])) {
      num = num * 10 + (expr[pos] - '0');
      pos++;
    }
    return num;
  }
  if (isalpha(expr[pos])) {
    char var = expr[pos++];
    return vars[var];
  }
  return 0; // should not happen
}

double parseTerm() {
  double left = parseFactor();
  skipSpaces();
  while (pos < expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
    char op = expr[pos++];
    double right = parseFactor();
    if (op == '*') left *= right;
    else left /= right;
    skipSpaces();
  }
  return left;
}

double parseExpression() {
  double left = parseTerm();
  skipSpaces();
  while (pos < expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
    char op = expr[pos++];
    double right = parseTerm();
    if (op == '+') left += right;
    else left -= right;
    skipSpaces();
  }
  return left;
}

double evaluate(const string& e) {
  expr = e;
  pos = 0;
  return parseExpression();
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line.find('=') != string::npos) {
      char var = line[0];
      string rest = line.substr(2);
      vars[var] = evaluate(rest);
    } else {
      double result = evaluate(line);
      printf("%.2f\n", result);
    }
  }
  return 0;
}
