#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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

typedef tree<pll, null_type, less<pll>, rb_tree_tag,
             tree_order_statistics_node_update>
    os_tree;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll N, x, y, size = 0;
  cin >> N;

  vll ans(N);
  os_tree t;

  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    size++;
    ans[t.order_of_key({x, size})]++;
    t.insert({x, size});
  }

  for (int i = 0; i < N; i++)
    cout << ans[i] << '\n';
}
