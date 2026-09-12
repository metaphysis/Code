#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int width, height;

int cmpValue(double x, double y = 0.0) {
    if (x <= y + eps) return x + eps < y ? -1 : 0;
    return 1;
}

struct Vector {
    double x, y;
    Vector() {
    }
    Vector(double xValue, double yValue) : x(xValue), y(yValue) {
    }
    void normalize() {
        double len = sqrt(x * x + y * y);
        x /= len;
        y /= len;
    }
    bool operator < (const Vector &other) const {
        if (cmpValue(x, other.x) != 0) return cmpValue(x, other.x) < 0;
        return cmpValue(y, other.y) < 0;
    }
    bool operator == (const Vector &other) const {
        return cmpValue(x, other.x) == 0 && cmpValue(y, other.y) == 0;
    }
};

struct Person {
    double x, y;
    Vector dir;
    string name;
    Person() {
    }
    Person(double xValue, double yValue, Vector direction, string personName) {
        x = xValue;
        y = yValue;
        dir = direction;
        name = personName;
    }
    double timeToFall() const {
        double horizontal, vertical;
        horizontal = cmpValue(dir.x, 0.0) < 0 ? x / (-dir.x) : (width - x) / dir.x;
        vertical = cmpValue(dir.y, 0.0) < 0 ? y / (-dir.y) : (height - y) / dir.y;
        return min(horizontal, vertical);
    }
};

struct Death {
    string name;
    double time;
    bool operator < (const Death &other) const {
        if (cmpValue(time, other.time) != 0) return cmpValue(time, other.time) < 0;
        return name < other.name;
    }
};

struct Collision {
    double time;
    Vector point;
    int personA, personB;
    Collision() {
    }
    Collision(double collisionTime) {
        time = collisionTime;
        personA = personB = -1;
    }
    Collision(double collisionTime, double x, double y, int a, int b) {
        time = collisionTime;
        point = Vector(x, y);
        personA = a;
        personB = b;
    }
    bool operator < (const Collision &other) const {
        if (cmpValue(time, other.time) != 0) return cmpValue(time, other.time) < 0;
        return point < other.point;
    }
};

double dotProduct(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

bool outsideWorld(double x, double y) {
    if (cmpValue(x, 0.0) < 0) return true;
    if (cmpValue(x, width) > 0) return true;
    if (cmpValue(y, 0.0) < 0) return true;
    if (cmpValue(y, height) > 0) return true;
    return false;
}

Collision collisionBetween(const Person &a, int indexA, const Person &b, int indexB) {
    double x0, y0, x1, y1, x2, y2, x3, y3, t0, t1, det;
    if (Vector(a.x, a.y) == Vector(b.x, b.y)) return Collision(-1.0);
    x0 = a.x;
    y0 = a.y;
    x1 = a.x + a.dir.x;
    y1 = a.y + a.dir.y;
    x2 = b.x;
    y2 = b.y;
    x3 = b.x + b.dir.x;
    y3 = b.y + b.dir.y;
    t0 = (y3 - y2) * (x0 - x2) - (x3 - x2) * (y0 - y2);
    t1 = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
    det = (y1 - y0) * (x3 - x2) - (y3 - y2) * (x1 - x0);
    if (cmpValue(det, 0.0) == 0) {
        if (cmpValue(t0, 0.0) == 0 || cmpValue(t1, 0.0) == 0) {
            if (cmpValue(dotProduct(a.dir, b.dir), 1.0) == 0) return Collision(-1.0);
            double midX, midY, dist;
            midX = (x0 + x2) / 2.0;
            midY = (y0 + y2) / 2.0;
            dist = hypot(x2 - x0, y2 - y0) / 2.0;
            if (cmpValue(x0 + dist * a.dir.x, midX) != 0) return Collision(-1.0);
            if (cmpValue(y0 + dist * a.dir.y, midY) != 0) return Collision(-1.0);
            if (cmpValue(x2 + dist * b.dir.x, midX) != 0) return Collision(-1.0);
            if (cmpValue(y2 + dist * b.dir.y, midY) != 0) return Collision(-1.0);
            return Collision(dist, midX, midY, indexA, indexB);
        }
        return Collision(-1.0);
    }
    t0 /= det;
    t1 /= det;
    if (cmpValue(t0, t1) != 0) return Collision(-1.0);
    if (cmpValue(t0, 0.0) < 0 || cmpValue(t1, 0.0) < 0) return Collision(-1.0);
    double x, y;
    x = x0 + t0 * (x1 - x0);
    y = y0 + t0 * (y1 - y0);
    if (outsideWorld(x, y)) return Collision(-1.0);
    return Collision(t0, x, y, indexA, indexB);
}

bool collidesWithSomeone(const vector<Person> &people, int id) {
    int i;
    for (i = 0; i < (int)people.size(); i++) {
        if (i == id) continue;
        Collision collision;
        collision = collisionBetween(people[id], id, people[i], i);
        if (cmpValue(collision.time, 0.0) > 0) return true;
    }
    return false;
}

vector<Person> processPeople(vector<Person> people, vector<Death> &deaths, double &elapsedTime) {
    int i, j, k, first, last;
    for (i = 0; i < (int)people.size(); i++) {
        if (collidesWithSomeone(people, i)) continue;
        deaths.push_back({people[i].name, elapsedTime + people[i].timeToFall()});
        vector<Person> nextPeople;
        for (j = 0; j < (int)people.size(); j++)
            if (i != j) nextPeople.push_back(people[j]);
        return nextPeople;
    }
    vector<Collision> collisions;
    for (i = 0; i < (int)people.size(); i++) {
        for (j = i + 1; j < (int)people.size(); j++) {
            Collision collision;
            collision = collisionBetween(people[i], i, people[j], j);
            if (cmpValue(collision.time, 0.0) > 0) collisions.push_back(collision);
        }
    }
    sort(collisions.begin(), collisions.end());
    double minTime;
    minTime = collisions[0].time;
    set<int> deadPeople;
    first = 0;
    while (first < (int)collisions.size() && cmpValue(collisions[first].time, minTime) == 0) {
        last = first;
        while (last < (int)collisions.size() && cmpValue(collisions[last].time, minTime) == 0 && collisions[last].point == collisions[first].point)
            last++;
        if (last - first == 1) {
            int personA, personB;
            personA = collisions[first].personA;
            personB = collisions[first].personB;
            swap(people[personA].name, people[personB].name);
        } else {
            for (k = first; k < last; k++) {
                deadPeople.insert(collisions[k].personA);
                deadPeople.insert(collisions[k].personB);
            }
        }
        first = last;
    }
    vector<Person> nextPeople;
    for (i = 0; i < (int)people.size(); i++) {
        if (deadPeople.count(i) > 0) {
            deaths.push_back({people[i].name, elapsedTime + minTime});
            continue;
        }
        people[i].x += minTime * people[i].dir.x;
        people[i].y += minTime * people[i].dir.y;
        nextPeople.push_back(people[i]);
    }
    elapsedTime += minTime;
    return nextPeople;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases, n, i;
    cin >> cases;
    while (cases--) {
        cin >> n >> width >> height;
        vector<Person> people;
        for (i = 0; i < n; i++) {
            double x, y, dx, dy;
            string name;
            cin >> x >> y >> dx >> dy >> name;
            dx -= x;
            dy -= y;
            Vector direction(dx, dy);
            direction.normalize();
            people.push_back(Person(x, y, direction, name));
        }
        vector<Death> deaths;
        double elapsedTime;
        elapsedTime = 0.0;
        while (!people.empty())
            people = processPeople(people, deaths, elapsedTime);
        sort(deaths.begin(), deaths.end());
        cout << deaths.back().name << '\n';
    }
    return 0;
}
