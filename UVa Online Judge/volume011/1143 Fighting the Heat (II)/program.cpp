#include <bits/stdc++.h>
using namespace std;

const int maxWord = 20005;
const int maxNode = 320005;
const int maxOcc = 320005;
const unsigned int base = 1000000000;

struct BigInteger {
    vector<unsigned int> digit;
    BigInteger(unsigned int value = 0) {
        if (value > 0)
            digit.push_back(value);
    }
    void add(const BigInteger &other) {
        int size, i;
        unsigned long long sum, carry;
        size = max(digit.size(), other.digit.size());
        digit.resize(size, 0);
        carry = 0;
        for (i = 0; i < size; i++) {
            sum = carry + digit[i];
            if (i < (int)other.digit.size())
                sum += other.digit[i];
            digit[i] = sum % base;
            carry = sum / base;
        }
        if (carry > 0)
            digit.push_back(carry);
    }
    string toString() const {
        int i;
        ostringstream output;
        if (digit.empty())
            return "0";
        output << digit.back();
        for (i = (int)digit.size() - 2; i >= 0; i--)
            output << setw(9) << setfill('0') << digit[i];
        return output.str();
    }
};

int n, m, nodeCount, occCount;
int trieNext[maxNode][26], head[maxNode];
int occWord[maxOcc], occNext[maxOcc];
int squareWord[16];
string wordList[maxWord];

int createNode() {
    return ++nodeCount;
}

void addWord(int wordId) {
    int node, i, index;
    node = 1;
    index = ++occCount;
    occWord[index] = wordId;
    occNext[index] = head[node];
    head[node] = index;
    for (i = 0; i < n; i++) {
        if (trieNext[node][wordList[wordId][i] - 'a'] == 0)
            trieNext[node][wordList[wordId][i] - 'a'] = createNode();
        node = trieNext[node][wordList[wordId][i] - 'a'];
        index = ++occCount;
        occWord[index] = wordId;
        occNext[index] = head[node];
        head[node] = index;
    }
}

BigInteger searchSquare(int depth) {
    int node, i, index;
    BigInteger answer;
    if (depth == n)
        return BigInteger(1);
    node = 1;
    for (i = 0; i < depth; i++) {
        node = trieNext[node][wordList[squareWord[i]][depth] - 'a'];
        if (node == 0)
            return answer;
    }
    for (index = head[node]; index != 0; index = occNext[index]) {
        squareWord[depth] = occWord[index];
        answer.add(searchSquare(depth + 1));
    }
    return answer;
}

int main() {
    int i;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        if (n == 0)
            break;
        cin >> m;
        nodeCount = 1;
        occCount = 0;
        memset(trieNext, 0, sizeof(trieNext));
        memset(head, 0, sizeof(head));
        for (i = 0; i < m; i++) {
            cin >> wordList[i];
            addWord(i);
        }
        cout << searchSquare(0).toString() << '\n';
    }
    return 0;
}
