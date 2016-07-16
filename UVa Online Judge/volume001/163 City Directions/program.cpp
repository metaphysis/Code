// City Directions
// UVa ID: 163
// Verdict: Accepted
// Submission Date: 2016-04-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

string cmds[7] = {
    "_TURN_LEFT", "_TURN_RIGHT", "_TURN_HALF_LEFT", "_TURN_HALF_RIGHT",
    "_TURN_SHARP_LEFT", "_TURN_SHARP_RIGHT", "_GO"
};

int TURN_LEFT = 0, TURN_RIGHT = 1, TURN_HALF_LEFT = 2, TURN_HALF_RIGHT = 3,
    TURN_SHARP_LEFT = 4, TURN_SHARP_RIGHT = 5, GO = 6, NONE = 7;

string directions[8] = { "N", "E", "S", "W", "NE", "NW", "SE", "SW" };

int N = 0, E = 1, S = 2, W = 3, NE = 4, NW = 5, SE = 6, SW = 7;

int aheadAfterTurn[8][7] = {
    {W, E, NW, NE, SW, SE, N}, {N, S, NE, SE, NW, SW, E},
    {E, W, SE, SW, NE, NW, S}, {S, N, SW, NW, SE, NE, W},
    {NW, SE, N, E, W, S, NE}, {SW, NE, W, N, S, E, NW},
    {NE, SW, E, S, N, W, SE}, {SE, NW, S, W, E, N, SW}
};

int step[8][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
};

int command, intersections, avenue, street, ahead;
vector < string > texts;

void parseDirection(string line)
{
    string text;
    texts.clear();
    istringstream iss(line);
    while (iss >> text)
        texts.push_back(text);
}

int isStayOnThroughways(int x, int y, int heading)
{
    if ((x % 50 == 0) && (heading == N || heading == S))
        return -1;
    if ((y % 50 == 0) && (heading == E || heading == W))
        return -1;
    if ((x - y) == 0 && (heading == NE || heading == SW))
        return -2;
    if ((x + y) == 100 && (heading == NW || heading == SE))
        return -2;
    return 1;
}

void displayDestination()
{
    if (isStayOnThroughways(avenue, street, ahead) < 0)
        cout << "Illegal stopping place" << endl;
    else
    {
        cout << "A" << abs(avenue - 50) << (avenue >= 50 ? 'E' : 'W');
        cout << " S" << abs(street - 50) << (street >= 50 ? 'N' : 'S');
        cout << " " << directions[ahead] << endl;
    }
}

int getAvenueOrStreet(string text)
{
    int index = 0;
    if (isalpha(text.back()))
        index = stoi(text.substr(1, text.length() - 2));
    index = 50 + (text.back() == 'E' || text.back() == 'N' ? index : -index);
    return index;
}

void setStartPosition()
{
    avenue = getAvenueOrStreet(texts[0]);
    street = getAvenueOrStreet(texts[1]);
    ahead = find(directions, directions + 8, texts[2]) - directions;
}

bool validateCommand()
{
    if (texts.size() < 2 || texts.size() > 3)
        return false;

    string target;
    for (int i = 0; i < texts.size(); i++)
        target += "_" + texts.at(i);

    if (texts.front() == "TURN")
    {
        command = find(cmds, cmds + 7, target) - cmds;
        intersections = 1;

        return command < GO;
    }
    else if (texts.front() == "GO")
    {
        if (texts.size() == 3 && texts[1] != "STRAIGHT")
            return false;

        if (texts.back().length() > 2 || !isdigit(texts.back().front()))
            return false;

        if (texts.back().length() == 2 && !isdigit(texts.back().back()))
            return false;

        command = GO;
        intersections = stoi(texts.back());

        return 1 <= intersections && intersections <= 99;
    }

    return false;
}

bool validateDirection(int x, int y, int heading)
{
    if (x == 100 && y == 100)
        return (heading == SW || heading == W || heading == S);
    if (x == 100 && y == 50)
        return (heading == NW || heading == SW || heading == N || heading == S || heading == W);
    if (x == 100 && y == 0)
        return (heading == NW || heading == N || heading == W);
    if (x == 50 && y == 100)
        return (heading == SE || heading == SW || heading == E || heading == S || heading == W);
    if (x == 50 && y == 0)
        return (heading == NE || heading == NW || heading == E || heading == N || heading == W);
    if (x == 0 && y == 100)
        return (heading == SE || heading == E || heading == S);
    if (x == 0 && y == 50)
        return (heading == NE && heading == SE || heading == N || heading == E || heading == S);
    if (x == 0 && y == 0)
        return (heading == NE || heading == N || heading == E);

    if ((x - y == -50 || x - y == 0 || x - y == 50) && (heading == NE || heading == SW))
        return true;
    if ((x + y == 50 || x + y == 100 || x + y == 150) && (heading == NW || heading == SE))
        return true;

    if (y == 100 && (heading == N || heading == NE || heading == NW))
        return false;
    if (y == 0 && (heading == SE || heading == S || heading == SW))
        return false;
    if (x == 0 && (heading == SW || heading == W || heading == NW))
        return false;
    if (x == 100 && (heading == NE || heading == E || heading == SE))
        return false;

    if (heading == N || heading == E || heading == S || heading == W)
        return true;

    return false;
}

bool validateMove()
{
    int x = avenue + step[ahead][0] * intersections;
    int y = street + step[ahead][1] * intersections;
    int heading = aheadAfterTurn[ahead][command];

    bool validMove = false;

    if (command == GO)
    {
        validMove = true;

        if (x < 0 || x > 100 || y < 0 || y > 100)
            validMove = false;

        return validMove;
    }

    // make sure the direction is valid
    if (validateDirection(x, y, heading) == false)
        return false;

    int before = isStayOnThroughways(avenue, street, ahead);
    int after = isStayOnThroughways(x, y, heading);

    // check enter or exiting throughways or boulevards
    if (before < 0 && after > 0)
    {
        if (before == -1)
            validMove = command == TURN_LEFT;
        else
            validMove = command == TURN_SHARP_LEFT;
    }
    else if (before > 0 && after < 0)
    {
        if (after == -1)
            validMove = command == TURN_LEFT;
        else
            validMove = command == TURN_SHARP_LEFT;
    }
    else
        validMove = true;

    // At nine intersections, any turn is valid
    if ((x == 0 || x == 50 || x == 100) && (y == 0 || y == 50 || y == 100))
        validMove = true;

    return validMove;
}

int main(int argc, char *argv[])
{
    string line;
    bool startPositionReaded = false;

    while (getline(cin, line), line != "END")
    {
        parseDirection(line);

        if (line == "STOP")
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

        if (validateCommand() && validateMove())
        {
            avenue += step[ahead][0] * intersections;
            street += step[ahead][1] * intersections;
            ahead = aheadAfterTurn[ahead][command];
        }
    }

    return 0;
}
