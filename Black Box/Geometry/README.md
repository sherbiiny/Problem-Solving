# 📐 Geometry Template

## 🧭 Points and Vectors

```cpp
using T = long double;
const T EPS = 1e-9, PI = acos(-1);

using P = complex<T>;
#define x real()
#define y imag()

// change the input to T (if input double)
void input(P &p) { int a, b; cin >> a >> b; p = P(a, b); }

// sign of a
int sgn(T a) { return (a > EPS) - (a < -EPS); }

// compare points
bool operator==(P a, P b) { return !sgn(a.x - b.x) && !sgn(a.y - b.y); }

// r^2 = abs(p)^2
T sq(P p) { return p.x * p.x + p.y * p.y; }

// dot product
T dot(P v, P w) { return v.x * w.x + v.y * w.y; }

// cross product
T cross(P v, P w) { return v.x * w.y - v.y * w.x; }

// the smaller angle between 2 vectors
T angle(P v, P w) { return acos(clamp(dot(v, w) / abs(v) / abs(w), T(-1), T(1))); }

// perpendicular on vector v
P perp(P v) { return {-v.y, v.x}; }

// 1 -> ac is LEFT of ab, -1: RIGHT, 0 -> touching
int orient(P a, P b, P c) { return sgn(cross(b - a, c - a)); }

// area of triangle (bac) * 2
T area(P a, P b, P c) { return cross(b - a, c - a); }

// angle(bac) counter clockwise
T angle(P a, P b, P c) { return ~orient(a, b, c)? angle(b - a, c - a) : PI * 2 - angle(b - a, c - a); }

// check if point is in angle
bool inAngle(P a, P b, P c, P p) {
    if(orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

// check if angle is 90
bool isPerp(P v, P w) { return !sgn(dot(v, w)); }

// tranlate point
P translate(P p, P v) { return p + v; }

// scale point
P scale(P p, P c, T factor) { return c + (p - c) * factor; }

// rotate p around c
P rotate(P p, P c, T a) { return c + (p - c) * polar(T(1), a); }
````

## 📏 Lines

```cpp
struct Line {
    // Line is represented by a vector and constant c
    P v; T c;

    // Constructor from direction vector and constant
    // Represents the line cross(v, p) = c
    Line(P v, T c): v(v), c(c) {}

    // Constructor from coefficients ax + by = c
    // Represents line using vector (b, -a)
    Line(T a, T b, T c): v(b, -a), c(c) {}

    // Constructor from two points a --> b
    // Direction vector v = b - a, and c = cross(v, a)
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

// Line bisector between a and b
Line bisector(Line a, Line b, bool interior) {
    assert(sgn(cross(a.v, b.v)) != 0); // a and b cannot be parallel
    T sign = interior ? 1 : -1;
    return {b.v / abs(b.v) + a.v / abs(a.v) * sign, b.c / abs(b.v) + a.c / abs(a.v) * sign};
}
```

## 📐 Segments

```cpp
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
```

## ➤ Rays

```cpp
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
```

## 🔷 Polygons

```cpp
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
```