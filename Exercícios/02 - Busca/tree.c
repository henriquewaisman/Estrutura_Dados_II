
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} node;

node *createTree(int data) {
  node *newNode = malloc(sizeof(node));
  if (newNode != NULL) {
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
  }
  return newNode;
}

bool insertNode(node **rootptr, int data){
  node *root = *rootptr;
  if (root == NULL) {
    (*rootptr) = createTree(data);
    return true;
  }
  if (data == root->data) {
    return false;
  }
  if (data < root->data) {
    return insertNode(&(root->left), data);
  } else {
    return insertNode(&(root->right), data);
  }
}

int main(void) {
  node *root = NULL;
  insertNode(&root, 15);
  insertNode(&root, 11);
  insertNode(&root, 24);
  insertNode(&root, 5);
  insertNode(&root, 19);
  insertNode(&root, 16);
  return 0;
}
