#include <cstdint>
#include <iostream>
#include <vector>
const int cByte = 8;
const int cVal = 256;
const uint64_t cMask = 255;
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n = 0;
  std::cin >> n;
  std::vector<uint64_t> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<uint64_t> b(n);
  std::vector<int> count(cVal);
  std::vector<int> prefix_count(cVal);
  for (int byte = 0; byte < cByte; ++byte) {
    for (int i = 0; i < cVal; ++i) {
      count[i] = 0;
      prefix_count[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      int val = static_cast<int>((a[i] >> (byte * cByte)) & cMask);
      ++count[val];
    }
    prefix_count[0] = count[0];
    for (int i = 1; i < cVal; ++i) {
      prefix_count[i] = prefix_count[i - 1] + count[i];
    }
    for (int i = n - 1; i >= 0; --i) {
      int val = static_cast<int>((a[i] >> (byte * cByte)) & cMask);
      --prefix_count[val];
      b[prefix_count[val]] = a[i];
    }
    a.swap(b);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << ' ';
  }
  std::cout << '\n';
  return 0;
}