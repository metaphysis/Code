const double PI = 2 * acos(0);

pair<int, int> collide(int a, int b, int x, int y, int A, int v, int s, int t)
{
    double d = (v + s * t) * t / 2.0;
    double dx = fabs(d * cos(A * PI / 180.0)), dy = fabs(d * sin(A * PI / 180.0));

    int ch = 0, cv = 0;
    if (A >= 0 && A <= 90) {
        ch = (y + b + dy) / (2 * b);
        cv = (x + a + dx) / (2 * a);
    }
    else if (A > 90 && A <= 180) {
        ch = (y + b + dy) / (2 * b);
        cv = (a - x + dx) / (2 * a);
    }
    else if (A > 180 && A <= 270) {
        ch = (b - y + dy) / (2 * b);
        cv = (a - x + dx) / (2 * a);
    }
    else if (A > 270 && A < 360) {
        ch = (b - y + dy) / (2 * b);
        cv = (x + a + dx) / (2 * a);
    }

    return make_pair(ch, cv);
}
