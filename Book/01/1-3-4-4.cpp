string round(double angle)
{
    stringstream ss;
    ss << fixed << setprecision(2) << (angle + 1e-7);
    string roundedAngle;
    ss >> roundedAngle;
    if (roundedAngle == "360.00") roundedAngle = "0.00";
    return roundedAngle;
}
