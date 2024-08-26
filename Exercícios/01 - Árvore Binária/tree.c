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

void printTabs(int numtabs) {
  for (int i = 0; i < numtabs; i++) {
    printf("\t");
  }
}

void printTree_Rec(node *root, int level) {
  if (root == NULL) {
    printTabs(level);
    printf("--<empty>--\n");
    return;
  }
  printTabs(level);
  printf("data = %d\n", root->data);
  printTabs(level);
  printf("left\n");
  printTree_Rec(root->left, level + 1);
  printTabs(level);
  printf("right\n");
  printTree_Rec(root->right, level +1);
  printTabs(level);
  printf("done\n");
}

void printTree(node* root){
  printTree_Rec(root, 0);
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

bool findNode(node * root, int data){
  if(root == NULL){
    return false;
  }
  if(root->data == data){
    return true;
  }
  if(data < root->data){
    return findNode(root->left, data);
  }
  else{
    return findNode(root->right, data);
  }
}

//TODO: Delete Note

int main(void) {
  node *root = NULL;
  insertNode(&root, 15);
  insertNode(&root, 11);
  insertNode(&root, 24);
  insertNode(&root, 5);
  insertNode(&root, 19);
  insertNode(&root, 16);

  printTree(root);

  printf("%d (%d)\n", 16, findNode(root, 16));
  printf("%d (%d)\n", 15, findNode(root, 15));
  printf("%d (%d)\n", 55, findNode(root, 55));
  printf("%d (%d)\n", 166, findNode(root, 166));
  return 0;
}
