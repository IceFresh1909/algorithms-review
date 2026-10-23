#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

const int cPrecision = 10;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  std::vector<double> a(n);
  std::vector<double> lg(n);
  std::vector<double> pr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    lg[i] = std::log(a[i]);
  }
  pr[0] = lg[0];
  for (int i = 1; i < n; ++i) {
    pr[i] = pr[i - 1] + lg[i];
  }
  int q;
  std::cin >> q;
  for (int z = 0; z < q; ++z) {
    int l;
    int r;
    std::cin >> l >> r;
    double ans = pr[r];
    if (l > 0) {
      ans -= pr[l - 1];
    }
    ans = std::exp(ans / (r - l + 1));
    std::cout << std::fixed;
    std::cout.precision(cPrecision);
    std::cout << ans << "\n";
  }
  return 0;
}