#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const int maxObj = 22;
const int maxVertex = 26;
const int maxTri = 52;
const int maxImage = 202;
const int maxDepth = 4;

struct Point {
    double x, y, z;
    Point(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
    void normalize() {
        double len = sqrt(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
};

typedef Point Vector;

Vector operator + (const Vector &a, const Vector &b) {
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator - (const Vector &a, const Vector &b) {
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator * (const Vector &a, double k) {
    return Vector(a.x * k, a.y * k, a.z * k);
}

Vector operator * (double k, const Vector &a) {
    return a * k;
}

double dot(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector cross(const Vector &a, const Vector &b) {
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

struct Object {
    Point vertex[maxVertex];
    Vector normal[maxTri];
    Vector color;
    int face[maxTri][3], vertexCount, triCount;
    double refl, refr, index;
};

struct Ray {
    Point point;
    Vector vector;
    double medium;
    Ray(const Point &point, const Vector &vector, double medium) : point(point), vector(vector), medium(medium) {
        this->vector.normalize();
    }
};

struct Intersection {
    Point point;
    int objId, triId;
    Intersection() : objId(-1), triId(-1) {}
};

Object obj[maxObj];
Vector image[maxImage][maxImage];
Point lightPoint;
Vector lightColor;
double ambient;
int objCount;

Intersection getIntersection(const Point &point, const Vector &vector) {
    double best = -1.0;
    Intersection result;
    for (int i = 0; i < objCount; i++) {
        for (int j = 0; j < obj[i].triCount; j++) {
            if (fabs(dot(vector, obj[i].normal[j])) < eps) continue;
            const Point &a = obj[i].vertex[obj[i].face[j][0]], &b = obj[i].vertex[obj[i].face[j][1]], &c = obj[i].vertex[obj[i].face[j][2]];
            Vector normal = obj[i].normal[j];
            double q = dot(normal, a - point) / dot(normal, vector);
            if (q < eps || (best > eps && q >= best)) continue;
            Point hit = point + vector * q;
            Vector c1 = cross(b - a, hit - a), c2 = cross(c - b, hit - b), c3 = cross(a - c, hit - c);
            if (dot(c1, c2) > 0.0 && dot(c1, c3) > eps) {
                best = q;
                result.point = hit;
                result.objId = i;
                result.triId = j;
            }
        }
    }
    return result;
}

double shade(const Point &point, const Vector &normal) {
    Vector vector = lightPoint - point;
    double len = sqrt(dot(vector, vector));
    vector = vector * (1.0 / len);
    for (int i = 0; i < objCount; i++) {
        for (int j = 0; j < obj[i].triCount; j++) {
            if (fabs(dot(vector, obj[i].normal[j])) < eps) continue;
            const Point &a = obj[i].vertex[obj[i].face[j][0]], &b = obj[i].vertex[obj[i].face[j][1]], &c = obj[i].vertex[obj[i].face[j][2]];
            Vector triNormal = obj[i].normal[j];
            double q = dot(triNormal, a - point) / dot(triNormal, vector);
            if (q < eps || q > len - eps) continue;
            Point hit = point + vector * q;
            Vector c1 = cross(b - a, hit - a), c2 = cross(c - b, hit - b), c3 = cross(a - c, hit - c);
            if (dot(c1, c2) > eps && dot(c1, c3) > eps) return 0.0;
        }
    }
    return fabs(dot(vector, normal));
}

Vector getPointColor(const Point &point, const Vector &normal, const Vector &color) {
    double value = ambient + (1.0 - ambient) * shade(point, normal);
    return Vector(color.x * lightColor.x, color.y * lightColor.y, color.z * lightColor.z) * value;
}

bool totalInternalReflection(const Vector &vector, const Vector &normal, double from, double to) {
    double cosine = dot(vector, normal);
    return from * sqrt(max(0.0, 1.0 - cosine * cosine)) >= to * (1.0 - eps);
}

Vector getReflectVector(const Vector &vector, const Vector &normal) {
    return vector - normal * (2.0 * dot(vector, normal));
}

Vector getRefractVector(const Vector &vector, const Vector &normal, double from, double to) {
    double cosine = dot(vector, normal), sine = from * sqrt(max(0.0, 1.0 - cosine * cosine)) / to;
    Vector normalPart = normal * cosine, tangentPart = vector - normalPart;
    normalPart.normalize();
    tangentPart.normalize();
    return normalPart * sqrt(max(0.0, 1.0 - sine * sine)) + tangentPart * sine;
}

Vector traceRay(int depth, const Ray &ray) {
    Vector color, reflectColor, refractColor;
    Intersection intersection = getIntersection(ray.point, ray.vector);
    if (intersection.objId >= 0) {
        Object &object = obj[intersection.objId];
        Vector normal = object.normal[intersection.triId];
        double refl = object.refl, refr = object.refr, nextMedium = ray.medium == 1.0 ? object.index : 1.0;
        color = getPointColor(intersection.point, normal, object.color) * (1.0 - refl - refr);
        if (depth == maxDepth) return color;
        if (refr > 0.0 && totalInternalReflection(ray.vector, normal, ray.medium, nextMedium)) refr = 0.0;
        if (refl > 0.0) reflectColor = traceRay(depth + 1, Ray(intersection.point, getReflectVector(ray.vector, normal), ray.medium)) * refl;
        if (refr > 0.0) refractColor = traceRay(depth + 1, Ray(intersection.point, getRefractVector(ray.vector, normal, ray.medium, nextMedium), nextMedium)) * refr;
    }
    return color + reflectColor + refractColor;
}

void printValue(double value) {
    int number = (int)(value * 255.0 + 0.5), high = number >> 4, low = number & 15;
    cout << (high < 10 ? char('0' + high) : char('a' + high - 10));
    cout << (low < 10 ? char('0' + low) : char('a' + low - 10));
}

void printColor(const Vector &color) {
    printValue(color.x);
    printValue(color.y);
    printValue(color.z);
    cout << ' ';
}

void solve() {
    for (int i = 0; i < objCount; i++) {
        cin >> obj[i].vertexCount;
        for (int j = 0; j < obj[i].vertexCount; j++) cin >> obj[i].vertex[j].x >> obj[i].vertex[j].y >> obj[i].vertex[j].z;
        cin >> obj[i].triCount;
        for (int j = 0; j < obj[i].triCount; j++) {
            cin >> obj[i].face[j][0] >> obj[i].face[j][1] >> obj[i].face[j][2];
            const Point &a = obj[i].vertex[obj[i].face[j][0]], &b = obj[i].vertex[obj[i].face[j][1]], &c = obj[i].vertex[obj[i].face[j][2]];
            obj[i].normal[j] = cross(b - a, c - a);
            obj[i].normal[j].normalize();
        }
        cin >> obj[i].color.x >> obj[i].color.y >> obj[i].color.z >> obj[i].refl >> obj[i].refr >> obj[i].index;
    }
    cin >> lightPoint.x >> lightPoint.y >> lightPoint.z >> ambient >> lightColor.x >> lightColor.y >> lightColor.z;
    int queryCount;
    cin >> queryCount;
    while (queryCount--) {
        Point camera, target;
        Vector up;
        double fov, step, xValue, yValue;
        int width, height;
        cin >> camera.x >> camera.y >> camera.z >> target.x >> target.y >> target.z >> up.x >> up.y >> up.z >> fov >> width >> height;
        Vector z = target - camera;
        z.normalize();
        Vector x = cross(z, up);
        x.normalize();
        step = tan(fov * acos(-1.0) / 360.0) / width;
        xValue = step * (1 - width);
        yValue = step * (height - 1);
        for (int i = 0; i < width; i++, xValue += step * 2.0) {
            double currentY = yValue;
            for (int j = 0; j < height; j++, currentY -= step * 2.0) image[i][j] = traceRay(0, Ray(camera, x * xValue + up * currentY + z, 1.0));
        }
        cout << width << ' ' << height << '\n';
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) printColor(image[j][i]);
            cout << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> objCount && objCount) solve();
    return 0;
}
