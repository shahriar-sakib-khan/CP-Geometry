#include <bits/stdc++.h>
using namespace std;
#define kamui ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define checkmate return 0;

using ll = long long;
using ld = long double;

#define For(i, a, n) for (auto i = a; i < n; ++i)
#define rFor(i, n, a) for (auto i = n; i >= a; --i)
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(x) (ll)(x).size()
#define pb push_back
#define endl '\n'

struct Pt {
    ll x, y;

    // Sorting by x then y — critical for convex hull
    bool operator<(const Pt &o) const {
        return (x == o.x) ? (y < o.y) : (x < o.x);
    }

    // Vector subtraction (b - a) = vector a→b
    Pt operator-(const Pt &o) const { return {x - o.x, y - o.y}; }
};

// ---------------- sgn(v) ----------------
ll sgn(ll v) { return (v > 0) - (v < 0); }

// ---------------- cross_val(a,b) ----------------
ll cross_val(const Pt &a, const Pt &b) {
    return a.x*b.y - a.y*b.x;
}

// ---------------- cross(a,b,c) ----------------
ll cross(const Pt &a, const Pt &b, const Pt &c) {
    // Vector AB = b-a ; AC = c-a
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

// ---------------- ccw(a,b,c) ----------------
ll ccw(const Pt &a, const Pt &b, const Pt &c) {
    return sgn(cross(a,b,c));
}

// ---------------- polygon_area(poly) ----------------
double polygon_area(const vector<Pt>& p) {
    ll A = 0;
    ll n = p.size();
    for (ll i = 0; i < n; i++) {
        ll j = (i + 1) % n;
        A += p[i].x * p[j].y - p[i].y * p[j].x;
    }
    return fabs(A) / 2.0;
}

// ---------------- convex_hull(pts) ----------------
vector<Pt> convex_hull(vector<Pt> pts) {
    ll n = pts.size();
    if (n <= 1) return pts;

    sort(pts.begin(), pts.end());
    vector<Pt> h; h.reserve(2*n);

    for (auto &p : pts) {
        while (h.size() >= 2 && cross(h[h.size()-2], h[h.size()-1], p) <= 0)
            h.pop_back();
        h.push_back(p);
    }

    ll lower_sz = h.size();

    for (ll i = n-1; i >= 0; i--) {
        while ((ll)h.size() > lower_sz &&
               cross(h[h.size()-2], h[h.size()-1], pts[i]) <= 0)
            h.pop_back();
        h.push_back(pts[i]);
    }

    h.pop_back();
    return h;
}

void check() {
    ll n; cin >> n;

    vector<Pt> v(n);
    for (auto &p: v) cin >> p.x >> p.y;

    auto ans = convex_hull(v);

    cout << ans.size() << endl;
    for (auto &p : ans) cout << p.x << " " << p.y << endl;

    cout << "Area: " << polygon_area(ans) << endl;

    return;
}

int main() {
    kamui;
    ll tc = 1;
    // cin >> tc;
    while (tc--) {
        check();
    }
    checkmate;
}
// 20 November 2025 : Thursday