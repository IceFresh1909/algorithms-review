#include <iostream>
#include <vector>

void MergeSort(std::vector<std::pair<int, int>>& a, int li, int ri) {
  if (ri - li <= 1) {
    return;
  }
  int mid = li + (ri - li) / 2;
  MergeSort(a, li, mid);
  MergeSort(a, mid, ri);
  int i = li;
  int j = mid;
  std::vector<std::pair<int, int>> b;
  while (i < mid && j < ri) {
    if (a[i] < a[j]) {
      b.push_back(a[i]);
      ++i;
    } else {
      b.push_back(a[j]);
      ++j;
    }
  }
  while (i < mid) {
    b.push_back(a[i]);
    ++i;
  }
  while (j < ri) {
    b.push_back(a[j]);
    ++j;
  }
  for (int i = li; i < ri; ++i) {
    a[i] = b[i - li];
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n = 0;
  std::cin >> n;
  std::vector<std::pair<int, int>> a;
  for (int i = 0; i < n; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    a.push_back({l, 0});
    a.push_back({r, 1});
  }
  MergeSort(a, 0, static_cast<int>(a.size()));
  std::vector<std::pair<int, int>> ans;
  int bal = 0;
  int ps = -1;
  for (int i = 0; i < static_cast<int>(a.size()); ++i) {
    if (a[i].second == 0) {
      ++bal;
      if (bal == 1) {
        ps = a[i].first;
      }
    } else {
      --bal;
      if (bal == 0) {
        ans.push_back({ps, a[i].first});
      }
    }
  }
  std::cout << ans.size() << '\n';
  for (const std::pair<int, int>& p : ans) {
    std::cout << p.first << ' ' << p.second << '\n';
  }
  return 0;
}