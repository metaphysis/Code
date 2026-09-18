#include <bits/stdc++.h>
using namespace std;

string trimText(const string &text) {
    size_t leftPos, rightPos;
    leftPos = text.find_first_not_of(' ');
    if (leftPos == string::npos) return "";
    rightPos = text.find_last_not_of(' ');
    return text.substr(leftPos, rightPos - leftPos + 1);
}

void printShelf(const deque<string> &bookQueue, const map<string, int> &bookSize, int shelfSize, int usedSpace) {
    for (const string &title : bookQueue)
        cout << left << setw(29) << title << right << setw(5) << bookSize.at(title) << '\n';
    cout << left << setw(29) << "AVAILABLE SHELF SPACE:" << right << setw(5) << shelfSize - usedSpace << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int shelfSize, usedSpace;
    cin >> shelfSize;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Program 2 by team X\n";
    deque<string> bookQueue;
    map<string, int> bookSize;
    string line, action, title, back;
    usedSpace = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        action = trimText(line.substr(0, min(static_cast<int>(line.size()), 9)));
        if (action == "PRINT") {
            printShelf(bookQueue, bookSize, shelfSize, usedSpace);
        } else if (action == "ADD") {
            title = trimText(line.substr(9, 30));
            bookSize[title] = stoi(line.substr(39));
            bookQueue.push_front(title);
            usedSpace += bookSize[title];
            while (usedSpace > shelfSize) {
                back = bookQueue.back();
                bookQueue.pop_back();
                usedSpace -= bookSize[back];
            }
        } else if (action == "RETURN") {
            title = trimText(line.substr(9));
            bookQueue.push_front(title);
            usedSpace += bookSize[title];
            while (usedSpace > shelfSize) {
                back = bookQueue.back();
                bookQueue.pop_back();
                usedSpace -= bookSize[back];
            }
        } else if (action == "CHECKOUT") {
            title = trimText(line.substr(9));
            for (deque<string>::iterator it = bookQueue.begin(); it != bookQueue.end(); ++it) {
                if (*it == title) {
                    usedSpace -= bookSize[title];
                    bookQueue.erase(it);
                    break;
                }
            }
        }
    }
    cout << "End of program 2 by team X\n";
    return 0;
}
