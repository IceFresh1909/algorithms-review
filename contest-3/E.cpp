#include <deque>
#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::deque<int> deql;
  std::deque<int> deqr;
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    char z;
    std::cin >> z;
    if (z == '-') {
      std::cout << deql.front() << '\n';
      deql.pop_front();
    } else if (z == '+') {
      int x;
      std::cin >> x;
      deqr.push_back(x);
    } else {
      int x;
      std::cin >> x;
      deqr.push_front(x);
    }
    if (deql.size() < deqr.size()) {
      deql.push_back(deqr.front());
      deqr.pop_front();
    }
  }
  return 0;
}