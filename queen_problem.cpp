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


ll R, C;
vector<vector<ll>> board;
bool printed = false;

bool safe(ll r, ll c) {
    for(ll j = 0; j < c; j++)
        if(board[r][j] == 1) return false;

    for(ll i = r, j = c; i >= 0 && j >= 0; i--, j--)
        if(board[i][j] == 1) return false;

    for(ll i = r, j = c; i < R && j >= 0; i++, j--)
        if(board[i][j] == 1) return false;

    return true;
}

void printBoard() {
    for(ll i = 0; i < R; i++) {
        for(ll j = 0; j < C; j++)
            cout << (board[i][j] ? 'Q' : '.') << ' ';
        cout << endl;
    }
    cout << endl;
}

bool solve(ll col) {
    if(col == C) {
        printBoard();
        return true;
    }

    for(ll r = 0; r < R; r++) {
        if(safe(r, col)) {
            board[r][col] = 1;
            if(solve(col + 1)) return true;
            board[r][col] = 0;
        }
    }

    return false;
}

void check() {
    ll r, c; cin >> r >> c;

    R = min(r, c); C = min(r, c);
    board.assign(R, vector<ll>(C, 0));

    if(!solve(0)) {
        cout << "No solution exists" << endl;
    }
    
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