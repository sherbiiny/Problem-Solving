// checks if point p inside disk with diameter ab
bool inDisk(P a, P b, P p) { return sgn(dot(a - p, b - p)) < 1; }

// checks if point p on segment ab
bool onSegment(P a, P b, P p) { return a == p || b == p || (!orient(a, b, p) && inDisk(a, b, p)); }

// proper intersection of 2 segments
pair<bool, P> properInter(P a, P b, P c, P d) {
    T oa = area(c,d,a), ob = area(c,d,b);
    T oc = area(a,b,c), od = area(a,b,d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {true, (a * ob - b * oa) / (ob - oa)};
    return {false, {}};
}

// distance point to segment
T segDist(P a, P b, P p) {
    Line l(a, b);
    if(l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p);
    return min(abs(a - p), abs(b - p));
}

// distance between 2 segments
T segSegDist(P a, P b, P c, P d) {
    if (properInter(a,b,c,d).first) return 0;
    return min({segDist(a,b,c), segDist(a,b,d), segDist(c,d,a), segDist(c,d,b)});
}