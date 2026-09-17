#include <bits/stdc++.h>
using namespace std;

enum ElementType {
    Basic,
    Matrix,
    Fraction
};

struct Element;

struct Box {
    vector<Element *> elems;
    Element *owner;
    int row, col, part;
};

struct Element {
    ElementType type;
    char value;
    Box *parent, *numerator, *denominator;
    vector<vector<Box *> > cells;
};

struct Rect {
    vector<string> lines;
    int base, width;
};

struct Editor {
    vector<unique_ptr<Box> > boxes;
    vector<unique_ptr<Element> > elements;
    Box *root, *curBox;
    int curPos;
    Editor();
    Box *createBox(Element *owner);
    Element *createElement(ElementType type);
    int findElement(Box *box, Element *elem);
    Box *getSibling(Box *box, int dr, int dc);
    void moveHome();
    void moveEnd();
    void moveLeft();
    void moveRight();
    void moveVertical(int direction);
    void insertBasic(char value);
    void insertMatrix();
    void insertFraction();
    void addRow();
    void addCol();
    void process(const string &command);
    void paste(Rect &target, const Rect &source, int top, int left);
    Rect renderBox(Box *box);
    Rect renderElement(Element *elem);
    Rect renderMatrix(Element *elem);
    Rect renderFraction(Element *elem);
};

Editor::Editor() {
    root = createBox(nullptr);
    curBox = root;
    curPos = 0;
}

Box *Editor::createBox(Element *owner) {
    boxes.emplace_back(new Box());
    Box *box = boxes.back().get();
    box->owner = owner;
    box->row = box->col = box->part = -1;
    return box;
}

Element *Editor::createElement(ElementType type) {
    elements.emplace_back(new Element());
    Element *elem = elements.back().get();
    elem->type = type;
    elem->value = 0;
    elem->parent = elem->numerator = elem->denominator = nullptr;
    return elem;
}

int Editor::findElement(Box *box, Element *elem) {
    for (int i = 0; i < static_cast<int>(box->elems.size()); i++)
        if (box->elems[i] == elem) return i;
    return -1;
}

Box *Editor::getSibling(Box *box, int dr, int dc) {
    Element *owner = box->owner;
    if (owner == nullptr) return nullptr;
    if (owner->type == Matrix) {
        int nr = box->row + dr, nc = box->col + dc;
        int n = static_cast<int>(owner->cells.size()), m = static_cast<int>(owner->cells[0].size());
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) return owner->cells[nr][nc];
    } else if (owner->type == Fraction && dc == 0) {
        if (dr == -1 && box->part == 1) return owner->numerator;
        if (dr == 1 && box->part == 0) return owner->denominator;
    }
    return nullptr;
}

void Editor::moveHome() {
    curPos = 0;
}

void Editor::moveEnd() {
    curPos = static_cast<int>(curBox->elems.size());
}

void Editor::moveLeft() {
    if (curPos == 0) {
        Box *sibling = getSibling(curBox, 0, -1);
        if (sibling != nullptr) {
            curBox = sibling;
            curPos = static_cast<int>(curBox->elems.size());
        } else if (curBox->owner != nullptr) {
            Element *owner = curBox->owner;
            curBox = owner->parent;
            curPos = findElement(curBox, owner);
        }
        return;
    }
    Element *elem = curBox->elems[curPos - 1];
    if (elem->type == Basic) {
        curPos--;
    } else if (elem->type == Fraction) {
        curBox = elem->numerator;
        curPos = static_cast<int>(curBox->elems.size());
    } else {
        int row = (static_cast<int>(elem->cells.size()) - 1) / 2;
        int col = static_cast<int>(elem->cells[0].size()) - 1;
        curBox = elem->cells[row][col];
        curPos = static_cast<int>(curBox->elems.size());
    }
}

void Editor::moveRight() {
    if (curPos == static_cast<int>(curBox->elems.size())) {
        Box *sibling = getSibling(curBox, 0, 1);
        if (sibling != nullptr) {
            curBox = sibling;
            curPos = 0;
        } else if (curBox->owner != nullptr) {
            Element *owner = curBox->owner;
            curBox = owner->parent;
            curPos = findElement(curBox, owner) + 1;
        }
        return;
    }
    Element *elem = curBox->elems[curPos];
    if (elem->type == Basic) {
        curPos++;
    } else if (elem->type == Fraction) {
        curBox = elem->numerator;
        curPos = 0;
    } else {
        int row = (static_cast<int>(elem->cells.size()) - 1) / 2;
        curBox = elem->cells[row][0];
        curPos = 0;
    }
}

void Editor::moveVertical(int direction) {
    Box *box = curBox;
    while (box != nullptr) {
        Box *sibling = getSibling(box, direction, 0);
        if (sibling != nullptr) {
            curBox = sibling;
            curPos = 0;
            return;
        }
        if (box->owner == nullptr) break;
        box = box->owner->parent;
    }
}

void Editor::insertBasic(char value) {
    Element *elem = createElement(Basic);
    elem->value = value;
    elem->parent = curBox;
    curBox->elems.insert(curBox->elems.begin() + curPos, elem);
    curPos++;
}

void Editor::insertMatrix() {
    Element *elem = createElement(Matrix);
    elem->parent = curBox;
    Box *cell = createBox(elem);
    cell->row = cell->col = 0;
    elem->cells.push_back(vector<Box *>(1, cell));
    curBox->elems.insert(curBox->elems.begin() + curPos, elem);
    moveRight();
}

void Editor::insertFraction() {
    Element *elem = createElement(Fraction);
    elem->parent = curBox;
    elem->numerator = createBox(elem);
    elem->denominator = createBox(elem);
    elem->numerator->part = 0;
    elem->denominator->part = 1;
    curBox->elems.insert(curBox->elems.begin() + curPos, elem);
    moveRight();
}

void Editor::addRow() {
    Box *cell = curBox;
    while (cell->owner != nullptr && cell->owner->type != Matrix) cell = cell->owner->parent;
    if (cell->owner == nullptr) return;
    Element *matrix = cell->owner;
    int row = cell->row, m = static_cast<int>(matrix->cells[0].size());
    vector<Box *> newRow;
    for (int col = 0; col < m; col++) {
        Box *newCell = createBox(matrix);
        newCell->row = row;
        newCell->col = col;
        newRow.push_back(newCell);
    }
    matrix->cells.insert(matrix->cells.begin() + row, newRow);
    for (int i = row + 1; i < static_cast<int>(matrix->cells.size()); i++)
        for (int j = 0; j < m; j++) matrix->cells[i][j]->row = i;
    curBox = matrix->cells[row][cell->col];
    curPos = 0;
}

void Editor::addCol() {
    Box *cell = curBox;
    while (cell->owner != nullptr && cell->owner->type != Matrix) cell = cell->owner->parent;
    if (cell->owner == nullptr) return;
    Element *matrix = cell->owner;
    int row = cell->row, col = cell->col;
    for (int i = 0; i < static_cast<int>(matrix->cells.size()); i++) {
        Box *newCell = createBox(matrix);
        newCell->row = i;
        newCell->col = col;
        matrix->cells[i].insert(matrix->cells[i].begin() + col, newCell);
        for (int j = col + 1; j < static_cast<int>(matrix->cells[i].size()); j++) matrix->cells[i][j]->col = j;
    }
    curBox = matrix->cells[row][col];
    curPos = 0;
}

void Editor::process(const string &command) {
    if (command == "Home") moveHome();
    else if (command == "End") moveEnd();
    else if (command == "Left") moveLeft();
    else if (command == "Right") moveRight();
    else if (command == "Up") moveVertical(-1);
    else if (command == "Down") moveVertical(1);
    else if (command == "Matrix") insertMatrix();
    else if (command == "Fraction") insertFraction();
    else if (command == "AddRow") addRow();
    else if (command == "AddCol") addCol();
    else if (command.size() == 1) insertBasic(command[0]);
}

void Editor::paste(Rect &target, const Rect &source, int top, int left) {
    for (int i = 0; i < static_cast<int>(source.lines.size()); i++)
        for (int j = 0; j < source.width; j++) target.lines[top + i][left + j] = source.lines[i][j];
}

Rect Editor::renderBox(Box *box) {
    vector<Rect> parts;
    int base = 0, below = 0, width = 0;
    for (Element *elem : box->elems) {
        Rect part = renderElement(elem);
        base = max(base, part.base);
        below = max(below, static_cast<int>(part.lines.size()) - part.base - 1);
        width += part.width;
        parts.push_back(part);
    }
    Rect result;
    result.base = base;
    result.width = width;
    result.lines.assign(base + below + 1, string(width, ' '));
    int left = 0;
    for (const Rect &part : parts) {
        paste(result, part, base - part.base, left);
        left += part.width;
    }
    return result;
}

Rect Editor::renderElement(Element *elem) {
    if (elem->type == Matrix) return renderMatrix(elem);
    if (elem->type == Fraction) return renderFraction(elem);
    Rect result;
    result.base = 0;
    if (elem->value == '-') {
        result.width = 3;
        result.lines.push_back(" - ");
    } else {
        result.width = 1;
        result.lines.push_back(string(1, elem->value));
    }
    return result;
}

Rect Editor::renderMatrix(Element *elem) {
    int n = static_cast<int>(elem->cells.size()), m = static_cast<int>(elem->cells[0].size());
    vector<vector<Rect> > cells(n, vector<Rect>(m));
    vector<int> colWidth(m, 0), rowUp(n, 0), rowDown(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cells[i][j] = renderBox(elem->cells[i][j]);
            colWidth[j] = max(colWidth[j], cells[i][j].width);
            rowUp[i] = max(rowUp[i], cells[i][j].base);
            rowDown[i] = max(rowDown[i], static_cast<int>(cells[i][j].lines.size()) - cells[i][j].base - 1);
        }
    }
    int width = m + 1, height = n - 1;
    for (int value : colWidth) width += value;
    for (int i = 0; i < n; i++) height += rowUp[i] + rowDown[i] + 1;
    vector<int> rowStart(n), colStart(m);
    int current = 0;
    for (int i = 0; i < n; i++) {
        rowStart[i] = current;
        current += rowUp[i] + rowDown[i] + 1;
        if (i + 1 < n) current++;
    }
    current = 1;
    for (int j = 0; j < m; j++) {
        colStart[j] = current;
        current += colWidth[j] + 1;
    }
    Rect result;
    result.width = width;
    result.lines.assign(height, string(width, ' '));
    for (int i = 0; i < n; i++) {
        int line = rowStart[i] + rowUp[i];
        result.lines[line][0] = '[';
        result.lines[line][width - 1] = ']';
        for (int j = 0; j < m; j++) {
            int top = line - cells[i][j].base;
            int left = colStart[j] + (colWidth[j] - cells[i][j].width) / 2;
            paste(result, cells[i][j], top, left);
        }
    }
    if (n % 2 == 1) result.base = rowStart[n / 2] + rowUp[n / 2];
    else result.base = rowStart[n / 2] - 1;
    return result;
}

Rect Editor::renderFraction(Element *elem) {
    Rect numerator = renderBox(elem->numerator), denominator = renderBox(elem->denominator);
    int width = max(numerator.width, denominator.width) + 2;
    int height = static_cast<int>(numerator.lines.size() + denominator.lines.size()) + 1;
    Rect result;
    result.base = static_cast<int>(numerator.lines.size());
    result.width = width;
    result.lines.assign(height, string(width, ' '));
    paste(result, numerator, 0, (width - numerator.width) / 2);
    result.lines[result.base] = string(width, '-');
    paste(result, denominator, result.base + 1, (width - denominator.width) / 2);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string command;
    int caseNum = 0;
    unique_ptr<Editor> editor;
    while (getline(cin, command)) {
        if (!command.empty() && command.back() == '\r') command.pop_back();
        if (command.empty()) continue;
        if (editor == nullptr) editor.reset(new Editor());
        if (command == "Done") {
            Rect result = editor->renderBox(editor->root);
            cout << "Case " << ++caseNum << ":\n";
            for (string line : result.lines) {
                while (!line.empty() && line.back() == ' ') line.pop_back();
                cout << line << '\n';
            }
            cout << '\n';
            editor.reset();
        } else {
            editor->process(command);
        }
    }
    return 0;
}
