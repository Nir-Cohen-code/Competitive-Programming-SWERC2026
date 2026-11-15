#include <bits/stdc++.h>
using namespace std;

using vs = vector<string>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vld = vector<ld>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using pld = pair<ld, ld>;
using vpld = vector<pld>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define FOR(i, a, b) for (auto i = (a); i < (b); i++)

using T = ll;

T E() { return 0; }
T merge(T a, T b) { return a + b; }
T take_vertex(T dp, ll) { return dp; }
T up_root(T dp, ll w) { return dp + w; }

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;

  vector<vpll> adj(n);
  FOR(i, 0, n - 1) {
    ll u, v;
    cin >> u >> v;
    --u;
    --v;
    adj[u].push_back({v, 0});
    adj[v].push_back({u, 1});
  }

  vll ans = reroot(adj);
  ll best = *min_element(all(ans));
  cout << best << '\n';
  FOR(v, 0, n) {
    if (ans[v] == best)
      cout << v + 1 << ' ';
  }
  cout << '\n';
  return 0;
}
