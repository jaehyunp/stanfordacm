#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;

typedef long long ll;

vector<int> sieve(int PMAX = 10000000) {
  vector<int> primes(1, 2);
  vector<bool> sieveP(PMAX / 2, true);
  for (int i = 1; i < PMAX / 2; ++i) {
    if (!sieveP[i]) continue;
    primes.push_back(2 * i + 1);
    for (int j = 3 * i + 1; j < PMAX / 2; j += 2 * i + 1)
      sieveP[j] = false;
  }
  return primes;
}

tuple<ll, ll, ll> extended_euclid(ll a, ll b) {
  ll s = 0, ss = 1, t = 1, tt = 0, r = b, rr = a, tmp;
  while (r) {
    tmp = ss - (rr / r) * s; ss = s; s = tmp;
    tmp = tt - (rr / r) * t; tt = t; t = tmp;
    tmp = rr % r; rr = r; r = tmp;
  }
  // ss * a + tt * b = rr = gcd(a, g)
  if (a < 0) { ss = -ss; tt = -tt; rr = -rr; }
  return make_tuple(ss, tt, rr);
}

ll mod(ll a, ll N) { a %= N; return a < 0 ? a + N : a; }

ll modmul(ll a, ll b, ll N) {
  a = mod(a, N); b = mod(b, N);
  if (a < b) swap(a, b);
  ll res = 0;
  for (int i = 63 - __builtin_clzll(b); i >= 0; --i) {
    res = (res + res) % N;
    if ((b >> i) & 1) res = (res + a) % N;
  }
  return res;
}

ll modpow(ll b, ll e, ll N) {
  ll res = 1;
  for (int i = 63 - __builtin_clzll(e); i >= 0; --i) {
    res = modmul(res, res, N);
    if ((e >> i) & 1) res = modmul(res, b, N);
  }
  return res;
}

ll mod_inverse(ll a, ll n) {
  ll b, k, g; // ba + kn = gcd(a, n)
  tie(b, k, g) = extended_euclid(a, n);
  if (g != 1) return -1;
  return mod(b, n);
}

pair<ll, ll> chinese_remainder_theorem(ll x, ll a, ll y, ll b) {
  // finds z (mod M) so z = a (mod x) and  z = b (mod y)
  ll s, t, d;
  tie(s, t, d) = extended_euclid(x, y);
  if (a % d != b % d) return make_pair(0, -1);
  ll M = x * y;
  ll z = (modmul(modmul(s, b, M), x, M) + modmul(modmul(t, a, M), y, M)) % M;
  return make_pair(z / d, M / d);
}

bool is_prime(ll N) {
  // deterministic for all <= 2 ^ 64
  static const int p[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
  if (N <= 1) return false;
  for (int i = 0; i < 12; ++i) {
    if (p[i] == N) return true;
    if (N % p[i] == 0) return false;
  }
  ll c = N - 1, g = 0;
  while (!(c & 1)) c >>= 1, ++g;
  for (int i = 0; i < 12; ++i) {
    ll k = modpow(p[i], c, N);
    for (int j = 0; j < g; ++j) {
      ll kk = modmul(k, k, N);
      if (kk == 1 && k != 1 && k != N - 1) return false;
      k = kk;
    }
    if (k != 1) return false;
  }
  return true;
}

mt19937 gen(time(0));
ll pollard_rho(ll N) {
  if (N % 2 == 0) return 2;
  ll xx = uniform_int_distribution<ll>()(gen) % N, x = xx;
  ll c = uniform_int_distribution<ll>()(gen) % N, d = 1;
  for (int iters = 0; iters < 2000; ++iters) {
    x = (modmul(x, x, N) + c) % N;
    xx = (modmul(xx, xx, N) + c) % N;
    xx = (modmul(xx, xx, N) + c) % N;
    d = __gcd(abs(x - xx), N);
    if (d != 1 && d != N) break;
  }
  return d;
}

int main() {
  ll x = 9826348294083898LL;
  while (!is_prime(x)) {
    ll p = pollard_rho(x);
    if (p != 1 && p != x) {
      cout << p << " " << x / p << endl;
      assert(x % p == 0);
      x /= p;
    }
  }
  cout << x << endl;

  // 987654329913580261, 126235313012408852
  // 987654323, 162611810
  // 1000000007, 128761668
  auto ans = chinese_remainder_theorem(
      987654323LL, 162611810LL,
      1000000007LL, 128761668LL);
  cout << ans.first << " " << ans.second << endl;

  // 15, 11
  // 6, 5
  // 10, 1
  ans = chinese_remainder_theorem(6, 5, 10, 1);
  cout << ans.first << " " << ans.second << endl;

  return 0;
}
