
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
