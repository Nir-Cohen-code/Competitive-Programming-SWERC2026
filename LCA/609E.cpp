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

vll parent, rank_;

void make_set(int v) {
  parent[v] = v;
  rank_[v] = 0;
}

int find_set(int v) {
  if (v == parent[v])
    return v;
  return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (rank_[a] < rank_[b])
      swap(a, b);
    parent[b] = a;
    if (rank_[a] == rank_[b])
      rank_[a]++;
  }
}

struct Edge {
  ll u, v, weight;
  bool operator<(Edge const &other) { return weight < other.weight; }
};

ll n, l;
vector<vpll> adj;

ll timer;
vll tin, tout;
vvll up, max_up;

void dfs(ll root, ll p) {
  vpll st{{root, p}};
  while (!st.empty()) {
    auto [v, parent] = st.back();
    st.pop_back();
    if (tin[v]) {
      tout[v] = ++timer;
      continue;
    }

    tin[v] = ++timer;
    up[v][0] = parent;
    for (int i = 1; i <= l; ++i) {
      up[v][i] = up[up[v][i - 1]][i - 1];
      max_up[v][i] = max(max_up[v][i - 1], max_up[up[v][i - 1]][i - 1]);
    }

    st.push_back({v, parent});
    for (auto [u, weight] : adj[v]) {
      if (u != parent) {
        max_up[u][0] = weight;
        st.push_back({u, v});
      }
    }
  }
}

bool is_ancestor(ll u, ll v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

ll lca(ll u, ll v) {
  if (is_ancestor(u, v))
    return u;
  if (is_ancestor(v, u))
    return v;
  for (int i = l; i >= 0; --i) {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }
  return up[u][0];
}

ll max_to_ancestor(ll v, ll ancestor) {
  ll answer = 0;
  for (int i = l; i >= 0; --i) {
    if (!is_ancestor(up[v][i], ancestor)) {
      answer = max(answer, max_up[v][i]);
      v = up[v][i];
    }
  }
  if (v != ancestor)
    answer = max(answer, max_up[v][0]);
  return answer;
}

void preprocess(ll root) {
  tin.resize(n + 1);
  tout.resize(n + 1);
  timer = 0;
  l = ceil(log2(n));
  up.assign(n + 1, vll(l + 1));
  max_up.assign(n + 1, vll(l + 1));
  dfs(root, root);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // IDEA
  // We build the MST.
  // To solve for (u, v), we add it to the MST.
  // If we mark z:=lca(u, v), then we have formed a circle u->...->z->...->v->u.
  // We must remove one edge from it.
  // To have the MST, it should be the one with max weight.

  ll m, ui, vi, wi;
  cin >> n >> m;

  vector<Edge> edges;
  FOR(i, 0, m) {
    cin >> ui >> vi >> wi;
    edges.push_back({ui, vi, wi});
  }

  // Build the MST.
  ll cost = 0;
  vector<Edge> mst;
  parent.resize(n + 1);
  rank_.resize(n + 1);
  for (int i = 1; i <= n; i++)
    make_set(i);

  vector<Edge> edges_ = edges;

  sort(all(edges_));

  for (Edge e : edges_) {
    if (find_set(e.u) != find_set(e.v)) {
      cost += e.weight;
      mst.push_back(e);
      union_sets(e.u, e.v);
    }
  }

  // Allow LCA on the MST.
  adj.assign(n + 1, vpll());
  for (Edge e : mst) {
    adj[e.u].push_back({e.v, e.weight});
    adj[e.v].push_back({e.u, e.weight});
  }
  preprocess(1);

  for (Edge e : edges) {
    ll z = lca(e.u, e.v);
    ll maximum = max(max_to_ancestor(e.u, z), max_to_ancestor(e.v, z));
    cout << cost + e.weight - maximum << '\n';
  }
}
