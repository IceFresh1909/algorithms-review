#include <iostream>
#include <vector>

const int cMaxDegree = 21;

struct Node {
  int value;
  int index;
  int degree;
  int heap_index;
  int parent;
  int child;
  int sibling;
};

struct Heap {
  std::vector<int> trees;
  int min_node;

  Heap() : trees(cMaxDegree, -1), min_node(-1) {}
};

struct BinomialHeap {
  std::vector<Node> nodes;
  std::vector<Heap> heaps;
  std::vector<int> position;
  int insert_count = 0;

  void Init(int n, int q) {
    heaps.resize(n + 1);
    position.resize(q + 1, -1);
    nodes.reserve(q);
  }

  bool Less(int first, int second) const {
    if (nodes[first].value != nodes[second].value) {
      return nodes[first].value < nodes[second].value;
    }
    return nodes[first].index < nodes[second].index;
  }

  void SwapData(int first, int second) {
    int value = nodes[first].value;
    nodes[first].value = nodes[second].value;
    nodes[second].value = value;
    int index = nodes[first].index;
    nodes[first].index = nodes[second].index;
    nodes[second].index = index;
    position[nodes[first].index] = first;
    position[nodes[second].index] = second;
  }

  int LinkTrees(int first, int second, int heap_index) {
    if (Less(second, first)) {
      int temp = first;
      first = second;
      second = temp;
    }
    nodes[second].parent = first;
    nodes[second].sibling = nodes[first].child;
    nodes[first].child = second;
    ++nodes[first].degree;
    nodes[first].heap_index = heap_index;
    return first;
  }

  void RecalcMin(int heap_index) {
    heaps[heap_index].min_node = -1;
    for (int degree = 0; degree < cMaxDegree; ++degree) {
      int root = heaps[heap_index].trees[degree];
      if (root == -1) {
        continue;
      }
      if (heaps[heap_index].min_node == -1 ||
          Less(root, heaps[heap_index].min_node)) {
        heaps[heap_index].min_node = root;
      }
    }
  }

  void MergeRoots(int heap_index, int other[]) {
    int carry = -1;
    for (int degree = 0; degree < cMaxDegree; ++degree) {
      int first = heaps[heap_index].trees[degree];
      int second = other[degree];
      int count = 0;
      if (first != -1) {
        ++count;
      }
      if (second != -1) {
        ++count;
      }
      if (carry != -1) {
        ++count;
      }
      heaps[heap_index].trees[degree] = -1;
      other[degree] = -1;
      if (count == 0) {
        continue;
      }
      if (count == 1) {
        if (first != -1) {
          heaps[heap_index].trees[degree] = first;
        } else if (second != -1) {
          heaps[heap_index].trees[degree] = second;
        } else {
          heaps[heap_index].trees[degree] = carry;
          carry = -1;
        }
        int root = heaps[heap_index].trees[degree];
        nodes[root].heap_index = heap_index;
        continue;
      }
      if (count == 2) {
        int tree1;
        int tree2;
        if (first == -1) {
          tree1 = second;
          tree2 = carry;
        } else if (second == -1) {
          tree1 = first;
          tree2 = carry;
        } else {
          tree1 = first;
          tree2 = second;
        }
        carry = LinkTrees(tree1, tree2, heap_index);
        continue;
      }
      heaps[heap_index].trees[degree] = first;
      nodes[first].heap_index = heap_index;
      carry = LinkTrees(second, carry, heap_index);
    }
  }

  void AddTree(int heap_index, int root) {
    while (true) {
      int degree = nodes[root].degree;
      if (heaps[heap_index].trees[degree] == -1) {
        nodes[root].parent = -1;
        nodes[root].sibling = -1;
        nodes[root].heap_index = heap_index;
        heaps[heap_index].trees[degree] = root;
        return;
      }
      int second = heaps[heap_index].trees[degree];
      heaps[heap_index].trees[degree] = -1;
      root = LinkTrees(root, second, heap_index);
    }
  }

  void Insert(int heap_index, int value) {
    ++insert_count;
    Node node;
    node.value = value;
    node.index = insert_count;
    node.degree = 0;
    node.heap_index = heap_index;
    node.parent = -1;
    node.child = -1;
    node.sibling = -1;
    nodes.push_back(node);
    int node_index = static_cast<int>(nodes.size()) - 1;
    position[insert_count] = node_index;
    AddTree(heap_index, node_index);
    if (heaps[heap_index].min_node == -1 ||
        Less(node_index, heaps[heap_index].min_node)) {
      heaps[heap_index].min_node = node_index;
    }
  }

  void Merge(int first_heap, int second_heap) {
    if (first_heap == second_heap) {
      return;
    }
    MergeRoots(second_heap, heaps[first_heap].trees.data());
    heaps[first_heap].min_node = -1;
    RecalcMin(second_heap);
  }

  int GetHeapIndex(int node_index) const {
    while (nodes[node_index].parent != -1) {
      node_index = nodes[node_index].parent;
    }
    return nodes[node_index].heap_index;
  }

  int SiftUp(int node_index) {
    while (nodes[node_index].parent != -1) {
      int parent = nodes[node_index].parent;
      if (!Less(node_index, parent)) {
        break;
      }
      SwapData(node_index, parent);
      node_index = parent;
    }
    return node_index;
  }

  void RemoveRoot(int heap_index, int root) {
    heaps[heap_index].trees[nodes[root].degree] = -1;
    int children[cMaxDegree];
    for (int degree = 0; degree < cMaxDegree; ++degree) {
      children[degree] = -1;
    }
    int child = nodes[root].child;
    while (child != -1) {
      int next = nodes[child].sibling;
      nodes[child].parent = -1;
      nodes[child].sibling = -1;
      nodes[child].heap_index = heap_index;
      children[nodes[child].degree] = child;
      child = next;
    }
    nodes[root].parent = -1;
    nodes[root].child = -1;
    nodes[root].sibling = -1;
    nodes[root].degree = 0;
    MergeRoots(heap_index, children);
    RecalcMin(heap_index);
  }

  int Detach(int index) {
    int node_index = position[index];
    int heap_index = GetHeapIndex(node_index);
    nodes[node_index].value = 0;
    node_index = SiftUp(node_index);
    RemoveRoot(heap_index, node_index);
    return node_index;
  }

  void Erase(int index) {
    Detach(index);
    position[index] = -1;
  }

  void Change(int index, int value) {
    int node_index = position[index];
    int heap_index = GetHeapIndex(node_index);
    node_index = Detach(index);
    nodes[node_index].value = value;
    nodes[node_index].index = index;
    nodes[node_index].degree = 0;
    nodes[node_index].heap_index = heap_index;
    nodes[node_index].parent = -1;
    nodes[node_index].child = -1;
    nodes[node_index].sibling = -1;
    position[index] = node_index;
    AddTree(heap_index, node_index);
    if (heaps[heap_index].min_node == -1 ||
        Less(node_index, heaps[heap_index].min_node)) {
      heaps[heap_index].min_node = node_index;
    }
  }

  int GetMin(int heap_index) const {
    return nodes[heaps[heap_index].min_node].value;
  }

  void ExtractMin(int heap_index) {
    int node_index = heaps[heap_index].min_node;
    int index = nodes[node_index].index;
    RemoveRoot(heap_index, node_index);
    position[index] = -1;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int q;
  std::cin >> n >> q;
  BinomialHeap h;
  h.Init(n, q);
  for (int i = 0; i < q; ++i) {
    int type;
    std::cin >> type;
    if (type == 0) {
      int a;
      int x;
      std::cin >> a >> x;
      h.Insert(a, x);
    } else if (type == 1) {
      int a;
      int b;
      std::cin >> a >> b;
      h.Merge(a, b);
    } else if (type == 2) {
      int index;
      std::cin >> index;
      h.Erase(index);
    } else if (type == 3) {
      int index;
      int x;
      std::cin >> index >> x;
      h.Change(index, x);
    } else if (type == 4) {
      int a;
      std::cin >> a;
      std::cout << h.GetMin(a) << '\n';
    } else {
      int a;
      std::cin >> a;
      h.ExtractMin(a);
    }
  }
  return 0;
}