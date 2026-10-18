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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll N, W;
  cin >> N >> W;

  vll a(N), b(W);
  for (auto &ai : a)
    cin >> ai;
  for (auto &bi : b)
    cin >> bi;

  // Moving a block of walls up and down changes their individual heights.
  // What's kept is the differences between them:
  // (5,2,3)-2 becomes (3,0,1) but the diff remains (-3, 1).
  //
  // So by converting to diffs we eliminate the movement,
  // and this problem becomes simply counting appearances of a subarray.
  //
  // To count subarrays, we'll modify KMP for arrays.

  // b diffs + separator + a diffs
  ll n = (W - 1) + 1 + (N - 1);
  vll s(n);
  for (ll i = 0; i < W - 1; i++)
    s[i] = b[i + 1] - b[i];
  s[W - 1] = LLONG_MAX;
  for (ll i = 0; i < N - 1; i++)
    s[W + i] = a[i + 1] - a[i];

  vll pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }

  ll ans = 0;
  for (ll i = 0; i < n; i++)
    ans += (pi[i] == W - 1);
  cout << ans << '\n';
}
