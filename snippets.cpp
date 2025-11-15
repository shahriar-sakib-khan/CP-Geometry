// graph input
    const int N = 2e5 + 5;
    vector<ll> g[N];
    bitset<N> vis;
    ll n, m;
    cin >> n >> m;
    For(i, 0, m) {
        ll u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    
    void bfs(ll s) {
        queue<ll> q;
        vis[s] = 1;
        q.push(s);
    
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            cout << u << " ";
    
            for (ll v : g[u]) {
                if (vis[v]) continue;
    
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    
    void dfs(ll u) {
        cout << u << " ";
        vis[u] = 1;
        for (ll v : g[u]) {
            if (vis[v]) continue;
            dfs(v);
        }
    }

// vector input
    ll n;
    cin >> n;
    vector<ll> v(n);
    For(i, 0, n) { cin >> v[i]; }