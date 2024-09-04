#include <iostream>

using namespace std;

struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
};

int maxDepth(TreeNode* root){
  if(root == nullptr){
    return 0;
  }
  //recursion
  int ldepth = maxDepth(root->left);
  int rdepth = maxDepth(root->right);

  return max(ldepth, rdepth) + 1;
}

int main (int argc, char *argv[]) {
  TreeNode root = {3, NULL, NULL};
  TreeNode a = {9, NULL, NULL};
  TreeNode b = {20, NULL, NULL};
  TreeNode c = {15, NULL, NULL};
  TreeNode d = {7, NULL, NULL};
  root.left = &a;
  root.right = &b;
  b.left = &c;
  b.right = &d;

  int depth = maxDepth(&root);
  cout << "max depth: " << depth << endl;

  return 0;
}
