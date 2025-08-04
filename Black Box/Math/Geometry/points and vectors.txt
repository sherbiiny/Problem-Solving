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