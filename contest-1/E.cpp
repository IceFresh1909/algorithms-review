#include <cmath>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::vector<int> b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int x;
    std::cin >> x;
    int l = -1;
    int r = n - 1;
    while (r - l > 1) {
      int mid = (r + l) / 2;
      if (a[mid] + x >= b[mid]) {
        r = mid;
      } else {
        l = mid;
      }
    }
    if (r == 0 || a[r] + x < b[r - 1]) {
      std::cout << r + 1 << "\n";
    } else {
      std::cout << r << "\n";
    }
  }
  return 0;
}