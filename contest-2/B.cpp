#include <iostream>
#include <vector>

const long long c1 = 123;
const long long c2 = 45;
const long long cMod = 10004321;

void Sort(std::vector<long long>& a, int l, int r) {
  for (int i = l + 1; i <= r; ++i) {
    long long x = a[i];
    int j = i;
    while (j > l && a[j - 1] > x) {
      a[j] = a[j - 1];
      --j;
    }
    a[j] = x;
  }
}

long long Select(std::vector<long long>& a, int l, int r, int k) {
  while (l <= r) {
    if (r - l < 5) {
      Sort(a, l, r);
      return a[l + k - 1];
    }
    std::vector<long long> m;
    m.reserve((r - l + 5) / 5);
    for (int i = l; i <= r; i += 5) {
      int j = i + 4;
      if (j > r) {
        j = r;
      }
      Sort(a, i, j);
      m.push_back(a[i + (j - i) / 2]);
    }
    int mk = (static_cast<int>(m.size()) + 1) / 2;
    long long x = Select(m, 0, static_cast<int>(m.size()) - 1, mk);
    int i = l;
    int j = l;
    int p = r;
    while (j <= p) {
      if (a[j] < x) {
        long long t = a[i];
        a[i] = a[j];
        a[j] = t;
        ++i;
        ++j;
      } else if (a[j] > x) {
        long long t = a[j];
        a[j] = a[p];
        a[p] = t;
        --p;
      } else {
        ++j;
      }
    }
    int left = i - l;
    int mid = p - i + 1;
    if (k <= left) {
      r = i - 1;
    } else if (k <= left + mid) {
      return x;
    } else {
      k -= left + mid;
      l = p + 1;
    }
  }
  return 0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n = 0;
  int k = 0;
  long long a0 = 0;
  long long a1 = 0;
  std::cin >> n >> k >> a0 >> a1;
  std::vector<long long> a(n);
  a[0] = a0;
  if (n > 1) {
    a[1] = a1;
  }
  for (int i = 2; i < n; ++i) {
    a[i] = (a[i - 1] * c1 + a[i - 2] * c2) % cMod;
  }
  std::cout << Select(a, 0, n - 1, k) << '\n';
  return 0;
}