#include <bits/stdc++.h>
using namespace std;

bool isNameChar(char ch) {
    return isalnum(static_cast<unsigned char>(ch)) || ch == '-';
}

void skipSpace(const string &doc, size_t &pos) {
    while (pos < doc.size() && isspace(static_cast<unsigned char>(doc[pos]))) ++pos;
}

string readName(const string &doc, size_t &pos) {
    size_t start = pos;
    while (pos < doc.size() && isNameChar(doc[pos])) ++pos;
    return doc.substr(start, pos - start);
}

bool isWellFormed(const string &doc) {
    vector<string> tagStack;
    unordered_set<string> activeNames;
    size_t pos = 0, len = doc.size();
    int rootCount = 0;
    while (pos < len) {
        if (doc[pos] != '<') {
            if (tagStack.empty() && !isspace(static_cast<unsigned char>(doc[pos]))) return false;
            ++pos;
            continue;
        }
        ++pos;
        if (pos == len) return false;
        if (doc[pos] == '/') {
            ++pos;
            string tagName = readName(doc, pos);
            if (tagName.empty()) return false;
            skipSpace(doc, pos);
            if (pos == len || doc[pos] != '>') return false;
            ++pos;
            if (tagStack.empty() || tagStack.back() != tagName) return false;
            activeNames.erase(tagName);
            tagStack.pop_back();
        } else {
            string tagName = readName(doc, pos);
            if (tagName.empty()) return false;
            unordered_set<string> attrNames;
            bool isEmpty = false, isClosed = false;
            while (pos < len) {
                size_t spaceStart = pos;
                skipSpace(doc, pos);
                if (pos == len) return false;
                if (doc[pos] == '>') {
                    ++pos;
                    isClosed = true;
                    break;
                }
                if (doc[pos] == '/') {
                    ++pos;
                    if (pos == len || doc[pos] != '>') return false;
                    ++pos;
                    isEmpty = true;
                    isClosed = true;
                    break;
                }
                if (pos == spaceStart) return false;
                string attrName = readName(doc, pos);
                if (attrName.empty() || !attrNames.insert(attrName).second) return false;
                skipSpace(doc, pos);
                if (pos == len || doc[pos] != '=') return false;
                ++pos;
                skipSpace(doc, pos);
                if (pos == len || doc[pos] != '"') return false;
                ++pos;
                while (pos < len && doc[pos] != '"') ++pos;
                if (pos == len) return false;
                ++pos;
            }
            if (!isClosed || activeNames.count(tagName)) return false;
            if (tagStack.empty()) {
                ++rootCount;
                if (rootCount > 1) return false;
            }
            if (!isEmpty) {
                tagStack.push_back(tagName);
                activeNames.insert(tagName);
            }
        }
    }
    return rootCount == 1 && tagStack.empty();
}

void printResult(const string &doc) {
    cout << (isWellFormed(doc) ? "well-formed" : "non well-formed") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line, doc;
    bool hasDoc = false;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line == "<?end?>") {
            if (hasDoc) printResult(doc);
            return 0;
        }
        if (line.compare(0, 5, "<?xml") == 0) {
            if (hasDoc) printResult(doc);
            doc.clear();
            hasDoc = true;
        } else if (hasDoc) {
            doc += line;
            doc += '\n';
        }
    }
    if (hasDoc) printResult(doc);
    return 0;
}
