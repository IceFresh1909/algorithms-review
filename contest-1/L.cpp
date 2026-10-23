#include <iostream>
#include <string>
#include <vector>
bool F(const std::string& a, const std::string& b, const std::vector<int>& ord,
       int del) {
  int sz = a.size();
  int sz_b = b.size();
  int cur_i = 0;
  for (int i = 0; i < sz; ++i) {
    if (ord[i] > del && b[cur_i] == a[i]) {
      ++cur_i;
      if (cur_i == sz_b) {
        return true;
      }
    }
  }
  return false;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::string s;
  std::string t;
  std::cin >> s >> t;
  int n = s.size();
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    p[x - 1] = i + 1;
  }
  int l = -1;
  int r = n;
  while (r - l > 1) {
    int mid = (r + l) / 2;
    if (F(s, t, p, mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  std::cout << l << "\n";
  return 0;
}