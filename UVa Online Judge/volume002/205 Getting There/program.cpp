// Getting There
// UVa ID: 205
// Verdict: Accepted
// Submission Date: 2016-04-23
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    string startCity, endCity, leaveTime, arriveTime, costMoney;
    int start, end, leave, arrive, time, cost;
};

vector<vector<edge>> edges;
map<string, int> cityIndexs;
vector<string> cityNames;
set<string> startCities, endCities;
bool found;
vector<edge> path, best;
vector<bool> visited;
int bestTime = 14400, bestCost = 100000;
bool costFirst;

int wait(int arrive, int leave)
{
    if (leave >= arrive)
        return leave - arrive;
    else
        return (1440 - (arrive - leave));
}

int interval(int leave, int arrive)
{
    if (arrive > leave)
        return arrive - leave;
    else
        return (1440 - (leave - arrive));
}

void backtrack(int start, int end, int index)
{
    if (start == end)
    {
        int totalTime = 0, totalCost = 0;
        for (int i = 0; i < index; i++)
        {
            totalTime += path[i].time;
            totalCost += path[i].cost;
            if (i > 0)
                totalTime += wait(path[i - 1].arrive, path[i].leave);
        }

        if (totalTime >= 14400 || totalCost >= 100000)
            return;

        if ((costFirst && (totalCost < bestCost ||
                    (totalCost == bestCost && totalTime < bestTime))) ||
            (!costFirst && (totalTime < bestTime ||
                    (totalTime == bestTime && totalCost < bestCost))))
        {
            best.clear();
            for (int i = 0; i < index; i++)
                best.push_back(path[i]);
            bestTime = totalTime;
            bestCost = totalCost;
            found = true;
        }

        return;
    }

    for (int i = 0; i < edges[start].size(); i++)
        if (visited[edges[start][i].end] == false)
        {
            visited[edges[start][i].end] = true;
            path[index] = edges[start][i];
            backtrack(edges[start][i].end, end, index + 1);
            visited[edges[start][i].end] = false;
        }
}

string toLower(string source)
{
    for (int i = 0; i < source.length(); i++)
        source[i] = tolower(source[i]);
    return source;
}

string toUpper(string source)
{
    source[0] = toupper(source[0]);
    return source;
}

int getTime(string time)
{
    int minutes = 0;
    int indexer = time.find(':');
    minutes = stoi(time.substr(0, indexer)) * 60;
    minutes += stoi(time.substr(indexer + 1, 2));
    if (time.back() == 'P')
        minutes += 720;
    return minutes;
}

int getCost(string cost)
{
    for (int i = 0; i < cost.length(); i++)
        if (cost[i] == '.')
        {
            cost.erase(cost.begin() + i);
            break;
        }

    return stoi(cost);
}

string toTime(int time)
{
    string text;

    int days = time / 1440;
    if (days >= 2)
    {
        text += to_string(days);
        text += " days ";
    }
    else if (days >= 1)
    {
        text += to_string(days);
        text += " day ";
    }
    time %= 1440;

    text += to_string(time / 60);
    text += ":";
    time %= 60;
    text += time >= 10 ? "" : "0";
    text += to_string(time);

    return text;
}

string toCost(int cost)
{
    string text = "$";

    text += to_string(cost / 100);
    text += '.';
    cost %= 100;
    text += cost >= 10 ? "" : "0";
    text += to_string(cost);

    return text;
}

string trimTime(string time)
{
    if (time[0] == '0' && time[1] != ':')
        time.erase(time.begin());
    return time;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    bool printTwoBlankLine = false;

    while (getline(cin, line))
    {
        edges.clear();
        cityIndexs.clear();
        cityNames.clear();
        startCities.clear();
        endCities.clear();

        // at most 20 cities
        edges.resize(20);
        visited.resize(20);
        path.resize(20);

        istringstream iss(line);
        string firstPart, secondPart;
        iss >> firstPart >> secondPart;

        // print two empty line
        if (printTwoBlankLine)
            cout << "\n\n";
        else
            printTwoBlankLine = true;

        cout << "Requests and optimal routes for travel ";
        cout << stoi(secondPart) << "\n";
        cout << "------------------------------------------\n";
        cout << "\n";

        while (getline(cin, line), line != "#")
        {
            edge aEdge;

            string startCity, endCity, leaveTime, arriveTime, costMoney;

            iss.clear();
            iss.str(line);
            iss >> startCity >> endCity >> leaveTime >> arriveTime >> costMoney;

            // parse city name
            startCity = toLower(startCity);
            endCity = toLower(endCity);

            if (cityIndexs.count(startCity) == 0)
            {
                cityNames.push_back(startCity);
                cityIndexs.insert({startCity, cityNames.size() - 1});
            }

            if (cityIndexs.count(endCity) == 0)
            {
                cityNames.push_back(endCity);
                cityIndexs.insert({endCity, cityNames.size() - 1});
            }

            startCities.insert(startCity);
            endCities.insert(endCity);

            // parse input to edge
            aEdge.startCity = toUpper(startCity);
            aEdge.endCity = toUpper(endCity);
            aEdge.start = cityIndexs[startCity];
            aEdge.end = cityIndexs[endCity];
            aEdge.leaveTime = trimTime(leaveTime);
            aEdge.arriveTime = trimTime(arriveTime);
            aEdge.leave = getTime(leaveTime);
            aEdge.arrive = getTime(arriveTime);
            aEdge.time = interval(aEdge.leave, aEdge.arrive);
            aEdge.cost = getCost(costMoney);
            aEdge.costMoney = toCost(aEdge.cost);

            // add edge to graph
            edges[aEdge.start].push_back(aEdge);
        }

        bool printOneBlankLine = false;
        while (getline(cin, line), line != "#")
        {
            string startCity, endCity, target;

            iss.clear();
            iss.str(line);
            iss >> startCity >> endCity >> target;

            startCity = toLower(startCity);
            endCity = toLower(endCity);

            // print empty line
            if (printOneBlankLine)
                cout << "\n";
            else
                printOneBlankLine = true;

            // special case
            if (startCity == endCity)
            {
                cout << "You are already in " << toUpper(startCity) << ".\n";
                continue;
            }
            
            if (startCities.count(startCity) == 0 ||
                endCities.count(endCity) == 0)
            {
                cout << "There is no route from ";
                cout << toUpper(startCity);
                cout << " to ";
                cout << toUpper(endCity);
                cout << ".\n";
                continue;
            }

            // backtrack
            found = false;
            costFirst = target == "COST";
            bestTime = 14400;
            bestCost = 100000;
            fill(visited.begin(), visited.end(), false);
            backtrack(cityIndexs[startCity], cityIndexs[endCity], 0);

            // output
            if (found)
            {
                // print from and to
                cout << "From: ";
                cout << setw(21) << left << toUpper(startCity);
                cout << "To: ";
                cout << setw(21) << left << toUpper(endCity);
                cout << "Optimize: ";
                cout << toUpper(toLower(target));
                cout << "\n";

                // print header
                cout <<
                    "==================================================================\n";
                cout << setw(20) << left << "From";
                cout << setw(23) << left << "To";
                cout << setw(8) << left << "Leave";
                cout << setw(6) << left << "Arrive";
                cout << setw(9) << right << "Cost";
                cout << "\n";
                cout <<
                    "==================================================================\n";

                // print path
                for (int i = 0; i < best.size(); i++)
                {
                    cout << setw(20) << left << best[i].startCity;
                    cout << setw(23) << left << best[i].endCity;
                    cout << setw(8) << left << best[i].leaveTime;
                    cout << setw(6) << left << best[i].arriveTime;
                    cout << setw(9) << right << best[i].costMoney;
                    cout << "\n";
                }

                // print summary
                cout << setw(66) << right << "-----------------------";
                cout << "\n";
                cout << setw(57) << right << toTime(bestTime);
                cout << setw(9) << right << toCost(bestCost);
                cout << "\n";
            }
            else
            {
                cout << "There is no route from ";
                cout << toUpper(startCity);
                cout << " to ";
                cout << toUpper(endCity);
                cout << ".\n";
            }
        }
    }

    return 0;
}
