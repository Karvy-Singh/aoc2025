#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
class Node {
public:
  long low;
  long high;
  Node *left;
  Node *right;
  long height;
  Node(long vall, long valh)
      : low(vall), high(valh), left(nullptr), right(nullptr), height(1) {}
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

bool freshfind(long val, Node *root) {
  if (root == nullptr) {
    return false;
  }

  if (val >= root->low && val <= root->high) {
    // cout << val << endl;
    return true;
  }

  if (val < root->low) {
    return freshfind(val, root->left);
  }
  if (val > root->low) {
    return freshfind(val, root->right);
  }
  return false;
}

void preOrder(Node *root) {
  if (root != nullptr) {
    cout << root->low << " " << root->high << endl;
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main() {
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
  long count = 0;
  ifstream input_file2("ingredients.txt");
  string line2;
  if (input_file.is_open()) {
    while (getline(input_file2, line2)) {
      // cout << line2 << endl;
      if (freshfind(stol(line2), root)) {
        count += 1;
      }
    }
  }
  cout << count << endl;

  preOrder(root);

  return 0;
}
