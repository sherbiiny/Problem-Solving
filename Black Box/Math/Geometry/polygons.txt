// area of polygon
T areaPolygon(vector<P> &p) {
    T area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++)
        area += cross(p[i], p[(i+1) % n]);
    return abs(area) / 2.0;
}

bool above(P a, P p) { return p.y >= a.y; }

// if ray A pointing right crosses segment(p, q)
bool crossesRay(P a, P p, P q) {
    return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}

// check if point a in polygon p
// strict = true --> edges does not count
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a)) return !strict;
        cnt += crossesRay(a, p[i], p[(i+1) % n]);
    }
    return cnt & 1;
}