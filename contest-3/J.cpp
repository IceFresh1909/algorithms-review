#include <iostream>
#include <string>
#include <vector>

struct Element {
  long long value;
  int request;
};

struct Heap {
  std::vector<Element> heap;
  std::vector<int> position;

  void Swap(int i, int j) {
    Element temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    position[heap[i].request] = i;
    position[heap[j].request] = j;
  }

  void SiftUp(int i) {
    while (i > 0) {
      int parent = (i - 1) / 2;
      if (heap[parent].value > heap[i].value) {
        Swap(parent, i);
        i = parent;
      } else {
        break;
      }
    }
  }

  void SiftDown(int i) {
    while (i * 2 + 1 < static_cast<int>(heap.size())) {
      int child1 = i * 2 + 1;
      int child2 = i * 2 + 2;
      if (child2 < static_cast<int>(heap.size()) &&
          heap[child1].value > heap[child2].value) {
        if (heap[i].value > heap[child2].value) {
          Swap(i, child2);
          i = child2;
        } else {
          break;
        }
      } else {
        if (heap[i].value > heap[child1].value) {
          Swap(i, child1);
          i = child1;
        } else {
          break;
        }
      }
    }
  }

  void Insert(long long x, int request) {
    heap.push_back({x, request});
    position[request] = static_cast<int>(heap.size()) - 1;
    SiftUp(position[request]);
  }

  long long GetMin() { return heap[0].value; }

  void ExtractMin() {
    Swap(0, static_cast<int>(heap.size()) - 1);
    heap.pop_back();
    if (!heap.empty()) {
      SiftDown(0);
    }
  }

  void DecreaseKey(int request, long long delta) {
    heap[position[request]].value -= delta;
    SiftUp(position[request]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int q = 0;
  std::cin >> q;
  Heap h;
  h.position.resize(q);
  for (int i = 0; i < q; ++i) {
    std::string z;
    std::cin >> z;
    if (z == "insert") {
      long long x = 0;
      std::cin >> x;
      h.Insert(x, i);
    } else if (z == "getMin") {
      std::cout << h.GetMin() << '\n';
    } else if (z == "extractMin") {
      h.ExtractMin();
    } else {
      int x = 0;
      long long y = 0;
      std::cin >> x >> y;
      --x;
      h.DecreaseKey(x, y);
    }
  }
  return 0;
}