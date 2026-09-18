from decimal import Decimal, localcontext
import sys

maxPos = 9899999
guardDigits = 100
leftEnd = 9999
rightBegin = 9890001
rightEnd = 9899999
chunkSize = 100

with localcontext() as ctx:
    ctx.prec = maxPos + guardDigits
    root2 = Decimal(2).sqrt()
    root3 = Decimal(3).sqrt()
    value = (Decimal(1) + root3 - root2) / Decimal(2)
    digits = format(value, "f").split(".")[1]
    if len(digits) < maxPos:
        digits += "0" * (maxPos - len(digits))
    leftTable = digits[:leftEnd]
    rightTable = digits[rightBegin - 1:rightEnd]

assert len(leftTable) == 9999
assert len(rightTable) == 9999
assert leftTable[1] == "5"
assert leftTable[3] == "9"
assert leftTable[5] == "8"
assert rightTable[9899898 - rightBegin] == "4"

def writeLiteral(text):
    for begin in range(0, len(text), chunkSize):
        print('        "' + text[begin:begin + chunkSize] + '"')

print("#include <bits/stdc++.h>")
print("using namespace std;")
print()
print("int main() {")
print("    ios::sync_with_stdio(false);")
print("    cin.tie(nullptr);")
print("    static const string table[] = {")
writeLiteral(leftTable)
print("        ,")
writeLiteral(rightTable)
print("    };")
print("    int k;")
print("    while (cin >> k) {")
print("        if (k <= 9999) cout << table[0][k - 1] << '\\n';")
print("        else cout << table[1][k - 9890001] << '\\n';")
print("    }")
print("    return 0;")
print("}")
