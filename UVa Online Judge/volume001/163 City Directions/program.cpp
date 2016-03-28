// City Directions
// UVa IDs: 163
// Verdict: Wrong Answer
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// truning
string commandText[6] = {
    "_TURN_LEFT", "_TURN_RIGHT", "_TURN_HALF_LEFT", "_TURN_HALF_RIGHT",
    "_TURN_SHARP_LEFT", "_TURN_SHARP_RIGHT"
};

int TURN_LEFT = 0, TURN_RIGHT = 1, TURN_HALF_LEFT = 2, TURN_HALF_RIGHT = 3,
    TURN_SHARP_LEFT = 4, TURN_SHARP_RIGHT = 5, GO = 6;

// direction
string directions[8] = { "N", "E", "S", "W", "NE", "NW", "SE", "SW" };

int N = 0, E = 1, S = 2, W = 3, NE = 4, NW = 5, SE = 6, SW = 7;

// direction after turning
int headingAfterTurn[8][7] = {
    {W, E, NW, NE, SW, SE, N}, {N, S, NE, SE, NW, SW, E},
    {E, W, SE, SW, NE, NW, S}, {S, N, SW, NW, SE, NE, W},
    {NW, SE, N, E, W, S, NE}, {SW, NE, W, N, S, E, NW},
    {NE, SW, E, S, N, W, SE}, {SE, NW, S, W, E, N, SW}
};

// position change after truning
int step[8][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
};

int command, intersections;
int avenue, street, heading;
vector < string > texts;

// parse line to command
void parseDirection(string line)
{
    string text;
    texts.clear();
    istringstream iss(line);
    while (iss >> text)
        texts.push_back(text);
}

// is on through ways?
bool isStayOnThroughways()
{
    if ((avenue == 0 || avenue == 50 || avenue == 100) && (heading == N || heading == S))
        return true;
    if ((street == 0 || street == 50 || street == 100) && (heading == E || heading == W))
        return true;
    if ((avenue - street) == 0 && (heading == NE || heading == SW))
        return true;
    if ((avenue + street) == 100 && (heading == NW || heading == SE))
        return true;
    return false;
}

void displayDestination()
{
    if (isStayOnThroughways())
        cout << "Illegal stopping place" << endl;
    else
    {
        cout << "A" << abs(avenue - 50) << (avenue >= 50 ? 'E' : 'W');
        cout << " S" << abs(street - 50) << (street >= 50 ? 'N' : 'S');
        cout << " " << directions[heading] << endl;
    }
}

int getAvenueOrStreet(string text)
{
    int index = 0;
    if (isalpha(text.back()))
        index = stoi(text.substr(1, text.length() - 2));
    index = 50 + (text.back() == 'E' || text.back() == 'N' ? index : -index);
}

void setStartPosition()
{
    avenue = getAvenueOrStreet(texts[0]);
    street = getAvenueOrStreet(texts[1]);
    
    for (int i = 0; i < 8; i++)
        if (texts[2] == directions[i])
        {
            heading = i;
            break;
        }
}

bool validateCommand()
{
    if (texts.front() == "TURN")
    {
        string text;
        for (int i = 0; i < texts.size(); i++)
            text += "_" + texts[i];
 
        command = -1;
        for (int i = 0; i < 6; i++)
            if (text == commandText[i])
            {
                command = i;
                break;
            }
            
        intersections = 1;

        return command >= 0;
    }

    if (texts.front() == "GO")
    {
        if (texts.size() < 2 || texts.size() > 3)
            return false;
            
        if (texts.size() == 3 && texts[1] != "STRAIGHT")
            return false;
        
        if (texts.back().length() > 2)
            return false;
            
        for (int i = 0; i < texts.back().length(); i++)
            if (isdigit(texts.back()[i]) == false)
                return false;

        command = GO;
        intersections = stoi(texts.back());

        return 1 <= intersections && intersections <= 99;
    }

    return false;
}

bool validateMove()
{
    

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

        if (validateCommand() && validateMove())
        {
            avenue += step[heading][0] * intersections;
            street += step[heading][1] * intersections;
            heading = headingAfterTurn[heading][command];
        }
    }

    return 0;
}
