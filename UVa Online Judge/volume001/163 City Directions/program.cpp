// City Directions
// UVa IDs: 163
// Verdict: Wrong Answer
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

// 转向
string cmds[7] = {
    "_TURN_LEFT", "_TURN_RIGHT", "_TURN_HALF_LEFT", "_TURN_HALF_RIGHT",
    "_TURN_SHARP_LEFT", "_TURN_SHARP_RIGHT", "_GO"
};

int TURN_LEFT = 0, TURN_RIGHT = 1, TURN_HALF_LEFT = 2, TURN_HALF_RIGHT = 3,
    TURN_SHARP_LEFT = 4, TURN_SHARP_RIGHT = 5, GO = 6, NONE = 7;

// 方位
string directions[8] = { "N", "E", "S", "W", "NE", "NW", "SE", "SW" };

int N = 0, E = 1, S = 2, W = 3, NE = 4, NW = 5, SE = 6, SW = 7;

// 给定起始方位经特定转向后的方位
int headingAfterTurn[8][7] = {
    {W, E, NW, NE, SW, SE, N}, {N, S, NE, SE, NW, SW, E},
    {E, W, SE, SW, NE, NW, S}, {S, N, SW, NW, SE, NE, W},
    {NW, SE, N, E, W, S, NE}, {SW, NE, W, N, S, E, NW},
    {NE, SW, E, S, N, W, SE}, {SE, NW, S, W, E, N, SW}
};

// 转向后坐标变化值
int step[8][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
};

int command, intersections;
int avenue, street, heading;
vector < string > texts;

// 将每行命令解析成单词以便判断。
void parseDirection(string line)
{
    string text;
    texts.clear();
    istringstream iss(line);
    while (iss >> text)
        texts.push_back(text);
}

// 判断最后是否停留在快速路上。
bool isStayOnThroughways()
{
    if ((avenue % 50 == 0) && (heading == N || heading == S))
        return true;
    if ((street % 50 == 0) && (heading == E || heading == W))
        return true;
    if ((avenue - street) == 0 && (heading == NE || heading == SW))
        return true;
    if ((avenue + street) == 100 && (heading == NW || heading == SE))
        return true;

    return false;
}

// 显示终点位置。因为以左下角为原点，显示时需要调整。
void displayDestination()
{
    if (isStayOnThroughways())
        //cout << "Illegal stopping place ";
        cout << "Illegal stopping place" << endl;
    else
    {
        cout << "A" << abs(avenue - 50) << (avenue >= 50 ? 'E' : 'W');
        cout << " S" << abs(street - 50) << (street >= 50 ? 'N' : 'S');
        cout << " " << directions[heading] << endl;
    }
}

// 获取经路和纬路的序号，将序号调整为以左下角为原点。
int getAvenueOrStreet(string text)
{
    int index = 0;
    if (isalpha(text.back()))
        index = stoi(text.substr(1, text.length() - 2));
    index = 50 + (text.back() == 'E' || text.back() == 'N' ? index : -index);
}

// 设置起始位置。以左下角为坐标原点计算街道的序号。
void setStartPosition()
{
    avenue = getAvenueOrStreet(texts[0]);
    street = getAvenueOrStreet(texts[1]);
    heading = find(directions, directions + 8, texts[2]) - directions;

    //cout << "Start Position: ";
    //displayDestination();
}

bool validateCommand()
{
    if (texts.size() < 2 || texts.size() > 3)
        return false;

    string target;
    for (int i = 0; i < texts.size(); i++)
        target += "_" + texts.at(i);

    // 检查是否为符合语法规则的 TURN 命令。
    if (texts.front() == "TURN")
    {
        // 设置转向命令。
        command = find(cmds, cmds + 7, target) - cmds;
        intersections = 1;

        return command < NONE;
    }

    // 检查是否为符合语法规则的 GO 命令。
    if (texts.front() == "GO")
    {
        // 排除形如 GO ON 2 AND 的命令。
        if (texts.size() == 3 && texts.at(1) != "STRAIGHT")
            return false;

        // 排除形如 GO 123 或 GO 12H 等形式的命令。
        if (texts.back().length() > 2 || !isdigit(texts.back().front()))
            return false;

        // 排除形如 GO 1H 的命令。
        if (texts.back().length() == 2 && !isdigit(texts.back().back()))
            return false;

        // 设置命令。
        command = GO;
        intersections = stoi(texts.back());

        // 排除形如 GO 0 的命令。
        return 1 <= intersections && intersections <= 99;
    }

    return false;
}

bool validateMove()
{
    if (command == TURN_LEFT)
    {
        if (heading == N && avenue == 0 || heading == S && avenue == 100 ||
            heading == W && street == 0 || heading == S && avenue == 100)
            return false;
        if (heading == NE)
        {
            if (street == 49 && avenue == 49)
                return true;
            if (street == 49 && avenue == 99)
                return true;
            return false;
        }
        if (heading == NW)
        {
            if (avenue == 51 && street == 49)
                return true;
            if (avenue == 51 && street == 99)
                return true;
            return false;
        }
        if (heading == SE)
        {
            if (avenue == 49 && street == 51)
                return true;
            if (avenue == 49 && street == 1)
                return true;
            return false;
        }
        if (heading == SW)
        {
            if (street == 51 && avenue == 51)
                return true;
            if (street == 51 && avenue == 1)
                return true;
            return false;
        }
    }

    if (command == TURN_RIGHT)
    {
        if (heading == N)
        {
            if (avenue == 0 || avenue == 50)
            {
                if (street == 49 || street == 99)
                    return true;
                return false;
            }
            if (avenue == 100)
                return false;
            if (street == 49 || street == 99)
                return false;
        }
        if (heading == E)
        {
            if (street == 50 || street == 100)
            {
                if (avenue == 49 || avenue == 99)
                    return true;
                return false;
            }
            if (street == 0)
                return false;
            if (avenue == 49 || avenue == 99)
                return false;

        }
        if (heading == S)
        {
            if (avenue == 50 || avenue == 100)
            {
                if (street == 1 || street == 51)
                    return true;
                return false;
            }
            if (avenue == 0)
                return false;
            if (street == 1 || street == 51)
                return false;
        }
        if (heading == W)
        {
            if (street == 0 || street == 50)
            {
                if (avenue == 1 || avenue == 51)
                    return true;
                return false;
            }
            if (street == 100)
                return false;
            if (avenue == 1 || avenue == 51)
                return false;
        }
        if (heading == NE)
        {
            if (avenue == 49 && (street == 49 || street == 99))
                return true;
            return false;
        }
        if (heading == NW)
        {
            if (street == 49 && (avenue == 51 || avenue == 1))
                return true;
            return false;
        }
        if (heading == SE)
        {
            if (street == 51 && (avenue == 49 || avenue == 99))
                return true;
            return false;
        }
        if (heading == SW)
        {
            if (avenue == 51 && (street == 51 && street == 1))
                return true;
            return false;
        }
    }

    if (command == TURN_HALF_LEFT)
    {
        if (heading == N)
        {
            if (avenue == 50 && street == 49)
                return true;
            if ((avenue + street) == 49 && (avenue >= 1 && avenue <= 49))
                return true;
            if ((avenue + street) == 149 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == E)
        {
            if (avenue == 49 && street == 50)
                return true;
            if ((street - avenue) == 51 && (street >= 51 && street <= 99))
                return true;
            if ((avenue - street) == 49 && (street >= 0 && street <= 49))
                return true;
            return false;
        }
        if (heading == S)
        {
            if (avenue == 50 && street == 51)
                return true;
            if ((avenue + street) == 51 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue + street) == 151 && (avenue >= 51 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == W)
        {
            if (avenue == 51 && street == 50)
                return true;
            if ((street - avenue) == 49 && (street >= 51 && street <= 100))
                return true;
            if ((avenue - street) == 51 && (street >= 1 && street <= 49))
                return true;
            return false;
        }
        if (heading == NE)
        {
            if (avenue == 49 && street == 49)
                return true;
            if ((street - avenue) == 50 && (avenue >= 0 && avenue <= 48))
                return true;
            if ((avenue - street) == 50 && (avenue >= 50 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == NW)
        {
            if (avenue == 51 && street == 49)
                return true;
            if ((avenue + street) == 50 && (avenue >= 2 && avenue <= 50))
                return true;
            if ((avenue + street) == 150 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == SE)
        {
            if (avenue == 49 && street == 51)
                return true;
            if ((avenue + street) == 50 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue + street) == 150 && (avenue >= 50 && avenue <= 98))
                return true;
            return false;
        }
        if (heading == SW)
        {
            if (avenue == 51 && street == 51)
                return true;
            if ((street - avenue) == 50 && (street >= 51 && street <= 100))
                return true;
            if ((avenue - street) == 50 && (street >= 2 && street <= 50))
                return true;
            return false;
        }
    }

    if (command == TURN_HALF_RIGHT)
    {
        if (heading == N)
        {
            if (avenue == 50 && street == 49)
                return true;
            if ((street - avenue) == 49 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue - street) == 51 && (avenue >= 51 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == E)
        {
            if (avenue == 49 && street == 50)
                return true;
            if ((avenue + street) == 49 && (street >= 1 && street <= 49))
                return true;
            if ((avenue + street) == 149 && (street >= 51 && street <= 100))
                return true;
            return false;
        }
        if (heading == S)
        {
            if (avenue == 50 && street == 51)
                return true;
            if ((street - avenue) == 51 && (avenue >= 1 && avenue <= 49))
                return true;
            if ((avenue - street) == 49 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == W)
        {
            if (avenue == 51 && street == 50)
                return true;
            if ((avenue + street) == 51 && (street >= 0 && street <= 49))
                return true;
            if ((avenue + street) == 151 && (street >= 51 && street <= 99))
                return true;
            return false;
        }
        if (heading == NE)
        {
            if (avenue == 49 && street == 49)
                return true;
            if ((street - avenue) == 50 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue - street) == 50 && (avenue >= 50 && avenue <= 98))
                return true;
            return false;
        }
        if (heading == NW)
        {
            if (avenue == 51 && street == 49)
                return true;
            if ((avenue + street) == 50 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue + street) == 150 && (avenue >= 52 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == SE)
        {
            if (avenue == 49 && street == 51)
                return true;
            if ((avenue + street) == 50 && (avenue >= 0 && avenue <= 48))
                return true;
            if ((avenue + street) == 150 && (avenue >= 50 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == SW)
        {
            if (avenue == 51 && street == 51)
                return true;
            if ((street - avenue) == 50 && (avenue >= 2 && avenue <= 50))
                return true;
            if ((avenue - street) == 50 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }
    }

    if (command == TURN_SHARP_LEFT)
    {
        if (heading == N)
        {
            if ((street - avenue) == 49 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue - street) == 51 && (avenue >= 51 && avenue <= 100))
                return true;
            if ((avenue - street) == 1 && (avenue >= 1 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == E)
        {
            if ((avenue + street) == 49 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue + street) == 149 && (avenue >= 50 && avenue <= 99))
                return true;
            if ((avenue + street) == 99 && (avenue >= 0 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == S)
        {
            if ((street - avenue) == 51 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue - street) == 49 && (avenue >= 50 && avenue <= 99))
                return true;
            if ((street - avenue) == 1 && (avenue >= 0 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == W)
        {
            if ((avenue + street) == 51 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue + street) == 151 && (avenue >= 51 && avenue <= 100))
                return true;
            if ((avenue + street) == 101 && (avenue >= 1 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == NE)
        {
            if ((street - avenue) == 50 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue - street) == 50 && (avenue >= 50 && avenue <= 99))
                return true;
            if ((avenue - street) == 0 && (avenue >= 0 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == NW)
        {
            if ((avenue + street) == 50 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue + street) == 150 && (avenue >= 51 && avenue <= 100))
                return true;
            if ((avenue + street) == 100 && (avenue >= 1 && avenue <= 100))
                return true;
            return false;
        }
        if (heading == SE)
        {
            if ((avenue + street) == 50 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue + street) == 150 && (avenue >= 50 && avenue <= 99))
                return true;
            if ((avenue + street) == 100 && (avenue >= 0 && avenue <= 99))
                return true;
            return false;
        }
        if (heading == SW)
        {
            if ((street - avenue) == 50 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue - street) == 50 && (avenue >= 51 && avenue <= 100))
                return true;
            if ((avenue - street) == 0 && (avenue >= 1 && avenue <= 100))
                return true;
            return false;
        }
    }

    if (command == TURN_SHARP_RIGHT)
    {
        if (heading == N)
        {
            if (avenue == 50 && street == 49)
                return true;
            if (avenue == 0 && street == 99)
                return true;
            if ((avenue + street) == 49 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue + street) == 149 && (avenue >= 50 && avenue <= 99))
                return true;
            return false;
        }

        if (heading == E)
        {
            if (avenue == 49 && street == 50)
                return true;
            if (avenue == 99 && street == 100)
                return true;
            if ((street - avenue) == 51 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue - street) == 49 && (avenue >= 50 && avenue <= 99))
                return true;
            return false;
        }

        if (heading == S)
        {
            if (avenue == 50 && street == 51)
                return true;
            if (avenue == 100 && street == 1)
                return true;
            if ((avenue + street) == 51 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue + street) == 151 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }

        if (heading == W)
        {
            if (avenue == 51 && street == 50)
                return true;
            if (avenue == 1 && street == 0)
                return true;
            if ((street - avenue) == 49 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue - street) == 51 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }

        if (heading == NE)
        {
            if (avenue == 49 && street == 49)
                return true;
            if (avenue == 99 && street == 99)
                return true;
            if ((street - avenue) == 50 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue - street) == 50 && (avenue >= 50 && avenue <= 99))
                return true;
            return false;
        }

        if (heading == NW)
        {
            if (avenue == 51 && street == 49)
                return true;
            if (avenue == 1 && street == 99)
                return true;
            if ((avenue + street) == 50 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue + street) == 150 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }

        if (heading == SE)
        {
            if (avenue == 49 && street == 51)
                return true;
            if (avenue == 99 && street == 1)
                return true;
            if ((avenue + street) == 50 && (avenue >= 0 && avenue <= 49))
                return true;
            if ((avenue + street) == 150 && (avenue >= 50 && avenue <= 99))
                return true;
            return false;
        }

        if (heading == SW)
        {
            if (avenue == 51 && street == 51)
                return true;
            if (avenue == 1 && street == 1)
                return true;
            if ((street - avenue) == 50 && (avenue >= 1 && avenue <= 50))
                return true;
            if ((avenue - street) == 50 && (avenue >= 51 && avenue <= 100))
                return true;
            return false;
        }
    }

    int index = avenue + step[heading][0] * intersections;
    if (index < 0 || index > 100)
        return false;
    index = street + step[heading][1] * intersections;
    if (index < 0 || index > 100)
        return false;

    return true;
}

int main(int argc, char *argv[])
{
    string line;
    bool startPositionReaded = false;

    while (getline(cin, line), line != "END")
    {
        parseDirection(line);

        if (texts.size() == 1 && texts[0] == "STOP")
        {
            displayDestination();
            startPositionReaded = false;
            continue;
        }

        if (startPositionReaded == false)
        {
            setStartPosition();
            startPositionReaded = true;
            continue;
        }

        if (validateCommand())
        {
            //cout << cmds[command] << " ";
            //if (command == GO)
            //cout << intersections << " ";

            if (validateMove())
            {
                avenue += step[heading][0] * intersections;
                street += step[heading][1] * intersections;
                heading = headingAfterTurn[heading][command];

                //displayDestination();
            }
            //else
                //cout << "Ignore" << endl;
        }
        //else
            //cout << "Ignore" << endl;
    }

    return 0;
}
