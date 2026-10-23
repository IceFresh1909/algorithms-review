#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n;
  int q;
  std::cin >> n >> q;
  std::set<std::pair<long long, long long>> by_st;
  std::set<std::pair<long long, long long>> by_sz;
  std::vector<std::pair<long long, long long>> seg(q + 1, {-1, -1});
  by_st.insert({1, n});
  by_sz.insert({-n, 1});
  for (int i = 1; i <= q; ++i) {
    long long k;
    std::cin >> k;
    if (k > 0) {
      if (by_sz.empty()) {
        std::cout << -1 << '\n';
        continue;
      }
      std::pair<long long, long long> t = *by_sz.begin();
      long long len = -t.first;
      long long st = t.second;
      long long fn = st + len - 1;
      if (len < k) {
        std::cout << -1 << '\n';
        continue;
      }
      by_sz.erase(by_sz.begin());
      by_st.erase({st, fn});
      seg[i] = {st, st + k - 1};
      std::cout << st << '\n';
      if (st + k <= fn) {
        long long new_st = st + k;
        long long new_len = fn - new_st + 1;
        by_st.insert({new_st, fn});
        by_sz.insert({-new_len, new_st});
      }
    } else {
      int request = static_cast<int>(-k);
      if (seg[request].first == -1) {
        continue;
      }
      long long st = seg[request].first;
      long long fn = seg[request].second;
      auto it = by_st.lower_bound({st, -1});
      if (it != by_st.begin()) {
        auto left = it;
        --left;
        std::pair<long long, long long> t = *left;
        if (t.second + 1 == st) {
          long long len = t.second - t.first + 1;
          by_sz.erase({-len, t.first});
          by_st.erase(left);
          st = t.first;
        }
      }
      it = by_st.lower_bound({st, -1});
      if (it != by_st.end()) {
        std::pair<long long, long long> t = *it;
        if (t.first == fn + 1) {
          long long len = t.second - t.first + 1;
          by_sz.erase({-len, t.first});
          by_st.erase(it);
          fn = t.second;
        }
      }
      long long len = fn - st + 1;
      by_st.insert({st, fn});
      by_sz.insert({-len, st});
      seg[request] = {-1, -1};
    }
  }
  return 0;
}