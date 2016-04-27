// Concurrent Simulator
// UVa IDs: 210
// Verdict: Accepted
// Submission Date: 2016-01-18
// UVa Run Time: 0.395s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <deque>
#include <cstring>
#include <sstream>

using namespace std;

const int ASSIGNMENT = 0;
const int OUTPUT = 1;
const int LOCK = 2;
const int UNLOCK = 3;
const int END = 4;

struct statement
{
    int programId;          // 程序 ID
    int statementType;      // 语句类型
    char variableName;      // 变量名称
    int variableValue;      // 变量值
};

typedef deque < statement > program;

int timeNeeded[END + 1];    // 每种语句执行所需时间
int timeQuantum;            // 时间片包含单位时间数
bool isLocked = false;      // 当前是否有程序使用了 lock 语句
int valueSetted[26];        // 存储变量的值

// 模拟程序执行过程
void execute(deque < program > ready)
{
    deque < program > blocked;  // 阻塞队列

    while (!ready.empty())
    {
        program pRunning = ready.front();
        ready.pop_front();

        int timeRemain = timeQuantum;
        bool intoBlockedQueue = false;
        while (timeRemain > 0)
        {
            statement sCurrent = pRunning.front();
            pRunning.pop_front();
            
            switch (sCurrent.statementType)
            {
                case ASSIGNMENT:
                    valueSetted[sCurrent.variableName - 'a'] =
                        sCurrent.variableValue;
                    break;
                    
                case OUTPUT:
                    cout << sCurrent.programId << ": ";
                    cout << valueSetted[sCurrent.variableName - 'a'] << endl;
                    break;
                    
                case LOCK:
                    if (isLocked)
                    {
                        pRunning.push_front(sCurrent);
                        blocked.push_back(pRunning);
                        timeRemain = 0;
                        intoBlockedQueue = true;
                    }
                    else
                        isLocked = true;
                    break;
                    
                case UNLOCK:
                    if (!blocked.empty())
                    {
                        program pNext = blocked.front();
                        blocked.pop_front();
                        ready.push_front(pNext);
                    }
                    isLocked = false;
                    break;
                    
                case END:
                    timeRemain = 0;
                    break;
            }

            timeRemain -= timeNeeded[sCurrent.statementType];
        }

        if (!pRunning.empty() && !intoBlockedQueue)
            ready.push_back(pRunning);
    }
}

// 解析语句类型
statement parseToStatement(string line, int programId)
{
    statement s;
    s.programId = programId;

    if (line.find('=') != line.npos)
    {
        istringstream iss(line);
        s.statementType = ASSIGNMENT;
        iss >> s.variableName;
        string blank;
        iss >> blank;
        iss >> s.variableValue;
    }
    else if (line == "end")
    {
        s.statementType = END;
    }
    else if (line == "lock")
    {
        s.statementType = LOCK;
    }
    else if (line == "unlock")
    {
        s.statementType = UNLOCK;
    }
    else
    {
        s.statementType = OUTPUT;
        s.variableName = line[line.length() - 1];
    }

    return s;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    string line;
    int cases, numbers;
    bool startPrintBlankLine = false;

    // 读入测试用例数
    cin >> cases;
    while (cases-- > 0)
    {
        // 在两个测试用例输出之间输出空行
        if (startPrintBlankLine)
            cout << endl;
        else
            startPrintBlankLine = true;

        // 读入空行
        getline(cin, line);

        // 读入各语句执行时间及单个时间片时间数
        cin >> numbers;
        for (int i = ASSIGNMENT; i <= END; i++)
            cin >> timeNeeded[i];
        cin >> timeQuantum;
        cin.ignore();

        // 读入程序语句
        int programId = numbers;
        deque < program > ready;
        while (numbers-- > 0)
        {
            deque < statement > program;
            while (getline(cin, line), line != "end")
                program.push_back(parseToStatement(line, programId - numbers));
            program.push_back(parseToStatement(line, programId - numbers));
            ready.push_back(program);
        }

        // 初始化变量的值
        memset(valueSetted, 0, sizeof(valueSetted));
        
        // 模拟执行
        execute(ready);
    }

    return 0;
}
