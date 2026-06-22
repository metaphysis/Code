// OOPS!
// UVa ID: 448
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<char, string> hex_value = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, 
    {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, 
    {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, 
    {'F', "1111"}
};

map<char, string> instruction = {
    {'0', "ADD"}, {'1', "SUB"}, {'2', "MUL"}, {'3', "DIV"}, {'4', "MOV"},
    {'5', "BREQ"}, {'6', "BRLE"}, {'7', "BRLS"}, {'8', "BRGE"}, {'9', "BRGR"},
    {'A', "BRNE"}, {'B', "BR"}, {'C', "AND"}, {'D', "OR"}, {'E', "XOR"},
    {'F', "NOT"}
};

string source_code;
int indexer = 0;

string getOperand(string& opcode)
{
    bitset<14> number(opcode.substr(2));
    string operand = to_string(number.to_ulong());
    if (opcode[0] == '0' && opcode[1] == '0') return "R" + operand;
    else if (opcode[0] == '0' && opcode[1] == '1') return "$" + operand;
    else if (opcode[0] == '1' && opcode[1] == '0') return "PC+" + operand;
    else return operand;
}

void arithmetic(char letter)
{
    string op1, op2;
    for (int i = 0; i < 4; i++) op1 += hex_value[source_code[indexer++]];
    for (int i = 0; i < 4; i++) op2 += hex_value[source_code[indexer++]];
    cout << instruction[letter] << ' ' << getOperand(op1) << ',' << getOperand(op2) << '\n';
}

void compare(char letter)
{
    string op1;
    for (int i = 0; i < 4; i++) op1 += hex_value[source_code[indexer++]];
    cout << instruction[letter] << ' ' << getOperand(op1) << '\n';    
}

void boolean(char letter)
{
    string op1, op2, op3;
    for (int i = 0; i < 4; i++) op1 += hex_value[source_code[indexer++]];
    for (int i = 0; i < 4; i++) op2 += hex_value[source_code[indexer++]];
    for (int i = 0; i < 4; i++) op3 += hex_value[source_code[indexer++]];
    cout << instruction[letter] << ' ';
    cout << getOperand(op1) << ',' << getOperand(op2) << ',' << getOperand(op3) << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line))
        source_code += line;

    for (int i = source_code.length(); i >= 0; i--)
        if (isblank(source_code[i]))
            source_code.erase(source_code.begin() + i);

    while (indexer < source_code.length())
    {
        char last_letter = source_code[indexer++];
        if (last_letter == '0' || last_letter == '1' || last_letter == '2' ||
            last_letter == '3' || last_letter == '4')
            arithmetic(last_letter);
        else if (last_letter == '5' || last_letter == '6' || last_letter == '7' ||
            last_letter == '8' || last_letter == '9' || last_letter == 'A' ||
            last_letter == 'B' || last_letter == 'F')
            compare(last_letter);
        else
            boolean(last_letter);
    }
    
	return 0;
}
