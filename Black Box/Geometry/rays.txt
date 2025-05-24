// check if point p on ray
bool onRay(P s, P e, P p) { return !orient(p, s, e) && sgn(dot(p - s, e - s)) >= 0; }

// point p distance from ray
T rayDist(P s, P e, P p) {
    if (sgn(dot(p - s, e - s)) <= 0) return abs(s - p);
    return Line(s, e).dist(p);
}

// 0: no intersection, -1: infinite
pair<int, P> rayInter(P s1, P e1, P s2, P e2) {
    auto [yes, p] = inter(Line(s1, e1), Line(s2, e2));
    if (yes == 0) return {0, {}};
    if (yes == 1) {
        if (onRay(s1, e1, p) && onRay(s2, e2, p)) return {1, p};
        return {0, {}};
    }
    if (onRay(s2, e2, s1) || onRay(s1, e1, s2))
        return {-1, onRay(s2, e2, s1) ? s1 : s2};
    return {0, {0, 0}};
}

// distance between two rays
T rayRayDist(P s1, P e1, P s2, P e2) {
    if (rayInter(s1, e1, s2, e2).first) return 0;
    return min(rayDist(s2, e2, s1), rayDist(s1, e1, s2));
}