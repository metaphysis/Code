// Document Validator
// UVa ID: 831
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct CaseResult {
    bool valid;
    vector<string> structuralTags;
    vector<string> semanticTags;
};

bool isLetter(char currentChar) {
    return (currentChar >= 'a' && currentChar <= 'z') ||
           (currentChar >= 'A' && currentChar <= 'Z');
}

bool isTagCharacter(char currentChar) {
    return isLetter(currentChar) || (currentChar >= '0' && currentChar <= '9');
}

void addTag(const string &tag, vector<string> &tagList, set<string> &tagSet) {
    if (tagSet.count(tag) == 0) {
        tagSet.insert(tag);
        tagList.push_back(tag);
    }
}

CaseResult validateDocument(const vector<string> &document) {
    CaseResult result;
    result.valid = true;
    set<string> structuralSet;
    set<string> semanticSet;
    stack<string> tagStack;
    string text;
    for (const string &line : document) text += line + '\n';
    int length = static_cast<int>(text.size());
    int index = 0;
    while (index < length) {
        if (text[index] == '[') {
            int nameStart = index + 1;
            if (nameStart >= length || !isLetter(text[nameStart])) {
                result.valid = false;
                break;
            }
            int nameEnd = nameStart + 1;
            while (nameEnd < length && isTagCharacter(text[nameEnd]))
                ++nameEnd;
            if (nameEnd >= length || text[nameEnd] != '[') {
                result.valid = false;
                break;
            }
            string tag = text.substr(nameStart, nameEnd - nameStart);
            tagStack.push(tag);
            addTag(tag, result.structuralTags, structuralSet);
            index = nameEnd + 1;
        } else if (text[index] == ']') {
            int nameStart = index + 1;
            if (nameStart >= length || !isLetter(text[nameStart])) {
                result.valid = false;
                break;
            }
            int nameEnd = nameStart + 1;
            while (nameEnd < length && isTagCharacter(text[nameEnd]))
                ++nameEnd;
            if (nameEnd >= length || text[nameEnd] != ']') {
                result.valid = false;
                break;
            }
            string tag = text.substr(nameStart, nameEnd - nameStart);
            if (tagStack.empty() || tagStack.top() != tag) {
                result.valid = false;
                break;
            }
            tagStack.pop();
            addTag(tag, result.structuralTags, structuralSet);
            index = nameEnd + 1;
        } else if (text[index] == '{') {
            int nameStart = index + 1;
            if (nameStart >= length || !isLetter(text[nameStart])) {
                result.valid = false;
                break;
            }
            int nameEnd = nameStart + 1;
            while (nameEnd < length && isTagCharacter(text[nameEnd])) ++nameEnd;
            string tag = text.substr(nameStart, nameEnd - nameStart);
            int endIndex = nameEnd;
            bool hasClosingBrace = false;
            while (endIndex < length && text[endIndex] != '}') {
                if (text[endIndex] == '[' || text[endIndex] == ']' ||
                    text[endIndex] == '{') {
                    result.valid = false;
                    break;
                }
                ++endIndex;
            }
            if (!result.valid) break;
            if (endIndex < length && text[endIndex] == '}')
                hasClosingBrace = true;
            if (!hasClosingBrace) {
                result.valid = false;
                break;
            }
            addTag(tag, result.semanticTags, semanticSet);
            index = endIndex + 1;
        } else if (text[index] == '}') {
            result.valid = false;
            break;
        } else ++index;
    }
    if (!tagStack.empty()) result.valid = false;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount;
    cin >> caseCount;
    string line;
    getline(cin, line);
    for (int caseIndex = 0; caseIndex < caseCount; ++caseIndex) {
        vector<string> document;
        while (getline(cin, line) && line.empty()) ;
        if (cin && !line.empty()) document.push_back(line);
        while (getline(cin, line) && !line.empty()) document.push_back(line);
        CaseResult result = validateDocument(document);
        if (caseIndex > 0) cout << '\n';
        if (!result.valid) cout << "ERROR\n";
        else {
            cout << "STRUCTURAL TAGS\n";
            for (const string &tag : result.structuralTags) cout << tag << '\n';
            cout << "SEMANTIC TAGS\n";
            for (const string &tag : result.semanticTags) cout << tag << '\n';
        }
    }
    return 0;
}
