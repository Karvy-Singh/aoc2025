#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <climits>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
class Node {
public:
  long low;
  long high;
  Node *left;
  Node *right;
  long height;
  int found;
  Node(long vall, long valh)
      : low(vall), high(valh), left(nullptr), right(nullptr), height(1),
        found(0) {}
};

long height(Node *n) {
  if (n == nullptr) {
    return 0;
  }
  return n->height;
}

long balance(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

Node *rightRotate(Node *unbalanced) {
  Node *leftchild = unbalanced->left;
  Node *temp = leftchild->right;

  unbalanced->left = temp;
  leftchild->right = unbalanced;

  unbalanced->height =
      1 + max(height(unbalanced->left), height(unbalanced->right));
  leftchild->height =
      1 + max(height(leftchild->left), height(leftchild->right));

  return leftchild;
}

Node *leftRotate(Node *unbalanced) {
  Node *rightchild = unbalanced->right;
  Node *temp = rightchild->left;

  unbalanced->right = temp;
  rightchild->left = unbalanced;

  unbalanced->height =
      1 + max(height(unbalanced->left), height(unbalanced->right));
  rightchild->height =
      1 + max(height(rightchild->left), height(rightchild->right));

  return rightchild;
}

Node *insert(Node *root, long valuel, long valueh) {

  if (root == nullptr) {
    return new Node(valuel, valueh);
  }

  if (root->low > valuel) {
    root->left = insert(root->left, valuel, valueh);
  } else if (root->low <= valuel) {
    root->right = insert(root->right, valuel, valueh);
  } else {
    return root;
  }

  root->height = 1 + max(height(root->left), height(root->right));
  long bal = balance(root);

  if (bal > 1 && root->left->low > valuel) {
    return rightRotate(root);
  } else if (bal < -1 && root->right->low < valuel) {
    return leftRotate(root);
  } else if (bal > 1 && root->left->low < valuel) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  } else if (bal < -1 && root->right->low > valuel) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

bool overlap(Node *one, Node *two) {
  return (one->low <= two->high && two->low <= one->high);
}

void bfs(Node *root, stack<Node *> &stk, vector<Node *> &allNodes) {
  stack<Node *> tmp;
  tmp.push(root);
  stk.push(root);
  allNodes.push_back(root);
  while (!tmp.empty()) {
    Node *top = tmp.top();
    tmp.pop();
    if (top->left != nullptr) {
      tmp.push(top->left);
      stk.push(top->left);
      allNodes.push_back(top->left);
    }
    if (top->right != nullptr) {
      tmp.push(top->right);
      stk.push(top->right);
      allNodes.push_back(top->right);
    }
  }
}

void findfresh(Node *root) {
  stack<Node *> nodes;
  vector<Node *> allNodes;
  bfs(root, nodes, allNodes);
  long total = 0;
  // cout << nodes.size() << allNodes.size();
  while (!nodes.empty()) {

    Node *node = nodes.top();
    if (node->found != 1) {
      vector<vector<long>> overlaps;

      stack<Node *> comp;
      comp.push(node);
      node->found = 1;

      while (!comp.empty()) {
        Node *cur = comp.top();
        comp.pop();
        overlaps.push_back({cur->low, cur->high});
        for (Node *i : allNodes) {
          if (i->found != 1 && overlap(cur, i)) {
            i->found = 1;
            comp.push(i);
          }
        }
      }
      long min = LONG_MAX;
      long max = LONG_MIN;
      for (const vector<long> &vec : overlaps) {
        if (vec[0] < min) {
          min = vec[0];
        }
        if (vec[1] > max) {
          max = vec[1];
        }
      }
      total += (max - min + 1);
    }
    nodes.pop();
  }
  cout << total;
}

void preOrder(Node *root) {
  if (root != nullptr) {
    cout << root->low << " " << root->high << endl;
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main() {
  unordered_set<long> hash;
  Node *root = nullptr;
  ifstream input_file("inputfile.txt");
  string line;
  if (input_file.is_open()) {
    while (getline(input_file, line)) {
      vector<string> range;
      boost::split(range, line, boost::is_any_of("-"));
      // cout << range[0] << " " << range[1] << endl;
      root = insert(root, stol(range[0]), stol(range[1]));
    }
  }
  findfresh(root);
  // preOrder(root);

  return 0;
}
