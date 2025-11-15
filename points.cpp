#include <bits/stdc++.h>
using namespace std;

// ===============================================================
//                       POINT STRUCT + UTILITIES
// ===============================================================

struct Pt {
    long long x, y;

    // Sorting by x then y — critical for convex hull
    bool operator<(const Pt &o) const {
        return (x == o.x) ? (y < o.y) : (x < o.x);
    }

    // Vector subtraction (b - a) = vector a→b
    Pt operator-(const Pt &o) const { return {x - o.x, y - o.y}; }
};

// ---------------- sgn(v) ----------------
// Returns +1, 0, -1 for positive, zero, negative
// Used for orientation logic to avoid overflow of boolean logic.
int sgn(long long v) { return (v > 0) - (v < 0); }





// ===============================================================
//                       BASIC VECTOR OPS
// ===============================================================

// ---------------- dot(a,b) ----------------
// Returns: a·b (scalar)
// Uses:
//   - Check angle between vectors
//   - Projection
//   - Checking perpendicularity (dot == 0)
// Expected: two vectors or (b - a)
long long dot(const Pt &a, const Pt &b) {
    return a.x*b.x + a.y*b.y;
}

// ---------------- cross_val(a,b) ----------------
// Returns: a×b (scalar 2D cross product)
// Meaning:
//   >0 = a→b is CCW turn
//   <0 = CW turn
//   =0 = collinear
// Use-case: orientation when anchor is at origin
long long cross_val(const Pt &a, const Pt &b) {
    return a.x*b.y - a.y*b.x;
}

// ---------------- cross(a,b,c) ----------------
// Orientation test for 3 points.
// Returns area * 2 of triangle (signed)
long long cross(const Pt &a, const Pt &b, const Pt &c) {
    // Vector AB = b-a ; AC = c-a
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}
// Use-case: convex hull, segment intersection, polygon area
// Returns: positive=left turn, negative=right, zero=collinear.

// ---------------- dist2(a,b) ----------------
// Squared distance (avoids sqrt, faster)
// Use-case: comparing distances, closest pair, hull
long long dist2(const Pt &a, const Pt &b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}

// ---------------- ccw(a,b,c) ----------------
// Clean orientation wrapper
int ccw(const Pt &a, const Pt &b, const Pt &c) {
    return sgn(cross(a,b,c));
}






// ===============================================================
//                        POLYGON AREA (Shoelace)
// ===============================================================

// ---------------- polygon_area(poly) ----------------
// Returns: double area of polygon (always positive)
double polygon_area(const vector<Pt>& p) {
    long long A = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;   // next vertex
        A += p[i].x * p[j].y - p[i].y * p[j].x;  // cross term
    }
    return fabs(A) / 2.0;
}
// Use-cases:
//   - Area of convex or concave polygon
//   - Order of points does not matter (CW/CCW)
// Output meaning: exact area as double








// ===============================================================
//                    SEGMENT INTERSECTION (Robust)
// ===============================================================

// ---------------- on_seg(a,b,c) ----------------
// Returns true if C lies on segment AB (collinearity assumed)
bool on_seg(const Pt& a, const Pt& b, const Pt& c) {
    return min(a.x,b.x) <= c.x && c.x <= max(a.x,b.x) &&
           min(a.y,b.y) <= c.y && c.y <= max(a.y,b.y);
}
// Use-case:
//   - Handle collinear overlaps
//   - Used inside full segment_intersect()

// ---------------- seg_intersect(a,b,c,d) ----------------
// Returns: true if segments AB and CD intersect
bool seg_intersect(const Pt& a, const Pt& b, const Pt& c, const Pt& d) {
    long long o1 = cross(a,b,c);
    long long o2 = cross(a,b,d);
    long long o3 = cross(c,d,a);
    long long o4 = cross(c,d,b);

    // General case — signs differ (proper intersection)
    if ((sgn(o1) != sgn(o2)) && (sgn(o3) != sgn(o4))) return true;

    // Collinear + on-segment cases
    if (o1 == 0 && on_seg(a,b,c)) return true;
    if (o2 == 0 && on_seg(a,b,d)) return true;
    if (o3 == 0 && on_seg(c,d,a)) return true;
    if (o4 == 0 && on_seg(c,d,b)) return true;

    return false;
}
// Use-cases:
//   - Detect if two paths cross
//   - Geometry constraints
//   - Checking polygon self-intersection
// Output:
//   true  → they intersect (touch or cross)
//   false → they don't








// ===============================================================
//                   CONVEX HULL — Monotone Chain
// ===============================================================

// ---------------- convex_hull(pts) ----------------
// Produces CCW hull without collinear edge points.
vector<Pt> convex_hull(vector<Pt> pts) {
    int n = pts.size();
    if (n <= 1) return pts;

    sort(pts.begin(), pts.end());      // critical for chain algorithm
    vector<Pt> h; h.reserve(2*n);

    // ---------- LOWER HULL ----------
    for (auto &p : pts) {
        while (h.size() >= 2 && cross(h[h.size()-2], h[h.size()-1], p) <= 0)
            h.pop_back();              // <= removes collinear points
        h.push_back(p);
    }

    int lower_sz = h.size();

    // ---------- UPPER HULL ----------
    for (int i = n-1; i >= 0; i--) {
        while ((int)h.size() > lower_sz &&
               cross(h[h.size()-2], h[h.size()-1], pts[i]) <= 0)
            h.pop_back();
        h.push_back(pts[i]);
    }

    h.pop_back(); // last = first
    return h;
}
// Use-cases:
//   - smallest convex polygon enclosing points
//   - nearest/farthest pair tricks
//   - rotating calipers (diameter, width, minimum triangle)
// Output:
//   vector<Pt> in CCW order






// ===============================================================
//                OPTIONAL — LINE INTERSECTION (Infinite lines)
// ===============================================================

// ---------------- line_intersect(a,b,c,d) ----------------
// Intersection point of infinite lines AB & CD
// (NOT segment intersection)
Pt line_intersect(Pt a, Pt b, Pt c, Pt d) {
    long long A1 = b.y - a.y;
    long long B1 = a.x - b.x;
    long long C1 = A1*a.x + B1*a.y;

    long long A2 = d.y - c.y;
    long long B2 = c.x - d.x;
    long long C2 = A2*c.x + B2*c.y;

    long long det = A1*B2 - A2*B1;  // = 0 means parallel lines

    return { (C1*B2 - C2*B1) / det,
             (A1*C2 - A2*C1) / det };
}
// Use-cases:
//   - Intersection point computation
//   - Needed for line equations
// Output:
//   The exact intersection point (assuming non-parallel)




// ===============================================================
// main()
// ===============================================================
int main() {
    // ------------- DEMO: Convex Hull ------------------
    // int n; cin >> n;
    // vector<Pt> v(n);
    // for (auto &p: v) cin >> p.x >> p.y;
    // auto hull = convex_hull(v);
    // cout << hull.size() << "\n";
    // for (auto &p : hull) cout << p.x << " " << p.y << "\n";

    // ------------- DEMO: Segment Intersection ---------
    // Pt a,b,c,d;
    // cin >> a.x >> a.y >> b.x >> b.y;
    // cin >> c.x >> c.y >> d.x >> d.y;
    // cout << (seg_intersect(a,b,c,d) ? "YES\n" : "NO\n");

    // ------------- DEMO: Polygon Area -----------------
    // int n; cin >> n;
    // vector<Pt> poly(n);
    // for (auto &p: poly) cin >> p.x >> p.y;
    // cout << fixed << setprecision(6) << polygon_area(poly) << "\n";

    return 0;
}

