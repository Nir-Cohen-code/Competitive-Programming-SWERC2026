
using T = ll /* dp data in each node */;

T E() { return /* unit */; }
T merge(T a, T b) {
  return /* merged values of 2 nodes. must be associative. */;
}
// Add vertex v itself to the aggregate of its included neighbors.
T take_vertex(T dp, ll) { return dp; }
// Turn the DP rooted at a neighbor into a contribution across the edge of
// weight w.
T up_root(T dp, ll w) { return dp + w; }

// Compute ans[v] for every root v of a nonempty weighted tree.
vll reroot(const vector<vpll> &adj) {
  ll n = sz(adj);
  vll p(n, -1), ord{0};
  FOR(i, 0, n) {
    ll v = ord[i];
    for (auto [u, w] : adj[v]) {
      if (u == p[v])
        continue;
      p[u] = v;
      ord.push_back(u);
    }
  }

  vector<T> dp(n, E()), rev(n, E()), ans(n, E());
  for (ll i = n - 1; i >= 0; i--) {
    ll v = ord[i];
    for (auto [u, w] : adj[v]) {
      if (u != p[v])
        dp[v] = merge(dp[v], up_root(dp[u], w));
    }
    dp[v] = take_vertex(dp[v], v);
  }

  for (ll v : ord) {
    ll m = sz(adj[v]);
    vector<T> pref(m + 1, E()), suff(m + 1, E());
    FOR(i, 0, m) {
      auto [u, w] = adj[v][i];
      pref[i + 1] = suff[i] = up_root(u == p[v] ? rev[v] : dp[u], w);
    }
    FOR(i, 0, m) pref[i + 1] = merge(pref[i], pref[i + 1]);
    for (ll i = m - 1; i >= 0; i--)
      suff[i] = merge(suff[i], suff[i + 1]);

    ans[v] = take_vertex(pref[m], v);
    FOR(i, 0, m) {
      ll u = adj[v][i].first;
      if (u != p[v])
        rev[u] = take_vertex(merge(pref[i], suff[i + 1]), v);
    }
  }
  return ans;
}
