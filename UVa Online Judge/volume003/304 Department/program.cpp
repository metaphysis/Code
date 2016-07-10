// Department
// UVa IDs: 304
// Verdict: Accepted
// Submission Date: 2016-07-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct event
{
    string details, room_label;
    bool is_elevator_event = false;
    int start_time = 0, duration = 0, waiting_time = 0, waiting_duration = 0;
};

struct schedule
{
    int floor, room, duration;
    string room_label;
};

struct agent
{
    int enter_time;
    vector<schedule> schedules;
    vector<event> events;
    map<string, int> event_indexer;
};

map<char, agent> agents;

int getTime(string text)
{
    return stoi(text.substr(0, 2)) * 3600 + stoi(text.substr(3, 2)) * 60 + stoi(text.substr(6, 2));
}

void toTime(int seconds)
{
    cout << setw(2) << setfill('0') << seconds / 3600 << ":";
    cout << setw(2) << setfill('0') << (seconds % 3600) / 60 << ":";
    cout << setw(2) << setfill('0') << seconds % 60;
}

string getLabel(int floor, int room)
{
    string label;
    label += (floor < 10 ? "0" : "") + to_string(floor);
    label += (room < 10 ? "0" : "") + to_string(room);
    return label;
}

void visiting(string label)
{
    bool is_room_event = (label.find("elevator") == label.npos);
    map<char, bool> visited;

    while (true)
    {
        // find the first visitor for a room or elevator
        int first_visitor = -1, minimum_start_time = 100000;
        for (int k = 'A'; k <= 'Z'; k++)
        {
            if (agents[k].event_indexer.count(label) && visited[k] == false)
            {
                int start_time = agents[k].events[agents[k].event_indexer[label]].start_time;
                
                // every 5 seconds, a agent can enter into elevator
                if (is_room_event == false)
                {
                    if (start_time % 5 > 0)
                        start_time += (5 - (start_time % 5));
                }

                if (start_time < minimum_start_time)
                {
                    minimum_start_time = start_time;
                    first_visitor = k;
                }
            }
        }

        // for this room or elevator, there is no visitor
        if (first_visitor == -1)
            return;

        int event_index = agents[first_visitor].event_indexer[label];
        int last_start_time = minimum_start_time;
        agents[first_visitor].events[event_index].waiting_duration = 0;

        visited[first_visitor] = true;

        priority_queue<char, vector<char>, greater<char>> waiting_queue;
        waiting_queue.push(first_visitor);

        // use room or elevator, add delay time to schedule time
        while (!waiting_queue.empty())
        {
            int current_user = waiting_queue.top();
            waiting_queue.pop();

            event_index = agents[current_user].event_indexer[label];
            int delay = last_start_time - agents[current_user].events[event_index].start_time;
            if (delay > 0)
            {
                agents[current_user].events[event_index].waiting_time = agents[current_user].events[event_index].start_time;
                agents[current_user].events[event_index].waiting_duration = delay;
            }

            // update schedule
            for (int k = event_index; k < agents[current_user].events.size(); k++)
                agents[current_user].events[k].start_time += delay;

            int last_duration = 5;
            if (is_room_event)
                last_duration = agents[current_user].events[event_index].duration;

            // get the next visitor
            for (int k = 'A'; k <= 'Z'; k++)
                if (agents[k].event_indexer.count(label) && visited[k] == false)
                {
                    if (agents[k].events[agents[k].event_indexer[label]].start_time <= last_start_time + last_duration)
                    {
                        waiting_queue.push(k);
                        visited[k] = true;
                    }
                }
            last_start_time += last_duration;
        }
    }
}

void getSchedule()
{
    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (agents[i].schedules.size() == 0)
            continue;

        int last_time = agents[i].enter_time;

        // enter the building
        event aEvent;
        aEvent.details = "Entry";
        aEvent.start_time = last_time;
        aEvent.duration = 30;
        agents[i].events.push_back(aEvent);
        last_time += aEvent.duration;

        for (int j = 0; j < agents[i].schedules.size(); j++)
        {
            if (j == 0)
            {
                if (agents[i].schedules[j].floor > 1)
                {
                    aEvent.details = "Stay in elevator";
                    aEvent.is_elevator_event = true;
                    aEvent.start_time = last_time;
                    aEvent.duration = 30 * (agents[i].schedules[j].floor - 1);
                    agents[i].events.push_back(aEvent);
                    agents[i].event_indexer["elevator1"] = agents[i].events.size() - 1;
                    last_time += aEvent.duration;
                    
                    aEvent.details = "Transfer from elevator to room " + agents[i].schedules[j].room_label;
                    aEvent.is_elevator_event = false;
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                }

                aEvent.details = "Stay in room " + agents[i].schedules[j].room_label;
                aEvent.is_elevator_event = false;
                aEvent.room_label = agents[i].schedules[j].room_label;
                aEvent.start_time = last_time;
                aEvent.duration = agents[i].schedules[j].duration;
                agents[i].events.push_back(aEvent);
                agents[i].event_indexer[agents[i].schedules[j].room_label] = agents[i].events.size() - 1;
                last_time += aEvent.duration;
            }
            else
            {
                if (agents[i].schedules[j].floor != agents[i].schedules[j - 1].floor)
                {
                    aEvent.details = "Transfer from room " + agents[i].schedules[j - 1].room_label + " to elevator";
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                    
                    aEvent.details = "Stay in elevator";
                    aEvent.is_elevator_event = true;
                    aEvent.start_time = last_time;
                    aEvent.duration = 30 * (agents[i].schedules[j].floor - agents[i].schedules[j - 1].floor);
                    agents[i].events.push_back(aEvent);
                    agents[i].event_indexer["elevator" + to_string(agents[i].schedules[j - 1].floor)] = agents[i].events.size() - 1;
                    last_time += aEvent.duration;
                    
                    aEvent.details = "Transfer from elevator to room " + agents[i].schedules[j].room_label;
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                }
                else
                {
                    aEvent.details = "Transfer from room " + agents[i].schedules[j - 1].room_label + " to room " + agents[i].schedules[j].room_label;
                    aEvent.start_time = last_time;
                    aEvent.duration = 10;
                    agents[i].events.push_back(aEvent);
                    last_time += aEvent.duration;
                }

                aEvent.details = "Stay in room " + agents[i].schedules[j].room_label;
                aEvent.is_elevator_event = false;
                aEvent.room_label = agents[i].schedules[j].room_label;
                aEvent.start_time = last_time;
                aEvent.duration = agents[i].schedules[j].duration;
                agents[i].events.push_back(aEvent);
                agents[i].event_indexer[agents[i].schedules[j].room_label] = agents[i].events.size() - 1;
                last_time += aEvent.duration;
            }
        }

        // leave the building
        if (agents[i].schedules.back().floor > 1)
        {
            aEvent.details = "Transfer from room " + agents[i].schedules.back().room_label + " to elevator";
            aEvent.start_time = last_time;
            aEvent.duration = 10;
            agents[i].events.push_back(aEvent);
            last_time += aEvent.duration;
            
            aEvent.details = "Stay in elevator";
            aEvent.is_elevator_event = true;
            aEvent.start_time = last_time;
            aEvent.duration = 30 * (agents[i].schedules.back().floor - 1);
            agents[i].events.push_back(aEvent);
            agents[i].event_indexer["elevator" + to_string(agents[i].schedules.back().floor)] = agents[i].events.size() - 1;
            last_time += aEvent.duration;
        }

        aEvent.details = "Exit";
        aEvent.start_time = last_time;
        aEvent.duration = 30;
        agents[i].events.push_back(aEvent);
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string block;
    while (cin >> block, block != ".")
    {
        agent aAgent;
        char code = block.front();
        cin >> block;
        aAgent.enter_time = getTime(block);

        while (cin >> block, block != "0")
        {
            schedule aAction;
            aAction.floor = stoi(block.substr(0, 2));
            aAction.room = stoi(block.substr(2, 2));
            aAction.room_label = block;
            cin >> aAction.duration;
            aAgent.schedules.push_back(aAction);
        }
        agents[code] = aAgent;
    }

    getSchedule();

    // floor by floor, room by room, elevator by elevator
    for (int floor = 1; floor < 20; floor++)
    {
        // visit room queue
        for (int room = 1; room < 20; room++)
            visiting(getLabel(floor, room));
            
        // visit elevator queue
        visiting("elevator" + to_string(floor));
    }

    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (agents[i].events.size() == 0)
            continue;
        
        cout << (char)(i) << endl;
        for (int j = 0; j < agents[i].events.size(); j++)
        {
            if (agents[i].events[j].waiting_duration > 0)
            {
                toTime(agents[i].events[j].waiting_time);
                cout << " ";
                toTime(agents[i].events[j].waiting_time + agents[i].events[j].waiting_duration);
                cout << " ";

                if (agents[i].events[j].is_elevator_event)
                    cout << "Waiting in elevator queue" << endl;
                else
                    cout << "Waiting in front of room " << agents[i].events[j].room_label << endl;
            }
            
            toTime(agents[i].events[j].start_time);
            cout << " ";
            toTime(agents[i].events[j].start_time + agents[i].events[j].duration);
            cout << " ";
            cout << agents[i].events[j].details << endl;
        }
        cout << endl;
    }

	return 0;
}
