// Strategy
// UVa IDs: 174
// Verdict: Accepted
// Submission Date: 2016-03-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int TRADE = 0, CHEAT = 1, CONDITION = 2, NONE = 3;

struct node
{
    int category;
    string conditions;
    node *leftChild, *rightChild;
};

vector < string > programs;

string spaceOut(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    line.erase(line.end() - 1);
    return line;
}

// parse the strategy by recursion
string strategy;
int index = 0;
void parseStrategy(node *parent)
{
    if (index >= strategy.length())
        return;
    
    if (strategy[index] == 'T')
    {
        parent->category = TRADE;
        parent->leftChild = NULL;
        parent->rightChild = NULL;
        index += 5;
        
        //cout << "TRADE";
    }
    else if (strategy[index] == 'C')
    {
        parent->category = CHEAT;
        parent->leftChild = NULL;
        parent->rightChild = NULL;
        index += 5;
        
        //cout << "CHEAT";
    }
    else if (strategy[index] == 'I')
    {
        parent->category = CONDITION;
        index += 2;
        
        //cout << "IF ";
        
        int thenIndex = strategy.find("THEN", index);
        parent->conditions = strategy.substr(index, thenIndex - index);
        
        //cout << parent->conditions;
        
        index = thenIndex + 4;
        
        //cout << " THEN ";
        
        node *leftNode = new node;
        parseStrategy(leftNode);
        parent->leftChild = leftNode;
        
        // ELSE
        index += 4;
        
        //cout << " ELSE ";
        
        node *rightNode = new node;
        parseStrategy(rightNode);
        parent->rightChild = rightNode;
    }
}

int scores = 0;
vector < int > myMemory, yourMemory;
vector < node* > nodes;

bool evaluatePart(string part, vector < int >& my, vector < int >& your)
{
    bool isEqual = true;
    int op = part.find("=");
    if (op == part.npos)
    {
        op = part.find("#");
        isEqual = false;
    }
    
    int right = NONE;
    if (part[op + 1] == 'T')
        right = TRADE;
    if (part[op + 1] == 'C')
        right = CHEAT;
        
    int index = part[op - 1] - '0';
    
    if (part[0] == 'M')
    {
        if (index > my.size())
            return isEqual ? NONE == right : NONE != right;
        else
            return isEqual ? my[my.size() - index] == right : my[my.size() - index] != right;
    }
    else
    {
        if (index > your.size())
            return isEqual ? NONE == right : NONE != right;
        else
            return isEqual ? your[your.size() - index] == right : your[your.size() - index] != right;
    }
}

bool evaluate(string conditions, vector < int >& my, vector < int >& your)
{
    int orIndex = conditions.find("OR", 0);
    int andIndex = conditions.find("AND", 0);
    
    if (orIndex == conditions.npos && andIndex == conditions.npos)
        return evaluatePart(conditions, my, your);
    
    int opIndex, nextIndex;
    bool isAnd = false;
    if (orIndex == conditions.npos)
    {
        opIndex = andIndex;
        nextIndex = andIndex + 3;
        isAnd = true;
    }
    else if (andIndex == conditions.npos)
    {
        opIndex = orIndex;
        nextIndex = orIndex + 2;
    }
    else if (orIndex < andIndex)
    {
        opIndex = orIndex;
        nextIndex = orIndex + 2;
    }
    else
    {
        opIndex = andIndex;
        nextIndex = andIndex + 3;
        isAnd = true;
    }
    
    bool leftPart = evaluatePart(conditions.substr(0, opIndex), my, your);
    bool rightPart = evaluate(conditions.substr(nextIndex), my, your);
    
    return isAnd ? (leftPart && rightPart) : (leftPart || rightPart);
}

int getStrategy(node *parent, vector < int >& my, vector < int >& your)
{
    if (parent->category == TRADE || parent->category == CHEAT)
        return parent->category;
        
    return evaluate(parent->conditions, my, your) ?
        getStrategy(parent->leftChild, my, your) :
        getStrategy(parent->rightChild, my, your);
}

void execute(int i, int j)
{
    int my = getStrategy(nodes[i], myMemory, yourMemory);
    int your = getStrategy(nodes[j], yourMemory, myMemory);
    
    myMemory.push_back(my);
    yourMemory.push_back(your);
    
    if (my == TRADE && your == TRADE)
        scores++;
    if (my == CHEAT && your == CHEAT)
        scores--;
    if (my == TRADE && your == CHEAT)
        scores -= 2;
    if (my == CHEAT && your == TRADE)
        scores += 2;
}

void play()
{
    for (int i = 0; i < programs.size(); i++)
    {
        index = 0;
        strategy = programs[i];
        
        //cout << strategy << endl;
        
        node *root = new node;
        parseStrategy(root);
        
        //cout << endl;
        
        nodes.push_back(root);
    }
    
    for (int i = 0; i < nodes.size(); i++)
    {
        scores = 0;
        
        for (int j = 0; j < nodes.size(); j++)
        {
            if (i == j)
                continue;
                
            myMemory.clear();  
            yourMemory.clear();
             
            for (int k = 1; k <= 10; k++)
                execute(i, j);
        }
        
        cout << right << setw(3) << scores << "\n";
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line, program;
    while (getline(cin, line), line != "#")
    {
        program += line;
        if (line.find('.') != line.npos)
        {
            programs.push_back(spaceOut(program));
            program.clear();
        }
    }
    
    play();
    
	return 0;
}
