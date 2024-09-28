#include <stdio.h>
#include <stdlib.h>
//Definir as cores binárias
#define RED 0
#define BLACK 1

//Criar a estrutura do nó com valor, cor, filhos da esquerda e direita e um pai "rootNode"
typedef struct node {
    int data;
    int color;
    struct node *left;
    struct node *right;
    struct node *rootNode;
} node;

//Cria o nó alocando espaço na memória
node *createNode(int data) {
    node *newNode = malloc(sizeof(struct node));
    if (newNode != NULL) {
        //seta o os filhos e o pai como nulos, a cor como vermelha (por definição) e o dado como o parâmetro
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->rootNode = NULL;
        newNode->color = RED;
    }
    return newNode;
}

//Rotação à esquerda
void leftRotation(node **root, node *x) {
    node *y = x->right; //define um nó "x" com um filho à direita "y"
    x->right = y->left; //o filho à esquerda de y se torna o filho à direita de x
    if (y->left != NULL)
        y->left->rootNode = x;
    y->rootNode = x->rootNode;
    if (x->rootNode == NULL)
        *root = y;
    else if (x == x->rootNode->left)
        x->rootNode->left = y;
    else
        x->rootNode->right = y;
    y->left = x;
    x->rootNode = y;
}

void rightRotation(node **root, node *x) {
    node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->rootNode = x;
    y->rootNode = x->rootNode;
    if (x->rootNode == NULL)
        *root = y;
    else if (x == x->rootNode->right)
        x->rootNode->right = y;
    else
        x->rootNode->left = y;
    y->right = x;
    x->rootNode = y;
}

void correctColor(node **root, node *z) {
    while (z != *root && z->rootNode->color == RED) {
        if (z->rootNode == z->rootNode->rootNode->left) {
            node *y = z->rootNode->rootNode->right;
            if (y != NULL && y->color == RED) {
                z->rootNode->color = BLACK;
                y->color = BLACK;
                z->rootNode->rootNode->color = RED;
                z = z->rootNode->rootNode;
            } else {
                if (z == z->rootNode->right) {
                    z = z->rootNode;
                    leftRotation(root, z);
                }
                z->rootNode->color = BLACK;
                z->rootNode->rootNode->color = RED;
                rightRotation(root, z->rootNode->rootNode);
            }
        } else {
            node *y = z->rootNode->rootNode->left;
            if (y != NULL && y->color == RED) {
                z->rootNode->color = BLACK;
                y->color = BLACK;
                z->rootNode->rootNode->color = RED;
                z = z->rootNode->rootNode;
            } else {
                if (z == z->rootNode->left) {
                    z = z->rootNode;
                    rightRotation(root, z);
                }
                z->rootNode->color = BLACK;
                z->rootNode->rootNode->color = RED;
                leftRotation(root, z->rootNode->rootNode);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertNode(node **root, int data) {
    node *z = createNode(data);
    node *y = NULL;
    node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->rootNode = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    correctColor(root, z);
}

void inOrder(node *root) {
    if (root != NULL) {
        inOrder(root->left);
        if (root->color == 0)
            printf("%d RED\n", root->data);
        else
            printf("%d BLACK\n", root->data);
        inOrder(root->right);
    }
}

void printTree(node *root, int b) {
    if (root != NULL) {
        printTree(root->right, b + 1);
        for (int i = 0; i < b; i++)
            printf("       ");
        if (root->color == 0)
            printf("\033[31m%d\033[0m\n\n", root->data);
        else
            printf("%d\n\n", root->data);
        printTree(root->left, b + 1);
    }
}

int main() {
    struct node *root = NULL;
    int nodes[] = {30, 35, 25, 20, 15, 10, 45};
    int i, tam = sizeof(nodes) / sizeof(nodes[0]);
    for (i = 0; i < tam; i++)
        insertNode(&root, nodes[i]);
    printTree(root, 3);
    printf("\n");
    return 0;
}
