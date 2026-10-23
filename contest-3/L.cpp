#include <iostream>
#include <vector>

const int cClearCommand = 6;

struct Element {
  int value;
  int request;
};

struct Heap {
  std::vector<Element> heap_mn;
  std::vector<Element> heap_mx;
  std::vector<int> position_in_mn;
  std::vector<int> position_in_mx;

  void SwapMn(int i, int j) {
    Element temp = heap_mn[i];
    heap_mn[i] = heap_mn[j];
    heap_mn[j] = temp;
    position_in_mn[heap_mn[i].request] = i;
    position_in_mn[heap_mn[j].request] = j;
  }

  void SwapMx(int i, int j) {
    Element temp = heap_mx[i];
    heap_mx[i] = heap_mx[j];
    heap_mx[j] = temp;
    position_in_mx[heap_mx[i].request] = i;
    position_in_mx[heap_mx[j].request] = j;
  }

  void SiftUpMn(int i) {
    while (i > 0) {
      int parent = (i - 1) / 2;
      if (heap_mn[parent].value > heap_mn[i].value) {
        SwapMn(parent, i);
        i = parent;
      } else {
        break;
      }
    }
  }

  void SiftUpMx(int i) {
    while (i > 0) {
      int parent = (i - 1) / 2;
      if (heap_mx[parent].value < heap_mx[i].value) {
        SwapMx(parent, i);
        i = parent;
      } else {
        break;
      }
    }
  }

  void SiftDownMn(int i) {
    while (i * 2 + 1 < static_cast<int>(heap_mn.size())) {
      int child1 = i * 2 + 1;
      int child2 = i * 2 + 2;
      int child = child1;
      if (child2 < static_cast<int>(heap_mn.size()) &&
          heap_mn[child2].value < heap_mn[child1].value) {
        child = child2;
      }
      if (heap_mn[i].value <= heap_mn[child].value) {
        break;
      }
      SwapMn(i, child);
      i = child;
    }
  }

  void SiftDownMx(int i) {
    while (i * 2 + 1 < static_cast<int>(heap_mx.size())) {
      int child1 = i * 2 + 1;
      int child2 = i * 2 + 2;
      int child = child1;
      if (child2 < static_cast<int>(heap_mx.size()) &&
          heap_mx[child2].value > heap_mx[child1].value) {
        child = child2;
      }
      if (heap_mx[i].value >= heap_mx[child].value) {
        break;
      }
      SwapMx(i, child);
      i = child;
    }
  }

  void Insert(int x, int request) {
    heap_mn.push_back({x, request});
    position_in_mn[request] = static_cast<int>(heap_mn.size()) - 1;
    SiftUpMn(position_in_mn[request]);
    heap_mx.push_back({x, request});
    position_in_mx[request] = static_cast<int>(heap_mx.size()) - 1;
    SiftUpMx(position_in_mx[request]);
  }

  int GetMin() const { return heap_mn[0].value; }

  int GetMax() const { return heap_mx[0].value; }

  void RemoveMn(int i) {
    int request = heap_mn[i].request;
    SwapMn(i, static_cast<int>(heap_mn.size()) - 1);
    heap_mn.pop_back();
    position_in_mn[request] = -1;
    if (i >= static_cast<int>(heap_mn.size())) {
      return;
    }
    if (i > 0 && heap_mn[i].value < heap_mn[(i - 1) / 2].value) {
      SiftUpMn(i);
    } else {
      SiftDownMn(i);
    }
  }

  void RemoveMx(int i) {
    int request = heap_mx[i].request;
    SwapMx(i, static_cast<int>(heap_mx.size()) - 1);
    heap_mx.pop_back();
    position_in_mx[request] = -1;
    if (i >= static_cast<int>(heap_mx.size())) {
      return;
    }
    if (i > 0 && heap_mx[i].value > heap_mx[(i - 1) / 2].value) {
      SiftUpMx(i);
    } else {
      SiftDownMx(i);
    }
  }

  int ExtractMin() {
    int value = heap_mn[0].value;
    int request = heap_mn[0].request;
    int index_mx = position_in_mx[request];
    RemoveMn(0);
    RemoveMx(index_mx);
    return value;
  }

  int ExtractMax() {
    int value = heap_mx[0].value;
    int request = heap_mx[0].request;
    int index_mn = position_in_mn[request];
    RemoveMx(0);
    RemoveMn(index_mn);
    return value;
  }

  int Size() const { return static_cast<int>(heap_mn.size()); }

  bool Empty() const { return heap_mn.empty(); }

  void Clear() {
    heap_mn.clear();
    heap_mx.clear();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int q = 0;
  std::cin >> q;
  Heap h;
  h.position_in_mn.resize(q, -1);
  h.position_in_mx.resize(q, -1);
  for (int i = 0; i < q; ++i) {
    int z = 0;
    std::cin >> z;
    if (z == 0) {
      int x = 0;
      std::cin >> x;
      h.Insert(x, i);
      std::cout << "ok\n";
    } else if (z == 1) {
      if (h.Empty()) {
        std::cout << "error\n";
      } else {
        std::cout << h.ExtractMin() << '\n';
      }
    } else if (z == 2) {
      if (h.Empty()) {
        std::cout << "error\n";
      } else {
        std::cout << h.GetMin() << '\n';
      }
    } else if (z == 3) {
      if (h.Empty()) {
        std::cout << "error\n";
      } else {
        std::cout << h.ExtractMax() << '\n';
      }
    } else if (z == 4) {
      if (h.Empty()) {
        std::cout << "error\n";
      } else {
        std::cout << h.GetMax() << '\n';
      }
    } else if (z == 5) {
      std::cout << h.Size() << '\n';
    } else if (z == cClearCommand) {
      h.Clear();
      std::cout << "ok\n";
    }
  }
  return 0;
}