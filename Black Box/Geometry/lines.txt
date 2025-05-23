struct Line {
    // Line is represented by a vector and constant c
    P v; T c;

    Line(P v, T c): v(v), c(c) {}

    // ax + by = c
    Line(T a, T b, T c): v(b, -a), c(c) {}

    // line from two points a --> b
    Line(P a, P b): v(b - a), c(cross(v, a)) {}

    // in which side p lies
    int side(P p) { return sgn(cross(v, p) - c); }

    // distance of p from the line
    T dist(P p) { return abs((cross(v, p) - c) / abs(v)); }

    // return perpendicular line touching p
    Line perpTrough(P p) { return {p, p + perp(v)}; }

    // translate line using vector
    Line translate(P t) { return {v, c + cross(v, t)}; }

    // translate line to the left using dist
    Line translate(T d) { return {v, c + d * abs(v)}; }

    // compare projection, used to sort point through line
    bool cmpProj(P a, P b) { return dot(v, a) < dot(v, b); }
};

// intersection betwen two lines
pair<bool, P> inter(Line a, Line b) {
    T d = cross(a.v, b.v);
    if (!sgn(d)) return {false, {}};
    return {true, (b.v * a.c - a.v * b.c) / d};
}

Line bisector(Line a, Line b, bool interior) {
    assert(sgn(cross(a.v, b.v)) != 0); // a and b cannot be parallel
    T sign = interior ? 1 : -1;
    return {b.v / abs(b.v) + a.v / abs(a.v) * sign, b.c / abs(b.v) + a.c / abs(a.v) * sign};
}