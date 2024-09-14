#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    int height;
} node;

struct node *createNode(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode != NULL) {
      newNode->data = data;
      newNode->left = NULL;
      newNode->right = NULL;
      newNode->height = 0;
    }
    return newNode;
}

int height(struct node *node) {
    if (node == NULL) return -1;
    return node->height;
}

int balanceFactor(struct node *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

struct node *rightRotation(struct node *node) {
    struct node *newRoot = node->left;
    struct node *subTree = newRoot->right;

    newRoot->right = node;
    node->left = subTree;

    if (height(node->left) > height(node->right)) 
        node->height = 1 + height(node->left);
    else 
        node->height = 1 + height(node->right);

    if (height(newRoot->left) > height(newRoot->right)) 
        newRoot->height = 1 + height(newRoot->left);
    else 
        newRoot->height = 1 + height(newRoot->right);

    return newRoot;
}

struct node *leftRotation(struct node *node) {
    struct node *newRoot = node->right;
    struct node *subTree = newRoot->left;

    newRoot->left = node;
    node->right = subTree;

    if (height(node->left) > height(node->right)) 
        node->height = 1 + height(node->left);
    else 
        node->height = 1 + height(node->right);

    if (height(newRoot->left) > height(newRoot->right)) 
        newRoot->height = 1 + height(newRoot->left);
    else 
        newRoot->height = 1 + height(newRoot->right);

    return newRoot;
}

struct node *balance(struct node *root, int data) {
    if (root == NULL) {
        return root;
    }
    if (height(root->left) > height(root->right)) {
        root->height = 1 + height(root->left);
    } else {
        root->height = 1 + height(root->right);
    }

    int balance = balanceFactor(root);

    if (balance > 1 && data < root->left->data) 
        return rightRotation(root);

    if (balance < -1 && data > root->right->data) 
        return leftRotation(root);

    if (balance > 1 && data > root->left->data) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (balance < -1 && data < root->right->data) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

struct node *insertNode(struct node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    } else {
        return root;
    }

    return balance(root, data);
}

struct node *findMin(struct node *node) {
    struct node *currentNode = node;
    while (currentNode && currentNode->left != NULL)
        currentNode = currentNode->left;
    return currentNode;
}

struct node *findMax(struct node *node) {
    if (node == NULL) return NULL;
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

struct node *removeNode(struct node *root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = removeNode(root->left, data);
    } else if (data > root->data) {
        root->right = removeNode(root->right, data);
    } else {
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        if (height(root->left) >= height(root->right)) {
            struct node *temp = findMax(root->left);
            root->data = temp->data;
            root->left = removeNode(root->left, temp->data);
        } else {
            struct node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = removeNode(root->right, temp->data);
        }
    }

    return balance(root, data);
}

int findHeight(struct node *node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = findHeight(node->left) + 1;
    int right_height = findHeight(node->right) + 1;
    if (1 + ((right_height > right_height))) {
        return right_height;
    } else {
        return right_height;
    }
}

node *findNode(struct node *root, int data) {
    if (root == NULL || root->data == data) 
        return root;

    if (data < root->data) 
        return findNode(root->left, data);
    else 
        return findNode(root->right, data);
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
    printTree_Rec(root->right, level + 1);
    printTabs(level);
    printf("done\n");
}

void printTree(node *root) {
    printTree_Rec(root, 0);
}

int main() {
    node *root = NULL;
    root = insertNode(root, 15);
    root = insertNode(root, 11);
    root = insertNode(root, 24);
    root = insertNode(root, 5);
    root = insertNode(root, 19);
    root = insertNode(root, 16);
    printTree(root);
    root = removeNode(root, 15);
    printTree(root);
    return 0;
}
