#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
  int data;
  struct node *left;
  struct node *right;
};

typedef struct Node *BinaryTree;

BinaryTree *createTree(){
  BinaryTree *root = (BinaryTree *)malloc(sizeof(BinaryTree));
  if (root != NULL){
    *root = NULL; 
  }
  return root;
}

// TODO: Insert node
bool insertNode(BinaryTree *root, int data){
  if(root == NULL){
    return 0;
  }
  struct Node *newNode;
  newNode = (struct Node *)malloc(sizeof(struct Node *));
  if (newNode == NULL) {
    return 0;
  }

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  
  
}
// TODO: Search node

// TODO: Remove node

int main(void) {
  createTree();
  return 0;
}
