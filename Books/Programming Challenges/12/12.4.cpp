double gcd(double R, double plat, double plong, double qlat, double qlong)
{
    double r = 0;
    r = R * acos(sin(plat) * sin(qlat) + cos(plat) * cos(qlat) * cos(plong - qlong));
    return r;
}

double haversine(double R, double plat, double plong, double qlat, double qlong)
{
    double dlon = qlong - plong, dlat = qlat - plat, a = 0, c = 0;
    a = pow((sin(dlat / 2)), 2) + cos(plat) * cos(qlat) * pow(sin(dlon / 2), 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}
