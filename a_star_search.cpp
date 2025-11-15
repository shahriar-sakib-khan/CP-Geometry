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


struct Node {
    string s;
    ll g, h;
    Node(string _s="", ll _g=0, ll _h=0): s(_s), g(_g), h(_h) {}
};

struct Cmp {
    bool operator()(const Node &a, const Node &b) const {
        return (a.g + a.h) > (b.g + b.h);
    }
};

ll distance(const string &curr, const string &goal) {
    ll d = 0;
    for(ll i = 0; i < 9; i++) {
        char c = curr[i];
        if(c == '0') continue;
        ll r1 = i / 3, c1 = i % 3;
        ll pos = goal.find(c);
        ll r2 = pos / 3, c2 = pos % 3;
        d += abs(r1 - r2) + abs(c1 - c2);
    }
    return d;
}

bool solvable(const string &s) {
    ll inv = 0;
    vector<ll> a;
    for(char c : s) if(c != '0') a.pb(c - '0');
    for(ll i = 0; i < a.size(); i++)
        for(ll j = i + 1; j < a.size(); j++)
            if(a[i] > a[j]) inv++;
    return (inv % 2 == 0);
}

// Possible moves
vector<pair<string,char>> neighbors(const string &s) {
    ll dr[4] = {-1,1,0,0};
    ll dc[4] = {0,0,-1,1};
    char mv[4] = {'U','D','L','R'};
    vector<pair<string,char>> out;

    ll pos = s.find('0');
    ll r = pos / 3, c = pos % 3;

    for(ll k = 0; k < 4; k++) {
        ll nr = r + dr[k], nc = c + dc[k];
        if(nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
        ll np = nr * 3 + nc;
        string t = s;
        swap(t[pos], t[np]);
        out.pb({t, mv[k]});
    }
    return out;
}


void check() {
    string start, goal;
    cin >> start >> goal;

    if(start == goal) { cout << 0 << endl; return; }
    if(!solvable(start)) { cout << -1 << endl; return; }

    priority_queue<Node, vector<Node>, Cmp> pq;
    unordered_map<string, ll> gscore;
    unordered_map<string, string> parent;
    unordered_map<string, char> move_taken;

    ll h0 = distance(start, goal);
    pq.emplace(start, 0, h0);
    gscore[start] = 0;

    while(!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if(gscore[curr.s] != curr.g) continue;

        if(curr.s == goal) {
            vector<char> moves;
            string t = goal;
            while(t != start) {
                moves.pb(move_taken[t]);
                t = parent[t];
            }
            reverse(moves.begin(), moves.end());

            cout << moves.size() << endl;
            for(char c : moves) cout << c;
            cout << endl;
            return;
        }

        for(auto &it : neighbors(curr.s)) {
            const string &ns = it.first;
            char mv = it.second;

            ll ng = curr.g + 1;
            if(!gscore.count(ns) || ng < gscore[ns]) {
                gscore[ns] = ng;
                parent[ns] = curr.s;
                move_taken[ns] = mv;
                ll h = distance(ns, goal);
                pq.emplace(ns, ng, h);
            }
        }
    }

    cout << -1 << endl;
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