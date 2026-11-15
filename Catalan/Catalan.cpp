// C[0] = 1
// C[i] = C[i-1] * (4*i - 2) / (i+1)

// C[0..N] in O(n).
// Requires N < 36 for ll.
vll catalan_exact(ll n) {
  vll C(n + 1);
  C[0] = 1;
  FOR(i, 1, n + 1)
  C[i] = (__int128)C[i - 1] * (4 * i - 2) / (i + 1);
  return C;
}

// C[0..N] modulo M in O(n).
// Requires prime M and N < M-1.
const ll M = 1000000007;
vll catalan_mod(ll n) {
  vll inv(n + 2), C(n + 1);
  inv[1] = 1;
  FOR(i, 2, n + 2) inv[i] = M - (M / i) * inv[M % i] % M;

  C[0] = 1;
  FOR(i, 1, n + 1) {
    C[i] = C[i - 1] * (4 * i - 2) % M;
    C[i] = C[i] * inv[i + 1] % M;
  }
  return C;
}
