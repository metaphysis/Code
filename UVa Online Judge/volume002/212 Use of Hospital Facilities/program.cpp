// Use of Hospital Facilities
// UVa ID: 212
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct patient
{
    string lastname;
    int index;
    int mintues_surgery, mintues_recovery;
    int enter_room, leave_room, enter_bed, leave_bed;
    int room_number, bed_number;

    bool operator<(patient x) const
    {
        return index < x.index;
    }
};

struct room
{
    int index, mintues_used, time_expried;
    patient someone;
    int available;

    bool operator<(room x) const
    {
        if (available != x.available)
            return x.available < available;

        if (available == 0)
            return x.index < index;

        if (time_expried != x.time_expried)
            return x.time_expried < time_expried;
        else
            return x.index < index;
    }
};

bool cmp_room(room x, room y)
{
    return x.index < y.index;
}

struct bed
{
    int index, mintues_used, time_expried;
    patient someone;
    int available;
};

int operating_rooms, recovery_rooms, starting_mintues,
    mintues_operating_to_recovery, mintues_preparing_operating,
    mintues_preparing_recovery, patients_counter, mintues_required_surgery,
    mintues_required_recovery;

vector<patient> patients;
priority_queue<room> rooms;

string toTime(int time)
{
    string text;
    text += to_string(time / 60);
    text += ":";
    time %= 60;
    text += (time >= 10 ? "" : "0") + to_string(time % 60);
    return text;
}

bool cmp(patient x, patient y)
{
    if (x.leave_room == y.leave_room)
        return x.room_number < y.room_number;
    else
        return x.leave_room < y.leave_room;
}

void arrange()
{
    vector<patient> next;
    while (patients.size())
    {
        room room = rooms.top();
        rooms.pop();

        if (room.available)
        {
            patient another = patients.front();
            patients.erase(patients.begin());

            another.enter_room = room.time_expried;
            another.room_number = room.index;

            room.someone = another;
            room.time_expried += another.mintues_surgery;
            room.available = 0;
            rooms.push(room);
        }
        else
        {
            patient someone = room.someone;
            someone.leave_room = room.time_expried;
            next.push_back(someone);

            room.mintues_used += someone.mintues_surgery;
            room.time_expried = room.time_expried + mintues_preparing_operating;
            room.available = 1;
            rooms.push(room);
        }
    }

    vector<room> usedRooms;
    while (rooms.size())
    {
        room room = rooms.top();
        rooms.pop();

        // there is a patient in room
        if (!room.available)
        {
            patient someone = room.someone;
            someone.leave_room = room.time_expried;
            room.mintues_used += someone.mintues_surgery;
            next.push_back(someone);
        }

        usedRooms.push_back(room);
    }

    // sort the patients before queue for recovery
    sort(next.begin(), next.end(), cmp);

    // queue to recovery room
    vector<bed> usedBeds;
    for (int i = 1; i <= recovery_rooms; i++)
    {
        bed bed;
        bed.index = i;
        bed.time_expried = starting_mintues;
        bed.available = 1;
        bed.mintues_used = 0;
        usedBeds.push_back(bed);
    }

    vector<patient> last;
    for (int i = 0; i < next.size(); i++)
    {
        patient another = next[i];
        for (int j = 0; j < usedBeds.size(); j++)
            if (usedBeds[j].available ||
                (usedBeds[j].available == 0
                    && another.leave_room >= usedBeds[j].time_expried))
            {
                if (usedBeds[j].available == 0)
                    last.push_back(usedBeds[j].someone);

                usedBeds[j].available = 0;
                another.enter_bed =
                    max(another.leave_room + mintues_operating_to_recovery,
                    usedBeds[j].time_expried);
                another.leave_bed =
                    another.enter_bed + another.mintues_recovery;
                another.bed_number = j + 1;
                usedBeds[j].someone = another;
                usedBeds[j].time_expried =
                    another.leave_bed + mintues_preparing_recovery;
                usedBeds[j].mintues_used += another.mintues_recovery;
                break;
            }
    }

    for (int i = 0; i < usedBeds.size(); i++)
        if (usedBeds[i].available == 0)
            last.push_back(usedBeds[i].someone);

    // sort patient by index
    sort(last.begin(), last.end());

    int space = to_string(patients_counter).length();

    // print header, tricky output format, the problem statement is not
    // very clear
    cout << " Patient          Operating Room          Recovery Room\n";
    cout << " #  Name     Room#  Begin   End      Bed#  Begin    End\n";
    cout << " ------------------------------------------------------\n";

    for (int i = 0; i < last.size(); i++)
    {
        cout << setw(2) << right << last[i].index;
        cout << "  ";
        cout << setw(10) << left << last[i].lastname;
        cout << setw(2) << right << last[i].room_number;
        cout << setw(8) << right << toTime(last[i].enter_room);
        cout << setw(8) << right << toTime(last[i].leave_room);
        cout << setw(7) << right << last[i].bed_number;
        cout << setw(8) << right << toTime(last[i].enter_bed);
        cout << setw(8) << right << toTime(last[i].leave_bed);
        cout << "\n";
    }

    int last_leave_bed = 0;
    for (int i = 0; i < last.size(); i++)
        if (last_leave_bed < last[i].leave_bed)
            last_leave_bed = last[i].leave_bed;

    sort(usedRooms.begin(), usedRooms.end(), cmp_room);

    cout << "\nFacility Utilization\n";
    cout << "Type  # Minutes  % Used\n";
    cout << "-------------------------\n";

    for (int i = 0; i < usedRooms.size(); i++)
    {
        cout << "Room";
        cout << setw(3) << right << usedRooms[i].index;
        cout << setw(8) << right << usedRooms[i].mintues_used;
        double percent =
            (double)(usedRooms[i].mintues_used) / (last_leave_bed -
            starting_mintues) * 100.0;
        cout << setw(8) << right << fixed << setprecision(2) << percent;
        cout << "\n";
    }

    for (int i = 0; i < usedBeds.size(); i++)
    {
        cout << "Bed";
        cout << setw(4) << right << usedBeds[i].index;
        cout << setw(8) << right << usedBeds[i].mintues_used;
        double percent =
            (double)(usedBeds[i].mintues_used) / (last_leave_bed -
            starting_mintues) * 100.0;
        cout << setw(8) << right << fixed << setprecision(2) << percent;
        cout << "\n";
    }
    cout << "\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);

    // there is multi input data set, but problem statement is not mention it
    while (cin >> operating_rooms >> recovery_rooms
        >> starting_mintues >> mintues_operating_to_recovery
        >> mintues_preparing_operating >> mintues_preparing_recovery
        >> patients_counter)
    {
        starting_mintues *= 60;

        for (int i = 1; i <= operating_rooms; i++)
        {
            room room;
            room.index = i;
            room.time_expried = starting_mintues;
            room.available = 1;
            room.mintues_used = 0;
            rooms.push(room);
        }

        cin.ignore();

        string lastname;
        for (int i = 1; i <= patients_counter; i++)
        {
            getline(cin, lastname);

            cin >> mintues_required_surgery >> mintues_required_recovery;
            cin.ignore();

            patient aPatient;
            aPatient.lastname = lastname;
            aPatient.index = i;
            aPatient.mintues_surgery = mintues_required_surgery;
            aPatient.mintues_recovery = mintues_required_recovery;
            patients.push_back(aPatient);
        }

        arrange();
    }

    return 0;
}
