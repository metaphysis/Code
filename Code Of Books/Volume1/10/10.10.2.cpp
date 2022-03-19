const int MAXN = 1100;
const double EPSILON = 1e-7;

// 判断给定的值是否为零值。
inline bool zero(double x) { return fabs(x) < EPSILON; }

// 三维空间点。
struct point3
{
    double x, y, z;
    point3 (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
    point3 operator*(double k) { return point3(x * k, y * k, z * k); }
    point3 operator/(double k) { return point3(x / k, y / k, z / k); }
    bool operator<(const point3 &p) const {
        if (!zero(x - p.x)) return x < p.x;
        if (!zero(y - p.y)) return y < p.y;
        return z < p.z;
    }
    bool operator==(const point3 &p) const {
        return zero(x - p.x) && zero(y - p.y) && zero(z - p.z);
    }
} ps[MAXN];

// 三维空间平面。平面的三个点使用点的序号予以表示。
struct plane3
{
    int a, b, c;
    plane3 (int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
};

// 三维向量的模。
double norm(point3 p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
}

// 三维向量的叉积。
point3 cross(point3 a, point3 b)
{
    point3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

// 三维向量的点积。
double dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double signedVolume(int p, int a, int b, int c)
{
    return dot(ps[a] - ps[p], cross(ps[b] - ps[p], ps[c] - ps[p]));
}

double signedArea(int a, int b, int c)
{
    return norm(cross(ps[b] - ps[a], ps[c] - ps[a]));
}

vector<plane3> faces;
int n, cnt, visited[MAXN][MAXN];

bool initializeConvexHull()
{
    for (int i = 2; i < n; i++) {
        if (zero(signedArea(0, 1, i))) continue;
        swap(ps[i], ps[2]);
        for (int j = i + 1; j < n; j++) {
            if (zero(signedVolume(0, 1, 2, j))) continue;
            swap(ps[j], ps[3]);
            faces.push_back(plane3(0, 1, 2));
            faces.push_back(plane3(0, 2, 1));
            return true;
        } 
    }
    return false;
}

void addPoint(int p)
{
    cnt++;
    vector<plane3> unlighted;
    for (int i = 0, a, b, c; i < faces.size(); i++) {
        a = faces[i].a, b = faces[i].b, c = faces[i].c;
        if (signedVolume(p, a, b, c) < 0) {
            visited[a][b] = visited[b][a] = visited[a][c] = cnt;
            visited[c][a] = visited[b][c] = visited[c][b] = cnt;
        }
        else unlighted.push_back(faces[i]);
    }
    faces = unlighted;
    for (int i = 0, a, b, c; i < unlighted.size(); i++) {
        a = unlighted[i].a, b = unlighted[i].b, c = unlighted[i].c;
        if (visited[a][b] == cnt) faces.push_back(plane3(b, a, p));
        if (visited[b][c] == cnt) faces.push_back(plane3(c, b, p));
        if (visited[c][a] == cnt) faces.push_back(plane3(a, c, p));
    }
}

double getAreaOf3DConvexHull()
{
    sort(ps, ps + n);
    n = unique(ps, ps + n) - ps;
    random_shuffle(ps, ps + n);
    faces.clear();
    if (initializeConvexHull()) {
        cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                visited[i][j] = 0;
        for (int i = 3; i < n; i++) addPoint(i);
        double area = 0;
        for (int i = 0; i < faces.size(); i++)
            area += signedArea(faces[i].a, faces[i].b, faces[i].c);
        return area / 2;
    }
    return -1.0;
}
