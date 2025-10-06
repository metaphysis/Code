// Typesetting
// UVa ID: 235
// Verdict: Accepted
// Submission Date: 2025-10-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int font[110][10];
map<char, int> idx;
int paragraph = 1;
int L, W;

void process(string lines) {
    int printedLines = 1;
    int size = 1, point = 10;
    int currentWidth = 0, spaceWidth;
    string firstWord, lastWord, word;
    istringstream iss(lines);
    cout << "Paragraph " << paragraph++ << '\n';
    while (iss >> word) {
        if (word[0] == '*') {
            if (word[1] == 'f') size = stoi(word.substr(2));
            if (word[1] == 's') point = stoi(word.substr(2));
            continue;
        }
        int wordWidth = 0;
        for (int i = 0; i < word.length(); i++)
            // use integer instead of round function, or you will get 'Wrong Answer'
            wordWidth += (font[idx[word[i]]][size] * point + 5) / 10;
        if ((currentWidth && currentWidth + spaceWidth + wordWidth >= W) || wordWidth >= W) {
            if (currentWidth) {
                cout << "Line " << printedLines++ << ": " << firstWord << " ... " << lastWord;
                cout << " (" << (W - currentWidth) << " whitespace)\n";
                currentWidth = 0;
            }
            if (wordWidth >= W) {
                cout << "Line " << printedLines++ << ": " << word;
                if (wordWidth == W) cout << " ... " << word;
                cout << " (" << (W - wordWidth) << " whitespace)\n";
                wordWidth = 0;
            }
        }
        if (currentWidth) currentWidth += spaceWidth;
        else firstWord = word;
        if (wordWidth) {
            currentWidth += wordWidth;
            lastWord = word;
        }
        // use integer instead of round function, or you will get 'Wrong Answer'
        spaceWidth = (font[idx[' ']][size] * point + 5) / 10;
    }
    if (currentWidth) {
        cout << "Line " << printedLines++ << ": " << firstWord << " ... " << lastWord;
        cout << " (" << (W - currentWidth) << " whitespace)\n";
    }
}

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    int n = stoi(line);
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        istringstream iss(line);
        if (line.front() == ' ') idx.insert(make_pair(' ', i));
        else {
            char character;
            iss >> character;
            idx.insert(make_pair(character, i));
        }
        for (int j = 1; j <= 6; j++) iss >> font[i][j];
    }
    while (getline(cin, line)) {
        istringstream iss(line);
        iss >> L >> W;
        if (L == 0) break;
        string allLines;    
        for (int i = 1; i <= L; i++) {
            getline(cin, line);
            allLines += line + ' ';
        }
        process(allLines);
    }
	return 0;
}
