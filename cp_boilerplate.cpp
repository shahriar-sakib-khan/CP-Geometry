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
#define sz(x) (int)(x).size()
#define pb push_back
#define endl '\n'

inline void Compress(auto& v) { sort(all(v)), v.erase(unique(all(v)), v.end()); }
inline void isOk(auto& condition) {cout << ( (condition) ? "YES" : "NO") << endl;}


void check() {
    ll n;
    cin >> n;
    vector<ll> v(n);
    For(i, 0, n) { cin >> v[i]; }
    
    return;
}

int main() {
    kamui;
    ll tc = 1;
    cin >> tc;
    while (tc--) {
        check();
    }
    checkmate;
}
// 15 November 2025 : Saturday